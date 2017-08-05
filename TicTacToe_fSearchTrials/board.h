#pragma once

#include <bitset>
#include <vector>

#define O_WON   -10
#define X_WON    10
#define DRAW     0 
#define NO_STATE 4

#define X   1
#define O  -1

typedef std::bitset<9> subfield;
typedef std::vector<char> board;
typedef int state;

extern subfield Xs;
extern subfield Os;
static int currPlayer = X;
static int ply = 1;

extern board game;
extern int player;

static int counter = 0;

extern std::vector<board> history;

void undo();

void choosePlayer();
void representBoard();
void initGame();
void runGame();


void getMove();

int determineState();