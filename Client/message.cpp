#include <QJsonObject>

#include "message.h"
#include "netizen.h"
#include "logger.h"
#include "group.h"

Message::Message(Netizen *sender, QObject *receiver, const QString &content, const QDateTime &timestamp, QObject *parent)
    : QObject(parent)
    , m_sender(sender)
    , m_receiver(receiver)
    , m_content(content)
    , m_timestamp(timestamp)
{}

QByteArray Message::ToJson()
{
    QJsonObject json;

    // 发送者消息获取
    json["sender_account"] = m_sender->GetAccount();
    json["sender_nickname"] = m_sender->GetNickname();

    // 进行类型转换，检测是发送群消息还是私聊
    if (auto user = qobject_cast<Netizen *>(m_receiver)) {
        json["receiver_type"] = "individual";
        json["receiver_account"] = user->GetAccount();
    } else if (auto group = qobject_cast<class Group *>(m_receiver)) {
        json["receiver_type"] = "group";
        json["receiver_account"] = group->GetGroupAccount();
    } else {
        json["receiver_type"] = "unknown";
    }

    json["content"] = m_content;
    json["timestamp"] = m_timestamp.toString();

    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Compact);
}

Message* Message::FromJson(const QByteArray &jsonData)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        Logger::Warning("JSON parse error:" + err.errorString());
        return nullptr;
    }

    QJsonObject json = doc.object();

    QString senderAccount = json["sender_account"].toString();
    QString senderNickname = json["sender_nickname"].toString();

    QString receiverType = json["receiver_type"].toString();
    QObject *receiver = nullptr;

    if (receiverType == "individual") {
        QString recvAccount = json["receiver_account"].toString();
        receiver = new Netizen("匿名", recvAccount, "", nullptr);
    } else if (receiverType == "group") {
        QString groupName = json["receiver_name"].toString();
        receiver = new class Group(groupName, groupName, nullptr);
    }

    QString content = json["content"].toString();
    QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);

    Netizen *sender = new Netizen(senderNickname, senderAccount, "", nullptr);
    return new Message(sender, receiver, content, timestamp);
}
