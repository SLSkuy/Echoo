// Echoo群组管理模块
// 提供群组的管理操作
// 如群组的创建与删除等功能

#pragma once

#include <QTcpSocket>
#include <QJsonObject>
#include <QList>
#include <QMap>

#include "echoogroup.h"

class GroupManager
{
public:
    GroupManager();
    ~GroupManager();
    QString CreateGroup(QTcpSocket *socket, const QJsonObject &content);
    QList<QString> RemoveGroup(QTcpSocket *socket, const QJsonObject &content);
    QList<QString> GetGroupMember(const QString &groupAccount);

private:
    QMap<QString, EchooGroup *> *_groups;
};
