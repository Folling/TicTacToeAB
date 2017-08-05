#pragma once

#include <algorithm>
#include <iostream>

#include "board.h"

void AiMove();

int alphabeta(int alpha, int beta, int l_player);

std::vector<int> getScores();
std::vector<int> possibleMoves();