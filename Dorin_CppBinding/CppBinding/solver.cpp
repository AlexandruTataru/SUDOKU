#include "solver.h"

void readBoard(uint8_t *incomingBoard)
{
	if (board)
	{
		delete[] board;
		board = nullptr;
	}

	board = new uint8_t[81];

	for (uint8_t i = 0; i < 81; ++i)
	{
		board[i] = 5;
	}
}

void solveBoard()
{
	for (uint8_t i = 0; i < 81; ++i)
	{
		board[i] += 1;
	}
}

void retrieveSolvedBoard(uint8_t* solvedBoard)
{
	solvedBoard = board;
}