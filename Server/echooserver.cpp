// written by SL_Skuy
// Echoo服务后端类实现
// 对头文件中声明的各种方法进行实现

#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>

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
    connect(socket, &QTcpSocket::readyRead, this, [socket, this]() {
        QByteArray data = socket->readAll(); // 读取字节序列
        this->ProcessMessage(socket, data);
    });

    // socket断开连接时处理用户在服务器中残留的信息
    connect(socket, &QTcpSocket::disconnected, this, [socket, this]() {
        QString userAccountToRemove; // 需要清除的用户的账号

        qDebug().noquote() << ServerInfo(0) + " User on " + socket->localAddress().toString() + ":"
                                  + socket->localPort() + " disconnected.";

        // 获取账号
        for (auto it = this->_sockets->begin(); it != this->_sockets->end(); it++) {
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
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err); // 捕获JSON字节流并反序列化
    if (err.error != QJsonParseError::NoError) {
        qDebug() << "Invalid JSON received";
        return;
    }

    QJsonObject obj = doc.object(); // 转换为JSON结构对象
    QString type = obj["type"].toString();

    if (type == "text") {
        qDebug() << obj["content"].toString();
        SendResponse(socket);
    }
}

void EchooServer::SendResponse(QTcpSocket *socket)
{
    QJsonObject obj; // 构建JSON的具体内容
    obj["type"] = "text";
    obj["content"] = "response";

    QJsonDocument doc(obj);      // 构建JSON内容的文档容器，容纳具体的JSON内容
    socket->write(doc.toJson()); // 序列化JSON数据进行传输
}
