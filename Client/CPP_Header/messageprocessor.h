// 消息处理类
// 用于处理接收到的消息
// 并发出对应的信号

#pragma once

#include <QObject>
#include <QJsonObject>

class QTcpSocket;
class Message;
class Group;
class Netizen;

class MessageProcessor : public QObject {
    Q_OBJECT
public:
    MessageProcessor(QObject *parent = nullptr);
    void messageProcess(QTcpSocket *socket, const QByteArray &jsonData);

signals:
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);
    void commandReceived(Message *message);
    void imageReceived(Message *message);
};
