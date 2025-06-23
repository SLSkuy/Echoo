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
    // UDP广播通信
    void BroadcastPresence(QJsonObject &obj);
    QString GetLocalIP();

    // 消息传输与处理
    void SendMessage(Message *message);
    void SendGroupMessage(Message *message);
    void OnlineMessageProcess(QTcpSocket *socket);
    void OfflineMessageProcess(Netizen *user);

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);
    void commandReceived(Message *message);

private:
    Netizen *_netizen;
    QUdpSocket *_udpSocket; // 用于广播通信
    QTcpServer *_tcpServer; // 用于接收其他客户端程序的连接
    quint16 m_udpPort;
    quint16 m_tcpPort;

    QMap<QString, QTcpSocket *> m_sockets; // 记录当前在线的账号的TcpSocket连接
    QMap<QTcpSocket *, QByteArray> m_buffers; // TcpSocket缓冲

    void OnUdpReadyRead();
    void OnNewTcpConnection();
    void OnlineProcess(QJsonObject &obj);
    void OfflineProcess(QJsonObject &obj);
    void ConnectProcess(const QString &account, const QString &ip);
};
