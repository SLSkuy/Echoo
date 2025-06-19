#pragma once

#include <QObject>
#include <QString>
#include <QMap>

class Netizen;

class Group : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString groupName READ GetGroupName NOTIFY groupNameChanged)
    Q_PROPERTY(QString account READ GetGroupAccount NOTIFY accountChanged)
    Q_PROPERTY(QString owner READ GetGroupOwner NOTIFY ownerChanged)
public:
    explicit Group(QObject *parent = nullptr);
    Group(const QString &groupName,const QString &account,QObject *parent = nullptr);

    QString GetGroupName() { return m_groupName; }
    QString GetGroupAccount() { return m_account; }
    QString GetGroupOwner() { return m_owner; }

signals:
    void groupNameChanged();
    void accountChanged();
    void ownerChanged();

private:
    QString m_account;
    QString m_groupName;
    QString m_owner;
    QMap<QString, Netizen *> m_members;
};
