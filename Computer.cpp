#include <iostream>
#include <ctime>
#include "Computer.h"
#define PIECE_2 'X'
using namespace std;

Computer::Computer() : gameParticipant(PIECE_2) {}
Computer::Computer(char pio) : gameParticipant(pio) {}

void Computer::move(Board<char> &board)
{
	char from_i;
	int from_j;
	char to_i;
	int to_j;
	bool okCheck = 0;
	bool ifAnotherCapturingMove = 0;
	srand(time(NULL));

	cout << "== WAIT!: CPU is making a move ==" << endl;
	while (okCheck != 1)
	{
		if (ifAnotherCapturingMove == 0)
		{
			from_j = rand() % PIECES_ARRAY_MAX;
			from_i = rand() % PIECES_ARRAY_MAX + 'A';
			if (from_i < 'A' || from_i > 'A' + PIECES_ARRAY_MAX || from_j < 0 || from_j > 4 || get_piece() != board.arr[from_j][from_i - 'A'])
			{
				from_i = 'z';
				from_j = -999;
				continue;
			}
		}

		bool insideOkCheck = 0;
		while (insideOkCheck != 1)
		{
			to_j = rand() % PIECES_ARRAY_MAX;
			to_i = rand() % PIECES_ARRAY_MAX + 'A';
			if (to_i < 'A' || to_i > 'A' + PIECES_ARRAY_MAX || to_j < 0 || to_j > 4 || board.arr[to_j][to_i - 'A'] != ' ')
			{
				to_i = 'z';
				to_j = -999;
				continue;
			}
			insideOkCheck = 1;
		}

		if (ifAnotherCapturingMove == 0)
			from_i -= 'A';
		to_i -= 'A';
		int distance_i = abs(from_i - to_i);
		int distance_j = abs(from_j - to_j);

		if ((distance_i == 1 && distance_j == 0) || (distance_i == 0 && distance_j == 1) || (distance_i == 1 && distance_j == 1)) //normal move
		{
			if (board.checkCapturingMove(*this))
				continue;
			if (from_i % 2 == from_j % 2)
			{
				board.arr[from_j][from_i] = ' ';
				board.arr[to_j][to_i] = get_piece();
				okCheck = 1;
			}
			else if (distance_i == 1 && distance_j == 1)
				continue;
			else
			{
				board.arr[from_j][from_i] = ' ';
				board.arr[to_j][to_i] = get_piece();
				okCheck = 1;
			}
		}
		else if ((distance_i == 2 && distance_j == 0) || (distance_i == 0 && distance_j == 2) || (distance_i == 2 && distance_j == 2)) //declaration of capturing move
		{
			if (board.checkPossibleCapturingMoves(from_j, from_i, to_j, to_i, get_piece()) == 1)
			{
				board.arr[from_j][from_i] = ' ';
				board.arr[from_j + ((to_j - from_j) / 2)][from_i + ((to_i - from_i) / 2)] = ' ';
				board.arr[to_j][to_i] = get_piece();
				//making a capturing move
				okCheck = 1;
				if (board.checkContinuationOfCapturingMove(to_j, to_i, *this) != 0)
				{
					okCheck = 0;
					board.write();
					ifAnotherCapturingMove = 1;
					from_i = to_i;
					from_j = to_j;
					cout << "== WAIT!: CPU is making a move ==" << endl;
				}
			}
			else //unallowable direction
				continue;
		}
		else //forbidden move
			continue;
	}
}
