#pragma once

#include <QObject>
#include <QString>

class Group;
class Message;
class Netizen;
class MessageSender;
class MessageProcessor;
class TcpManager;
class UdpBroadcaster;

class Communicator : public QObject
{
    Q_OBJECT
public:
    Communicator(Netizen *user);
    ~Communicator();

    // 消息发送
    void sendMessage(Message *message);
    void sendGroupMessage(Message *message);

    // IP相关
    QString getLocalIP();

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);
    void commandReceived(Message *message);
    void imageReceived(Message *message);

private:
    Netizen *_user;
    MessageSender *_msgSender;
    MessageProcessor *_msgProcessor;
    TcpManager *_tm;
    UdpBroadcaster *_ub;

    void signalsConnect();
};
