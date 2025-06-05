// written by SL_Skuy
// Echoo服务后端类声明
// 包括服务端的启动，信息转发，用户创建删除等功能

#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QMap>

#include "echoouser.h"

class EchooServer : public QTcpServer
{
    Q_OBJECT
public:
    EchooServer(QObject *parent = nullptr);
    ~EchooServer();
    bool StartServer(const QHostAddress &address, quint16 port);

protected:
    virtual void incomingConnection(qintptr socketDescriptor) override;

private:
    void ProcessMessage(QTcpSocket *socket, const QByteArray &data);
    void SendResponse(QTcpSocket *socket, bool result, QString &content);
    void RegisterUser(QTcpSocket *socket, const QJsonObject &content);
    void LoginDetection(QTcpSocket *socket, const QJsonObject &content);
    void PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content);

    QMap<QString, QTcpSocket *> *_sockets; // account -> socket 在线的所有用户
    QMap<QString, EchooUser *> *_accounts; // account -> EchooUser 注册的所有用户
};
