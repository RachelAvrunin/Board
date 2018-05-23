#include "DummyPlayers.h"


const Pixel XYPlayer::play(const Board& board) {
	for (uint x=0; x<board.size(); ++x) {
		for (uint y=0; y<board.size(); ++y) {
			Pixel c{x,y};
			if (board[c]=='.') {
				return c;
			}
		}
	}
	return {0,0};  // did not find an empty square - play on the top-left
}


const Pixel YXPlayer::play(const Board& board) {
	for (uint y=0; y<board.size(); ++y) {
		for (uint x=0; x<board.size(); ++x) {
			Pixel c{x,y};
			if (board[c]=='.') {
				return c;
			}
		}
	}
	return {0,0};  // did not find an empty square - play on the top-left
}



/**
 * The illegal player tries to put a char on a cell owned by the other player.
 */
const Pixel IllegalPlayer::play(const Board& board) {
	char charOfOtherPlayer = (
		myChar=='X'? 'O': 'X'
		);
	for (uint y=0; y<board.size(); ++y) {
		for (uint x=0; x<board.size(); ++x) {
			Pixel c{x,y};
			if (board[c]==charOfOtherPlayer) {
				return c;
			}
		}
	}
	return {0,0};  // did not find an illegal square - play on the top-left
}


const Pixel ExceptionPlayer::play(const Board& board) {
	throw string("hahaha");
}