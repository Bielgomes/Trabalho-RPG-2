#include "../headers/EntityContext.hpp"

// Functions
EntityGroup* EntityContext::getGroup(std::string name) {
    return _entityContext.getGroup(name);
}

void EntityContext::addGroup(std::string groupName) {
    _entityContext.addGroup(groupName);
}

void EntityContext::deleteGroup(std::string groupName) {
    _entityContext.deleteGroup(groupName);
}

void EntityContext::listGroups() {
    _entityContext.listGroups();
}

EntityGroupNode* EntityContext::getEntitiesInGroup(std::string groupName) {
    return _entityContext.getGroup(groupName)->getEntities();
}

void EntityContext::addToGroup(std::string groupName, Entity* entity) {
    _entityContext.addToGroup(groupName, entity);
}

void EntityContext::removeFromGroup(std::string groupName, Entity* entity) {
    _entityContext.removeFromGroup(groupName, entity);
}

void EntityContext::listEntitiesInGroup(std::string groupName) {
    EntityGroup* group = _entityContext.getGroup(groupName);

    if (group != nullptr) {
        group->listEntities();
    }
}

void EntityContext::updateGroup(std::string groupName) {
    EntityGroup* group = _entityContext.getGroup(groupName);

    if (group != nullptr)
        group->update();
}

void EntityContext::renderGroup(std::string groupName, sf::RenderTarget& target) {
    EntityGroup* group = _entityContext.getGroup(groupName);

    if (group != nullptr)
        group->render(target);
}