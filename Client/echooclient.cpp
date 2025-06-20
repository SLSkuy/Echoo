#include "databasemanager.h"
#include "echooclient.h"
#include "netizen.h"
#include "logger.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent){}

EchooClient::~EchooClient()
{
    delete _user;
}

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

void EchooClient::AddFriend(const QString &account)
{
    Netizen *user = DatabaseManager::instance()->GetNetizen(account);
    // 调用双方对象进行双向添加好友
    user->AddFriend(_user);
    _user->AddFriend(user);
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
