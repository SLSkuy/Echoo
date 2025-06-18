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
    Q_INVOKABLE bool Login(QString account, QString password); // 暴露给qml使用
    Q_INVOKABLE bool Register(QString nickName, QString account, QString password);
    Q_INVOKABLE void SendMessage(Message *msg);
    Q_INVOKABLE void SendGroupMessage(Message *msg, Group *group);

signals:
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    Netizen *_user;
    Communicator *_cmc;
    DatabaseManager *_dm;
};
