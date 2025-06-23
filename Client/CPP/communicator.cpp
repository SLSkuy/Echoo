// Communicator类实现
// 该类用于实现局域网网络通信
// 使用UDP广播发现消息
// TCP连接进行消息传输

#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QNetworkInterface>

#include "communicator.h"
#include "databasemanager.h"
#include "message.h"
#include "logger.h"

Communicator::Communicator(Netizen *netizen) : _netizen(netizen), QObject(netizen)
{
    m_udpPort = 1145;
    m_tcpPort = 1145;

    _udpSocket = new QUdpSocket(this);
    _udpSocket->bind(QHostAddress::AnyIPv4, m_udpPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(_udpSocket, &QUdpSocket::readyRead, this, &Communicator::OnUdpReadyRead);

    _tcpServer = new QTcpServer(this);
    _tcpServer->listen(QHostAddress::AnyIPv4, m_tcpPort);
    connect(_tcpServer, &QTcpServer::newConnection, this, &Communicator::OnNewTcpConnection);
}

Communicator::~Communicator()
{
    // 发送离线消息
    QJsonObject response;
    response["nickName"] = _netizen->GetNickname();
    response["account"] = _netizen->GetAccount();
    response["online"] = false;
    response["ip"] = _netizen->GetIpAddress();
    response["avatar"] = _netizen->getAvatar();
    response["sign"] = _netizen->GetSign();
    BroadcastPresence(response);

    _udpSocket->deleteLater();
    _tcpServer->deleteLater();
}

QString Communicator::GetLocalIP()
{
    // 返回本机IP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
            return address.toString();
        }
    }
    return QHostAddress(QHostAddress::LocalHost).toString();
}

void Communicator::BroadcastPresence(QJsonObject &obj)
{
    // 广播消息
    QJsonDocument doc(obj);
    _udpSocket->writeDatagram(doc.toJson(), QHostAddress::Broadcast, m_udpPort);
}

void Communicator::OnUdpReadyRead()
{
    // 处理收到的广播消息
    // 读取连接队列中所有的Socket
    while (_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(_udpSocket->pendingDatagramSize()));
        QHostAddress senderAddr;
        quint16 senderPort;
        _udpSocket->readDatagram(datagram.data(), datagram.size(), &senderAddr, &senderPort);

        // 转换为Json文档便于后续处理
        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        if(!doc.isNull() && doc.isObject())
        {
            // 读取json内容
            QJsonObject obj = doc.object();
            bool online = obj["online"].toBool();

            // 检测为离线操作还是在线操作
            if (online) {
                OnlineProcess(obj);
            } else {
                OfflineProcess(obj);
            }
        }
    }
}

