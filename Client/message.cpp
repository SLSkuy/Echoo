#include "message.h"
#include <QDataStream>

Message::Message(Netizen *sender, QObject *receiver, const QString &content, const QDateTime &timestamp, QObject *parent)
    : QObject(parent)
    , m_sender(sender)
    , m_receiver(receiver)
    , m_content(content)
    , m_timestamp(timestamp)
{}
