// written by SL_Skuy
// Echoo 服务器主程序
// 调用各个子模块实现多种功能

#include <QTime>
#include <QJsonDocument>

#include "echooserver.h"
#include "logger.h"

EchooServer::EchooServer(QObject *parent)
    : QTcpServer(parent)
    , _accounts(new AccountManager)
{}

EchooServer::~EchooServer()
{
    delete _accounts;
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
        this->ProcessMessage(socket, data);
    });

    // socket断开连接时处理用户在服务器中残留的信息
    connect(socket, &QTcpSocket::disconnected, this, [socket, this]() {
        // 调用AccountManager进行账号离线操作
        _accounts->ExitConnection(socket);
    });
}

void EchooServer::SendResponse(QTcpSocket *socket, bool result, QString &content)
{
    QJsonObject obj;
    obj["success"] = result;
    obj["content"] = content;

    QJsonDocument doc(obj);      // 构建JSON内容的文档容器，容纳具体的JSON内容
    socket->write(doc.toJson()); // 序列化JSON数据进行传输
}

void EchooServer::ProcessMessage(QTcpSocket *socket, const QByteArray &data)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err); // 捕获JSON字节流并反序列化
    if (err.error != QJsonParseError::NoError) {
        Logger::Error("Invalid JSON received");
        return;
    }

    QJsonObject obj = doc.object(); // 转换为JSON结构对象
    QString type = obj["type"].toString();

    if (type == "text") {
        // 测试收取信息
        qDebug() << obj["content"].toString();
    } else if (type == "register") {
        // 用户注册
        _accounts->RegisterUser(socket, obj);
    } else if (type == "login") {
        // 登录检测
        _accounts->LoginDetection(socket, obj);
    } else if (type == "privateMsg") {
        // 消息转发
        PrivateMessageForwarding(socket, obj);
    }
}

void EchooServer::PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content)
{
    // 获取信息发送对象
    QString to = content["to"].toString();

    QJsonDocument doc(content);
    QTcpSocket *receiver = _accounts->GetSocket(to);

    if(receiver != nullptr)
    {
        receiver->write(doc.toJson());
    }

    QString response = "The user does not exist or is not online.";
    SendResponse(socket,false,response);
}
