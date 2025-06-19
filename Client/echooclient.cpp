#include "databasemanager.h"
#include "echooclient.h"
#include "message.h"
#include "netizen.h"
#include "logger.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent){}

EchooClient::~EchooClient()
{
    delete _user;
}

QString EchooClient::GetName()
{
    return _user->GetNickname();
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
            // 连接消息处理
            connect(_user, &Netizen::messageProcessed, this, &EchooClient::processedMessageReceived);
            connect(_user, &Netizen::groupMessageProcessed, this, &EchooClient::processedGroupMessageReceived);
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
