
#pragma once
#include <sys/types.h>

class Coordinate{
    public:
        uint xPlace;
        uint yPlace;    
        Coordinate();
        Coordinate(uint, uint);
        Coordinate(const Coordinate &);

};