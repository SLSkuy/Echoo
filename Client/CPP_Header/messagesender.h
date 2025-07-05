// 消息发送类
// 用于进行消息发送

#pragma once
#include <QObject>
#include <QTcpSocket>

#include "message.h"

class TcpManager;

class MessageSender : public QObject {
    Q_OBJECT
public:
    MessageSender(TcpManager *tcpManager = nullptr);
    void sendMessage(Message *message);
    void sendGroupMessage(Message *message);
    void sendOfflineMessage(Netizen *user);

private:
    TcpManager *_tcpManager;
};
