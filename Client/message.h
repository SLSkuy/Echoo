#pragma once

#include <QObject>
#include <QDateTime>
#include "netizen.h"

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

    // 序列化方法
    QByteArray serialize() const;
    static Message *deserialize(const QByteArray &data);

private:
    Netizen *m_sender;
    QObject *m_receiver; // 可以是Netizen或Group
    QString m_content;
    QDateTime m_timestamp;
};
