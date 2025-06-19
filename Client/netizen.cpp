#include <QJsonObject>

#include "databasemanager.h"
#include "communicator.h"
#include "message.h"
#include "netizen.h"
#include "logger.h"

Netizen::Netizen(QObject *parent) : QObject(parent) {}

Netizen::Netizen(const QString &nickName, const QString &account, const QString &password, QObject *parent)
    : m_nickName(nickName)
    , m_account(account)
    , m_password(password)
    , m_isOnline(false)
    , QObject(parent)
{}

Netizen::~Netizen()
{
    delete _cmc;
}

bool Netizen::LoginDetection(const QString &password)
{
    if (password == m_password) {
        // 连接p2p服务器
        _cmc = new Communicator(this);
        m_ip = _cmc->GetLocalIP();
        connect(_cmc, &Communicator::messageReceived, this, &Netizen::MessageProcess);
        connect(_cmc, &Communicator::groupMessageReceived, this, &Netizen::GroupMessageProcess);

        // 设置在线信息
        m_isOnline = true;

        // 广播在线消息
        QJsonObject obj;
        obj["nickName"] = m_nickName;
        obj["account"] = m_account;
        obj["online"] = true;
        obj["ip"] = GetIpAddress();
        _cmc->BroadcastPresence(obj);
        return true;
    }
    return false;
}

void Netizen::SendMessage(const QString &receiverAccount, const QString &content)
{
    // 从数据库获取发送对象指针
    Netizen *receiver = DatabaseManager::instance()->GetNetizen(receiverAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (HasFriend(receiverAccount)) {
        // 创建消息实体对象,接受者设置为空用于委托检测是否有对应好友
        Message *msg = new Message(this, receiver, content, curTime);
        _cmc->SendMessage(msg);
    } else {
        Logger::Warning(receiverAccount + " is not " + m_account + "'s friend.");
    }
}

void Netizen::SendGroupMessage(const QString &groupAccount, const QString &content)
{
    Group *receiver = DatabaseManager::instance()->GetGroup(groupAccount);
    QDateTime curTime = QDateTime::currentDateTime();

    if (HasGroup(groupAccount)) {
        // 创建消息实体
        Message *msg = new Message(this, receiver, content, curTime);
        _cmc->SendGroupMessage(msg);
    } else {
        Logger::Warning(m_account + " not in group " + groupAccount);
    }
}

bool Netizen::AddFriend(Netizen *user)
{
    if (HasFriend(user->GetAccount())) {
        Logger::Warning(user->GetAccount() + " is already your friend.");
        return false;
    } else {
        Logger::Log("Add friend " + user->GetAccount());
        m_friends.insert(user->GetAccount(), user);
        return true;
    }
}

void Netizen::MessageProcess(Message *message)
{
    Logger::Log("Receive message from account " + message->GetSender()->GetAccount() + ": " + message->GetMessage());

    // 检测消息接受对象是否为此对象
    if (message->GetReceiver() == this) {
        QString sender = message->GetSender()->GetAccount();
        QString content = message->GetMessage();
        QDateTime time = message->GetMessageTime();

        // 触发信号
        emit messageProcessed(sender, content, time);
    }
}

void Netizen::GroupMessageProcess(Group *group, Message *message) {}
