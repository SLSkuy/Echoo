#include "messagesender.h"
#include "databasemanager.h"
#include "tcpmanager.h"

MessageSender::MessageSender(TcpManager *tcpManager): QObject(tcpManager),_tcpManager(tcpManager) {}

void MessageSender::sendMessage(Message *message)
{
    QString receiverAccount = qobject_cast<Netizen *>(message->getReceiver())->getAccount();

    QTcpSocket *socket = _tcpManager->getSocket(receiverAccount);
    if (socket) {
        // 消息序列化
        QByteArray json = message->ToJson();

        // 写入4字节长度前缀，解决粘包问题
        QByteArray packet;
        QDataStream stream(&packet, QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::BigEndian);
        stream << (quint32) json.size();
        packet.append(json);

        socket->write(packet);
        DatabaseManager::instance()->AddMessage(receiverAccount, message);
    } else {
        // 用户当前不在线
        DatabaseManager::instance()->AddOfflineMessage(message);
    }
}

void MessageSender::sendGroupMessage(Message *msg) {}

void MessageSender::sendOfflineMessage(Netizen *user)
{
    // 获取所有离线消息
    QList<Message *> offlines = DatabaseManager::instance()->GetOfflineMessages();
    QList<Message *> toRemove; // 记录已经发送的离线消息
    for (QList<Message *>::iterator it = offlines.begin(); it != offlines.end(); ++it) {
        if (auto receiver = qobject_cast<Netizen *>((*it)->getReceiver())) {
            if (receiver == user) {
                qDebug() << "Sending offline message to user:" << user->getAccount()
                << "content:" << (*it)->getMessage();
                sendMessage(*it);
                toRemove.append(*it);
            }
        }
    }
    for (QList<Message *>::iterator it = toRemove.begin(); it != toRemove.end(); ++it) {
        if ((*it)->getReceiver() == user) {
            offlines.removeOne(*it); // 删除已经发送的离线消息
        }
    }
    // 更新离线消息
    DatabaseManager::instance()->UpdateOfflineMessages(offlines);
}
