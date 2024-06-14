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
        Entity* deleteEntity(Entity* entity);
        void listEntities();

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
        EntityListGroupNode* _head;
        EntityGroupNode* _entityToDestroy;

        void addToDestroy(Entity* entity);

    public:
        EntityGroupList();
        virtual ~EntityGroupList();

        EntityGroup* getGroup(std::string groupName);
        void addGroup(std::string groupName);
        void deleteGroup(std::string groupName);
        void listGroups();

        void addToGroup(std::string groupName, Entity* entity);
        void removeFromGroup(std::string groupName, Entity* entity);

        void processDestroy();
};