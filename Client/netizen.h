#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QList>

class Message;
class Group;

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
    bool LoginDetection(const QString &password) { return password == m_password; };
    void Logout();

    // 好友管理
    bool AddFriend(Netizen *user);
    bool RemoveFriend(const QString &account);

    // 消息功能
    void SendMessage(Netizen *receiver, const QString &content);
    void SendGroupMessage(Group *group, const QString &content);

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
};
