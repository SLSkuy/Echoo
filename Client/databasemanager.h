#pragma once

#include <QString>

class Netizen;

class DatabaseManager
{
public:
    DatabaseManager();

    // 账号检测
    bool Contains(const QString &account);

    // 账号管理
    void AddNetizen(Netizen *user);
    void RemoveNetizen(const QString &account);
    Netizen *GetNetizen(const QString &account);

private:
};
