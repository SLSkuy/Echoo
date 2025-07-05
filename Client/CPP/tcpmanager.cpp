#include "tcpmanager.h"
#include "databasemanager.h"
#include "logger.h"

TcpManager::TcpManager(QObject *parent): QObject(parent)
{
    _tcpServer = new QTcpServer(this);
    _tcpServer->listen(QHostAddress::AnyIPv4,m_tcpPort);
    connect(_tcpServer, &QTcpServer::newConnection, this, &TcpManager::onNewConnection);
}

TcpManager::~TcpManager()
{
    _tcpServer->deleteLater();
    for(auto it = m_sockets.begin();it != m_sockets.end();it++)
    {
        it.value()->deleteLater();
    }
}

QTcpSocket *TcpManager::getSocket(const QString &account)
{
    return m_sockets.contains(account) ? m_sockets[account] : nullptr;
}

void TcpManager::onNewConnection()
{
    // 读取连接队列中所有的Socket
    while (_tcpServer->hasPendingConnections()) {
        QTcpSocket *socket = _tcpServer->nextPendingConnection();

        // 连接信号
        connect(socket, &QTcpSocket::readyRead, this,[socket, this]() { byteArrayProcess(socket); });
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
}

void TcpManager::byteArrayProcess(QTcpSocket *socket)
{
    m_buffers[socket].append(socket->readAll());

    while (true) {
        // 检查是否能读出完整长度前缀
        if (m_buffers[socket].size() < 4) return;

        QDataStream stream(m_buffers[socket]);
        stream.setByteOrder(QDataStream::BigEndian);
        quint32 length;
        stream >> length;

        // 不完整的包，等待数据完整
        if (m_buffers[socket].size() - 4 < length) return;

        QByteArray jsonData = m_buffers[socket].mid(4, length);
        m_buffers[socket].remove(0, 4 + length);

        // 触发信号供消息处理器接收处理
        emit messageReceived(socket,jsonData);
    }
}

void TcpManager::onlineProcess(const QJsonObject &obj)
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
            user->SetNickname(nickName);
            user->updateAvatar(avatar);
            user->SetSign(sign);

            // 在线处理
            connectProcess(account, ip);

            // 发送信号处理对方离线时发送给对方的消息
            emit offlineMessageProcess(db->GetNetizen(account));
            Logger::Log(account + " online.");
        }
    } else {
        // 不存在该用户，则添加
        Netizen *newUser = new Netizen(nickName, account, NULL, nullptr);
        newUser->SetIpAddress(ip);
        newUser->SetOnline(true);
        newUser->updateAvatar(avatar);
        db->AddNetizen(newUser);

        // 在线处理
        connectProcess(account, ip);
        Logger::Log(account + " online.");
    }
}

void TcpManager::offlineProcess(const QJsonObject &obj)
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

void TcpManager::connectProcess(const QString &account, const QString &ip)
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
}
