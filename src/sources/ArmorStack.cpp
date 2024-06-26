#include "../headers/ArmorStack.hpp"
#include <iostream> 

ArmorStack::ArmorStack(unsigned int capacity) {
    _capacity = capacity;
    _top = 0;
    _stack = new unsigned int[_capacity];
}

ArmorStack::~ArmorStack() {
    delete[] _stack;
}

void ArmorStack::push(unsigned int armorSize) {
    if (_top == _capacity)
        return;
    
    _stack[_top] = armorSize;
    _top++;
}

void ArmorStack::pop() {
    if(_top == 0)
        return;

    _top--;
}

unsigned int ArmorStack::getArmor() const {
    std::cout << "TOP " << _top << std::endl;
    unsigned int def = 0;
    for (int i = 0; i < (int) _top; i++) {
        std::cout << "STACK " << _stack[i] << std::endl;
        def += _stack[i];
    }

    std::cout << "DEF: " << def << std::endl;
    return def;
}