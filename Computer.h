#pragma once
#include "GameParticipant.h"
#include "Board.h"

class Computer : public gameParticipant
{
public:
	Computer();
	Computer(char pie); //pie - piece

	void move(Board<char> &board);
};