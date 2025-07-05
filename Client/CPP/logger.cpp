#include <QDebug>
#include <QDateTime>

#include "logger.h"

void Logger::Log(const QString &content) {
    qDebug().noquote() << "[Info" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "]" << content;
}

void Logger::Error(const QString &content) {
    qDebug().noquote() << "[Error" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "]" << content;
}

void Logger::Warning(const QString &content) {
    qDebug().noquote() << "[Warning" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "]" << content;
}

Logger::Stream::Stream(void (*logFunc)(const QString&))
    : m_stream(&m_buffer, QIODevice::WriteOnly), m_logFunc(logFunc)
{}

Logger::Stream::~Stream() {
    if (m_logFunc) {
        m_logFunc(m_buffer);
    }
}

Logger::Stream Logger::log() {
    return Stream(&Logger::Log);
}

Logger::Stream Logger::warning() {
    return Stream(&Logger::Warning);
}

Logger::Stream Logger::error() {
    return Stream(&Logger::Error);
}
