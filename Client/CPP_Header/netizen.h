#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>

class UserProfileManager;
class SessionManager;
class ChatOperation;
class Message;
class Group;

class Netizen : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString nickname READ getNickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString account READ getAccount CONSTANT)
    Q_PROPERTY(bool online READ isOnline NOTIFY onlineChanged)
    Q_PROPERTY(QString ipAddress READ getIpAddress WRITE setIpAddress NOTIFY ipChanged)
    Q_PROPERTY(QString sign READ getSign WRITE setSign NOTIFY signChanged)
    Q_PROPERTY(QString avatar READ getAvatar WRITE updateAvatar NOTIFY avatarChanged)

public:
    explicit Netizen(QObject *parent = nullptr);
    Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent = nullptr);
    ~Netizen();

    // 账号操作
    bool LoginDetection(const QString &password);
    void Logout();
    Q_INVOKABLE QVariantList getFriends();
    QList<QString> GetFriendsAccount();
    Q_INVOKABLE QVariantList getGroups();

    // 消息操作
    void sendMessage(const QString &receiverAccount, const QString &content);
    void sendGroupMessage(const QString &groupAccount, const QString &content);
    void sendImage(const QString &receiverAccount, const QString &imgPath);

    // 属性获取
    QString getNickname();
    QString getAccount();
    QString getPassword();
    bool isOnline();
    QString getIpAddress();
    QString getSign();
    QString getAvatar();    // 只有一处引用时可以是直接通过avatar属性获取头像，否则使用临时文件
    Q_INVOKABLE QString getAvatarTmpFile();

    // 属性更新
    void setNickname(const QString &nickname);
    void setIpAddress(const QString &ip);
    void setSign(const QString &sign);
    void setOnline(const bool online);
    void updateAvatar(const QString &base64);
    Q_INVOKABLE void setAvatar(const QString &filePath);

    // 好友管理
    bool addFriend(Netizen *user);
    bool removeFriend(const QString &account);
    void removeFriendRequest(const QString &account);
    void addFriendRequest(const QString &account);
    void addFriendResponse(const QString &account, const bool result);
    bool hasFriend(const QString &account);

    // 群组功能
    bool createGroup(const QString &name, const QString &owner);
    bool joinGroup(Group *group);
    bool leaveGroup(Group *group);
    bool hasGroup(const QString &account);

signals:
    // 属性变更
    void nicknameChanged();
    void onlineChanged();
    void ipChanged();
    void signChanged();
    void avatarChanged();
    // 消息接收
    void messageReceived(Message *msg);
    void groupMessageReceived(Group *group, Message *msg);
    void imgReceived(Message *msg);
    void receivedFriendRequest(Netizen *newFriend);
    void receivedFriendResponse(Netizen *newFriend, const bool result);

private:
    UserProfileManager *_upm;
    SessionManager *_sm;
    ChatOperation *_co;

    void signalConnect();
};
