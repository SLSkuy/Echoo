#pragma once

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

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
    QString GetLocalIP();

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
    quint16 m_udpPort;
    quint16 m_tcpPort;

    QMap<QString, QTcpSocket *> m_sockets; // 记录当前在线的账号的TcpSocket连接

    void OnUdpReadyRead();
    void OnlineProcess(QJsonObject &obj);
    void OfflineProcess(QJsonObject &obj);
    void OnNewTcpConnection();
};
