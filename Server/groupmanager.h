// Echoo 群组管理模块
// 提供群组的管理操作
// 如群组的创建与删除等功能

#pragma once

#include <QMap>

#include "echoogroup.h"

class GroupManager
{
public:
    GroupManager();
    ~GroupManager();

private:
    QMap<QString, EchooGroup *> *_groups;
};
