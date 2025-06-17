// Echoo用户账号类声明
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
    bool PasswordDetection(QString password);
    bool HasFriend(QString account);
    void AddFriend(QString account);
    void RemoveFriend(QString account);
    bool HasGroup(QString account);
    void AddGroup(QString account);
    void ExitGroup(QString account);
    QJsonObject GetUserInfo();

private:
    QString m_nickName;
    QString m_account;
    QString m_password;
    QList<QString> m_friends; // friend accounts
    QList<QString> m_groups;  // group accounts
};
