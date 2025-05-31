#pragma once

#include <QString>
#include <QTcpSocket>

class Logger
{
public:
    static void Log(QString content);
    static void Error(QString content);
    static void Warning(QString content);
    static void Message(QString content, QTcpSocket *socket);
};
