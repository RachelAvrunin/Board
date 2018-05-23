#include "Player.h"
using namespace std;


Player::Player(){}

void Player::setChar(char c){
    this->myChar = c;
}

const char Player::getChar() const{
    return myChar;
}