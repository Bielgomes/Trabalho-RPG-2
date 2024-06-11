#include "../headers/EntityContext.h"

EntityGroup* EntityContext::getGroup(std::string name) {
    return _entityContext.getGroup(name);
};

void EntityContext::addGroup(std::string groupName) {
    _entityContext.addGroup(groupName);
};

void EntityContext::deleteGroup(std::string groupName) {
    _entityContext.deleteGroup(groupName);
};

void EntityContext::listGroups() {
    _entityContext.listGroups();
};

void EntityContext::addToGroup(std::string groupName, Entity* entity) {
    _entityContext.addToGroup(groupName, entity);
};

void EntityContext::removeFromGroup(std::string groupName, Entity* entity) {
    _entityContext.removeFromGroup(groupName, entity);
};

void EntityContext::listEntitiesInGroup(std::string groupName) {
    EntityGroup* group = _entityContext.getGroup(groupName);

    if (group != nullptr) {
        group->listEntities();
    }
};