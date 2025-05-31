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

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *_socket;
};
