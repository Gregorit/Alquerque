#pragma once
#include "GameParticipant.h"
#include "Board.h"

class Player : public gameParticipant
{
public:
	Player();
	Player(char pie);  //pie - piece

	void move(Board<char> &board);
};