#pragma once

#include <QTcpSocket>

class EchooClient : public QObject
{
    Q_OBJECT
public:
    explicit EchooClient(QObject *parent = nullptr);
    ~EchooClient();
    Q_INVOKABLE void Login(QString account, QString password); // 暴露给qml使用
    Q_INVOKABLE void Register(QString nickName, QString account, QString password);
    Q_INVOKABLE void SendPrivateMessage(QString content, QString toAccount);

signals:
    void loginSuccess(bool result);
    void registerSuccess(bool result);
    void receiveMsg(QString content);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *_socket;

    // 账号信息
    QString m_nickName;
    QString m_account;
    QString m_password;
    QList<QString> m_friends; // friend's accounts
};
