#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class Armor {
    public:

        Armor();
        virtual ~Armor();

        void push(int armorSize);
        void pop();
        int getArmor();
    
    private:

        int *_stack;
        int _top;

    
};