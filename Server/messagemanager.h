// MessageManager类声明
// 该类作为一个服务类来使用
// 不占用过多资源，用作消息转发与处理

#pragma once

#include <QTcpSocket>
#include <QJsonObject>

#include "accountmanager.h"

class MessageManager
{
public:
    MessageManager(AccountManager *am);
    static void SendResponse(QTcpSocket *socket, bool result, QString &content);
    void PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content);
    void ProcessMessage(QTcpSocket *socket, const QByteArray &data);

private:
    // 用于访问账户信息
    AccountManager *_accounts;
};
