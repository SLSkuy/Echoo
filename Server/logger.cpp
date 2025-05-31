#include "logger.h"

#include <QDebug>
#include <QTime>

void Logger::Log(QString content)
{
    qDebug().noquote() << "[INFO" << QTime::currentTime().toString("HH:mm:ss") + "] " + content;
}

void Logger::Error(QString content)
{
    qDebug().noquote() << "[ERROR" << QTime::currentTime().toString("HH:mm:ss") + "] " + content;
}

void Logger::Warning(QString content)
{
    qDebug().noquote() << "[WARNING" << QTime::currentTime().toString("HH:mm:ss") + "] " + content;
}
