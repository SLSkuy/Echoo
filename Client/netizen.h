#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QMap>

class Group;
class Communicator;
class Message;

class Netizen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString nickname READ GetNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString account READ GetAccount CONSTANT)
    Q_PROPERTY(bool online READ IsOnline NOTIFY onlineChanged)
    Q_PROPERTY(QString ipAddress READ GetIpAddress WRITE SetIpAddress NOTIFY ipChanged)
public:
    explicit Netizen(QObject *parent = nullptr);
    Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent = nullptr);
    ~Netizen();

    // 用户属性获取，用户数据库信息存储
    QString GetNickname()  { return m_nickName; }
    QString GetAccount()  { return m_account; }
    QString GetIpAddress()  { return m_ip; }
    void SetIpAddress(QString ip) { m_ip=ip; }
    void SetOnline(bool result) { m_isOnline=result; }
    bool IsOnline() const { return m_isOnline; }

    // 账号功能
    Q_INVOKABLE QVariantList GetFriends();
    Q_INVOKABLE QVariantList GetGroups();
    bool LoginDetection(const QString &password);
    void Logout() { m_isOnline = false; };

    // 好友管理
    bool AddFriend(Netizen *user);
    bool RemoveFriend(const QString &account);
    void RemoveFriendRequest(const QString &account);
    void AddFriendRequest(const QString &account);
    void AddFriendResponse(const QString &account, const bool result);
    bool HasFriend(const QString &account) { return m_friends.contains(account); }

    // 消息功能
    void SendMessage(const QString &receiverAccount, const QString &content);
    void SendGroupMessage(const QString &groupAccount, const QString &content);

    // 群组功能
    bool CreateGroup(const QString &name, const QString &owner);
    bool JoinGroup(Group *group);
    bool LeaveGroup(Group *group);
    bool HasGroup(const QString &account) { return m_groups.contains(account); }

signals:
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);
    void receivedFriendRequest(Netizen *);
    void receivedFriendResponse(Netizen *, const bool result);
    void nicknameChanged();
    void onlineChanged();
    void ipChanged();

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    bool m_isOnline;

    QMap<QString, Netizen *> m_friends;
    QMap<QString, Group *> m_groups;

    // p2p服务
    Communicator *_cmc;
    QString m_ip;

    void CommandProcess(Message *msg);
};
