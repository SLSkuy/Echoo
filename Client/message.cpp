#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{
    m_time = QDateTime::currentDateTime();
}

void Message::setFrom(const QString &from)
{
    if (m_from != from) {
        m_from = from;
        emit fromChanged();
    }
}

void Message::setTo(const QString &to)
{
    if (m_to != to) {
        m_to = to;
        emit toChanged();
    }
}

void Message::setContent(const QString &content)
{
    if (m_content != content) {
        m_content = content;
        emit contentChanged();
    }
}

void Message::setTime(const QDateTime &time)
{
    if (m_time != time) {
        m_time = time;
        emit timeChanged();
    }
}

void Message::setType(MessageType type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged();
    }
}

void Message::setObjectType(ObjectType objectType)
{
    if (m_objectType != objectType) {
        m_objectType = objectType;
        emit objectTypeChanged();
    }
}
