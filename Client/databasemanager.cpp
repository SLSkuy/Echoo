#include "databasemanager.h"

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

bool DatabaseManager::Contains(const QString &account)
{
    // TODO
    return true;
}

bool DatabaseManager::AddNetizen(Netizen *user)
{
    // TODO
    return true;
}

bool DatabaseManager::RemoveNetizen(const QString &account)
{
    // TODO
    return true;
}

Netizen *DatabaseManager::GetNetizen(const QString &account)
{
    // TODO
    return nullptr;
}

Group *DatabaseManager::GetGroup(const QString &account)
{
    // TODO
    return nullptr;
}
