// written by SL_Skuy
// 用户类实现

#include "echoouser.h"

EchooUser::EchooUser() {}

EchooUser::~EchooUser() {}

bool EchooUser::hasFriend(QString account)
{
    return m_friends.contains(account);
}
