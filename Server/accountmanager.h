// Echoo 账号管理模块
// 包含多种对账号管理方法
// 用户账号对象的创建等

#pragma once

#include <QTcpSocket>
#include <QJsonObject>
#include <QMap>

#include "echoouser.h"

class AccountManager
{
public:
    AccountManager();
    ~AccountManager();
    void RegisterUser(QTcpSocket *socket, const QJsonObject &content);
    void LoginDetection(QTcpSocket *socket, const QJsonObject &content);
    void ExitConnection(QTcpSocket *socket);
    void ResponseInfo(QTcpSocket *socket, const QJsonObject &content);
    QTcpSocket *GetSocket(QString &account);

private:
    QMap<QString, QTcpSocket *> *_sockets; // account -> socket 在线的所有用户
    QMap<QString, EchooUser *> *_accounts; // account -> EchooUser 注册的所有用户
};
