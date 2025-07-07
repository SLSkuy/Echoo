// 聊天操作类
// 用于处理好友关系、群聊关系、发送消息、命令处理等操作

#include <QObject>
#include <QMap>

class Netizen;
class Group;
class Message;
class Communicator;

class ChatOperation : public QObject
{
    Q_OBJECT
public:
    ChatOperation(Communicator *cmc,Netizen *owner = nullptr);

    // 消息功能
    void sendMessage(const QString &receiverAccount, const QString &content);
    void sendGroupMessage(const QString &groupAccount, const QString &content);
    void sendImage(const QString &receiverAccount, const QString &imgPath);
    void commandProcess(Message *msg);

    // 好友管理
    bool addFriend(Netizen *user);
    bool removeFriend(const QString &account);
    void removeFriendRequest(const QString &account);
    void addFriendRequest(const QString &account);
    void addFriendResponse(const QString &account, const bool result);
    bool hasFriend(const QString &account) { return m_friends.contains(account); }
    QList<Netizen *> getFriends() { return m_friends.values(); }
    QList<QString> getFriendsAccount() { return m_friends.keys();}

    // 群组管理
    bool createGroup(const QString &name, const QString &owner) {return false;}
    bool joinGroup(Group *group) {return false;}
    bool leaveGroup(Group *group) {return false;}
    bool hasGroup(const QString &account) { return m_groups.contains(account); }
    QList<Group *> getGroups() { return m_groups.values(); }

signals:
    void receivedFriendRequest(Netizen *newFriend);
    void receivedFriendResponse(Netizen *newFriend,bool result);

private:
    QMap<QString, Netizen *> m_friends;
    QMap<QString, Group *> m_groups;

    Netizen *_owner;
    Communicator *_cmc;
};

