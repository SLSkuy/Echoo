#include "groupmanager.h"

GroupManager::GroupManager() : _groups(new QMap<QString, EchooGroup *>) {}

GroupManager::~GroupManager()
{
    for (auto it = _groups->begin(); it != _groups->end(); it++) {
        delete it.value();
    }
    delete _groups;
}