void Communicator::OnNewTcpConnection()
{
    // 读取连接队列中所有的Socket
    while (_tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = _tcpServer->nextPendingConnection();
        // 连接信号
        connect(socket, &QTcpSocket::readyRead, this, [socket, this]() { OnlineMessageProcess(socket); });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
}

void Communicator::OnlineMessageProcess(QTcpSocket *socket)
{
    m_buffers[socket].append(socket->readAll());

    while (true) {
        // 检查是否能读出完整长度前缀（4字节）
        if (m_buffers[socket].size() < 4) return;

        QDataStream stream(m_buffers[socket]);
        stream.setByteOrder(QDataStream::BigEndian);
        quint32 length;
        stream >> length;

        if (m_buffers[socket].size() - 4 < length) return; // 不够完整包，等下次再读

        QByteArray jsonData = m_buffers[socket].mid(4, length);
        m_buffers[socket].remove(0, 4 + length);

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (!doc.isNull() && doc.isObject()) {
            Message *message = Message::FromJson(jsonData);
            QString type = doc["message_type"].toString();

            // 保存消息，接受的消息的sender即是此客户端的receiver
            QString sender = message->GetSender()->GetAccount();
            DatabaseManager::instance()->AddMessage(sender, message);
            if (type == "individual") {
                emit messageReceived(message);
            } else if (type == "group") {
                Group *group = qobject_cast<Group *>(message->GetReceiver());
                emit groupMessageReceived(group, message);
            } else if (type == "command") {
                emit commandReceived(message);
            } else if (type == "image") {
                emit imageReceived(message);
            }
        }
    }
}

void Communicator::OfflineMessageProcess(Netizen *user)
{
    // 获取所有离线消息
    QList<Message *> offlines = DatabaseManager::instance()->GetOfflineMessages();
    QList<Message *> toRemove; // 记录已经发送的离线消息
    for (QList<Message *>::iterator it = offlines.begin(); it != offlines.end(); ++it) {
        if (auto receiver = qobject_cast<Netizen *>((*it)->GetReceiver())) {
            if (receiver == user) {
                qDebug() << "Sending offline message to user:" << user->GetAccount()
                         << "content:" << (*it)->GetMessage();
                SendMessage(*it);
                toRemove.append(*it);
            }
        }
    }
    for (QList<Message *>::iterator it = toRemove.begin(); it != toRemove.end(); ++it) {
        if ((*it)->GetReceiver() == user) {
            offlines.removeOne(*it); // 删除已经发送的离线消息
        }
    }
    // 更新离线消息
    DatabaseManager::instance()->UpdateOfflineMessages(offlines);
}

void Communicator::OnlineProcess(QJsonObject &obj)
{
    QString nickName = obj["nickName"].toString();
    QString account = obj["account"].toString();
    QString ip = obj["ip"].toString();
    QString avatar = obj["avatar"].toString();
    QString sign = obj["sign"].toString();
    // 检测当前设备本地数据库是否存在广播者信息
    DatabaseManager *db = DatabaseManager::instance();
    if (db->Contains(account)) {
        // 存在该用户
        if (!db->GetNetizen(account)->IsOnline()) {
            // 检测用户是否在线，若为否则标志为在线，并告诉对方自己也在线
            Netizen *user = db->GetNetizen(account);
            user->SetOnline(true);
            user->SetIpAddress(ip);
            user->updateAvatar(avatar);
            user->SetSign(sign);

            ConnectProcess(account, ip);

            // 处理有关对应用户的离线消息
            OfflineMessageProcess(db->GetNetizen(account));
            Logger::Log(account + " online.");
        }
    } else {
        // 不存在该用户，则添加
        Netizen *newUser = new Netizen(nickName, account, NULL, nullptr);
        newUser->SetIpAddress(ip);
        newUser->SetOnline(true);
        newUser->updateAvatar(avatar);
        db->AddNetizen(newUser);

        ConnectProcess(account, ip);
        Logger::Log(account + " online.");
    }
}

void Communicator::OfflineProcess(QJsonObject &obj)
{
    // 处理其他客户端传来的离线消息
    QString account = obj["account"].toString();
    if (DatabaseManager::instance()->Contains(account)) {
        auto netizen = DatabaseManager::instance()->GetNetizen(account);
        if (netizen->IsOnline()) {
            netizen->SetOnline(false);

            // 删除socket连接
            m_buffers.remove(m_sockets[account]);
            m_sockets[account]->deleteLater();
            m_sockets.remove(account);
            Logger::Log(account + " went offline.");
        }
    }
}

void Communicator::ConnectProcess(const QString &account, const QString &ip)
{
    // 建立TCP连接
    if (!m_sockets.contains(account)) {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(ip, m_tcpPort);
        connect(socket, &QTcpSocket::connected, this, [this, account]() {
            // 测试信息
            Logger::Log("Connected to " + account);
        });
        connect(socket, &QTcpSocket::disconnected, this, [this, account]() {
            // 测试信息
            m_sockets.remove(account);
            Logger::Log("Disconnected from " + account);
        });

        // 记录TcpSocket在线
        m_sockets[account] = socket;
    }

    // 广播回应自己也在线，以此确保双向连接
    QJsonObject response;
    response["nickName"] = _netizen->GetNickname();
    response["account"] = _netizen->GetAccount();
    response["online"] = true;
    response["ip"] = _netizen->GetIpAddress();
    response["avatar"] = _netizen->getAvatar();
    response["sign"] = _netizen->GetSign();
    BroadcastPresence(response);
}

void Communicator::SendMessage(Message *message)
{
    QString receiverAccount = qobject_cast<Netizen *>(message->GetReceiver())->GetAccount();
    if (m_sockets.contains(receiverAccount)) {
        QTcpSocket *socket = m_sockets[receiverAccount];
        QByteArray json = message->ToJson();
        QByteArray packet;
        QDataStream stream(&packet, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::BigEndian);
        stream << (quint32) json.size(); // 写入4字节长度前缀，解决粘包问题
        packet.append(json);

        socket->write(packet);
        DatabaseManager::instance()->AddMessage(receiverAccount, message);
    } else {
        DatabaseManager::instance()->AddOfflineMessage(message);
    }
}

void Communicator::SendGroupMessage(Message *message) {}
