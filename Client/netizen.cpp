#include <QJsonObject>

#include "communicator.h"
#include "netizen.h"

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
        _cmc = new Communicator;

        // 广播在线消息
        QJsonObject obj;
        obj["nickName"] = m_nickName;
        obj["account"] = m_account;
        obj["password"] = m_password;
        obj["online"] = true;
        _cmc->BroadcastPresence(obj);

        m_isOnline = true;
        return true;
    }
    return false;
}

void Netizen::SendMessage(Netizen *receiver, Message *msg) {}

void Netizen::SendGroupMessage(Group *group, Message *msg) {}
