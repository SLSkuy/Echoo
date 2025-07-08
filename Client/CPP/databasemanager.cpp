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
    qDeleteAll(m_allMessages);
    qDeleteAll(m_offlineMessages);
    for (auto it = m_groups.begin(); it != m_groups.end(); ++it) {
        delete it.value();
    }
    for (auto it = m_netizens.begin(); it != m_netizens.end(); ++it) {
        delete it.value();
    }
}

bool DatabaseManager::initDatabase()
{
    if (m_db.isOpen()) m_db.close();

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("databse.db");

    if (!m_db.open()) {
        qWarning() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // 创建netizens表
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS netizens ("
            "account TEXT PRIMARY KEY,"
            "nickname TEXT,"
            "password TEXT,"
            "avatar TEXT,"
            "sign TEXT,"
            "ip TEXT,"
            "online INTEGER)")) {
        qWarning() << "Failed to create netizens table:" << query.lastError().text();
        return false;
    }

    // 创建friends表
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS friends ("
            "user_account TEXT,"
            "friend_account TEXT,"
            "PRIMARY KEY (user_account, friend_account))")) {
        qWarning() << "Failed to create friends table:" << query.lastError().text();
        return false;
    }

    // 创建groups表
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS groups ("
            "account TEXT PRIMARY KEY,"
            "name TEXT,"
            "owner TEXT)")) {
        qWarning() << "Failed to create groups table:" << query.lastError().text();
        return false;
    }

    // 创建messages表
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS messages ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "sender TEXT,"
            "receiver TEXT,"
            "content TEXT,"
            "timestamp TEXT,"
            "type INTEGER,"
            "image_data TEXT)")) {
        qWarning() << "Failed to create messages table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::loadFromDatabase()
{
    if (!m_db.isOpen() && !m_db.open()) {
        qWarning() << "Database is not open:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // 加载所有用户
    if (!query.exec("SELECT account, nickname, password, avatar, sign FROM netizens")) {
        qWarning() << "Failed to query netizens:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        QString account = query.value(0).toString();
        QString nickname = query.value(1).toString();
        QString password = query.value(2).toString();
        QString avatar = query.value(3).toString();
        QString sign = query.value(4).toString();

        Netizen *user = new Netizen(nickname, account, password);
        user->setOnline(false);
        user->setSign(sign);
        user->updateAvatar(avatar);

        m_netizens.insert(account, user);
    }

    // 加载好友关系
    if (!query.exec("SELECT user_account, friend_account FROM friends")) {
        qWarning() << "Failed to query friends:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        QString userAccount = query.value(0).toString();
        QString friendAccount = query.value(1).toString();

        Netizen *user = m_netizens.value(userAccount, nullptr);
        Netizen *friendUser = m_netizens.value(friendAccount, nullptr);
        if (user && friendUser) {
            user->addFriend(friendUser);
            friendUser->addFriend(user);
        } else {
            qWarning() << "Friend link failed for " << userAccount << " -> " << friendAccount;
        }
    }


    // 加载消息
    if (!query.exec("SELECT sender, receiver, content, timestamp, type, image_data FROM messages")) {
        qWarning() << "Failed to query messages:" << query.lastError().text();
        return false;
    }

    while (query.next()) {
        QString senderAccount = query.value(0).toString();
        QString receiverAccount = query.value(1).toString();
        QString content = query.value(2).toString();
        QString timestampStr = query.value(3).toString();
        int type = query.value(4).toInt();
        QString imageData = query.value(5).toString();

        Netizen *sender = m_netizens[senderAccount];
        if (!sender) {
            qWarning() << "Message sender not found:" << senderAccount;
            continue;
        }

        QObject *receiver = nullptr;
        if (m_netizens.contains(receiverAccount)) {
            receiver = m_netizens[receiverAccount];
        } else if (m_groups.contains(receiverAccount)) {
            receiver = m_groups[receiverAccount];
        }

        if (!receiver) {
            qWarning() << "Message receiver not found:" << receiverAccount;
            continue;
        }

        QDateTime timestamp = QDateTime::fromString(timestampStr, Qt::ISODate);
        Message *msg = new Message(sender, receiver, content, timestamp, static_cast<Message::MessageType>(type));
        msg->setImageData(imageData); // 加载图片Base64数据
        m_allMessages.insert(msg);
    }

    return true;
}

bool DatabaseManager::saveToDatabase()
{
    if (!m_db.isOpen() && !m_db.open()) {
        qWarning() << "Database is not open:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // 事务保护
    m_db.transaction();

    // 清空旧的Netizen数据
    if (!query.exec("DELETE FROM netizens") ||
        !query.exec("DELETE FROM messages") ||
        !query.exec("DELETE FROM friends")) {
        qWarning() << "Failed to clear tables:" << query.lastError().text();
        m_db.rollback();
        return false;
    }

    // 保存netizens
    query.prepare("INSERT INTO netizens (account, nickname, password, avatar, sign) "
                  "VALUES (?, ?, ?, ?, ?)");
    for (auto user : m_netizens.values()) {
        query.addBindValue(user->getAccount());
        query.addBindValue(user->getNickname());
        query.addBindValue(user->getPassword());
        query.addBindValue(user->getAvatarBase64());
        query.addBindValue(user->getSign());

        if (!query.exec()) {
            qWarning() << "Failed to insert netizen:" << query.lastError().text();
            m_db.rollback();
            return false;
        }
    }

    // 保存好友关系
    query.prepare("INSERT INTO friends (user_account, friend_account) VALUES (?, ?)");
    for (auto user : m_netizens.values()) {
        QString userAccount = user->getAccount();
        for (const QString &friendAccount : user->GetFriendsAccount()) {
            query.addBindValue(userAccount);
            query.addBindValue(friendAccount);
            if (!query.exec()) {
                qWarning() << "Failed to insert friend relation:" << query.lastError().text();
                m_db.rollback();
                return false;
            }
        }
    }

    // 保存消息
    query.prepare("INSERT INTO messages (sender, receiver, content, timestamp, type, image_data) "
                  "VALUES (?, ?, ?, ?, ?, ?)");

    for (auto msg : m_allMessages) {
        query.addBindValue(msg->GetSender()->getAccount());

        QString recAccount;
        if (Netizen *n = qobject_cast<Netizen*>(msg->GetReceiver())) {
            recAccount = n->getAccount();
        } else if (Group *g = qobject_cast<Group*>(msg->GetReceiver())) {
            recAccount = g->GetGroupAccount();
        } else {
            recAccount = "";
        }

        query.addBindValue(recAccount);
        query.addBindValue(msg->GetMessage());
        query.addBindValue(msg->GetMessageTime());
        query.addBindValue(static_cast<int>(msg->getMessageType()));
        query.addBindValue(msg->getImageData()); // 新增图片数据

        if (!query.exec()) {
            qWarning() << "Failed to insert message:" << query.lastError().text();
            m_db.rollback();
            return false;
        }
    }

    return m_db.commit();
}


bool DatabaseManager::AddNetizen(Netizen *user)
{
    // 检测是否存在对应用户
    if (user && !Contains(user->getAccount())) {
        m_netizens.insert(user->getAccount(), user);
        Logger::Log("Account " + user->getAccount() + " add successfully.");
        return true;
    } else {
        Logger::Error("Account " + user->getAccount() + " already exist.");
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
    m_allMessages.insert(message); // 确保记录唯一指针
}

bool DatabaseManager::RemoveNetizen(const QString &account)
{
    Netizen *toRemove = GetNetizen(account);
    m_netizens.remove(account);
    delete toRemove;
    return true;
}
