#pragma once
#include <string>
#include "Board.h"

using namespace std;

class Player{
    public:
        Player();
        virtual const string name() const = 0;
        char myChar;
        virtual const Coordinate play(const Board&) = 0;
        const char getChar() const;
        void setChar(char);
};