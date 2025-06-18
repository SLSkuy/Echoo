#include "databasemanager.h"
#include "echooclient.h"
#include "netizen.h"

EchooClient::EchooClient(QObject *parent) : QObject(parent)
{
    _dm = new DatabaseManager;
}

EchooClient::~EchooClient()
{
    delete _dm;
}

bool EchooClient::Login(const QString &account, const QString &password)
{
    Netizen *user = nullptr;
    if (_dm->Contains(account)) {
        // TODO
        user = _dm->GetNetizen(account);
        return user->LoginDetection(password);
    }
    return false;
}
