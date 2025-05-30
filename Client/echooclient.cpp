#include "echooclient.h"

EchooClient::EchooClient(QObject* parent) : QObject(parent), _socket(new QTcpSocket)
{
    connect(_socket, &QTcpSocket::connected, this, &EchooClient::onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &EchooClient::onDisconnected);

    _socket->connectToHost("127.0.0.1", 8080);
}

void EchooClient::onConnected()
{
    qDebug() << "Server connected";
    _socket->write(QString("Client").toUtf8());
}

void EchooClient::onDisconnected()
{
    qDebug() << "Disconnected";
}

EchooClient::~EchooClient()
{
    delete _socket;
}
