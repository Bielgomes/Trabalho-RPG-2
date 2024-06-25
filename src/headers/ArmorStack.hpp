#pragma once

#include <SFML/Graphics.hpp>

class ArmorStack {
    private:
        unsigned int *_stack;
        unsigned int _top;
        unsigned int _capacity;

    public:
        // Constructor and Destructor
        ArmorStack(unsigned int capacity);
        virtual ~ArmorStack();

        // Functions
        void push(unsigned int armorSize);
        void pop();
        unsigned int getArmor() const;
};