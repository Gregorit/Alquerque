#include "GameParticipant.h"

void gameParticipant::move(Board<char> &plansza) {}
gameParticipant::gameParticipant(char pio) : piece(pio) {}

char gameParticipant::get_piece()
{
	return piece;
}