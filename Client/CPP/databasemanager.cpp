#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

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

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    saveToDatabase();
    // 释放内存
    for (auto it = m_groups.begin(); it != m_groups.end(); ++it) {
        it.value()->deleteLater();
    }
    for (auto it = m_netizens.begin(); it != m_netizens.end(); ++it) {
        it.value()->deleteLater();
    }
    qDeleteAll(m_allMessages);
    // qDeleteAll(m_offlineMessages);
}

bool DatabaseManager::initDatabase()
{
    if (m_db.isOpen()) m_db.close();

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("databse.db");

    if (!m_db.open()) {
        Logger::Warning("Failed to open database:" + m_db.lastError().text());
        return false;
    }

    QSqlQuery query;

    // 创建netizens表
    if (!query.exec("CREATE TABLE IF NOT EXISTS netizens ("
                    "account TEXT PRIMARY KEY,"
                    "nickname TEXT,"
                    "password TEXT,"
                    "avatar TEXT,"
                    "sign TEXT)")) {
        Logger::Warning("Failed to create netizens table:" + query.lastError().text());
        return false;
    }

    // 创建friends表
    if (!query.exec("CREATE TABLE IF NOT EXISTS friends ("
                    "user_account TEXT,"
                    "friend_account TEXT,"
                    "PRIMARY KEY (user_account, friend_account))")) {
        Logger::Warning("Failed to create netizens table:" + query.lastError().text());
        return false;
    }

    // 创建groups表
    if (!query.exec("CREATE TABLE IF NOT EXISTS groups ("
                    "account TEXT PRIMARY KEY,"
                    "name TEXT,"
                    "owner TEXT)")) {
        Logger::Warning("Failed to create netizens table:" + query.lastError().text());
        return false;
    }

    // 创建messages表
    if (!query.exec("CREATE TABLE IF NOT EXISTS messages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "sender TEXT,"
                    "receiver TEXT,"
                    "content TEXT,"
                    "timestamp TEXT,"
                    "type INTEGER)")) {
        Logger::Warning("Failed to create netizens table:" + query.lastError().text());
        return false;
    }

    return true;
}

bool DatabaseManager::loadFromDatabase()
{
    if (!m_db.isOpen() && !m_db.open()) {
        Logger::Warning("Database is not open:" + m_db.lastError().text());
        return false;
    }

    QSqlQuery query;

    // 加载所有用户
    if (!query.exec("SELECT account, nickname, password, avatar, sign FROM netizens")) {
        Logger::Warning("Failed to query netizens:" + m_db.lastError().text());
        return false;
    }

    while (query.next()) {
        QString account = query.value(0).toString();
        QString nickname = query.value(1).toString();
        QString password = query.value(2).toString();
        QString avatar = query.value(3).toString();
        QString sign = query.value(4).toString();

        Logger::Log("Add Netizen: " + nickname + " " + account + " " + sign);

        Netizen *user = new Netizen(nickname, account, password);
        user->SetOnline(false);
        user->SetSign(sign);
        user->updateAvatar(avatar);

        m_netizens.insert(account, user);
    }

    // 加载好友关系
    if (!query.exec("SELECT user_account, friend_account FROM friends")) {
        Logger::Warning("Failed to query friends:" + query.lastError().text());
        return false;
    }

    while (query.next()) {
        QString userAccount = query.value(0).toString();
        QString friendAccount = query.value(1).toString();

        Netizen *user = m_netizens.value(userAccount, nullptr);
        Netizen *friendUser = m_netizens.value(friendAccount, nullptr);

        if (user && friendUser) {
            user->AddFriend(friendUser);
            friendUser->AddFriend(user);
        } else {
            Logger::Warning("Friend link failed for " + userAccount + "->" + friendAccount);
        }
    }


    // 加载消息
    if (!query.exec("SELECT sender, receiver, content, timestamp, type FROM messages")) {
        Logger::Warning("Failed to query messages:" + query.lastError().text());
        return false;
    }

    while (query.next()) {
        QString senderAccount = query.value(0).toString();
        QString receiverAccount = query.value(1).toString();
        QString content = query.value(2).toString();
        QString timestampStr = query.value(3).toString();
        int type = query.value(4).toInt();
        Logger::Log(senderAccount + " " + receiverAccount);

        Netizen *sender = m_netizens[senderAccount];
        if (!sender) {
            Logger::Warning("Message sender not found:" + senderAccount);
            continue;
        }

        QObject *receiver = nullptr;
        if (m_netizens.contains(receiverAccount)) {
            receiver = m_netizens[receiverAccount];
        } else if (m_groups.contains(receiverAccount)) {
            receiver = m_groups[receiverAccount];
        }

        if (!receiver) {
            Logger::Warning("Message receiver not found:" + receiverAccount);
            continue;
        }

        Logger::Log("Add Message: " + senderAccount + " " + receiverAccount + " " + content + " " + timestampStr);

        QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
        Message *msg = new Message(sender, receiver, content, timestamp, static_cast<Message::MessageType>(type));
        m_allMessages.append(msg); // 记录消息
    }

    return true;
}

