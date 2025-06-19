#include "databasemanager.h"
#include "logger.h"

// 初始化单例指针
DatabaseManager *DatabaseManager::m_instance = nullptr;

DatabaseManager *DatabaseManager::instance()
{
    if (!m_instance) { m_instance = new DatabaseManager(); }
    return m_instance;
}

void DatabaseManager::destroy()
{
    if (m_instance) {
        delete m_instance;
        m_instance = nullptr;
    }
}

DatabaseManager::DatabaseManager()
{
    // 测试用户数据
    Netizen *newUser = new Netizen("SL_Skuy", "123", "123");
    AddNetizen(newUser);
    Netizen *newUser2 = new Netizen("Yumikaze", "0721", "0721");
    AddNetizen(newUser2);
}

bool DatabaseManager::AddNetizen(Netizen *user)
{
    // 检测是否存在对应用户
    if (user && !Contains(user->GetAccount())) {
        m_netizens.insert(user->GetAccount(), user);
        Logger::Log("Account " + user->GetAccount() + " add successfully.");
        return true;
    } else {
        Logger::Error("Account " + user->GetAccount() + " already exist.");
        return false;
    }
}

bool DatabaseManager::RemoveNetizen(const QString &account)
{
    // TODO
    return true;
}

Group *DatabaseManager::GetGroup(const QString &account)
{
    // TODO
    return nullptr;
}
