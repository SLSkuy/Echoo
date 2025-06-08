// written by SL_Skuy
// Echoo服务后端类声明

#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QMap>

#include "accountmanager.h"

class EchooServer : public QTcpServer
{
    Q_OBJECT
public:
    EchooServer(QObject *parent = nullptr);
    ~EchooServer();
    static void SendResponse(QTcpSocket *socket, bool result, QString &content);
    bool StartServer(const QHostAddress &address, quint16 port);

protected:
    virtual void incomingConnection(qintptr socketDescriptor) override;

private:
    void ProcessMessage(QTcpSocket *socket, const QByteArray &data);
    void PrivateMessageForwarding(QTcpSocket *socket, const QJsonObject &content);

    AccountManager *_accounts;
};
