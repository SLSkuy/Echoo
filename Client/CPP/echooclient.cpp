#include "databasemanager.h"
#include "echooclient.h"
#include "netizen.h"
#include "logger.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent)
{
    DatabaseManager::instance()->initDatabase();
    DatabaseManager::instance()->loadFromDatabase();
}

EchooClient::~EchooClient(){}

void EchooClient::login(const QString &account, const QString &password)
{
    Netizen *user = nullptr;
    if (DatabaseManager::instance()->Contains(account)) {
        user = DatabaseManager::instance()->GetNetizen(account);
        if (user->LoginDetection(password)) {
            // 设置当前用户的Netizen为从数据管理层获取到的Netizen对象
            _user = user;

            DatabaseManager::instance()->DivideMessage(_user->getAccount());
            emit loginSuccess(true);

            // 连接消息发送
            connect(this, &EchooClient::triggerMessage, _user, &Netizen::sendMessage);
            connect(this, &EchooClient::triggerGroupMessage, _user, &Netizen::sendGroupMessage);
            connect(this, &EchooClient::triggerImage, _user, &Netizen::sendImage);
            // 连接消息接收
            connect(_user, &Netizen::messageReceived, this, &EchooClient::messageReceived);
            connect(_user, &Netizen::groupMessageReceived, this, &EchooClient::groupMessageReceived);
            connect(_user, &Netizen::imgReceived, this, &EchooClient::imgReceived);
            connect(_user, &Netizen::receivedFriendRequest, this, &EchooClient::receivedFriendRequest);
            connect(_user, &Netizen::removeFriendList11, this, &EchooClient::removeFriendList11);
            connect(_user, &Netizen::removeMessagList, this, &EchooClient::removeMessagList);
            connect(_user, &Netizen::receivedFriendResponse, this, &EchooClient::receivedFriendResponse);
        }
    }
    emit loginSuccess(false);
}

void EchooClient::reg(const QString &nickName, const QString &account, const QString &password)
{
    if (DatabaseManager::instance()->Contains(account)) {
        // 如果数据库中已存在则返回注册失败
        emit registerSuccess(false);
        Logger::Error("Account " + account + " already exist.");
        return;
    }

    Netizen *newUser = new Netizen(nickName, account, password);
    _user = newUser; // 设置当前客户端的账号信息
    DatabaseManager::instance()->AddNetizen(newUser);
    emit registerSuccess(true);
}

QVariantList EchooClient::getMessageList(const QString &account)
{
    QList<Message *> msgs = DatabaseManager::instance()->GetHistroyMessages(account);
    QVariantList list;
    for (auto it = msgs.begin(); it != msgs.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

QVariantList EchooClient::getNetizenList()
{
    QList<Netizen *> users = DatabaseManager::instance()->GetAllNetizen();
    QVariantList list;
    for (auto it = users.begin(); it != users.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

void EchooClient::addFriendRequest(const QString &account)
{
    _user->addFriendRequest(account);
}

void EchooClient::addFriendResponse(const QString &account, const bool result)
{
    _user->addFriendResponse(account, result);
}

void EchooClient::removeFriend(const QString &account)
{
    _user->removeFriendRequest(account);
    emit removeFriendsSignals(account);
}

void EchooClient::sendImage(const QString &receiverAccount, const QString &imgPath)
{
    _user->sendImage(receiverAccount, imgPath);
}

void EchooClient::setAvatar(const QString &filePath)
{
    _user->setAvatar(filePath);
}

Netizen *EchooClient::getNetizen(const QString &account)
{
    return DatabaseManager::instance()->GetNetizen(account);
}
