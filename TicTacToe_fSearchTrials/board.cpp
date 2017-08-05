#include <iostream>
#include <conio.h>

#include "board.h"
#include "search.h"

subfield Xs = 0;
subfield Os = 0;
board game =   { '0','0','0',
			     '0','0','0',
			     '0','0','0' };
std::vector<board> history;
subfield winStates[8] = {   0b000000111,
							0b000111000,
							0b111000000,
							0b100100100,
							0b010010010,
							0b001001001,
							0b100010001,
							0b001010100 
							};
int player;

void representBoard()
{
	int index = 8;
	std::cout << std::endl;
	std::cout << " " << game.at(index--) << " | " << game.at(index--) << " | " << game.at(index--) << std::endl
		      << "¯¯¯¯¯¯¯¯¯¯¯" << std::endl
			  << " " << game.at(index--) << " | " << game.at(index--) << " | " << game.at(index--) << std::endl
			  << "¯¯¯¯¯¯¯¯¯¯¯" << std::endl
			  << " " << game.at(index--) << " | " << game.at(index--) << " | " << game.at(index--) << std::endl << std::endl;
}

void initGame()
{
	history.push_back(game);
}

void undo()
{
	if (counter == 0) return;
	game = history.at(counter - 1);
	history.pop_back();
	counter--;
}

void choosePlayer()
{
	char choice;
	while (true) {
		std::cout << "Which player do you want to play? (X|O)\n";
		std::cin >> choice;
		tolower(choice);
		if (choice != 'x' && choice != 'o')
		{
			system("CLS");
			std::cout << "Invalid input, please choose between X or O: \n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else break;
	}
	if (choice == 'x') player = X;
	else player = O;
}

void runGame()
{
	int currState;
	while (true)
	{
		if (currPlayer == player) {
			getMove();
			currState = determineState();
			if (currState != NO_STATE) break;
			ply++;
			system("CLS");
			representBoard();
			currPlayer *= -1;
		}

		AiMove();
		currState = determineState();
		if (currState != NO_STATE) break;
		ply++;
		system("CLS");
		representBoard();
		currPlayer *= -1;
	}

	system("CLS");
	representBoard();

	switch(currState)
	{
	case DRAW: std::cout << "The game ended in a draw.\n";
		break;
	case X_WON: std::cout << "X won!\n";
		break;
	case O_WON: std::cout << "O WON!\n";
		break;
	default: std::cout << "wtf\n";
	}	
}

void getMove()
{
	int row = 0;
	int column = 0;
	while (true) {
		while (true) {
			std::cout << "Enter row \n";
			std::cin >> row;
			if (row < 1 || row > 3)
			{
				system("CLS");
				representBoard();
				std::cout << "Row must be between 1 and 3, please reenter\n";
				continue;
			}
			std::cout << "Enter column \n";
			std::cin >> column;
			if (column < 1 || column > 3)
			{
				system("CLS");
				representBoard();
				std::cout << "Row must be between 1 and 3, please reenter\n";
				continue;
			}
			break;
		}
		int choice = (row - 1) * 3 + column - 1;
		if (game.at(choice) != '0')
		{
			std::cout << "Square is already taken, please reenter your choice: \n";
			continue;
		}
		game.at(choice) = currPlayer == X? 'X' : 'O';
		if (currPlayer == X){
			Xs.set(choice, true);
		}
		else{
			Os.set(choice, true);
		}
		break;
	}
}

int determineState()
{

	for(int i = 0; i < 8; i++)
	{
		if ((winStates[i] & Xs) == winStates[i]) return X_WON;
		if ((winStates[i] & Os) == winStates[i]) return O_WON;
	}
	if ((Xs | Os) == 0b111111111) return DRAW;

	return NO_STATE;
}