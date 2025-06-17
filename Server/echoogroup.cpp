// Echoo群组类实现
// 用于检测、添加与删除账号等与群组类成员相关操作

#include "echoogroup.h"
#include "logger.h"

EchooGroup::EchooGroup(QString &groupName, QString &groupAccount, QString &ownerAccount)
    : m_groupName(groupName)
    , m_groupAccount(groupAccount)
    , m_ownerAccount(ownerAccount)
{}

EchooGroup::~EchooGroup() {}

bool EchooGroup::HasAccount(QString account)
{
    return m_groupUsers.contains(account);
}

void EchooGroup::AddAccount(QString account)
{
    if (!HasAccount(account)) {
        m_groupUsers.append(account);
    } else {
        Logger::Warning("Account: " + account + " has existed in this group: " + m_groupAccount);
    }
}

void EchooGroup::RemoveAccount(QString account)
{
    if (HasAccount(account)) {
        m_groupUsers.removeOne(account);
    } else {
        Logger::Warning("Account: " + account + " not exist in this group: " + m_groupAccount);
    }
}

QList<QString> EchooGroup::GetGroupMember()
{
    return m_groupUsers;
}
