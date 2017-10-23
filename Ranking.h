#pragma once

struct Element
{
	char piece;
	int points, gamemode;
	Element *next;
};
class Ranking
{
private:
	Element *head;
	char character;
public:
	Ranking();
	void add(char piece, int points, int gamemode);
	int loadRanking();
	void saveRanking();
	void write();
};