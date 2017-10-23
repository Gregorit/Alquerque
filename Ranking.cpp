#include <iostream>
#include "Ranking.h"
#include "Board.h"
#define PIECE_1 'O'
#define PIECE_2 'X'

void Ranking::saveRanking()
{
	FILE *ranking_save;
	ranking_save = fopen("ranking.txt", "w");
	Element *pointer = head;
	while (pointer != NULL)
	{
		if (pointer->next !=NULL)
			fprintf(ranking_save, "%c %d %d\n", pointer->piece, pointer->points, pointer->gamemode);
		pointer = pointer->next;
	}
	fclose(ranking_save);
}

int Ranking::loadRanking()
{
	FILE *ranking_load;
	ranking_load = fopen("ranking.txt", "r");
	if (ranking_load == NULL)
	{
		return 0;
	}
	character = getc(ranking_load);
	if (character == EOF)
	{
		return 0;
	}
	rewind(ranking_load);

	Element *pointer = NULL;
	while (!feof(ranking_load))
	{
		if (head == NULL)
		{
			pointer=head = new Element();
			fscanf(ranking_load, "%c %d %d\n", &head->piece, &head->points, &head->gamemode);
			head->next = NULL;
		}
		else
		{
			pointer->next = new Element();
			pointer = pointer->next;
			fscanf(ranking_load, "%c %d %d\n", &pointer->piece, &pointer->points, &pointer->gamemode);
			pointer->next = NULL;
		}
	}

	fclose(ranking_load);
}

void Ranking::add(char piece, int points, int gamemode)
{
	if (head == NULL)
	{
		head = new Element();
		head->piece = piece;
		head->points = points;
		head->gamemode = gamemode;
		head->next = NULL;
	}
	else
	{
		Element *pointer = head;
		while (pointer->next != NULL)
			pointer = pointer->next;
		pointer->next = new Element();
		pointer = pointer->next;
		pointer->piece = piece;
		pointer->points = points;
		pointer->gamemode = gamemode;
		pointer->next = NULL;
	}
	saveRanking();
}

Ranking::Ranking() :head(NULL)
{
	loadRanking();
};

void Ranking::write()
{
	Element *pointer = head;
	while (pointer!= NULL)
	{
		cout << pointer->piece << " " << pointer->points << "\t";
		if (pointer->gamemode == 1)
			cout << "Player vs Player" << endl;
		else if (pointer->gamemode == 2)
			cout << "Player vs Computer" << endl;
		pointer = pointer->next;
	}

}