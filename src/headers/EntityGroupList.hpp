#pragma once

#include "Entity.hpp"

struct EntityGroupNode {
    Entity* entity;
    EntityGroupNode* next;
};

class EntityGroup {
    private:
        // Variables
        EntityGroupNode* _head;

    public:
        // Constructor and Destructor
        EntityGroup();
        virtual ~EntityGroup();

        // Functions
        EntityGroupNode* getEntities();
        void addEntity(Entity* entity);
        void deleteEntity(Entity* entity);
        void listEntities();

        bool isColliding(sf::FloatRect bound, sf::Vector2f direction, Entity* entity);

        void update();
        void render(sf::RenderTarget& target);
};

struct EntityListGroupNode
{
    std::string name;
    EntityGroup* group;
    EntityListGroupNode* next;
};

class EntityGroupList {
    private:
        // Variables
        EntityListGroupNode* _head;

    public:
        // Constructor and Destructor
        EntityGroupList();
        virtual ~EntityGroupList();

        // Functions
        EntityGroup* getGroup(std::string groupName);
        void addGroup(std::string groupName);
        void deleteGroup(std::string groupName);
        void listGroups();

        void addToGroup(std::string groupName, Entity* entity);
        void removeFromGroup(std::string groupName, Entity* entity);
};