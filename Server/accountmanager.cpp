// Echoo 账号管理模块

#include "accountmanager.h"
#include "echooserver.h"
#include "logger.h"

AccountManager::AccountManager()
    :_sockets(new QMap<QString, QTcpSocket *>)
    , _accounts(new QMap<QString, EchooUser *>)
{
    // 测试使用账号
    // 在线账号
    EchooUser *user1 = new EchooUser("SL_Skuy", "114514", "114514");
    _accounts->insert("114514", user1);
    _sockets->insert("114514", nullptr);
    // 离线账号
    EchooUser *user2 = new EchooUser("SL_Skuy", "0721", "0721");
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
    QString nickName = content["nickName"].toString();
    QString account = content["account"].toString();
    QString password = content["password"].toString();

    QJsonObject obj; // 客户端返回Json对象
    obj["type"] = "register";
    if (_accounts->contains(account)) {
        // 创建的用户已存在
        // 返回创建失败信息
        QString str = "Account " + account + " has already registered.";
        EchooServer::SendResponse(socket, false, str);

        Logger::Warning("Account " + account + " has already registered.");
        return;
    }

    // 记录用户信息
    EchooUser *newUser = new EchooUser(nickName, account, password);
    _accounts->insert(account, newUser);

    // 返回成功注册成功信息
    QString str = account + " register successfully, please log in.";
    EchooServer::SendResponse(socket, true, str);
    Logger::Log("Account " + account + " register successfully.");
}

void AccountManager::LoginDetection(QTcpSocket *socket, const QJsonObject &content)
{
    QString account = content["account"].toString();
    QString password = content["password"].toString();

    QJsonObject obj;
    obj["type"] = "login";
    if (!_accounts->contains(account)) {
        // 不存在对应账号的用户
        QString str = "Account " + account + " is not exist, please register or check input account.";
        EchooServer::SendResponse(socket, false, str);

        Logger::Warning("No such account " + account + " exist.");
        return;
    }

    if (!(*_accounts)[account]->PasswordDetection(password)) {
        // 密码错误
        QString str = "Error password.";
        EchooServer::SendResponse(socket, false, str);

        Logger::Warning("error password");
        return;
    }

    if (_sockets->contains(account)) {
        // 当前账号已经登录
        QString str = "Account " + account + " has logged in, please don't log again.";
        EchooServer::SendResponse(socket, false, str);

        Logger::Warning("Account " + account + " has logged in.");
        return;
    }

    _sockets->insert(account, socket); // 记录账号在线
    QString str = "login successfully.";
    EchooServer::SendResponse(socket, true, str);
    Logger::Log("Account " + account + " login successfully.");
}

void AccountManager::ExitConnection(QTcpSocket *socket)
{
    QString userAccountToRemove; // 需要清除的用户的账号

    // 获取账号
    for (auto it = this->_sockets->begin(); it != this->_sockets->end(); it++) {
        if(it.value() == socket)
        {
            userAccountToRemove = it.key();
            break;
        }
    }

    if(!userAccountToRemove.isEmpty())
    {
        this->_sockets->remove(userAccountToRemove);
        Logger::Log("Account " + userAccountToRemove + " disconnected.");
    }

    // 释放空间
    socket->deleteLater();
}

QTcpSocket *AccountManager::GetSocket(QString account)
{
    for(auto it = _sockets->begin();it != _sockets->end();it++){
        if(it.key() == account && it.value() != nullptr){
            return it.value();
        }
    }
    return nullptr;
}
