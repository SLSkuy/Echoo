// Tcp连接类
// 用于管理与其他客户端之间的Tcp连接

#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QByteArray>
#include <QObject>
#include <QJsonObject>

class Netizen;

class TcpManager : public QObject {
    Q_OBJECT
public:
    TcpManager(QObject *parent = nullptr);
    ~TcpManager();
    void onlineProcess(const QJsonObject &obj);
    void offlineProcess(const QJsonObject &obj);
    QTcpSocket *getSocket(const QString &account);

signals:
    void messageReceived(QTcpSocket *socket, const QByteArray &jsonData);
    void offlineMessageProcess(Netizen *user);

private slots:
    void onNewConnection();

private:
    QTcpServer *_tcpServer;
    quint16 m_tcpPort = 1145;
    QMap<QString, QTcpSocket *> m_sockets;
    QMap<QTcpSocket *, QByteArray> m_buffers;

    void connectProcess(const QString &account, const QString &ip);
    void byteArrayProcess(QTcpSocket *socket);
};
