#pragma once

#include <QObject>
#include <QDateTime>
#include <QtQml/qqmlregistration.h>

#include "netizen.h"

class Message : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString content READ GetMessage NOTIFY contentChanged)
    Q_PROPERTY(QString timestamp READ GetMessageTime NOTIFY timestampChanged)
    Q_PROPERTY(Netizen* sender READ GetSender NOTIFY senderChanged FINAL)
    Q_PROPERTY(QObject *receiver READ GetReceiver NOTIFY receiverChanged)
public:
    enum MessageType { Text, Command, Image };

    explicit Message(QObject *parent = nullptr);
    Message(Netizen *sender,
            QObject *receiver,
            const QString &content,
            const QDateTime &timestamp,
            MessageType mType = Text,
            QObject *parent = nullptr);

    // 消息内容相关
    Netizen *GetSender() { return m_sender; }
    QObject *GetReceiver() { return m_receiver; }
    QString GetMessage() { return m_content; }
    QString GetMessageTime() { return m_timestamp.toString(); } // 返回字符串格式的时间
    QDateTime GetTime() { return m_timestamp; }                 // 返回时间戳
    int GetMessageType() { return m_messageType; }
    QString GetImageData() const { return m_imageData.toBase64(); } // 获取base64编码图片
    bool LoadImage();                                               // 将本地图片转换为base64编码图片

    // 使用Json作为消息传输媒介
    QByteArray ToJson();                              // 序列化
    static Message *FromJson(const QByteArray &data); // 反序列化

signals:
    void contentChanged();
    void timestampChanged();
    void receiverChanged();
    void senderChanged();

private:
    Netizen *m_sender = nullptr;
    QObject *m_receiver = nullptr; // 可以是Netizen或Group
    QString m_content;
    QDateTime m_timestamp;
    QByteArray m_imageData = NULL; // 若传输图片时启用
    MessageType m_messageType = Text;
};
