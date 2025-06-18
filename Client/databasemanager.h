#pragma once

#include <QTcpSocket>
#include <QString>
#include <QMap>

#include "netizen.h"
#include "group.h"

class DatabaseManager
{
public:
    // 单例访问方法
    static DatabaseManager *instance();
    static void destroy();
    DatabaseManager();

    // 账号检测与管理
    bool Contains(const QString &account) { return m_netizens.contains(account); };
    bool AddNetizen(Netizen *user);
    bool RemoveNetizen(const QString &account);
    Netizen *GetNetizen(const QString &account) { return m_netizens[account]; };
    Group *GetGroup(const QString &account);

    // 数据管理
    bool loadFromDatabase();
    bool saveToDatabase();

private:
    // 单例访问指针
    static DatabaseManager *m_instance;
    // 缓存管理
    QMap<QString, Group *> m_groups;
    QMap<QString, Netizen *> m_netizens;   // 记录局域网中的所有账号
    QMap<QString, QTcpSocket *> m_sockets; // 记录当前在线的账号的TcpSocket连接
};
