#include "sessionmanager.h"
#include "communicator.h"
#include "netizen.h"

SessionManager::SessionManager(QString account,QString password,Netizen *parent)
    : QObject(parent)
    , m_account(account)
    , m_password(password)
    , _owner(parent)
{}

bool SessionManager::login(const QString &password)
{
    if (password == m_password) {
        // 设置在线信息
        m_isOnline = true;
        return true;
    }
    return false;
}

void SessionManager::setOnline(bool online)
{
    if(online != m_isOnline)
    {
        m_isOnline = online;
        emit onlineChanged(m_isOnline);
    }
}
