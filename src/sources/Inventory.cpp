#include "Inventory.hpp"

void Inventory::initialize()
{
    this->itemsQuantity = 0;
    this->itemArray = new Item*[this->capacity];
    
    this->nullify();
}


void Inventory::nullify(const unsigned from)
{
    for(size_t i = from; i < this->capacity; i++){
        this->itemArray[i] = nullptr;
    }
}

void Inventory::freeMemory()
{
    for(size_t i = 0; i < this->itemsQuantity; i++){
        delete &itemArray[i];
    }

    delete[] this->itemArray;
}

//Contstructors and Destructors

Inventory::Inventory(const unsigned capacity)
{
    this->capacity = capacity;

    this->initialize();
}

Inventory::~Inventory()
{
    this->freeMemory();
}

// Modifiers

// Functions

void Inventory::clear(){

    for(size_t i = 0; i < this->itemsQuantity; i++){
            delete &itemArray[i];
    }

    this->itemsQuantity = 0;
    this->nullify(0);
}

const bool Inventory::empty() const
{
    return this->itemsQuantity == 0;
}

const unsigned Inventory::size() const
{
    return this->itemsQuantity;
}

const bool Inventory::add(Item* item) 
{
    if(this->itemsQuantity < this->capacity){
        this->itemArray[this->itemsQuantity++] = item->clone();

        return true;
    }

    return false;
}

const bool Inventory::remove(const unsigned index)
{
    if(this->itemsQuantity > 0){
        if(index < 0 || index >= this->capacity)
            return false;
        
        delete &itemArray[index];
        // this->itemArray[index] = nullptr;
        --this->itemsQuantity;

        return true;
    }
    return false;
}


const bool Inventory::saveToFile(const std::string fileName)
{
    return false;
}


const bool Inventory::loadFromFile(const std::string fileName)
{
    return false;
}