#include "databasemanager.h"
#include "logger.h"
#include <QDateTime>

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
    Netizen *newUser3 = new Netizen("1", "1", "1");
    AddNetizen(newUser3);

    Message *message1 = new Message(newUser, newUser2, "123", QDateTime::currentDateTime());
    Message *message2 = new Message(newUser, newUser2, "1234", QDateTime::currentDateTime());
    Message *message3 = new Message(newUser, newUser2, "12345", QDateTime::currentDateTime());
    Message *message4 = new Message(newUser, newUser3, "12345", QDateTime::currentDateTime());

    // 添加历史消息
    QString account = newUser2->GetAccount();
    QString account2 = newUser3->GetAccount();
    AddMessage(account, message1);
    AddMessage(account, message2);
    AddMessage(account, message3);
    AddMessage(account2, message4);

    newUser2->AddFriend(newUser);
    newUser->AddFriend(newUser2);
    newUser->AddFriend(newUser3);
}

DatabaseManager::~DatabaseManager()
{
    // 释放内存
    for (auto it = m_groups.begin(); it != m_groups.end(); ++it) {
        delete it.value();
    }
    for (auto it = m_netizens.begin(); it != m_netizens.end(); ++it) {
        delete it.value();
    }
    for (auto it = m_messages.begin(); it != m_messages.end(); ++it) {
        qDeleteAll(it.value());
    }
    qDeleteAll(m_offlineMessages);
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

void DatabaseManager::AddMessage(QString &account, Message *message)
{
    if (!m_messages.contains(account)) {
        QList<Message *> messageList;
        m_messages[account] = messageList;
    }
    m_messages[account].append(message);
}

bool DatabaseManager::RemoveNetizen(const QString &account)
{
    Netizen *toRemove = GetNetizen(account);
    m_netizens.remove(account);
    delete toRemove;
    return true;
}
