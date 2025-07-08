#include "chatoperation.h"
#include "databasemanager.h"
#include "communicator.h"
#include "message.h"
#include "logger.h"
#include "netizen.h"

ChatOperation::ChatOperation(Communicator *cmc,Netizen *owner)
    :_cmc(cmc)
    ,_owner(owner)
    ,QObject(owner)
{}

void ChatOperation::sendMessage(const QString &receiverAccount, const QString &content)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (hasFriend(receiverAccount)) {
        // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
        Message *msg = new Message(_owner, receiver, content, curTime);
        _cmc->sendMessage(msg);

        QString rec = receiverAccount;
        DatabaseManager::instance()->AddMessage(rec,msg);
    } else {
        Logger::warning() << receiverAccount + " is not your friend.";
    }
}

void ChatOperation::sendGroupMessage(const QString &groupAccount, const QString &content)
{
    Group *receiver = DatabaseManager::instance()->GetGroup(groupAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (hasGroup(groupAccount)) {
        // 创建消息实体
        Message *msg = new Message(_owner, receiver, content, curTime);
        _cmc->sendGroupMessage(msg);
    } else {
        Logger::warning() << "your are not in group " << groupAccount << ".";
    }
}

void ChatOperation::sendImage(const QString &receiverAccount, const QString &imgPath)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (hasFriend(receiverAccount)) {
        // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
        Message *msg = new Message(_owner, receiver, imgPath, curTime, Message::Image);
        if (!msg->LoadImage()) {
            // 图片加载失败
            Logger::Error("Fail to load image.");
            return;
        }
        _cmc->sendMessage(msg);

        QString rec = receiverAccount;
        DatabaseManager::instance()->AddMessage(rec,msg);
    } else {
        Logger::warning() << receiverAccount + " is not your friend.";
    }
}

void ChatOperation::commandProcess(Message *msg)
{
    Netizen *user = msg->GetSender();
    QString command = msg->GetMessage();
    if (command == "addFriend") {
        qDebug() << "add friend.";
        emit receivedFriendRequest(user);

    } else if (command == "acceptFriend") {
        // 确认接受则双向确认
        user->addFriend(_owner);
        _owner->addFriend(user);
        emit receivedFriendResponse(user, true);

    } else if (command == "rejectFriend") {
        emit receivedFriendResponse(user, false);

    } else if (command == "removeFriend") {
        // 双向删除好友
        user->removeFriend(_owner->getAccount());
        _owner->removeFriend(user->getAccount());

        emit removeFriendList11(user, _owner->getAccount());
        emit removeMessagList(user);
    }
}

bool ChatOperation::addFriend(Netizen *user)
{
    if (hasFriend(user->getAccount())) {
        Logger::Warning(user->getAccount() + " is already your friend.");
        return false;
    } else {
        Logger::Log("Add friend " + user->getAccount());
        m_friends.insert(user->getAccount(), user);
        return true;
    }
}

bool ChatOperation::removeFriend(const QString &account)
{
    if (hasFriend(account)) {
        Logger::Log("Remove friend " + account);
        m_friends.remove(account);
        return true;
    }
    Logger::Warning("you don't have friend " + account);
    return false;
}

void ChatOperation::removeFriendRequest(const QString &account)
{
    // 发送删除好友请求
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    // 本地客户端双向删除
    removeFriend(account);
    user->removeFriend(_owner->getAccount());

    Message *msg = new Message(_owner, user, "removeFriend", time, Message::Command);
    _cmc->sendMessage(msg);
    QString myAccouunt = _owner->getAccount();
    // emit removeFriendList11(user, myAccouunt);
}

void ChatOperation::addFriendRequest(const QString &account)
{
    // 发送添加好友请求
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    Message *msg = new Message(_owner, user, "addFriend", time, Message::Command);
    _cmc->sendMessage(msg);
}

void ChatOperation::addFriendResponse(const QString &account, const bool result)
{
    // 发送添加好友回应
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    QDateTime time = QDateTime::currentDateTime();

    // 若同意添加好友则双向添加
    // 发送确认信息给对方使对方也进行双向添加确认
    if (result) {
        addFriend(user);
        user->addFriend(_owner);
    }

    QString response = (result == true) ? "acceptFriend" : "rejectFriend";
    Message *msg = new Message(_owner, user, response, time, Message::Command);
    _cmc->sendMessage(msg);
}
