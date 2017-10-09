#pragma once

#include <cstdint>
#include <set>

class Board
{
	struct Region;
	struct Square;

	struct Square
	{
		uint8_t value, row, column;
		std::set<uint8_t> possibleValues;
		Region* region;
	};

	struct Region
	{
		std::set<Square*> includedSquares;
	};

	Square board[9][9];

	Square& operator ()(uint8_t r, uint8_t c)
	{
		return board[r][c];
	}
};