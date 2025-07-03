#pragma once

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QMap>
#include <QDebug>
#include <QtQml/qqmlregistration.h>

class Group;
class Communicator;
class Message;

class Netizen : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString nickname READ GetNickname WRITE SetNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString account READ GetAccount CONSTANT)
    Q_PROPERTY(bool online READ IsOnline NOTIFY onlineChanged)
    Q_PROPERTY(QString ipAddress READ GetIpAddress WRITE SetIpAddress NOTIFY ipChanged)
    Q_PROPERTY(QString sign READ GetSign WRITE SetSign NOTIFY signChanged FINAL)
    Q_PROPERTY(QString avatar READ getAvatar WRITE updateAvatar NOTIFY avatarChanged FINAL)
public:
    explicit Netizen(QObject *parent = nullptr);
    Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent = nullptr);
    ~Netizen();

    // 用户属性获取，用户数据库信息存储
    QString GetPassword() {return m_password;}
    QString GetNickname()  { return m_nickName; }
    QString GetAccount()  { return m_account; }
    QString GetIpAddress()  { return m_ip; }
    bool IsOnline() const { return m_isOnline; }
    void SetNickname(QString nickname)
    {
        if (nickname != m_nickName) {
            m_nickName = nickname;
            emit nicknameChanged();
            qDebug() << "update nickname";
        }
    }
    void SetIpAddress(QString ip) { m_ip=ip; }
    void SetOnline(bool result) { m_isOnline=result; }
<<<<<<< HEAD
    bool IsOnline() const { return m_isOnline; }
    Q_INVOKABLE QString GetSign() { return m_sign; }
    Q_INVOKABLE void SetSign(QString sign)
=======
    QString GetSign() { return m_sign; }
    void SetSign(QString sign)
>>>>>>> origin/Client-Logic
    {
        if (sign != m_sign) {
            m_sign = sign;
            emit signChanged();
<<<<<<< HEAD
            qDebug() << "update sign";
            qDebug() << m_sign;
=======
>>>>>>> origin/Client-Logic
        }
    }

    // 头像
    Q_INVOKABLE void setAvatar(const QString &filePath);
    void updateAvatar(const QString &base64Form) { m_avatar = base64Form; }
    QString getAvatar() { return m_avatar; }

    // 账号功能
    QList<QString> GetFriendsAccount() { return m_friends.keys(); }
    Q_INVOKABLE QVariantList getFriends();
    Q_INVOKABLE QVariantList getGroups();
    bool LoginDetection(const QString &password);

    // 好友管理
    bool AddFriend(Netizen *user);
    bool RemoveFriend(const QString &account);
    void RemoveFriendRequest(const QString &account);
    void AddFriendRequest(const QString &account);
    void AddFriendResponse(const QString &account, const bool result);
    bool HasFriend(const QString &account) { return m_friends.contains(account); }

    // 消息功能
    void SendMessage(const QString &receiverAccount, const QString &content);
    void SendGroupMessage(const QString &groupAccount, const QString &content);
    void SendImage(const QString &receiverAccount, const QString &imgPath);

    // 群组功能
    bool CreateGroup(const QString &name, const QString &owner);
    bool JoinGroup(Group *group);
    bool LeaveGroup(Group *group);
    bool HasGroup(const QString &account) { return m_groups.contains(account); }

signals:
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);
    void imgReceived(Message *msg);
    void receivedFriendRequest(Netizen *newFriend);
    void receivedFriendResponse(Netizen *newFriend, const bool result);
    void removeFriendSignal(const QString &account);
    void nicknameChanged();
    void onlineChanged();
    void ipChanged();
    void signChanged();
    void avatarChanged();
    void removefriendList(Netizen *notFriend);
    void removemessagList(Netizen *notFriend);

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    bool m_isOnline;
    QString m_avatar; // 使用base64存储的头像信息
    QString m_sign;

    QMap<QString, Netizen *> m_friends;
    QMap<QString, Group *> m_groups;

    // p2p服务
    Communicator *_cmc;
    QString m_ip;

    void CommandProcess(Message *msg);
};
