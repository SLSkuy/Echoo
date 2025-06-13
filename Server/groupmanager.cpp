// Echoo 群组管理模块实现
// 所有的群组管理逻辑都在此实现
// 包括群组创建等

#include <QRandomGenerator>

#include "groupmanager.h"
#include "messagemanager.h"
#include "logger.h"

GroupManager::GroupManager() : _groups(new QMap<QString, EchooGroup *>) {}

GroupManager::~GroupManager()
{
    for (auto it = _groups->begin(); it != _groups->end(); it++) {
        delete it.value();
    }
    delete _groups;
}

void GroupManager::CreateGroup(QTcpSocket *socket, const QJsonObject &content)
{
    QString groupName = content["groupName"].toString();
    QString groupOwner = content["groupOwner"].toString();
    QString groupAccount;

    do {
        // 生成随机6位数群账号
        groupAccount = QString::number(100000 + QRandomGenerator::global()->bounded(900000));
    } while (_groups->contains(groupAccount));

    // 创建并记录新群组
    EchooGroup *newGroup = new EchooGroup(groupName, groupAccount, groupOwner);
    newGroup->AddAccount(groupOwner); // 添加群主
    _groups->insert(groupAccount, newGroup);

    // 返回创建成功信息
    QString str = "Group create successfully.";
    MessageManager::SendResponse(socket, true, str);
    Logger::Log("Group: " + groupAccount + " create successfully.");
}
