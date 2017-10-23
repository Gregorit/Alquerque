#pragma once
#include "Player.h"
#include "Computer.h"
#include "Ranking.h"

class Alquerque
{
private:
	Board<char> board;
	Player *player1;
	Player *player2;
	Computer *computer;
	Ranking ranking;
	int gameMode;
	char move;
public:
	Alquerque();
	void writeRules();
	void mainMenu();
	~Alquerque();
};