#pragma once

#include <QTcpSocket>

class DatabaseManager;
class Communicator;
class Message;
class Netizen;
class Group;

class EchooClient : public QObject
{
    Q_OBJECT
public:
    explicit EchooClient(QObject *parent = nullptr);
    ~EchooClient();

    // 账号功能
    Q_INVOKABLE void Login(const QString &account, const QString &password); // 暴露给qml使用
    Q_INVOKABLE void Register(const QString &nickName, const QString &account, const QString &password);

    // 消息功能
    Q_INVOKABLE void SendMessage(Message *msg);
    Q_INVOKABLE void SendGroupMessage(Message *msg, Group *group);

signals:
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);

private:
    Netizen *_user;
    Communicator *_cmc;
    DatabaseManager *_dm;

    // 初始化相关
    void InitCommunicator();
};
