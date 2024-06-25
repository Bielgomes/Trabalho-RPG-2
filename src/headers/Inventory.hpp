#pragma once

#include <string>

struct Item {
    unsigned int id;
    unsigned int quantity;
};

class Inventory {
    private:
        // Variables
        Item* _data;
        unsigned int _capacity;
        unsigned int _size;
        unsigned int _start;
        unsigned int _end;

        // Private Functions
        void initVariables();
        void initTextures();

    public:
        // Constructor and Destructor
        Inventory(unsigned int capacity);
        virtual ~Inventory();

        // Accessors
        bool isEmpty() const;
        bool isFull() const;
        unsigned int getSize() const;
        unsigned int getCapacity() const;
        unsigned int getStart() const;
        unsigned int getEnd() const;
        Item* getData() const;

        // Functions
        void enqueue(unsigned int id, unsigned int quantity);
        void dequeue();
};