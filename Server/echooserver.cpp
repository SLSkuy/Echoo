// written by SL_Skuy
// Echoo服务后端类实现
// 对头文件中声明的各种方法进行实现

#include <QTime>
#include <QJsonDocument>

#include "echooserver.h"
#include "echoouser.h"
#include "logger.h"

EchooServer::EchooServer(QObject *parent)
    : QTcpServer(parent)
    , _sockets(new QMap<QString, QTcpSocket *>)
    , _accounts(new QMap<QString, EchooUser *>)
{
    // 测试使用账号
    // 在线账号
    EchooUser *user1 = new EchooUser("SL_Skuy", "114514", "114514");
    _accounts->insert("114514", user1);
    _sockets->insert("114514", nullptr);
    // 离线账号
    EchooUser *user2 = new EchooUser("SL_Skuy", "0721", "0721");
    _accounts->insert("0721", user2);
}

EchooServer::~EchooServer()
{
    for (auto it = _sockets->begin(); it != _sockets->end(); it++) {
        // 释放socket指针指向的内存空间
        delete it.value();
    }
    for (auto it = _accounts->begin(); it != _accounts->end(); it++) {
        // 释放EchooUser指针指向的内存空间
        delete it.value();
    }
    delete _sockets;
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
        QString userAccountToRemove; // 需要清除的用户的账号

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
            Logger::Log("Account " + userAccountToRemove + " disconnected.");
        }

        // 释放空间
        socket->deleteLater();
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
        RegisterUser(socket, obj);
    } else if (type == "login") {
        // 登录检测
        LoginDetection(socket, obj);
    }
}

void EchooServer::RegisterUser(QTcpSocket *socket, const QJsonObject &content)
{
    QString nickName = content["nickName"].toString();
    QString account = content["account"].toString();
    QString password = content["password"].toString();

    QJsonObject obj; // 客户端返回Json对象
    obj["type"] = "register";
    if (_accounts->contains(account)) {
        // 创建的用户已存在
        // 返回创建失败信息
        QString str = "Account " + account + " has already registered.";
        SendResponse(socket, false, str);

        Logger::Warning("Account " + account + " has already registered.");
        return;
    }

    // 记录用户信息
    EchooUser *newUser = new EchooUser(nickName, account, password);
    _accounts->insert(account, newUser);

    // 返回成功注册成功信息
    QString str = account + " register successfully, please log in.";
    SendResponse(socket, true, str);
    Logger::Log("Account " + account + " register successfully.");
}

void EchooServer::LoginDetection(QTcpSocket *socket, const QJsonObject &content)
{
    QString account = content["account"].toString();
    QString password = content["password"].toString();

    QJsonObject obj;
    obj["type"] = "login";
    if (!_accounts->contains(account)) {
        // 不存在对应账号的用户
        QString str = "Account " + account + " is not exist, please register or check input account.";
        SendResponse(socket, false, str);

        Logger::Warning("No such account " + account + " exist.");
        return;
    }

    if (!(*_accounts)[account]->PasswordDetection(password)) {
        // 密码错误
        QString str = "Error password.";
        SendResponse(socket, false, str);

        Logger::Warning("error password");
        return;
    }

    if (_sockets->contains(account)) {
        // 当前账号已经登录
        QString str = "Account " + account + " has logged in, please don't log again.";
        SendResponse(socket, false, str);

        Logger::Warning("Account " + account + " has logged in.");
        return;
    }

    _sockets->insert(account, socket); // 记录账号在线
    QString str = "login successfully.";
    SendResponse(socket, true, str);
    Logger::Log("Account " + account + " login successfully.");
}
