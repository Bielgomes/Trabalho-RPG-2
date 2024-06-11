#pragma once

#include "Entity.h"

struct EntityGroupNode {
    Entity* entity;
    EntityGroupNode* next;
};

class EntityGroup {
    private:
        EntityGroupNode* _head;

    public:
        EntityGroup();
        virtual ~EntityGroup();

        EntityGroupNode* getEntities();
        void addEntity(Entity* entity);
        void deleteEntity(Entity* entity);
        void listEntities();

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
        EntityListGroupNode* _head;

    public:
        EntityGroupList();
        virtual ~EntityGroupList();

        EntityGroup* getGroup(std::string groupName);
        void addGroup(std::string groupName);
        void deleteGroup(std::string groupName);
        void listGroups();

        void addToGroup(std::string groupName, Entity* entity);
        void removeFromGroup(std::string groupName, Entity* entity);
};