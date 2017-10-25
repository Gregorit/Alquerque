#include <iostream>
#include <limits> //it's needed to make this line works in gcc: cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include "Player.h"
#define PIECE_2 'X'
using namespace std;

Player::Player() : gameParticipant(PIECE_2) {}
Player::Player(char pie) : gameParticipant(pie) {}

void Player::move(Board<char> &board)
{
	char from_i;
	int from_j;
	char to_i;
	int to_j;
	bool okCheck = 0;
	bool ifAnotherCapturingMove = 0;

	cout << "== Player " << get_piece() << " move ==" << endl;
	while (okCheck != 1)
	{
		if (ifAnotherCapturingMove == 0)
		{
			cout << "Give coordinates of your's piece, which you want to make a move" << endl << "(how to?: Letter Number): ";
			cin >> from_i;
			cin.clear();
			cin >> from_j;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	//deleting from stream cin all incorrect characters
			if (from_i < 'A' || from_i > 'A' + PIECES_ARRAY_MAX || from_j < 0 || from_j > 4 || get_piece() != board.arr[from_j][from_i - 'A'])
			{
				from_i = 'z';
				from_j = -999;
				cout << endl << "*****************************************************" << endl;
				cout << "**            The field chosen by you:             **" << endl;
				cout << "*****************************************************" << endl;
				cout << "**   #contains an enemy's piece,\t\t   **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #contains an empty field,\t\t\t   **" << endl << "**\tor\t\t\t\t\t   **" << endl << "**   #field was inputted incorrectly.\t\t   **" << endl;
				cout << "*****************************************************" << endl;
				cout << "** Try again." << endl << endl;
				continue;
			}
		}
		else
		{
			from_i = from_i + 'A';
			from_j = from_j;
		}

		bool insideOkCheck = 0;
		while (insideOkCheck != 1)
		{
			cout << "Give coordinates of empty field for making a move: ";
			cin >> to_i;
			cin.clear();
			cin >> to_j;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');	//deleting from stream cin all incorrect characters
			if (to_i < 'A' || to_i > 'A' + PIECES_ARRAY_MAX || to_j < 0 || to_j > 4 || board.arr[to_j][to_i - 'A'] != ' ')
			{
				to_i = 'z';
				to_j = -999;
				cout << endl << "****************************************************" << endl;
				cout << "**            The field chosen by you:            **" << endl;
				cout << "****************************************************" << endl;
				cout << "**   #is not an empty field.\t\t\t  **" << endl;
				cout << "****************************************************" << endl;
				cout << "** Try again." << endl << endl;
				continue;
			}
			insideOkCheck = 1;
		}

		int distance_i = abs(from_i - to_i);
		int distance_j = abs(from_j - to_j);
		from_i -= 'A';
		to_i -= 'A';

		if ((distance_i == 1 && distance_j == 0) || (distance_i == 0 && distance_j == 1) || (distance_i == 1 && distance_j == 1)) //normal move
		{
			if (board.checkCapturingMove(*this))
			{
				cout << "************************************************" << endl;
				cout << "** Capturing move available!\t\t      **" << endl << "** Normal move is not possible right now.     **" << endl;
				cout << "************************************************" << endl;
				cout << "** Try again." << endl << endl;
				continue;
			}
			if (from_i % 2 == from_j % 2)
			{
				board.arr[from_j][from_i] = ' ';
				board.arr[to_j][to_i] = get_piece();
				okCheck = 1;
			}
			else if (distance_i == 1 && distance_j == 1)
			{
				cout << "****************************" << endl;
				cout << "** Unallowable direction. **" << endl;
				cout << "****************************" << endl;
				cout << "** Try again." << endl << endl;
				continue;
			}
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
					cout << "************************************************************************" << endl;
					cout << "** Continuation of capturing move is available! Piece coordinates: " << (char)(to_i + 'A') << to_j << " **" << endl;
					cout << "************************************************************************" << endl;
				}
			}
			else //unallowable direction
			{
				cout << "****************************" << endl;
				cout << "** Unallowable direction. **" << endl;
				cout << "****************************" << endl;
				cout << "** Try again." << endl << endl;
				continue;
			}
		}
		else //forbidden move
		{
			cout << "*********************" << endl;
			cout << "** Forbidden move. **" << endl;
			cout << "*********************" << endl;
			cout << "** Try again." << endl << endl;
			continue;
		}
	}
}
