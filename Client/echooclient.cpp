#include <QJsonDocument>
#include <QJsonObject>

#include "echooclient.h"

EchooClient::EchooClient(QObject* parent) : QObject(parent), _socket(new QTcpSocket)
{
    connect(_socket, &QTcpSocket::connected, this, &EchooClient::onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &EchooClient::onDisconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &EchooClient::onReadyRead);

    _socket->connectToHost("127.0.0.1", 8080);
}

void EchooClient::onConnected()
{
    // 与服务端构建连接时触发
    qDebug() << "Server connected";

    QJsonObject obj;
    obj["type"] = "text";
    obj["content"] = "Client connected";

    QJsonDocument doc(obj);

    _socket->write(doc.toJson());
}

void EchooClient::onReadyRead()
{
    // 获取到服务端发送来的消息时触发
    QByteArray data = _socket->readAll();
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    QJsonObject obj = doc.object();

    qDebug() << obj["content"].toString();
}

void EchooClient::onDisconnected()
{
    // 与服务端断开连接时触发
    qDebug() << "Disconnected";
}

EchooClient::~EchooClient()
{
    delete _socket;
}
