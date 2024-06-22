#pragma once
class Item {
    private:
    public:
        Item();
        virtual ~Item();

        // Function
        virtual Item* clone() = 0;
};