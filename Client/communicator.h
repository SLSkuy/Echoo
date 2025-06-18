#pragma once

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>

class Group;
class Message;
class Netizen;

class Communicator : public QObject
{
    Q_OBJECT
public:
    Communicator(Netizen *netizen);
    ~Communicator();
    void BroadcastPresence(QJsonObject &obj);

    // 消息传输
    void SendMessage(Message *message);
    void SendGroupMessage(Message *message);

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);

private:
    Netizen *_netizen;
    QUdpSocket *_udpSocket;
    QTcpServer *_tcpServer;
    QTcpSocket *_tcpClientSocket;
    quint16 m_udpPort;
    quint16 m_tcpPort;

    void OnUdpReadyRead();
    void OnlineProcess(QJsonObject &obj);
    void OfflineProcess(QJsonObject &obj);
    void OnNewTcpConnection();
};
