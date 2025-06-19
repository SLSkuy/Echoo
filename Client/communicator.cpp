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
    BroadcastPresence(response);

    _udpSocket->deleteLater();
    _tcpServer->deleteLater();
}

QString Communicator::GetLocalIP()
{
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
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            // 处理接收到的消息
            QByteArray data = socket->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);

            // 反序列化获取Message对象
            Message *message = Message::FromJson(data);
            if (!doc.isNull() && doc.isObject()) {
                QJsonObject obj = doc.object();
                QString type = obj["message_type"].toString();

                Logger::Log("Receiver message form " + message->GetSender()->GetAccount() + ": "
                            + message->GetMessage());

                //判断消息类型
                if (type == "individual") {
                    emit messageReceived(message);
                } else if (type == "group") {
                    Group *group = qobject_cast<class Group *>(message->GetReceiver());
                    emit groupMessageReceived(group, message);
                }
            }
        });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
}

void Communicator::OnlineProcess(QJsonObject &obj)
{
    QString nickName = obj["nickName"].toString();
    QString account = obj["account"].toString();
    QString ip = obj["ip"].toString();
    // 检测当前设备本地数据库是否存在广播者信息
    DatabaseManager *db = DatabaseManager::instance();
    if (db->Contains(account)) {
        // 存在该用户
        if (!db->GetNetizen(account)->IsOnline()) {
            // 检测用户是否在线，若为否则标志为在线，并告诉对方自己也在线
            db->GetNetizen(account)->SetOnline(true);

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
                m_sockets[account] = socket;
            }

            // 回应广播自己在线
            QJsonObject response;
            response["nickName"] = _netizen->GetNickname();
            response["account"] = _netizen->GetAccount();
            response["online"] = true;
            response["ip"] = _netizen->GetIpAddress();
            BroadcastPresence(response);

            Logger::Log(account + " online.");
        }
    } else {
        // 不存在该用户，则添加
        Netizen *newUser = new Netizen(nickName, account, NULL, nullptr);
        newUser->SetOnline(true);
        db->AddNetizen(newUser);

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
            m_sockets[account] = socket;
        }

        // 广播回应自己也在线，以此确保双方都确定对方在线
        QJsonObject response;
        response["nickName"] = _netizen->GetNickname();
        response["account"] = _netizen->GetAccount();
        response["online"] = true;
        response["ip"] = _netizen->GetIpAddress();
        BroadcastPresence(response);

        Logger::Log(account + " online.");
    }
}

void Communicator::OfflineProcess(QJsonObject &obj)
{
    QString account = obj["account"].toString();
    if (DatabaseManager::instance()->Contains(account)) {
        auto netizen = DatabaseManager::instance()->GetNetizen(account);
        if (netizen->IsOnline()) {
            netizen->SetOnline(false);
            Logger::Log(account + " went offline.");
        }
    }
}

void Communicator::SendMessage(Message *message)
{
    QString receiverAccount = qobject_cast<Netizen *>(message->GetReceiver())->GetAccount();
    if (m_sockets.contains(receiverAccount)) {
        // 如果已有连接，直接发送
        QTcpSocket *socket = m_sockets[receiverAccount];
        socket->write(message->ToJson());
    } else {
        // 建立新连接
        QTcpSocket *socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::connected, this, [socket, message]() { socket->write(message->ToJson()); });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

        // 从数据库获取接收者的IP地址（这里需要你的数据库支持存储IP）
        QString ip = DatabaseManager::instance()->GetNetizen(receiverAccount)->GetIpAddress();
        socket->connectToHost(ip, m_tcpPort);

        // 添加到连接映射
        m_sockets[receiverAccount] = socket;
    }
}

void Communicator::SendGroupMessage(Message *message) {}
