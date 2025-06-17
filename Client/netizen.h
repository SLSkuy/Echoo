#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QList>

#include "databasemanager.h"
#include "communicator.h"
#include "message.h"
#include "group.h"

class Netizen : public QObject
{
    Q_OBJECT
public:
    Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent = nullptr);

    // 用户属性获取
    QString GetNickname();
    QString GetAccount();
    bool IsOnline();

    // 好友管理
    bool addFriend(Netizen *user);
    bool removeFriend(const QString &account);

    // 消息功能
    void sendMessage(Netizen *receiver, const QString &content);
    void sendGroupMessage(Group *group, const QString &content);

    // 群组功能
    bool createGroup(const QString &name, const QString &owner);
    bool joinGroup(Group *group);
    bool leaveGroup(Group *group);

    // 账号功能
    bool login(const QString &password);
    void logout();

    // 数据库操作
    void loadFromDatabase();
    void saveToDatabase() const;

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

    Communicator *_cmc;
    DatabaseManager *_dm;

    // 初始化
    void initCommunicator();
    void setUpConnection();
};
