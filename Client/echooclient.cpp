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

EchooClient::~EchooClient()
{
    delete _socket;
}

void EchooClient::onConnected()
{
    // 与服务端构建连接时触发
    qDebug() << "Server connected";
}

void EchooClient::onDisconnected()
{
    // 与服务端断开连接时触发
    qDebug() << "Disconnected";
}

void EchooClient::onReadyRead()
{
    QByteArray data = _socket->readAll();
    QJsonParseError err;

    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    QJsonObject obj = doc.object();

    // 获取到服务端发送来的消息时触发
    qDebug() << "Receive message form server: " + obj["content"].toString();
    QString type = obj["type"].toString();
    bool result = obj["success"].toBool();

    if (type == "login") {
        emit loginSuccess(result);
    } else if (type == "register") {
        emit registerSuccess(result);
    } else if (type == "privateMsg") {
        emit receiveMsg(obj["content"].toString());
    }
}

void EchooClient::Login(QString account, QString password)
{
    QJsonObject obj;
    obj["type"] = "login";
    obj["account"] = account;
    obj["password"] = password;

    QJsonDocument doc(obj);
    _socket->write(doc.toJson());
}

void EchooClient::Register(QString nickName, QString account, QString password)
{
    QJsonObject obj;
    obj["type"] = "register";
    obj["nickName"] = nickName;
    obj["account"] = account;
    obj["password"] = password;

    QJsonDocument doc(obj);
    _socket->write(doc.toJson());
}

void EchooClient::SendPrivateMessage(QString content, QString toAccount)
{
    QJsonObject obj;
    obj["type"] = "privateMsg";
    obj["from"] = this->m_account;
    obj["to"] = toAccount;
    obj["content"] = content;

    QJsonDocument doc(obj);
    _socket->write(doc.toJson());
}
