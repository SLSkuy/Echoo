// 群组类声明
// 该类记录群聊的人员等各种信息

#pragma once

#include <QString>
#include <QList>

class EchooGroup
{
public:
    EchooGroup(QString groupName, QString groupAccount, QString ownerAccount);
    ~EchooGroup();
    bool HasAccount(QString account);

private:
    QString m_groupName;
    QString m_groupAccount;
    QString m_ownerAccount;
    QList<QString> m_groupUsers; // 存储群组中所有用户的账号
};
