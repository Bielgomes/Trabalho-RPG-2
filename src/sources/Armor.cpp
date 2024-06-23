#include "../headers/Armor.hpp"

Armor::Armor(){
    _stack = new int[8];
    _top = 0;
}

Armor::~Armor(){
    delete _stack;
}

void Armor::push(int armorSize){
    if(_top == 7){
        return;
    } else {
        _stack[_top] = armorSize;
        _top+=1;
    }
}

void Armor::pop(){
    if(_top == 0){
        return;
    } else {
        _top-=1;
    }
}

int Armor::getArmor(){
    int def = 0;
    for(int i = 0; i < _top; i+=1){
        def += _stack[i];
    }

    return def;
}