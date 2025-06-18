#pragma once

#include <QString>

#include "netizen.h"

class DatabaseManager
{
public:
    // 单例访问方法
    static DatabaseManager *instance();
    static void destroy();

    // 账号检测与管理
    bool Contains(const QString &account);
    bool AddNetizen(Netizen *user);
    bool RemoveNetizen(const QString &account);
    Netizen *GetNetizen(const QString &account);

    // 数据管理
    bool loadFromDatabase();
    bool saveToDatabase();

private:
    // 单例访问指针
    static DatabaseManager *m_instance;
    // 缓存管理
    QHash<QString, Netizen *> m_netizens;
};
