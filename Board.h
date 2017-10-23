#pragma once
//#pragma warning (disable : 4996) //if there will be a problem with fopen

//Defines for cleaning terminal/commandline which supports multiple systems
#ifdef _WIN32 //For Windows OS
#define CLEAR "cls"
#else //Any other OS
#define CLEAR "clear"
#endif

#include <iostream>
#include "GameParticipant.h"
#define PIECE_1 'O'
#define PIECE_2 'X'
#define PIECES_ARRAY_MAX 5
#define MAX PIECES_ARRAY_MAX+4
using namespace std;

class gameParticipant;

template<typename T1>
class Board
{
private:
	T1 arr[PIECES_ARRAY_MAX][PIECES_ARRAY_MAX];
public:
	friend class Player;
	friend class Computer;
	Board()
	{
		/** Initialization of the pieces to the array arr[i][j] **/
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			if (i <= 1)
				arr[i][j] = PIECE_2;
			else if (i == 2)
			{
				if (j <= 1)
					arr[i][j] = PIECE_2;
				else if (j == 2)
					arr[i][j] = ' ';
				else
					arr[i][j] = PIECE_1;
			}
			else
				arr[i][j] = PIECE_1;
		}
	}

	char get_arr(int i, int j)
	{
		return arr[i][j];
	}

	bool checkGameOver()
	{
		int checkPlayer1 = 0; //amout of 1st player's pieces
		int checkPlayer2 = 0; //amout of 2nd player's pieces
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			if (arr[i][j] == PIECE_2)
				checkPlayer1++;
			if (arr[i][j] == PIECE_1)
				checkPlayer2++;
		}
		if (checkPlayer1 == 0 || checkPlayer2 == 0) //if 1st or 2nd player is out of pieces, then game over
			return 0;
		else
			return 1;
	}

	/** Returns to ranking how many pieces have victorious player. **/
	int howManyPieces(char piece)
	{
		int numberOfPieces = 0;
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			if (arr[i][j] == piece)
				numberOfPieces++;
		}
		return numberOfPieces;
	}

	bool checkCapturingMove(gameParticipant &player) //in VS '13: bool checkCapturingMove(gameParticipant player)
	{
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			if (arr[i][j] == player.get_piece())
			{
				if (checkContinuationOfCapturingMove(i, j, player) != 0)
					return 1;
			}
		}
		return 0;
	}

	bool checkContinuationOfCapturingMove(int from_i, int from_j, gameParticipant &player) //in VS '13: bool checkContinuationOfCapturingMove(int from_i, int from_j, gameParticipant player)
	{
		int checking = 0;
		//on normal
		if (from_i < 3)
			checking += checkPossibleCapturingMoves(from_i, from_j, from_i + 2, from_j, player.get_piece());
		if (from_j < 3)
			checking += checkPossibleCapturingMoves(from_i, from_j, from_i, from_j + 2, player.get_piece());
		if (from_i >= 2)
			checking += checkPossibleCapturingMoves(from_i, from_j, from_i - 2, from_j, player.get_piece());
		if (from_j >= 2)
			checking += checkPossibleCapturingMoves(from_i, from_j, from_i, from_j - 2, player.get_piece());
		if (from_i % 2 == from_j % 2) //on diagonal
		{
			if (from_i >= 2 && from_j < 3)
				checking += checkPossibleCapturingMoves(from_i, from_j, from_i - 2, from_j + 2, player.get_piece());
			if (from_i < 3 && from_j >= 2)
				checking += checkPossibleCapturingMoves(from_i, from_j, from_i + 2, from_j - 2, player.get_piece());
			if (from_i >= 2 && from_j >= 2)
				checking += checkPossibleCapturingMoves(from_i, from_j, from_i - 2, from_j - 2, player.get_piece());
			if (from_i < 3 && from_j < 3)
				checking += checkPossibleCapturingMoves(from_i, from_j, from_i + 2, from_j + 2, player.get_piece());
		}
		if (checking != 0)
			return 1;
		else
			return 0;
	}

	bool checkPossibleCapturingMoves(int from_i, int from_j, int to_i, int to_j, char piece)
	{
		if (arr[(from_i + to_i) / 2][(from_j + to_j) / 2] == piece || arr[(from_i + to_i) / 2][(from_j + to_j) / 2] == ' ' || arr[to_i][to_j] != ' ') //checking above the opponent's pawn
			return 0;
		else if (from_i % 2 != from_j % 2 && (from_i == to_i || from_j == to_j)) //non diagonal
			return 1;
		else if (from_i % 2 == from_j % 2)
			return 1;
		return 0;
	}

	void saveBoard(int gaMod, int mv)
	{
		FILE *boardSave;
		boardSave = fopen("board.txt", "w");
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			if (arr[i][j] == ' ')
				fprintf(boardSave, "_");
			else
				fprintf(boardSave, "%c", arr[i][j]);
		}
		if (gaMod == 1)
			fprintf(boardSave, "1");
		else if (gaMod == 2)
			fprintf(boardSave, "2");
		if (mv == PIECE_1)
			fprintf(boardSave, "%c", PIECE_1);
		else if (mv == PIECE_2)
			fprintf(boardSave, "%c", PIECE_2);
		fclose(boardSave);
	}

	int loadBoard(T1 &mv)
	{
		FILE *boardLoad;
		char gaMod;
		boardLoad = fopen("board.txt", "r");
		if (boardLoad == NULL)
			return 0;
		for (int i = 0; i < PIECES_ARRAY_MAX; i++)
		for (int j = 0; j < PIECES_ARRAY_MAX; j++)
		{
			fscanf(boardLoad, "%c", &arr[i][j]);
			if (arr[i][j] == '_')
				arr[i][j] = ' ';
		}
		fscanf(boardLoad, "%c", &gaMod);
		fscanf(boardLoad, "%c", &mv);
		if (gaMod == '1')
			return 1;
		else
			return 2;
		fclose(boardLoad);
	}

	void write()
	{
		char letter = 65;
		int number = 0;

		system(CLEAR);
		cout << "  ";
		for (int i = 0; i < MAX - 4; i++)
		{
			cout << letter << "   ";
			letter++;
		}
		cout << endl;
		for (int i = 0; i < MAX; i++)
		{
			if (i % 2 == 0)
			{
				cout << number << " ";
				number++;
			}
			for (int j = 0; j < MAX; j++)
			{
				if (i % 2 == 0)
				{
					if (j % 2 == 0)
						cout << arr[i / 2][j / 2];
					else
						cout << " - ";
				}
				else
				{
					if (j == 0)
						cout << "  ";
					if (j % 2 == 0)
						cout << "| ";
					else
					{
						if (i == 1 || i == 5)
						{
							if (j == 1 || j == 5)
								cout << "\\ ";
							else
								cout << "/ ";
						}
						else
						{
							if (j == 1 || j == 5)
								cout << "/ ";
							else
								cout << "\\ ";
						}
					}
				}
			}
			cout << endl;
		}
	}
};
