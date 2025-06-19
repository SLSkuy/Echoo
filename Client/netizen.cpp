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
        connect(_cmc, &Communicator::messageReceived, this, &Netizen::messageReceived);
        connect(_cmc, &Communicator::groupMessageReceived, this, &Netizen::groupMessageReceived);

        // 设置在线信息
        m_isOnline = true;

        // 广播在线消息
        QJsonObject obj;
        obj["nickName"] = m_nickName;
        obj["account"] = m_account;
        obj["online"] = true;
        _cmc->BroadcastPresence(obj);
        return true;
    }
    return false;
}

void Netizen::SendMessage(QString &receiverAccount, QString &content)
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

void Netizen::SendGroupMessage(QString &groupAccount, QString &content)
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
