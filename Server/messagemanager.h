// MessageManager类声明
// 该类作为一个服务类来使用
// 不占用过多资源，用作消息转发与处理

#pragma once

#include <QTcpSocket>
#include <QJsonObject>

#include "accountmanager.h"
#include "groupmanager.h"

class MessageManager
{
public:
    MessageManager();
    ~MessageManager();
    void DisconnectionProcess(QTcpSocket *socket);
    static void SendResponse(QTcpSocket *socket, bool result, QString &content, QString &type);
    // 命令处理
    void ProcessMessage(QTcpSocket *socket, const QByteArray &data);
    // 消息转发
    void PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content);
    void GroupMessageForwarding(QTcpSocket *socket, const QJsonObject &content);

private:
    AccountManager *_accounts; // 用于访问账户信息
    GroupManager *_groups;     // 用于访问群组信息
};
