// written by SL_Skuy
// 用户账号类声明
// 该类用于储存每一个用户账号的信息
// 并提供密码检测等方法

#pragma once

#include <QJsonObject>
#include <QString>
#include <QList>

class EchooUser
{
public:
    EchooUser(QString &nickName, QString &account, QString &password);
    ~EchooUser();
    bool HasFriend(QString account);
    bool PasswordDetection(QString password);
    QJsonObject GetUserInfo();

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    QList<QString> m_friends; // friend accounts
    QList<QString> m_groups;  // group accounts
};
