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

	typedef std::vector<Square*> line;

	struct Square
	{
		uint8_t value, row, column;
		std::vector<uint8_t> allowedValues;
		Region* region;

		Square()
		{
			value = 0;
			uint8_t possibleValues[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			std::copy(possibleValues, possibleValues + 9, std::back_inserter(allowedValues));
		}

		void AssignLocation(uint8_t r, uint8_t c, Region& reg)
		{
			row = r;
			column = c;
			region = &reg;
			reg.includedSquares.emplace_back(this);
		}
	};

	struct Region
	{
		std::vector<Square*> includedSquares;
	};

	Square board[9][9];
	Region regions[3][3];

	Board()
	{
		for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) board[row][column].AssignLocation(row, column, regions[row / 3][column / 3]);
	}

	void printBoard()
	{
		for (uint8_t r = 0;r < 9;++r)
		{
			for (uint8_t c = 0;c < 9;++c)
				console << (int)board[r][c].value << " ";
			console << "\n";
		}
	}

	line getRow(uint8_t r)
	{
		line row;
		for (uint8_t c = 0;c < 9;++c) row.emplace_back(&board[r][c]);
		return row;
	}

	line getColumn(uint8_t c)
	{
		line column;
		for (uint8_t r = 0;r < 9;++r) column.emplace_back(&board[r][c]);
		return column;
	}

	void placeValue(uint8_t r, uint8_t c, uint8_t v)
	{
		Square &square = board[r][c];

		// Process region
		for (auto square : square.region->includedSquares)
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
		}

		// Process row
		for (auto square : getRow(r))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
		}

		// Process column
		for (auto square : getColumn(c))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
		}

		// Process direct square
		square.value = v;
		square.allowedValues.clear();
		square.allowedValues.emplace_back(v);
	}

	Square& operator ()(uint8_t r, uint8_t c)
	{
		return board[r][c];
	}
};