#pragma once

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>

class Group;
class Message;

class Communicator : public QObject
{
    Q_OBJECT
public:
    Communicator();
    void BroadcastPresence(QJsonObject &obj);

    // 消息传输
    void SendMessage(Message *message);
    void SendGroupMessage(Message *message);

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);

private:
    QUdpSocket *m_udpSocket;
    QTcpServer *m_tcpServer;
    QTcpSocket *m_tcpClientSocket;
    quint16 m_udpPort;
    quint16 m_tcpPort;

    void OnUdpReadyRead();
    void OnNewTcpConnection();
};
