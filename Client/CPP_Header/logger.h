// Logger类声明
// 该类用于格式化显示服务器信息

#pragma once

#include <QString>
#include <QTcpSocket>

class Logger
{
public:
    static void Log(const QString &content);
    static void Error(const QString &content);
    static void Warning(const QString &content);
    static void Message(const QString &content, QTcpSocket *socket);
};
