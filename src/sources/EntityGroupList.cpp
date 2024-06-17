#include "../headers/EntityGroupList.hpp"

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

void EntityGroup::deleteEntity(Entity* entity) {
    EntityGroupNode* current = _head;
    EntityGroupNode* previous = nullptr;

    while (current != nullptr) {
        if (current->entity == entity) {
            if (previous == nullptr)
                _head = current->next;
            else
                previous->next = current->next;
            
            delete current->entity;
            delete current;
            return;
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
    EntityGroupNode* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->entity->update();
        current = next;
    }
}

void EntityGroup::render(sf::RenderTarget& target) {
    EntityGroupNode* current = _head;

    while (current != nullptr) {
        current->entity->render(target);
        current = current->next;
    }
}

bool EntityGroup::isColliding(sf::FloatRect bound, sf::Vector2f direction, Entity* entity) {
    EntityGroupNode* current = _head;
    while (current != nullptr && current->entity != entity) {
        if (current->entity->getShape().intersects(
            sf::FloatRect(bound.left + direction.x, bound.top + direction.y, bound.width, bound.height)
        )) {
            return true;
        }

        current = current->next;
    }

    return false;
}






// Private Functions

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

    while (current != nullptr) {
        if (current->name == groupName) {
            current->group->deleteEntity(entity);
            return;
        }

        current = current->next;
    }
}
