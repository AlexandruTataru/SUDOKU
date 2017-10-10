#pragma once

#include <cstdint>
#include <set>
#include <vector>
#include <stack>
#include <map>
#include <algorithm>

#include "Console.h"

using namespace std;

class Board
{
public:
	Console console;

	struct Region;
	struct Square;

	struct Square
	{
		uint8_t value, row, column;
		std::vector<uint8_t> possibleValues;
		Region* region;
	};

	struct Region
	{
		std::vector<Square*> includedSquares;
	};

	Square board[9][9];
	Region regions[3][3];

	Board()
	{
		uint8_t possibleValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		for (uint8_t row = 0; row < 9; ++row)
		{
			for (uint8_t column = 0; column < 9; ++column)
			{
				board[row][column].row = row;
				board[row][column].column = column;
				board[row][column].value = 0;
				std::copy(begin(possibleValues), end(possibleValues), board[row][column].possibleValues.begin());
				board[row][column].region = &regions[row / 3][column / 3];
				regions[row / 3][column / 3].includedSquares.emplace_back(&board[row][column]);
			}
		}
	}

	Board(const Board& other)
	{
	}

	Square& operator ()(uint8_t r, uint8_t c)
	{
		return board[r][c];
	}
};