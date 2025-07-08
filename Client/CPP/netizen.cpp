#include <qvariant.h>
#include <QCryptographicHash>

#include "group.h"
#include "netizen.h"
#include "userprofilemanager.h"
#include "sessionmanager.h"
#include "chatoperation.h"
#include "communicator.h"

Netizen::Netizen(QObject *parent) : QObject(parent) {}
Netizen::Netizen(const QString &nickname, const QString &account, const QString &password, QObject *parent)
{
    // 初始化用户资料
    _upm = new UserProfileManager(nickname,this);
    _sm = new SessionManager(account,password,this);
    _co = new ChatOperation(nullptr,this);
}

Netizen::~Netizen()
{
    delete _upm;
    delete _sm;
    delete _co;
    if(_cmc)delete _cmc;
}

void Netizen::signalConnect()
{
    // 消息接收
    connect(_cmc, &Communicator::messageReceived, this, &Netizen::messageReceived);
    connect(_cmc, &Communicator::groupMessageReceived, this, &Netizen::groupMessageReceived);
    connect(_cmc, &Communicator::imageReceived, this, &Netizen::imgReceived);
    connect(_co, &ChatOperation::receivedFriendRequest, this, &Netizen::receivedFriendRequest);
    connect(_co, &ChatOperation::removeFriendList11, this, &Netizen::removeFriendList11);
    connect(_co, &ChatOperation::removeMessagList, this, &Netizen::removeMessagList);
    connect(_co, &ChatOperation::receivedFriendResponse, this, &Netizen::receivedFriendResponse);

    // 命令处理
    connect(_cmc, &Communicator::commandReceived, _co, &ChatOperation::commandProcess);

    // 属性处理
    connect(_sm, &SessionManager::onlineChanged, this, &Netizen::onlineChanged);
    connect(_sm, &SessionManager::ipChanged, this, &Netizen::ipChanged);
    connect(_upm, &UserProfileManager::nicknameChanged, this, &Netizen::nicknameChanged);
    connect(_upm, &UserProfileManager::signChanged, this, &Netizen::signChanged);
    connect(_upm, &UserProfileManager::avatarChanged, this, &Netizen::avatarChanged);
}

// 账号操作
void Netizen::Logout() {_sm->logout();}
QList<QString> Netizen::GetFriendsAccount() { return _co->getFriendsAccount(); }

bool Netizen::LoginDetection(const QString &password)
{
    if(_sm->login(password))
    {
        delete _co;
        _cmc = new Communicator(this);
        _co = new ChatOperation(_cmc,this);
        signalConnect();
        return true;
    }
    return false;
}

QVariantList Netizen::getFriends()
{
    QList<Netizen *> friends = _co->getFriends();
    QVariantList list;
    for (auto it = friends.begin(); it != friends.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }

    return list;
}
QVariantList Netizen::getGroups()
{
    QList<Group *> groups = _co->getGroups();
    QVariantList list;
    for (auto it = groups.begin(); it != groups.end(); it++) {
        list.append(QVariant::fromValue(*it));
    }
    return list;
}

// 消息操作
void Netizen::sendMessage(const QString &receiverAccount, const QString &content) { _co->sendMessage(receiverAccount,content); }
void Netizen::sendGroupMessage(const QString &groupAccount, const QString &content) { _co->sendGroupMessage(groupAccount,content); }
void Netizen::sendImage(const QString &receiverAccount, const QString &imgPath) { _co->sendImage(receiverAccount,imgPath); }

// 属性获取
QString Netizen::getNickname() { return _upm->nickname(); }
QString Netizen::getAccount() { return _sm->getAccount(); }
QString Netizen::getPassword() { return _sm->getPassword(); }
bool Netizen::isOnline() { return _sm->isOnline(); }
QString Netizen::getIpAddress() { return _cmc->getLocalIP(); }
QString Netizen::getSign() { return _upm->sign(); }
QString Netizen::getAvatarBase64() { return _upm->avatar(); }
QString Netizen::getAvatarTmpFile() { return _upm->avatarTmpFilePath(); }
QString Netizen::getAvatarHash() {
    QByteArray avatarData = QByteArray::fromBase64(_upm->avatar().toUtf8());
    return QString(QCryptographicHash::hash(avatarData, QCryptographicHash::Md5).toHex());
}

// 属性更新
void Netizen::setNickname(const QString &nickname) { _upm->setNickname(nickname); }
void Netizen::setIpAddress(const QString &ip) { _sm->setIpAddress(ip); }
void Netizen::setSign(const QString &sign) { _upm->setSign(sign); }
void Netizen::setOnline(const bool online) { _sm->setOnline(online); }
void Netizen::updateAvatar(const QString &base64) { _upm->updateAvatar(base64); }
void Netizen::setAvatar(const QString &filePath) { _upm->setAvatarFromFile(filePath); }

// 好友管理
bool Netizen::addFriend(Netizen *user) { return _co->addFriend(user); }
bool Netizen::removeFriend(const QString &account) { return _co->removeFriend(account); }
void Netizen::removeFriendRequest(const QString &account) { return _co->removeFriendRequest(account); }
void Netizen::addFriendRequest(const QString &account) { return _co->addFriendRequest(account); }
void Netizen::addFriendResponse(const QString &account, const bool result) { return _co->addFriendResponse(account,result); }
bool Netizen::hasFriend(const QString &account) { return _co->hasFriend(account); }
void Netizen::avatarRequest(const QString &account) { _co->requestAvatar(account); }

// 群组功能
bool Netizen::createGroup(const QString &name, const QString &owner) { return _co->createGroup(name,owner); }
bool Netizen::joinGroup(Group *group) { return _co->joinGroup(group); }
bool Netizen::leaveGroup(Group *group) { return _co->leaveGroup(group); }
bool Netizen::hasGroup(const QString &account) { return _co->hasGroup(account); }
