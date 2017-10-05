#include "solver.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <set>
#include <algorithm>
#include <numeric>

uint8_t board[9][9];

bool internal_isRowValid(uint8_t row)
{
	std::set<uint8_t> values;
	for (uint8_t column = 0; column < 9; ++column) values.insert(board[row][column]);
	return std::accumulate(values.begin(), values.end(), 0) == 45;
}

bool internal_isColumnValid(uint8_t column)
{
	std::set<uint8_t> values;
	for (uint8_t row = 0; row < 9; ++row) values.insert(board[row][column]);
	return std::accumulate(values.begin(), values.end(), 0) == 45;
}

bool internal_isBoardSolved()
{
	size_t sum = 0;
	int row = 0, column = 0;
	for (; row < 9; ++row) for (column = 0; column < 9; ++column) sum += board[row][column];

	if (sum != 405) return false;

	for (uint8_t idx = 0; idx < 9; ++idx) if (!internal_isRowValid(idx) || !internal_isColumnValid(idx)) return false;

	return true;
}

bool internal_hasColumnDigit(uint8_t colNr, uint8_t digit)
{
	for (uint8_t row = 0; row < 9; ++row) if (board[row][colNr] == digit) return true;
	return false;
}

bool internal_hasRowDigit(uint8_t rowNr, uint8_t digit)
{
	for (uint8_t column = 0; column < 9; ++column) if (board[rowNr][column] == digit) return true;
	return false;
}

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
	while (!internal_isBoardSolved())
	{

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