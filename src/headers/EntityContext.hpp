#pragma once

#include "EntityGroupList.hpp"

class EntityContext {
    private:
        // Variables
        EntityGroupList _entityContext;

    public:
        // Functions
        EntityGroup* getGroup(std::string name);
        void addGroup(std::string groupName);
        void deleteGroup(std::string groupName);
        void listGroups();

        EntityGroupNode* getEntitiesInGroup(std::string groupName);
        void addToGroup(std::string groupName, Entity* entity);
        void removeFromGroup(std::string groupName, Entity* entity);
        void listEntitiesInGroup(std::string groupName);

        bool isColliding(std::vector<std::string> groupsName, sf::FloatRect bound, sf::Vector2f direction, Entity* entity);

        void updateGroup(std::string groupName);
        void renderGroup(std::string groupName, sf::RenderTarget& target);
};