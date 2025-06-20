#include "databasemanager.h"
#include "echooclient.h"
#include "netizen.h"
#include "logger.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent){}

EchooClient::~EchooClient(){}

void EchooClient::Login(const QString &account, const QString &password)
{
    Netizen *user = nullptr;
    if (DatabaseManager::instance()->Contains(account)) {
        user = DatabaseManager::instance()->GetNetizen(account);
        if (user->LoginDetection(password)) {
            // 设置当前用户的Netizen为从数据管理层获取到的Netizen对象
            _user = user;
            emit loginSuccess(true);

            // 连接消息发送
            connect(this, &EchooClient::triggerMessage, _user, &Netizen::SendMessage);
            connect(this, &EchooClient::triggerGroupMessage, _user, &Netizen::SendGroupMessage);
            // 连接消息接收
            connect(_user, &Netizen::messageReceived, this, &EchooClient::messageReceived);
            connect(_user, &Netizen::groupMessageReceived, this, &EchooClient::groupMessageReceived);
            connect(_user, &Netizen::receivedFriendRequest, this, &EchooClient::receivedFriendRequest);
            connect(_user, &Netizen::receivedFriendResponse, this, &EchooClient::receivedFriendResponse);
        }
    }
    emit loginSuccess(false);
}

void EchooClient::Register(const QString &nickName, const QString &account, const QString &password)
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

QVariantList EchooClient::GetMessageList(const QString &account)
{
    QList<Message *> msgs = DatabaseManager::instance()->GetHistroyMessages(account);
    QVariantList list;
    for (auto it = msgs.begin(); it != msgs.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

QVariantList EchooClient::GetNetizenList()
{
    QList<Netizen *> users = DatabaseManager::instance()->GetAllNetizen();
    QVariantList list;
    for (auto it = users.begin(); it != users.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

void EchooClient::AddFriendRequest(const QString &account)
{
    _user->AddFriendRequest(account);
}

void EchooClient::AddFriendResponse(const QString &account, const bool result)
{
    _user->AddFriendResponse(account, result);
}

void EchooClient::RemoveFriend(const QString &account)
{
    _user->RemoveFriendRequest(account);
}
