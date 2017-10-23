#include "Alquerque.h"

int main()
{
	Alquerque *game = new Alquerque();
	game->mainMenu();
	delete game;
	return 0;
}