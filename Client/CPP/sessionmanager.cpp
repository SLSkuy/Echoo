#include "sessionmanager.h"
#include "communicator.h"
#include "netizen.h"

SessionManager::SessionManager(QString account,QString password,Netizen *parent)
    : QObject(parent)
    , m_account(account)
    , m_password(password)
    , _owner(parent)
{}

Communicator *SessionManager::login(const QString &password)
{
    if (password == m_password) {
        // 初始化p2p网络通信
        _cmc = new Communicator(_owner);

        m_ip = _cmc->getLocalIP();
        // 连接信息接收信号
        connect(_cmc, &Communicator::messageReceived, this, &SessionManager::messageReceived);
        connect(_cmc, &Communicator::groupMessageReceived, this, &SessionManager::groupMessageReceived);
        connect(_cmc, &Communicator::imageReceived, this, &SessionManager::imageReceived);
        connect(_cmc, &Communicator::commandReceived, this, &SessionManager::commandReceived);

        // 设置在线信息
        m_isOnline = true;
        return _cmc;
    }
    return nullptr;
}

QString SessionManager::getLocalIP()
{
    return _cmc->getLocalIP();
}

void SessionManager::setOnline(bool online)
{
    if(online != m_isOnline)
    {
        m_isOnline = online;
        emit onlineChanged(m_isOnline);
    }
}

void SessionManager::setIpAddress(const QString &ip)
{
    if(ip != m_ip)
    {
        m_ip = ip;
        emit ipChanged();
    }
}
