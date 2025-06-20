#pragma once

#include <QObject>
#include <QDateTime>

#include "netizen.h"

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString content READ GetMessage NOTIFY contentChanged)
    Q_PROPERTY(QDateTime timestamp READ GetMessageTime NOTIFY timestampChanged)
    Q_PROPERTY(Netizen* sender READ GetSender NOTIFY senderChanged FINAL)
    Q_PROPERTY(QObject* receiver READ GetReceiver NOTIFY receiverChanged)
public:
    enum ReceiverType { Individual, GroupMsg };
    enum MessageType { Text, Command };
    Q_ENUM(ReceiverType)

    explicit Message(QObject *parent = nullptr);
    Message(Netizen *sender,
            QObject *receiver,
            const QString &content,
            const QDateTime &timestamp,
            ReceiverType rType = Individual,
            MessageType mType = Text,
            QObject *parent = nullptr);

    QString GetMessage() { return m_content; }
    QObject *GetReceiver() { return m_receiver; }
    QDateTime GetMessageTime() { return m_timestamp; }
    Netizen *GetSender()  { return m_sender; }
    void setSender(Netizen *sender) { m_sender = sender; }

    // 使用Json作为消息传输媒介
    QByteArray ToJson();
    static Message *FromJson(const QByteArray &data);

signals:
    void contentChanged();
    void timestampChanged();
    void receiverChanged();
    void senderChanged();

private:
    Netizen *m_sender = nullptr;
    QObject *m_receiver = nullptr; // 可以是Netizen或Group
    QString m_content;
    QDateTime m_timestamp;
    ReceiverType m_receiverType = Individual;
    MessageType m_messageType = Text;
};
