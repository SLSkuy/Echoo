#pragma once

#include <QObject>
#include <QDateTime>

class Netizen;

class Message : public QObject
{
    Q_OBJECT
public:
    enum ReceiverType { Individual, Group };

    Message(Netizen *sender,
            QObject *receiver,
            const QString &content,
            const QDateTime &timestamp,
            QObject *parent = nullptr);

    Netizen *GetSender() { return m_sender; }
    QObject *GetReceiver() { return m_receiver; }
    QString GetMessage() { return m_content; }
    QDateTime GetMessageTime() { return m_timestamp; }

    // 使用Json作为消息传输媒介
    QByteArray ToJson();
    static Message *FromJson(const QByteArray &data);

private:
    Netizen *m_sender;
    QObject *m_receiver; // 可以是Netizen或Group
    QString m_content;
    QDateTime m_timestamp;
};
