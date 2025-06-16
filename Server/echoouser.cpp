// written by SL_Skuy
// 用户类实现

#include "echoouser.h"

EchooUser::EchooUser(QString &nickName, QString &account, QString &password)
    : m_nickName(nickName)
    , m_account(account)
    , m_password(password)
{}

EchooUser::~EchooUser() {}

bool EchooUser::HasFriend(QString account)
{
    // 是否存在对应账号的好友
    return m_friends.contains(account);
}

bool EchooUser::PasswordDetection(QString password)
{
    // 密码检测
    return password == m_password;
}

QJsonObject EchooUser::GetUserInfo()
{
    // 返回各种账号的信息用于客户端的初始化
    QJsonObject obj;
    obj["nickname"] = m_nickName;

    return obj;
}
