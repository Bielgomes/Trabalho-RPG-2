#pragma once

#include "EntityGroupList.h"

class EntityContext {
    private:
        EntityGroupList _entityContext;

    public:
        EntityGroup* getGroup(std::string name);
        void addGroup(std::string groupName);
        void deleteGroup(std::string groupName);
        void listGroups();

        void addToGroup(std::string groupName, Entity* entity);
        void removeFromGroup(std::string groupName, Entity* entity);
        void listEntitiesInGroup(std::string groupName);
};