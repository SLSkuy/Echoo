// UDP广播类
// 用于检测当前局域网内的在线用户
// 定时发送在线消息供局域网内其余用户获取在线信息

#pragma once

#include <QJsonObject>
#include <QUdpSocket>
#include <QDateTime>
#include <QObject>
#include <QTimer>
#include <QMap>

class Netizen;

class UdpBroadcaster : public QObject {
    Q_OBJECT
public:
    UdpBroadcaster(Netizen *netizen = nullptr);
    void startBroadcast();
    void checkTimeout();
    QString getLocalIP();

signals:
    void userOnline(const QJsonObject &user);
    void userOffline(const QJsonObject &user);

private slots:
    void onUdpReadyRead();

private:
    QUdpSocket *_udpSocket;
    QTimer *_timer;
    QMap<QString, QDateTime> m_lastInfo;
    quint16 m_udpPort = 1145;
    Netizen *_netizen;
};
