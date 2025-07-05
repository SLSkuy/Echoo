// Logger类声明
// 该类用于格式化显示服务器信息

#pragma once

#include <QString>
#include <QTextStream>
#include <QIODevice>

class Logger
{
public:
    class Stream {
    public:
        Stream(void (*logFunction)(const QString&));
        ~Stream();

        template <typename T>
        Stream& operator<<(const T& value) {
            m_stream << value;
            return *this;
        }

    private:
        QString m_buffer;
        QTextStream m_stream;
        void (*m_logFunc)(const QString&);
    };

    static void Log(const QString &content);
    static void Error(const QString &content);
    static void Warning(const QString &content);

    static Stream log();
    static Stream warning();
    static Stream error();
};


