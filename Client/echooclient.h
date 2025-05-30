#pragma once

#include <QTcpSocket>

class EchooClient : public QObject
{
    Q_OBJECT
public:
    EchooClient(QObject *parent = nullptr);
    ~EchooClient();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();

private:
    QTcpSocket *_socket;
};
