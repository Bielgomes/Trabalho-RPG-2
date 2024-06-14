#include "../headers/EntityGroupList.h"

// Constructor and Destructor
EntityGroup::EntityGroup() {
    _head = nullptr;
}

EntityGroup::~EntityGroup() {
    EntityGroupNode* current = _head;

    while (current != nullptr) {
        EntityGroupNode* next = current->next;
        delete current->entity;
        delete current;
        current = next;
    }
}

// Functions
EntityGroupNode* EntityGroup::getEntities() {
    return _head;
}

void EntityGroup::addEntity(Entity* entity) {
    EntityGroupNode* node = new EntityGroupNode();
    node->entity = entity;
    node->next = nullptr;

    if (_head == nullptr) {
        _head = node;
    } else {
        node->next = _head;
        _head = node;
    }
}

Entity* EntityGroup::deleteEntity(Entity* entity) {
    EntityGroupNode* current = _head;
    EntityGroupNode* previous = nullptr;

    Entity* entityToDelete = nullptr;

    while (current != nullptr) {
        if (current->entity == entity) {
            if (previous == nullptr)
                _head = current->next;
            else
                previous->next = current->next;
            
            entityToDelete = current->entity;
            delete current;
            return entityToDelete;
        }

        previous = current;
        current = current->next;
    }
}

void EntityGroup::listEntities() {
    EntityGroupNode* current = _head;

    while (current != nullptr) {
        std::cout << current->entity << std::endl;
        current = current->next;
    }
}

void EntityGroup::update() {
    EntityGroupNode* current = _head;

    while (current != nullptr) {
        current->entity->update();
        current = current->next;
    }
}

void EntityGroup::render(sf::RenderTarget& target) {
    EntityGroupNode* current = _head;

    while (current != nullptr) {
        current->entity->render(target);
        current = current->next;
    }
}






// Private Functions
void EntityGroupList::addToDestroy(Entity* entity) {
    EntityGroupNode* node = new EntityGroupNode();
    node->entity = entity;
    node->next = nullptr;

    if (_entityToDestroy == nullptr) {
        _entityToDestroy = node;
    } else {
        node->next = _entityToDestroy;
        _entityToDestroy = node;
    }
}

// Constructor and Destructor
EntityGroupList::EntityGroupList() {
    _head = nullptr;
}

EntityGroupList::~EntityGroupList() {
    EntityListGroupNode* current = _head;
    while (current != nullptr) {
        EntityListGroupNode* next = current->next;
        delete current->group;
        delete current;
        current = next;
    }

    processDestroy();
}

// Functions
EntityGroup* EntityGroupList::getGroup(std::string groupName) {
    EntityListGroupNode* current = _head;

    while (current != nullptr) {
        if (current->name == groupName)
            return current->group;

        current = current->next;
    }

    return nullptr;
}

void EntityGroupList::addGroup(std::string groupName) {
    EntityListGroupNode* node = new EntityListGroupNode();
    node->name = groupName;
    node->group = new EntityGroup();
    node->next = nullptr;

    if (_head == nullptr) {
        _head = node;
    } else {
        node->next = _head;
        _head = node;
    }
}

void EntityGroupList::deleteGroup(std::string groupName) {
    EntityListGroupNode* current = _head;
    EntityListGroupNode* previous = nullptr;

    while (current != nullptr) {
        if (current->name == groupName) {
            if (previous == nullptr) {
                _head = current->next;
            } else {
                previous->next = current->next;
            }

            delete current->group;
            delete current;
            return;
        }

        previous = current;
        current = current->next;
    }
}

void EntityGroupList::listGroups() {
    EntityListGroupNode* current = _head;

    while (current != nullptr) {
        std::cout << current->name << std::endl;
        current = current->next;
    }
}

void EntityGroupList::addToGroup(std::string groupName, Entity* entity) {
    EntityListGroupNode* current = _head;

    while (current != nullptr) {
        if (current->name == groupName) {
            current->group->addEntity(entity);
            return;
        }

        current = current->next;
    }
}

void EntityGroupList::removeFromGroup(std::string groupName, Entity* entity) {
    EntityListGroupNode* current = _head;
    Entity* entityToDelete = nullptr;

    while (current != nullptr) {
        if (current->name == groupName) {
            entity = current->group->deleteEntity(entity);
            if (entity == nullptr)
                return;

            addToDestroy(entity);
        }

        current = current->next;
    }
}

void EntityGroupList::processDestroy() {
    EntityGroupNode* current = _entityToDestroy;
    _entityToDestroy = nullptr;

    while (current != nullptr) {
        EntityGroupNode* next = current->next;
        
        if (current->entity != nullptr) {
            delete current->entity;
            current->entity = nullptr;
        }

        delete current;
        current = next;
    }
}