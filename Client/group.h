#pragma once

#include <QObject>
#include <QString>
#include <QList>

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(const QString &groupName,const QString &account,QObject *parent = nullptr);

    QString GetGroupName() { return m_groupName; }
    QString GetGroupAccount() { return m_account; }

private:
    QString m_account;
    QString m_groupName;
    QString m_owner;
    QList<QString> m_members;
};
