#pragma once

#include <QUdpSocket>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QTimer>

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
    void SendPeriodicOnlineBroadcast();
    void CheckUserTimeout();
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
    void imageReceived(Message *message);

private:
    Netizen *_netizen;
    QUdpSocket *_udpSocket; // 用于广播通信
    QTcpServer *_tcpServer; // 用于接收其他客户端程序的连接
    quint16 m_udpPort;
    quint16 m_tcpPort;
    QTimer *_timer;

    QMap<QString, QTcpSocket *> m_sockets; // 记录当前在线的账号的TcpSocket连接
    QMap<QTcpSocket *, QByteArray> m_buffers; // TcpSocket缓冲
    QMap<QString, QDateTime> m_lastSeen; // 最后一次在线时间

    void OnUdpReadyRead();                                          // UDP处理
    void OnNewTcpConnection();                                      // TCP处理
    void OnlineProcess(QJsonObject &obj);                           // 上线消息处理
    void OfflineProcess(QJsonObject &obj);                          // 离线消息处理
    void ConnectProcess(const QString &account, const QString &ip); // 与对应账号建立TCP连接用于后续消息发送传输等
};
