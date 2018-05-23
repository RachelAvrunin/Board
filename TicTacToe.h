#pragma once
#include <iostream>
#include <string>
#include "Player.h"
using namespace std;

class TicTacToe{
    private:
        int n;
        Board* game;
        Player* _winner;
        bool winMove(Coordinate,char);
        void turn(Board *,Player&, Player&);
        
    public:
        TicTacToe(int);
        const Board& board() const;
        Player& winner() const;
        void play(Player&, Player&);
        ~TicTacToe();
    
};