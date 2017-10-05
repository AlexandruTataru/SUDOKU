#include "solver.h"

uint8_t *board;

bool loadBoard(uint8_t *incomingBoard)
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

	return true;
}

bool solveBoard()
{
	for (uint8_t i = 0; i < 81; ++i)
	{
		board[i] += 1;
	}

	return true;
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
	for (uint8_t i = 0; i < 81; ++i)
	{
		solvedBoard[i] = 5;
	}
	return true;
}