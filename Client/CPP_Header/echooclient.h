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
    Q_INVOKABLE void login(const QString &account, const QString &password); // 暴露给qml使用
    Q_INVOKABLE void reg(const QString &nickName, const QString &account, const QString &password);
    Q_INVOKABLE void addFriendRequest(const QString &account);
    Q_INVOKABLE void addFriendResponse(const QString &account, const bool result);
    Q_INVOKABLE void removeFriend(const QString &account);
    Q_INVOKABLE void setAvatar(const QString &filePath); // 设置头像
    Q_INVOKABLE QVariantList getNetizenList();
    Q_INVOKABLE Netizen *getNetizen(const QString &account);
    Q_INVOKABLE QVariantList getMessageList(const QString &account);
    Q_INVOKABLE Netizen *getThisInfo() { return _user; };

    // 消息功能
    Q_INVOKABLE void sendMessage(const QString &receiverAccount, const QString &content)
    {
        emit triggerMessage(receiverAccount, content);
    }
    Q_INVOKABLE void sendGroupMessage(const QString &groupAccount, const QString &content)
    {
        emit triggerGroupMessage(groupAccount, content);
    }
    Q_INVOKABLE void sendImage(const QString &receiverAccount, const QString &imgPath);

signals:
    // 消息发送信号
    void triggerMessage(QString receiverAccount, QString content);
    void triggerGroupMessage(QString groupAccount, QString content);
    void triggerImage(QString receiverAccount, QString imgPath);
    // 账号处理信号
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    // 消息接收信号
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);
    void imgReceived(Message *msg);
    void receivedFriendRequest(Netizen *newFriend);
    void receivedFriendResponse(Netizen *newFriend, const bool result);
    void acceptFriendRequestn(Netizen *);                //发送同意信号，添加好友到好友列表
    void acceptFriendRequestnm(Netizen *, QVariantList); //发送同意信号，添加好友到消息列表
    void removeFriendsSignals(const QString &account);
    void removeFriendList(Netizen *);
    void removeMessagList(Netizen *);

private:
    Netizen *_user;
};
