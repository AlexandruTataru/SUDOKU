#include "solver.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t board[9][9];

bool loadBoard(uint8_t *incomingBoard)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	size_t row = 0, column = 0;
	for (int i = 0; i < 81; ++i)
	{
		board[row][column] = incomingBoard[i];
		column++;
		if (column == 9)
		{
			column = 0;
			row++;
		}
	}

	row = 0; column = 0;
	for (; row < 9; ++row)
	{
		for (column = 0; column < 9; ++column)
		{
			printf("%d ", board[row][column]);
		}
		printf("\n");
	}

	return true;
}

bool solveBoard()
{
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