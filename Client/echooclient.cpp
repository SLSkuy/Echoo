#include "databasemanager.h"
#include "communicator.h"
#include "echooclient.h"
#include "netizen.h"
#include "message.h"
#include "logger.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent)
{
    _dm = new DatabaseManager;
}

EchooClient::~EchooClient()
{
    delete _dm;
    delete _cmc;
    delete _user;
}

void EchooClient::InitCommunicator()
{
    _cmc = new Communicator;
}

void EchooClient::Login(const QString &account, const QString &password)
{
    Netizen *user = nullptr;
    if (_dm->Contains(account)) {
        // user = _dm->GetNetizen(account);
        // if (user->LoginDetection(password)) {
        //     // 设置当前用户的Netizen为从数据管理层获取到的Netizen对象
        //     _user = user;
        //     emit loginSuccess(true);
        // }

        // 登录成功初始化p2p服务
        InitCommunicator();

        // 测试使用，直接触发成功信号
        emit loginSuccess(true);
    }
    emit loginSuccess(false);
}

void EchooClient::Register(const QString &nickName, const QString &account, const QString &password)
{
    if (_dm->Contains(account)) {
        // 如果数据库中已存在则返回注册失败
        emit registerSuccess(false);
        Logger::Error("Account " + account + " already exist.");
    }

    Netizen *newUser = new Netizen(nickName, account, password);
    _user = newUser; // 设置当前客户端的账号信息
    emit registerSuccess(true);
}

void EchooClient::SendMessage(Message *msg) {}

void EchooClient::SendGroupMessage(Message *msg, Group *group) {}
