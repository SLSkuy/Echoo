#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class Netizen;

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(const QString &groupName,const QString &account,QObject *parent = nullptr);

    QString GetGroupName() { return m_groupName; }
    QString GetGroupAccount() { return m_account; }
    QString GetGroupOwner() { return m_owner; }

private:
    QString m_account;
    QString m_groupName;
    QString m_owner;
    QMap<QString, Netizen *> m_members;
};
