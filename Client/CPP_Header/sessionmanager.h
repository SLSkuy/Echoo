// 通信连接类
// 用于登录检测、服务器连接、信息接收等操作

#pragma once

#include <QObject>
#include <QString>

class Netizen;
class Communicator;
class Message;
class Group;

class SessionManager : public QObject {
    Q_OBJECT
public:
    SessionManager(QString account,QString password,Netizen *parent = nullptr);
    ~SessionManager();

    // 在线操作
    Communicator *login(const QString &password);
    void logout() { m_isOnline = false; }

    // 属性获取
    QString getAccount() { return m_account; }
    QString getPassword() { return m_password; }
    bool isOnline() { return m_isOnline; }
    QString ipAddress() { return m_ip; }
    QString getLocalIP();

    // 属性设置
    void setOnline(bool online);
    void setIpAddress(const QString &ip);

signals:
    void onlineChanged(bool isOnline);
    void ipChanged();
    void messageReceived(Message *message);
    void groupMessageReceived(Group *group, Message *message);
    void commandReceived(Message *message);
    void imageReceived(Message *message);

private:
    QString m_account;
    QString m_password;
    QString m_ip;
    bool m_isOnline;

    Netizen *_owner;
    Communicator *_cmc;
};

