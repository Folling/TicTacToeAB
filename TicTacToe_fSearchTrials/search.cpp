#include "search.h"

void AiMove()
{
	int movInd = 0;
	bool isO = (player == X);
	subfield* AIfield = (isO? &Os : &Xs);
	int currScore = (isO? std::numeric_limits<int>::max(): -std::numeric_limits<int>::max());
	std::vector<int> moves = possibleMoves();
	std::vector<int> scores = getScores();

	for(int i = 0; i < scores.size(); i++)
	{
		if((isO && scores.at(i) < currScore) 
			|| (!isO && scores.at(i) > currScore))
		{
			currScore = scores.at(i);
			movInd = i;
		}		
	}
	AIfield->set(moves.at(movInd), true);
	game.at(moves.at(movInd)) = (isO? 'O' : 'X');
}

int alphabeta(int alpha, int beta, int l_player)
{
	int state = determineState();
	if (state != NO_STATE) {
		if (state == DRAW)	return state;
		return (state + ply * player);
	}
	bool breakStatement = false;

	std::vector<int> moves = possibleMoves();

	if(l_player == X)
	{
		int bestVal = -std::numeric_limits<int>::max();
		for(int i = 0; i < moves.size(); i++)
		{
			ply++;
			Xs.set(moves.at(i), true);
			bestVal = std::max(bestVal, alphabeta(alpha, beta, O));
			alpha = std::max(alpha, bestVal);
			if (beta <= alpha) breakStatement = true;
			Xs.set(moves.at(i), false);
			ply--;
			if (breakStatement) break;
		}
		return bestVal;
	}
	else
	{
		int bestVal = std::numeric_limits<int>::max();
		for (int i = 0; i < moves.size(); i++)
		{
			ply++;
			Os.set(moves.at(i), true);
			bestVal = std::min(bestVal, alphabeta(alpha, beta, X));
			beta = std::min(beta, bestVal);
			if (beta <= alpha) breakStatement = true;
			Os.set(moves.at(i), false);
			ply--;
			if (breakStatement) break;
		}
		return bestVal;
	}
}

std::vector<int> getScores()
{
	std::vector<int> moves = possibleMoves();
	std::vector<int> scores; 
	subfield* AIfield = (player == X? &Os : &Xs);
	for(int i = 0; i < moves.size(); i++)
	{
		AIfield->set(moves.at(i), true);
		ply++;
		scores.push_back(alphabeta(-std::numeric_limits<int>::max(), 
								    std::numeric_limits<int>::max(), player));
		AIfield->set(moves.at(i), false);
		ply--;
	}
	return scores;
}

std::vector<int> possibleMoves()
{
	std::vector<int> result;
	for(int i = 0; i < Os.size(); i++)
	{
		if (Os.test(i) == false && Xs.test(i) == false) result.push_back(i);
	}
	return result;
}