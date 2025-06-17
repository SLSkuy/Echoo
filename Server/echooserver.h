// Echoo服务后端类声明

#pragma once

#include <QTcpServer>
#include <QMap>

#include "messagemanager.h"

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
    MessageManager *_mm;
};
