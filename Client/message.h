#pragma once

#include <QString>
#include <QDateTime>

class Message
{
public:
    enum MessageType { text, image, file };
    Message();

private:
    QString m_from;
    QString m_to;
    QString m_content;
    QDateTime m_time;
    MessageType m_type;
};
