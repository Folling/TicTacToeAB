#include <iostream>
#include <conio.h>
#include "board.h"

int main()
{
	choosePlayer();
	initGame();
	representBoard();	
	runGame();
	_getch();
}
