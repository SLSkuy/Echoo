#pragma once

#include <QString>

class Logger
{
public:
    static void Log(QString content);
    static void Error(QString content);
    static void Warning(QString content);
};
