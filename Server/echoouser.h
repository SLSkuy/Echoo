// written by SL_Skuy
// 用户类声明

#pragma once

#include <QString>
#include <QList>

class EchooUser
{
public:
    EchooUser(QString nickName, QString account, QString password);
    ~EchooUser();
    bool HasFriend(QString account);
    bool PasswordDetection(QString password);

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    QList<QString> m_friends; // friend's accounts
};
