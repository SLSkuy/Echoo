#include <QJsonObject>
#include <QFile>

#include "databasemanager.h"
#include "message.h"
#include "logger.h"
#include "group.h"

Message::Message(QObject *parent): QObject(parent){}
Message::Message(Netizen *sender,
                 QObject *receiver,
                 const QString &content,
                 const QDateTime &timestamp,
                 MessageType mType,
                 QObject *parent)
    : QObject(parent)
    , m_sender(sender)
    , m_receiver(receiver)
    , m_content(content)
    , m_timestamp(timestamp)
    , m_messageType(mType)
{}

QByteArray Message::ToJson()
{
    QJsonObject json;

    // 进行类型转换，检测是发送群消息还是私聊
    if (auto user = qobject_cast<Netizen *>(m_receiver)) {
        json["message_type"] = "individual";
        json["receiver_account"] = user->GetAccount();
    } else if (auto group = qobject_cast<class Group *>(m_receiver)) {
        json["message_type"] = "group";
        json["receiver_account"] = group->GetGroupAccount();
    } else {
        // 错误的消息类型，返回空
        json["message_type"] = "unknown";
        Logger::Error("Unknown message type.");
        return NULL;
    }

    // 设置键值对
    json["sender_account"] = m_sender->GetAccount();
    json["content"] = m_content;
    json["timestamp"] = m_timestamp.toString();

    // 设置消息类型
    if (m_messageType == Command) {
        json["message_type"] = "command";
    } else if (m_messageType == Image) {
        json["message_type"] = "image";
        json["content"] = GetImageData();
        // 使用base64进行图片传递
    }

    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Compact);
}

Message* Message::FromJson(const QByteArray &jsonData)
{
    // 反序列化字节流获取Json对象
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(jsonData, &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject()) {
        Logger::Warning("JSON parse error:" + err.errorString());
        return nullptr;
    }
    QJsonObject json = doc.object();

    // 读取Json对象数据
    QString senderAccount = json["sender_account"].toString();
    QString receiverAccount = json["receiver_account"].toString();
    QString messageType = json["receiver_type"].toString();
    QString content = json["content"].toString();
    QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);

    // 创建Message类
    QObject *receiver = nullptr;
    Netizen *sender = DatabaseManager::instance()->GetNetizen(senderAccount);
    if (messageType == "individual") {
        receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    } else if (messageType == "group") {
        receiver = DatabaseManager::instance()->GetGroup(receiverAccount);
    } else if (messageType == "command") {
        receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
        return new Message(sender, receiver, content, timestamp, Command);
    } else if (messageType == "image") {
        receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
        return new Message(sender, receiver, content, timestamp, Image);
    }

    return new Message(sender, receiver, content, timestamp);
}

bool Message::LoadImage()
{
    if (m_content.startsWith("file:///")) {
        m_content = QUrl(m_content).toLocalFile();
    }

    QFile file(m_content);
    if (!file.open(QIODevice::ReadOnly)) {
        Logger::Error("Can't open image: " + m_content);
        return false;
    }

    m_imageData = file.readAll();
    file.close();

    if (m_imageData.isEmpty()) {
        Logger::Error("Empty image: " + m_content);
        return false;
    }

    // 将内容设置为图片转换为base64格式的数据
    m_content = GetImageData();

    return true;
}
