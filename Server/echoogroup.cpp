#include "echoogroup.h"

EchooGroup::EchooGroup(QString groupName, QString groupAccount, QString ownerAccount)
    : m_groupName(groupName)
    , m_groupAccount(groupAccount)
    , m_ownerAccount(ownerAccount)
{}

EchooGroup::~EchooGroup() {}

bool EchooGroup::HasAccount(QString account)
{
    return m_groupUsers.contains(account);
}
