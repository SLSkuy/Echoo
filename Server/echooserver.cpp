// written by SL_Skuy
// Echoo 服务器主程序
// 调用各个子模块实现多种功能

#include <QTime>
#include <QTcpSocket>

#include "echooserver.h"
#include "logger.h"

EchooServer::EchooServer(QObject *parent)
    : QTcpServer(parent)
    , _am(new AccountManager)
    , _gm(new GroupManager)
    , _msgManager(new MessageManager(_am, _gm))
{}

EchooServer::~EchooServer()
{
    delete _am;
    delete _gm;
    delete _msgManager;
}

bool EchooServer::StartServer(const QHostAddress &address, quint16 port)
{
    Logger::Log("Server is starting...");

    if (!this->listen(address, port))
    {
        Logger::Error("Server start failed: " + this->errorString());
        Logger::Error("Server will exit later.");
        return false;
    }

    Logger::Log("Server listening on port: " + QString::number(port));
    return true;
}

void EchooServer::incomingConnection(qintptr socketDescriptor)
{
    // 捕获客户端socket
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    // 从能够读取的socket中读取二进制信息
    connect(socket, &QTcpSocket::readyRead, this, [socket, this]() {
        QByteArray data = socket->readAll(); // 读取字节序列
        _msgManager->ProcessMessage(socket, data);
    });

    // socket断开连接时处理用户在服务器中残留的信息
    connect(socket, &QTcpSocket::disconnected, this, [socket, this]() {
        // 调用AccountManager进行账号离线操作
        _am->ExitConnection(socket);
    });
}
