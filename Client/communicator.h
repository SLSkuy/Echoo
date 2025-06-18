#pragma once

#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>

#include "message.h"
#include "group.h"

class Communicator : public QObject
{
    Q_OBJECT
public:
    Communicator();

    // 消息传输
    void SendMessage(Message *message);
    void SendGroupMessage(Message *message);

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);

private:
    QUdpSocket* m_udpSocket;
    QTcpSocket* m_tcpServer;
    QTcpSocket* m_tcpClientSocket;
    quint16 m_udpPort;
    quint16 m_tcpPort;
};
