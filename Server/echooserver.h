// written by SL_Skuy
// Echoo服务后端类声明
// 包括服务端的启动，信息转发，用户创建删除等功能

#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class EchooServer : public QTcpServer
{
    Q_OBJECT
public:
    EchooServer(QObject *parent = nullptr);
    ~EchooServer();
    bool StartServer(const QHostAddress &address,quint16 port);

protected:
    virtual void incomingConnection(qintptr socketDescriptor) override;

private:
    QString ServerInfo(int type);
    void ProcessMessage(QTcpSocket *socket, const QByteArray &data);
    void SendResponse(QTcpSocket *socket);

    QMap<QString, QTcpSocket *> *_sockets; // account -> socket
    QMap<QString, QString> *_accounts;     // account -> password
};
