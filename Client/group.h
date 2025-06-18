#pragma once

#include <QString>
#include <QList>

class Group
{
public:
    Group();

private:
    QString m_account;
    QString m_groupName;
    QString m_owner;
    QList<QString> m_members;
};
