#include "databasemanager.h"
// #include "communicator.h"
#include "echooclient.h"
#include "netizen.h"
#include "message.h"
#include "group.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent)
{
    _dm = new DatabaseManager;
}

EchooClient::~EchooClient()
{
    delete _dm;
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

        // 测试使用，直接触发成功信号
        emit loginSuccess(true);
    }
    emit loginSuccess(false);
}

void EchooClient::Register(const QString &nickName, const QString &account, const QString &password)
{
    // Netizen *newUser = new Netizen(nickName, account, password);
    emit registerSuccess(true);
}

void EchooClient::SendMessage(Message *msg) {}

void EchooClient::SendGroupMessage(Message *msg, Group *group) {}
