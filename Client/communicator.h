#pragma once

#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>

class Communicator
{
public:
    Communicator();

private:
    QUdpSocket* m_udpSocket;
    QTcpSocket* m_tcpServer;
    QTcpSocket* m_tcpClientSocket;
    quint16 m_udpPort;
    quint16 m_tcpPort;
};
