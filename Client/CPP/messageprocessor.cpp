#include "messageprocessor.h"
#include "databasemanager.h"

MessageProcessor::MessageProcessor(QObject *parent): QObject(parent) {}

void MessageProcessor::messageProcess(QTcpSocket *socket, const QByteArray &jsonData)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isNull() && doc.isObject()) {
        Message *message = Message::FromJson(jsonData);
        QString type = doc["message_type"].toString();

        // 保存消息，接受的消息的sender即是此客户端的receiver
        QString sender = message->GetSender()->GetAccount();
        DatabaseManager::instance()->AddMessage(sender, message);

        // 触发消息接收信号
        if (type == "individual") {
            emit messageReceived(message);
        } else if (type == "group") {
            Group *group = qobject_cast<Group *>(message->GetReceiver());
            emit groupMessageReceived(group, message);
        } else if (type == "command") {
            emit commandReceived(message);
        } else if (type == "image") {
            emit imageReceived(message);
        }
    }
}