bool DatabaseManager::saveToDatabase()
{
    if (!m_db.isOpen() && !m_db.open()) {
        Logger::Warning("Database is not open:" + m_db.lastError().text());
        return false;
    }

    QSqlQuery query;

    // 事务保护
    m_db.transaction();

    // 清空旧的Netizen数据
    if (!query.exec("DELETE FROM netizens") ||
        !query.exec("DELETE FROM messages") ||
        !query.exec("DELETE FROM friends")) {
        Logger::Warning("Failed to clear tables:" + query.lastError().text());
        m_db.rollback();
        return false;
    }

    // 保存netizens
    query.prepare("INSERT INTO netizens (account, nickname, password, avatar, sign) "
                  "VALUES (?, ?, ?, ?, ?)");
    for (auto user : m_netizens.values()) {
        query.addBindValue(user->GetAccount());
        query.addBindValue(user->GetNickname());
        query.addBindValue(user->GetPassword());
        query.addBindValue(user->getAvatar());
        query.addBindValue(user->GetSign());

        Logger::Log("Save Netizen: " + user->GetNickname() + " " + user->GetAccount() + " " + user->GetSign());

        if (!query.exec()) {
            Logger::Warning("Failed to insert netizen:" + query.lastError().text());
            m_db.rollback();
            return false;
        }
    }

    // 保存好友关系
    query.prepare("INSERT INTO friends (user_account, friend_account) VALUES (?, ?)");
    for (auto it = m_netizens.begin(); it != m_netizens.end(); it++) {
        QString userAccount = it.value()->GetAccount();
        for (auto friendAccount : it.value()->GetFriendsAccount()) {
            query.addBindValue(userAccount);
            query.addBindValue(friendAccount);
            if (!query.exec()) {
                Logger::Warning("Failed to insert friend relation:" + query.lastError().text());
                m_db.rollback();
                return false;
            }
        }
    }

    // 保存消息
    query.prepare("INSERT INTO messages (sender, receiver, content, timestamp, type) "
                  "VALUES (?, ?, ?, ?, ?)");
    for (auto it = m_allMessages.begin(); it != m_allMessages.end(); it++) {
        query.addBindValue((*it)->GetSender()->GetAccount());

        QString recAccount;
        if (Netizen *n = qobject_cast<Netizen *>((*it)->GetReceiver())) {
            recAccount = n->GetAccount();
        } else if (Group *g = qobject_cast<Group *>((*it)->GetReceiver())) {
            recAccount = g->GetGroupAccount();
        } else {
            recAccount = "";
        }

        query.addBindValue(recAccount);
        query.addBindValue((*it)->GetMessage());
        query.addBindValue((*it)->GetMessageTime());
        query.addBindValue(static_cast<int>((*it)->GetMessageType()));

        if (!query.exec()) {
            Logger::Warning("Failed to insert message:" + query.lastError().text());
            m_db.rollback();
            return false;
        }
    }

    return m_db.commit();
}

void DatabaseManager::ClassifyMessage(const QString account)
{
    // 按时间升序排序
    std::sort(m_allMessages.begin(), m_allMessages.end(), [](Message *a, Message *b) {
        return a->GetTime() < b->GetTime();
    });
    // 将数据库中的历史消息根据账号分类
    for (auto it = m_allMessages.begin(); it != m_allMessages.end(); it++) {
        if ((*it)->GetSender()->GetAccount() == account) {
            auto receiver = (*it)->GetReceiver();
            QString account;
            if (auto user = qobject_cast<Netizen *>(receiver)) { account = user->GetAccount(); }
            m_messages[account].append(*it);
        } else {
            QString account = (*it)->GetSender()->GetAccount();
            m_messages[account].append(*it);
        }
    }
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
    m_allMessages.append(message); // 确保记录唯一指针
}

bool DatabaseManager::RemoveNetizen(const QString &account)
{
    Netizen *toRemove = GetNetizen(account);
    m_netizens.remove(account);
    delete toRemove;
    return true;
}
