// written by SL_Skuy
// 用户类声明

#pragma once

#include <QString>
#include <QList>

class EchooUser
{
public:
    EchooUser();
    ~EchooUser();
    bool hasFriend(QString account);

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    QList<QString> m_friends; // friend's account
};
