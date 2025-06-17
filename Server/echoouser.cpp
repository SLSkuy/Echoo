// Echoo用户类实现

#include "echoouser.h"
#include "logger.h"

EchooUser::EchooUser(QString &nickName, QString &account, QString &password)
    : m_nickName(nickName)
    , m_account(account)
    , m_password(password)
{}

EchooUser::~EchooUser() {}

bool EchooUser::PasswordDetection(QString password)
{
    // 密码检测
    return password == m_password;
}

bool EchooUser::HasFriend(QString account)
{
    // 是否存在对应账号的好友
    return m_friends.contains(account);
}

void EchooUser::AddFriend(QString account)
{
    if (!HasFriend(account))
        m_friends.append(account);
    else
        Logger::Warning(m_account + " already has friend " + account);
}

void EchooUser::RemoveFriend(QString account)
{
    if (HasFriend(account))
        m_friends.removeOne(account);
    else
        Logger::Warning(m_account + " dosen't has friend " + account);
}

bool EchooUser::HasGroup(QString account)
{
    return m_groups.contains(account);
}

void EchooUser::AddGroup(QString account)
{
    if (!HasGroup(account))
        m_groups.append(account);
    else
        Logger::Warning(m_account + " already join group " + account);
}

void EchooUser::ExitGroup(QString account)
{
    if (HasGroup(account))
        m_groups.removeOne(account);
    else
        Logger::Warning(m_account + " doesn't join group " + account);
}

QJsonObject EchooUser::GetUserInfo()
{
    // 返回各种账号的信息用于客户端的初始化
    QJsonObject obj;
    obj["nickname"] = m_nickName;

    return obj;
}
