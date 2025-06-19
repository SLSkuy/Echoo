#pragma once

#include <QTcpSocket>
#include <QDateTime>

class Message;
class Netizen;
class Group;

class EchooClient : public QObject
{
    Q_OBJECT
public:
    explicit EchooClient(QObject *parent = nullptr);
    ~EchooClient();

    // 账号功能
    Q_INVOKABLE void Login(const QString &account, const QString &password); // 暴露给qml使用
    Q_INVOKABLE void Register(const QString &nickName, const QString &account, const QString &password);

    // 消息功能
    Q_INVOKABLE void SendMessage(const QString &receiverAccount, const QString &content)
    {
        emit triggerMessage(receiverAccount, content);
    }
    Q_INVOKABLE void SendGroupMessage(const QString &groupAccount, const QString &content)
    {
        emit triggerGroupMessage(groupAccount, content);
    }

signals:
    // 消息发送信号
    void triggerMessage(QString receiverAccount, QString content);
    void triggerGroupMessage(QString groupAccount, QString content);
    // 账号处理信号
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    // 消息处理信号
    void processedMessageReceived(QString account, QString content, QDateTime time);
    void processedGroupMessageReceived(QString account, QString content, QDateTime time);

private:
    Netizen *_user;
};
