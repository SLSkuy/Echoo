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
