#pragma once

#include <QObject>
#include <QString>
#include <QDateTime>

class Message : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QString to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QDateTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(MessageType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(ObjectType objectType READ objectType WRITE setObjectType NOTIFY objectTypeChanged)

public:
    explicit Message(QObject *parent = nullptr);

    // 枚举类型定义
    enum MessageType { Text, Image, File };
    enum ObjectType { Private, Group };
    Q_ENUM(MessageType)
    Q_ENUM(ObjectType)

    // Getter方法 - 添加const修饰符
    QString from() const { return m_from; }
    QString to() const { return m_to; }
    QString content() const { return m_content; }
    QDateTime time() const { return m_time; }
    MessageType type() const { return m_type; }
    ObjectType objectType() const { return m_objectType; }

    // Setter方法
    void setFrom(const QString &from);
    void setTo(const QString &to);
    void setContent(const QString &content);
    void setTime(const QDateTime &time);
    void setType(MessageType type);
    void setObjectType(ObjectType objectType);

signals:
    void fromChanged();
    void toChanged();
    void contentChanged();
    void timeChanged();
    void typeChanged();
    void objectTypeChanged();

private:
    QString m_from;
    QString m_to;
    QString m_content;
    QDateTime m_time;
    MessageType m_type = Text;
    ObjectType m_objectType = Private;
};
