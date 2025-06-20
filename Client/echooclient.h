#pragma once

#include <QQmlListProperty>
#include <QTcpSocket>
#include <QDateTime>
#include <QList>

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
    Q_INVOKABLE void AddFriend(const QString &account);
    Q_INVOKABLE QVariantList GetNetizenList();
    Q_INVOKABLE QVariantList GetMessageList(const QString &account);
    Q_INVOKABLE Netizen *GetThisInfo() { return _user; };

    // 消息功能
    Q_INVOKABLE void SendMessage(const QString &receiverAccount, const QString &content)
    {
        emit triggerMessage(receiverAccount, content);
    }
    Q_INVOKABLE void SendGroupMessage(const QString &groupAccount, const QString &content)
    {
        emit triggerGroupMessage(groupAccount, content);
    }

signals:
    // 消息发送信号
    void triggerMessage(QString receiverAccount, QString content);
    void triggerGroupMessage(QString groupAccount, QString content);
    // 账号处理信号
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    // 消息接收信号
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);

private:
    Netizen *_user;
};
