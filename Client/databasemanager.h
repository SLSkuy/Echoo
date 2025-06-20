#pragma once

#include <QTcpSocket>
#include <QString>
#include <QList>
#include <QMap>

#include "message.h"
#include "netizen.h"
#include "group.h"

class DatabaseManager
{
public:
    // 单例访问方法
    static DatabaseManager *instance();
    static void destroy();
    DatabaseManager();

    // 用于账号检测与管理
    bool Contains(const QString &account) { return m_netizens.contains(account); };
    bool AddNetizen(Netizen *user);
    bool RemoveNetizen(const QString &account);
    Netizen *GetNetizen(const QString &account) { return m_netizens[account]; };
    QList<Netizen *> GetAllNetizen() { return m_netizens.values(); };

    // 群聊检测与管理
    bool AddGroup(Group *group);
    bool RemoveGroup(const QString &account);
    Group *GetGroup(const QString &account);

    // 消息存储与检测
    void AddMessage(QString &account, Message *message);
    void AddOfflineMessage(Message *message) { m_offlineMessages.append(message); }
    QList<Message *> GetHistroyMessages(const QString &account) { return m_messages[account]; }
    QList<Message *> GetOfflineMessages() { return m_offlineMessages; }
    void UpdateOfflineMessages(QList<Message *> offlineMessages) { m_offlineMessages = offlineMessages; }

    // 数据管理
    bool loadFromDatabase();
    bool saveToDatabase();

private:
    // 单例访问指针
    static DatabaseManager *m_instance;
    // 缓存管理
    QMap<QString, Group *> m_groups;       // 记录所有的群聊信息
    QMap<QString, Netizen *> m_netizens;   // 记录局域网中的所有账号
    QMap<QString, QList<Message *>> m_messages; // 记录所有聊天信息
    // QList<Message *> m_messages;
    QList<Message *> m_offlineMessages; // 发送的离线消息，当有用户上线时，监测是否有离线消息，若有则向其发送消息
};
