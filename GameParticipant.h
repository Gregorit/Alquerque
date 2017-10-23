#pragma once
#include "Board.h"

template<typename T1>
class Board;
class gameParticipant
{
protected:
	char piece;
public:
	virtual void move(Board<char> &board);
	gameParticipant(char pie); //pie - piece

	char get_piece();
};
