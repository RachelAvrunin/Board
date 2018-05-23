#pragma once
#include "Player.h"

/* 
*	This player scans the board looping on x then on y, 
*	and plays on the first empty cell. 
*	Selects a single place to put my symbol, given the current board.
*	Defines the strategy of the player.
*/
class Champion: public Player {
public:
	const string name() const override { return "Champion"; }
	const Coordinate play(const Board& board) override;
};