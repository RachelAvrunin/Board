#include <iostream>
#include <string>
#include "TicTacToe.h"
using namespace std;


TicTacToe::TicTacToe(int n){
    this->n = n;
    game = new Board(n);;
    _winner = NULL;
}

const Board& TicTacToe::board() const{
    return *game;
}

Player& TicTacToe::winner() const{
    return *_winner;
}

void TicTacToe::play(Player& xPlayer, Player& oPlayer){
    xPlayer.setChar('X');
    oPlayer.setChar('O');
    *game = '.';
    _winner = NULL;
    uint i = 0;
    for( ; i < (uint)(*game).size()*(*game).size() ; i+=2){
        turn(game,xPlayer,oPlayer);
        if(_winner)
            break;
        turn(game,oPlayer,xPlayer);
        if(_winner)
           break;
    }
    if(i == (uint)(*game).size()*(*game).size() - 1)
            _winner = &oPlayer;
}

void TicTacToe::turn(Board * game,Player& current, Player& other){
    Coordinate move;
    try{
            move = current.play(*game);
        }catch(...){
            _winner = &other;
            return;
        }
        if((*game)[move] == '.')
           (*game)[move] = current.getChar();
        else {
            _winner = &other;
            return;
        }
        if(winMove(move,current.getChar())){
            _winner = &current;
        }
}

bool TicTacToe::winMove(Coordinate move,char c){
    bool col = true;
    bool row = true;
    bool diag = true;
    bool mdiag = true;
    for(uint i = 0 ; i < n ; i++)
        if((*game)[{move.xPlace,i}] != c)
            col = false;
    
    for(uint i = 0 ; i < n ; i++)
        if((*game)[{i,move.yPlace}] != c)
            row = false;
    
    if(move.xPlace == (n - move.yPlace - 1)){
        for(uint i = 0, j = n-1 ; i < n ; i++,j--)
            if((*game)[{i,j}] != c)
                mdiag = false;
    } else mdiag = false;
    
    if(move.xPlace == move.yPlace){
        for(uint i = 0, j = 0 ; i < n ; i++,j++)
            if((*game)[{i,j}] != c)
                diag = false;
    } else diag = false;
    
    
    
    return col||row||diag||mdiag;
}

TicTacToe::~TicTacToe(){
    delete game;
}