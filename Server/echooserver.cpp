// written by SL_Skuy
// Echoo服务后端类实现
// 对头文件中声明的各种方法进行实现

#include <QDebug>
#include <QTime>

#include "echooserver.h"

EchooServer::EchooServer(QObject *parent)
    : QTcpServer(parent)
    , _sockets(new QMap<QString, QTcpSocket *>)
    , _accounts(new QMap<QString, QString>)
{

}

EchooServer::~EchooServer()
{
    delete _sockets;
    delete _accounts;
}

QString EchooServer::ServerInfo(int type)
{
    QString prefix = (type == 1) ? "[ERROR" : "[INFO";
    return prefix + " " + QTime::currentTime().toString("HH:mm:ss") + "]";
}

bool EchooServer::StartServer(const QHostAddress &address, quint16 port)
{
    qDebug().noquote() << ServerInfo(0) + " Server is starting...";

    if (!this->listen(address, port))
    {
        qDebug().noquote() << ServerInfo(1) + " Server start failed: " + this->errorString();
        qDebug().noquote() << ServerInfo(1) + " Server will exit later.";
        return false;
    }

    qDebug().noquote() << ServerInfo(0) + " Server listening on port:" << QString::number(port);
    return true;
}

void EchooServer::incomingConnection(qintptr socketDescriptor)
{
    // 捕获客户端socket
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    // 从能够读取的socket中读取二进制信息
    connect(socket,&QTcpSocket::readyRead,this,[socket,this](){
        QByteArray data = socket->readAll();
        this->ProcessMessage(socket, data);
    });

    // socket断开连接时处理用户在服务器中残留的信息
    connect(socket,&QTcpSocket::disconnected,this,[socket,this](){
        QString userAccountToRemove;   // 需要清除的用户的账号

         // 获取账号
        for(auto it = this->_sockets->begin();it != this->_sockets->end();it++)
        {
            if(it.value() == socket)
            {
                userAccountToRemove = it.key();
                break;
            }
        }

        if(!userAccountToRemove.isEmpty())
        {
            this->_sockets->remove(userAccountToRemove);
            qDebug() << "Account " + userAccountToRemove + " disconnected.\n";
        }

        // 释放空间
        socket->deleteLater();
    });
}

void EchooServer::ProcessMessage(QTcpSocket *socket, const QByteArray &data)
{
    qDebug() << QString::fromUtf8(data);
}

void EchooServer::SendResponse(QTcpSocket *socket)
{
    socket->write("response");
}
