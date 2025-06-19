#include "group.h"

Group::Group(const QString &groupName, const QString &account, QObject *parent)
    : QObject(parent), m_account(account), m_groupName(groupName)
{}
