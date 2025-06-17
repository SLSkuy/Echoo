// Echoo 账号管理模块

#include <QJsonDocument>

#include "accountmanager.h"
#include "messagemanager.h"
#include "logger.h"

AccountManager::AccountManager()
    :_sockets(new QMap<QString, QTcpSocket *>)
    , _accounts(new QMap<QString, EchooUser *>)
{
    // 测试使用账号
    // 在线账号
    QString name = "SL_Skuy";
    QString account = "114514";
    QString account2 = "0721";

    EchooUser *user1 = new EchooUser(name, account, account);
    _accounts->insert("114514", user1);
    _sockets->insert("114514", nullptr);
    // 离线账号
    EchooUser *user2 = new EchooUser(name, account2, account2);
    _accounts->insert("0721", user2);
}

AccountManager::~AccountManager()
{
    for(auto it = _sockets->begin();it != _sockets->end();it++){
        delete it.value();
    }
    for(auto it = _accounts->begin();it != _accounts->end();it++){
        delete it.value();
    }
    delete _sockets;
    delete _accounts;
}

void AccountManager::RegisterUser(QTcpSocket *socket, const QJsonObject &content)
{
    // 用户注册
    QString nickName = content["nickName"].toString();
    QString account = content["account"].toString();
    QString password = content["password"].toString();
    QString type = content["type"].toString();

    QJsonObject obj; // 客户端返回Json对象
    obj["type"] = type;
    if (_accounts->contains(account)) {
        // 创建的用户已存在
        // 返回创建失败信息
        QString str = "Account " + account + " has already registered.";
        MessageManager::SendResponse(socket, false, str, type);

        Logger::Warning("Account " + account + " has already registered.");
        return;
    }

    // 记录用户信息
    EchooUser *newUser = new EchooUser(nickName, account, password);
    _accounts->insert(account, newUser);

    // 返回成功注册成功信息
    QString str = account + " register successfully, please log in.";
    MessageManager::SendResponse(socket, true, str, type);
    Logger::Log("Account " + account + " register successfully.");
}

void AccountManager::LoginDetection(QTcpSocket *socket, const QJsonObject &content)
{
    // 账号登录
    QString account = content["account"].toString();
    QString password = content["password"].toString();
    QString type = content["type"].toString();

    QJsonObject obj;
    obj["type"] = type;
    if (!_accounts->contains(account)) {
        // 不存在对应账号的用户
        QString str = "Account " + account + " is not exist, please register or check input account.";
        MessageManager::SendResponse(socket, false, str, type);

        Logger::Warning("No such account " + account + " exist.");
        return;
    }

    if (!(*_accounts)[account]->PasswordDetection(password)) {
        // 密码错误
        QString str = "Error password.";
        MessageManager::SendResponse(socket, false, str, type);

        Logger::Warning("error password");
        return;
    }

    if (_sockets->contains(account)) {
        // 当前账号已经登录
        QString str = "Account " + account + " has logged in, please don't log again.";
        MessageManager::SendResponse(socket, false, str, type);

        Logger::Warning("Account " + account + " has logged in.");
        return;
    }

    _sockets->insert(account, socket); // 记录账号在线

    QString str = "login successfully.";
    MessageManager::SendResponse(socket, true, str, type);
    Logger::Log("Account " + account + " login successfully.");
}

void AccountManager::ExitConnection(QTcpSocket *socket)
{
    // 断开连接
    QString userAccountToRemove; // 需要清除的用户的账号

    // 获取账号
    userAccountToRemove = _sockets->key(socket);

    if(!userAccountToRemove.isEmpty())
    {
        this->_sockets->remove(userAccountToRemove);
        Logger::Log("Account " + userAccountToRemove + " disconnected.");
    }

    // 释放空间
    socket->deleteLater();
}

QTcpSocket *AccountManager::GetSocket(QString &account)
{
    // 返回Socket用于消息转发
    if(_sockets->contains(account))
    {
        return (*_sockets)[account];
    }
    return nullptr;
}

void AccountManager::ResponseInfo(QTcpSocket *socket,const QJsonObject &content)
{
    // 回应客户端账号的各种信息
    QString account = content["account"].toString();

    // 委托获取账号信息
    QJsonObject obj = (*_accounts)[account]->GetUserInfo();
    QJsonDocument doc(obj);

    socket->write(doc.toJson());
}
