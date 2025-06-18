#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QList>

class Group;
class Communicator;
class Message;

class Netizen : public QObject
{
    Q_OBJECT
public:
    explicit Netizen(QObject *parent = nullptr);
    Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent = nullptr);
    ~Netizen();

    // 用户属性获取，用户数据库信息存储
    QString GetNickname() { return m_nickName; };
    QString GetAccount() { return m_account; };
    QList<Netizen *> GetFriendAccounts() { return m_friends; };
    QList<Group *> GetGroupAccounts() { return m_groups; };
    bool IsOnline() { return m_isOnline; };

    // 账号功能
    bool LoginDetection(const QString &password);
    void Logout() { m_isOnline = false; };
    void SetOnline() { m_isOnline = true; };

    // 好友管理
    bool AddFriend(Netizen *user);
    bool RemoveFriend(const QString &account);

    // 消息功能
    void SendMessage(Netizen *receiver, Message *msg);
    void SendGroupMessage(Group *group, Message *msg);

    // 群组功能
    bool CreateGroup(const QString &name, const QString &owner);
    bool JoinGroup(Group *group);
    bool LeaveGroup(Group *group);

signals:
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    bool m_isOnline;

    QList<Netizen *> m_friends;
    QList<Group *> m_groups;

    // p2p服务
    Communicator *_cmc;
};
