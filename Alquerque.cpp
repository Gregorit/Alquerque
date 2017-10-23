//Defines for cleaning terminal/commandline which supports multiple systems
#ifdef _WIN32 //For Windows OS
#define CLEAR "cls"
#else //Any other OS
#define CLEAR "clear"
#endif

#include <iostream>
#include "Alquerque.h"
#define PIECE_1 'O'
#define PIECE_2 'X'
using namespace std;

//DEFAULT CONSTRUCTOR
Alquerque::Alquerque() : player1(new Player(PIECE_1)), player2(new Player(PIECE_2)), computer(new Computer(PIECE_2)) {}

void Alquerque::writeRules()
{
	system(CLEAR);
	cout << "RULES OF ALQUERQUE:" << endl;
	cout << "Rules are similar to checkers. The purpose of the game is to capture all enemy's" << endl << "pieces from board." << endl;
	cout << "This game is designated to 2 persons only. Each player at the beginning of the game" << endl;
	cout << "have 12 pieces. All field on board are occupied by pieces except middle." << endl;
	cout << "Pieces can move only on designated lines on board. Normal move distance is 1 field." << endl;
	cout << "Players are making moves alternately. Making a capturing move is only possible if" << endl;
	cout << "enemy's piece is exactly 1 field distance from our piece and behind enemy's piece" << endl;
	cout << "is empty field (exactly 2 field distance from our piece). Multiple capturing moves" << endl;
	cout << "are permitted. If there are minimum 2 different capturing moves then you can choose" << endl;
	cout << "which one you want to perform. The game ends when one of the players will not have any pieces" << endl;
	cout << "on board." << endl << endl;
	cout << "Press Enter to return to the main menu.";
	cin.ignore().get(); //waiting for input
}

