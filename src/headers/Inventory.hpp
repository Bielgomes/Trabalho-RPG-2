#pragma once
#include "Item.hpp"
#include <string>

class Inventory
{
    private:
        Item** itemArray;
        unsigned itemsQuantity;
        unsigned capacity;

        // Private functions
        void initialize();
        void nullify(const unsigned from = 0);
        void freeMemory();

    public:
        Inventory(unsigned capacity);
        virtual ~Inventory();

        // Modifiers

        // Functions
        void clear();
        const bool empty() const;
        const unsigned size() const;

        const bool add(Item* item);
        const bool remove(const unsigned index);

        const bool saveToFile(const std::string fileName);
        const bool loadFromFile(const std::string fileName);
};