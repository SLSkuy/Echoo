#include <QJsonObject>
#include <QFile>

#include "databasemanager.h"
#include "communicator.h"
#include "message.h"
#include "netizen.h"
#include "logger.h"

Netizen::Netizen(QObject *parent) : QObject(parent) {}
Netizen::Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent)
    : m_nickName(nickName)
    , m_account(account)
    , m_password(password)
    , m_isOnline(false)
    , QObject(parent)
{}

Netizen::~Netizen()
{
    delete _cmc;
}

bool Netizen::LoginDetection(const QString &password)
{
    if (password == m_password) {
        // 连接p2p服务器
        _cmc = new Communicator(this);

        m_ip = _cmc->getLocalIP();
        connect(_cmc, &Communicator::messageReceived, this, &Netizen::messageReceived);
        connect(_cmc, &Communicator::groupMessageReceived, this, &Netizen::groupMessageReceived);
        connect(_cmc, &Communicator::imageReceived, this, &Netizen::imgReceived);
        connect(_cmc, &Communicator::commandReceived, this, &Netizen::CommandProcess);

        // 设置在线信息
        m_isOnline = true;
        return true;
    }
    return false;
}

void Netizen::SendMessage(const QString &receiverAccount, const QString &content)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (HasFriend(receiverAccount)) {
        // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
        Message *msg = new Message(this, receiver, content, curTime);
        _cmc->sendMessage(msg);

        QString rec = receiverAccount;
        DatabaseManager::instance()->AddMessage(rec,msg);
    } else {
        Logger::Warning(receiverAccount + " is not " + m_account + "'s friend.");
    }
}

void Netizen::SendGroupMessage(const QString &groupAccount, const QString &content)
{
    Group *receiver = DatabaseManager::instance()->GetGroup(groupAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (HasGroup(groupAccount)) {
        // 创建消息实体
        Message *msg = new Message(this, receiver, content, curTime);
        _cmc->sendGroupMessage(msg);
    } else {
        Logger::Warning(m_account + " not in group " + groupAccount);
    }
}

void Netizen::SendImage(const QString &receiverAccount, const QString &imgPath)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (HasFriend(receiverAccount)) {
        // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
        Message *msg = new Message(this, receiver, imgPath, curTime, Message::Image);
        if (!msg->LoadImage()) {
            // 图片加载失败
            Logger::Error("Fail to load image.");
            return;
        }
        _cmc->sendMessage(msg);

        QString rec = receiverAccount;
        DatabaseManager::instance()->AddMessage(rec,msg);
    } else {
        Logger::Warning(receiverAccount + " is not " + m_account + "'s friend.");
    }
}

bool Netizen::AddFriend(Netizen *user)
{
    if (HasFriend(user->GetAccount())) {
        // Logger::Warning(user->GetAccount() + " is already your friend.");
        return false;
    } else {
        // Logger::Log("Add friend " + user->GetAccount());
        m_friends.insert(user->GetAccount(), user);
        return true;
    }
}

bool Netizen::RemoveFriend(const QString &account)
{
    if (HasFriend(account)) {
        Logger::Log("Remove friend " + account);
        m_friends.remove(account);
        return true;
    }
    Logger::Warning("you don't have friend " + account);
    return false;
}

void Netizen::CommandProcess(Message *msg)
{
    Netizen *user = msg->GetSender();
    QString command = msg->GetMessage();
    if (command == "addFriend") {
        emit receivedFriendRequest(user);
    } else if (command == "acceptFriend") {
        // 确认接受则双向确认
        user->AddFriend(this);
        AddFriend(user);
        emit receivedFriendResponse(user, true);
    } else if (command == "rejectFriend") {
        emit receivedFriendResponse(user, false);
    } else if (command == "removeFriend") {
        // 双向删除好友

        user->RemoveFriend(m_account);
        RemoveFriend(user->GetAccount());
    }
}

void Netizen::RemoveFriendRequest(const QString &account)
{
    // 发送删除好友请求
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    // 本地客户端双向删除
    RemoveFriend(account);
    user->RemoveFriend(m_account);

    Message *msg = new Message(this, user, "removeFriend", time, Message::Command);
    _cmc->sendMessage(msg);
}

void Netizen::AddFriendRequest(const QString &account)
{
    // 发送添加好友请求
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    Message *msg = new Message(this, user, "addFriend", time, Message::Command);
    _cmc->sendMessage(msg);
}

void Netizen::AddFriendResponse(const QString &account, const bool result)
{
    // 发送添加好友回应
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    // 若同意添加好友则双向添加
    // 发送确认信息给对方使对方也进行双向添加确认
    if (result) {
        AddFriend(user);
        user->AddFriend(this);
    }

    QString response = (result == true) ? "acceptFriend" : "rejectFriend";
    Message *msg = new Message(this, user, response, time, Message::Command);
    _cmc->sendMessage(msg);
}

QVariantList Netizen::getFriends()
{
    QList<Netizen *> friends = m_friends.values();
    QVariantList list;
    for (auto it = friends.begin(); it != friends.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

QVariantList Netizen::getGroups()
{
    QList<Group *> groups = m_groups.values();
    QVariantList list;
    for (auto it = groups.begin(); it != groups.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
};

void Netizen::setAvatar(const QString &filePath)
{
    QString path = QUrl(filePath).toLocalFile();    // 转换为本地路径

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        Logger::Error("Can't open image: " + filePath);
        return;
    }

    QByteArray imageData = file.readAll();
    file.close();

    if (imageData.isEmpty()) {
        Logger::Error("Image file is empty: " + filePath);
        return;
    }

    // 判断图片格式
    QString imageType;
    if (imageData.startsWith("\x89PNG")) {
        imageType = "png";
    } else if (imageData.startsWith("\xFF\xD8\xFF")) {
        imageType = "jpeg";
    } else {
        Logger::Error("Unsupported image format: " + filePath);
        return;
    }

    // 自动设置图片解析前缀
    QString base64 = QString::fromLatin1(imageData.toBase64());
    m_avatar = QString("data:image/%1;base64,%2").arg(imageType, base64);
}
