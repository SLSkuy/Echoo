#include "databasemanager.h"
#include "echooclient.h"
#include "message.h"
#include "netizen.h"
#include "logger.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent)
{
    connect(_user,&Netizen::messageReceived,this,&EchooClient::messageReceived);
    connect(_user,&Netizen::groupMessageReceived,this,&EchooClient::groupMessageReceived);
}

EchooClient::~EchooClient()
{
    delete _user;
}

void EchooClient::Login(const QString &account, const QString &password)
{
    Netizen *user = nullptr;
    if (DatabaseManager::instance()->Contains(account)) {
        // user = _dm->GetNetizen(account);
        // if (user->LoginDetection(password)) {
        //     // 设置当前用户的Netizen为从数据管理层获取到的Netizen对象
        //     _user = user;
        //     emit loginSuccess(true);
        // }

        // 测试使用，直接触发成功信号
        emit loginSuccess(true);
    }
    emit loginSuccess(false);
}

void EchooClient::Register(const QString &nickName, const QString &account, const QString &password)
{
    if (DatabaseManager::instance()->Contains(account)) {
        // 如果数据库中已存在则返回注册失败
        emit registerSuccess(false);
        Logger::Error("Account " + account + " already exist.");
    }

    Netizen *newUser = new Netizen(nickName, account, password);
    _user = newUser; // 设置当前客户端的账号信息
    emit registerSuccess(true);
}

void EchooClient::SendMessage(QString &receiverAccount, QString &content)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
    Message *msg = new Message(_user, nullptr, content, curTime);
    _user->SendMessage(receiver, msg);
}

void EchooClient::SendGroupMessage(QString &groupAccount, QString &content)
{
    Group *receiver = DatabaseManager::instance()->GetGroup(groupAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    // 创建消息实体
    Message *msg = new Message(_user, nullptr, content, curTime);
    _user->SendGroupMessage(receiver, msg);
}
