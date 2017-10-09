#include "BruteForceSolver.h"

BruteForceSolver::BruteForceSolver()
{
}


BruteForceSolver::~BruteForceSolver()
{
}

bool BruteForceSolver::loadBoard(uint8_t* incomingBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row)
	{
		for (uint8_t column = 0; column < 9; ++column)
		{
			board[row][column].row = row;
			board[row][column].column = column;
			board[row][column].value = incomingBoard[i++];
		}
	}
	return true;
}

bool BruteForceSolver::solveBoard()
{

}

bool BruteForceSolver::retrieveSolvedBoard(uint8_t* solvedBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) solvedBoard[i++] = board[row][column].value;
	return true;
}
