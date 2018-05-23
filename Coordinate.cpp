#include "Coordinate.h"

Coordinate::Coordinate(){}

Coordinate::Coordinate(const Coordinate & c){
    this->xPlace = c.xPlace;
    this->yPlace = c.yPlace;
}

Coordinate::Coordinate(uint x, uint y){
    this->xPlace = x;
    this->yPlace = y;
}