void Alquerque::mainMenu()
{
	int choice;
	int choiceConfirmation = 0;	//a counter that checks confirmation of choice when exiting the game
	while (choiceConfirmation != 1)
	{
		system(CLEAR);
		cout << "\t  ~~~~~~ ALQUERQUE ~~~~~~" << endl;
		cout << "\t   AUTHOR: GRZEGORZ URYCH\n\n" << endl;
		cout << "       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++        MAIN MENU:       ++\n       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++(1)New game\t\t  ++\n       ++(2)Load last game\t  ++\n       ++(3)Rules\t\t  ++\n       ++(4)Scoreboard\t\t  ++" << endl;
		cout << "       +++++++++++++++++++++++++++++" << endl;
		cout << "       ++(0)Exit from game\t  ++\n       +++++++++++++++++++++++++++++" << endl << endl;
		cout << "\t       Your choose: ";
		cin >> choice;
		switch (choice)
		{
		case 1:	//new game
			system(CLEAR);
			cout << "\t    ~~~~~~ ALQUERQUE ~~~~~~" << endl;
			cout << "\t     AUTHOR: GRZEGORZ URYCH\n\n" << endl;
			cout << "       ++++++++++++++++++++++++++++++++" << endl;
			cout << "       ++      CHOOSE GAME MODE:     ++\n       ++++++++++++++++++++++++++++++++" << endl;
			cout << "       ++(1)Player vs Player\t     ++\n       ++(2)Player vs CPU\t     ++" << endl;
			cout << "       ++++++++++++++++++++++++++++++++" << endl;
			cout << "       ++(0)Back to main menu\t     ++\n       ++++++++++++++++++++++++++++++++" << endl;
			cout << "\n                Your choose: ";
			cin >> choice;
			switch (choice)
			{
			case 1:	//start game (Player vs Player)
				while (board.checkGameOver() == 1)
				{
					gameMode = 1;
					board.write();
					player1->move(board);
					move = PIECE_2;
					board.saveBoard(gameMode, move);
					if (board.checkGameOver() == 1)
					{
						board.write();
						player2->move(board);
						move = PIECE_1;
						board.saveBoard(gameMode, move);
					}
				}
				move = move == PIECE_1 ? PIECE_2 : PIECE_1;
				//ADDING TO THE RANKING
				ranking.add(move, board.howManyPieces(move), gameMode);
				board.write();
				cout << "GAME OVER" << endl << endl;
				cout << "Press Enter to return to the main menu.";
				cin.ignore().get(); //waiting for input
				break;
			case 2:	//start game (Player vs CPU (AI on rand))
				while (board.checkGameOver() == 1)
				{
					gameMode = 2;
					board.write();
					player1->move(board);
					move = PIECE_2;
					board.saveBoard(gameMode, move);
					if (board.checkGameOver() == 1)
					{
						board.write();
						computer->move(board);
						move = PIECE_1;
						board.saveBoard(gameMode, move);
					}
				}
				move = move == PIECE_1 ? PIECE_2 : PIECE_1;
				//ADDING TO THE RANKING
				ranking.add(move, board.howManyPieces(move), gameMode);
				board.write();
				cout << "GAME OVER" << endl << endl;
				cout << "Press Enter to return to the main menu.";
				cin.ignore().get(); //waiting for input
				break;
			case 0:	//back to the menu
				break;
			}
			break;
		case 2:	//loading save file
			gameMode = board.loadBoard(move);

			if (gameMode == 1 || gameMode == 2)
			{
				if (board.checkGameOver() != 1)
				{
					cout << "This save includes already ended game." << endl;
					cout << "Returning to the main menu..." << endl << endl;
					cout << "Press Enter to continue.";
					cin.ignore().get(); //waiting for input
					break;
				}
				cout << "Save has been loaded successfully." << endl;
				cout << "Press Enter to continue.";
				cin.ignore().get(); //waiting for input
			}
			if (gameMode == 1)
			{
				if (move == PIECE_2)
				{
					board.write();
					player2->move(board);
					move = PIECE_1;
					board.saveBoard(gameMode, move);
				}
				while (board.checkGameOver() == 1)
				{
					gameMode = 1;
					board.write();
					player1->move(board);
					move = PIECE_2;
					board.saveBoard(gameMode, move);
					if (board.checkGameOver() == 1)
					{
						board.write();
						player2->move(board);
						move = PIECE_1;
						board.saveBoard(gameMode, move);
					}
				}
			}
			else if (gameMode == 2)
			{
				if (move == PIECE_2)
				{
					board.write();
					computer->move(board);
					move = PIECE_1;
					board.saveBoard(gameMode, move);
				}
				while (board.checkGameOver() == 1)
				{
					gameMode = 2;
					board.write();
					player1->move(board);
					move = PIECE_2;
					board.saveBoard(gameMode, move);
					if (board.checkGameOver() == 1)
					{
						board.write();
						computer->move(board);
						move = PIECE_1;
						board.saveBoard(gameMode, move);
					}
				}
			}
			else
			{
				cout << "No save file." << endl;
				cout << "Returning to the main menu..." << endl << endl;
				cout << "Press Enter to continue.";
				cin.ignore().get(); //waiting for input
				break;
			}
			//ADDING TO THE RANKING
			move = move == PIECE_1 ? PIECE_2 : PIECE_1;
			ranking.add(move, board.howManyPieces(move), gameMode);
			board.write();
			cout << "GAME OVER" << endl << endl;
			cout << "Press Enter to return to the main menu.";
			cin.ignore().get(); //waiting for input
			break;
		case 3: //rules
			writeRules();
			break;
		case 4:
			system(CLEAR);
			cout << "SCOREBOARD:" << endl;
			cout << "[Who, pieces left, game mode]" << endl << endl;
			ranking.write();
			cout << endl << "Press Enter to return to the main menu.";
			cin.ignore().get(); //waiting for input
			break;
		case 0:	//exit from program
			system(CLEAR);
			cout << "Are you sure to exit the program?\n[(1)Yes, (0)No]: ";
			cin >> choiceConfirmation;
			if (choiceConfirmation == 1)
			{
				cout << "\nSee you soon. Thanks for playing." << endl;
				break;
			}
		}
	}
}

Alquerque::~Alquerque()
{
	delete player1;
	delete player2;
	delete computer;
}
