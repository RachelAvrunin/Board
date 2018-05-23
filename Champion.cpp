#include "Champion.h"

const Coordinate Champion::play(const Board& board) {
	if(board[{0, (uint)board.size() - 1}] == '.')
		return {0, (uint)board.size() - 1};
	else if(board[{(uint)board.size() - 1, 0}] == '.')
		return {(uint)board.size() - 1, 0};
	else
	for(uint i = 0, j = (uint)board.size()-1 ; i < (uint)board.size() ; i++,j--)
		if(board[{i,j}] == '.')
			return {i,j};

	return {0,0};  // did not find an empty square - play on the top-left
}