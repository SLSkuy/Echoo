// Echoo群组管理模块实现
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

QString GroupManager::CreateGroup(QTcpSocket *socket, const QJsonObject &content)
{
    QString groupName = content["groupName"].toString();
    QString groupOwner = content["groupOwner"].toString();
    QString type = content["type"].toString();
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
    MessageManager::SendResponse(socket, true, str, type);
    Logger::Log("Group: " + groupAccount + " create successfully.");

    // 返回新创建的群组号，用于委托账号管理器给特定用户记录群聊信息
    return groupAccount;
}

QList<QString> GroupManager::RemoveGroup(QTcpSocket *socket, const QJsonObject &content)
{
    QList<QString> member;
    QString groupAccout = content["groupAccount"].toString();

    if (_groups->contains(groupAccout)) {
        // 若存在对应群聊则删除
        // 返回成员对象列表用于委托删除用户加入的群聊记录
        EchooGroup *group = (*_groups)[groupAccout];
        _groups->remove(groupAccout);
        member = group->GetGroupMember();
        delete group;
        Logger::Log(groupAccout + " group removed.");
    } else {
        Logger::Error(groupAccout + " group not exist.");
    }
    return member;
}

QList<QString> GroupManager::GetGroupMember(const QString &groupAccount)
{
    // 返回群聊成员信息
    EchooGroup *group = (*_groups)[groupAccount];
    return group->GetGroupMember();
}
