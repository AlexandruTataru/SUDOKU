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

		void AssignLocationWithValue(uint8_t r, uint8_t c, Region& reg, Square s)
		{
			AssignLocation(r, c, reg);
			value = s.value;
			allowedValues.clear();
			std::copy(s.allowedValues.begin(), s.allowedValues.end(), std::back_inserter(allowedValues));
		}

		bool isAvailable()
		{
			return value == 0;
		}
	};

	struct Region
	{
		std::vector<Square*> includedSquares;
	};

	mutable Square board[9][9];
	Region regions[3][3];

	Board()
	{
		for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) board[row][column].AssignLocation(row, column, regions[row / 3][column / 3]);
	}

	Board(const Board& other)
	{
		for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) board[row][column].AssignLocationWithValue(row, column, regions[row / 3][column / 3], other(row, column));
	}

	void printBoard()
	{
		console << "Printing actual values\n";
		for (uint8_t r = 0;r < 9;++r)
		{
			for (uint8_t c = 0; c < 9; ++c)
			{
				console << (int)board[r][c].value;
				if (c == 2 || c == 5) console << "|";
				else console << " ";
			}
			if (r == 2 || r == 5) console << "\n-----------------";
			console << "\n";
		}
	}

	void printAvailableMovesBoard()
	{
		console << "Printing available moves\n";
		for (uint8_t r = 0; r < 9; ++r)
		{
			for (uint8_t c = 0; c < 9; ++c)
				console << (int)board[r][c].allowedValues.size() << " ";
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

	size_t getNrEmptyCells()
	{
		size_t emptyCells = 0;
		for (uint8_t r = 0; r < 9; ++r)
		{
			for (uint8_t c = 0; c < 9; ++c)
			{
				if (board[r][c].allowedValues.size() > 0)
				{
					++emptyCells;
				}
			}
		}
		return emptyCells;
	}

	std::vector<Square*> bestSquares()
	{
		size_t smallestNrOfAvailableMoves = 9;
		for (uint8_t r = 0; r < 9; ++r)
		{
			for (uint8_t c = 0; c < 9; ++c)
			{
				if (board[r][c].isAvailable() && board[r][c].allowedValues.size() < smallestNrOfAvailableMoves)
				{
					smallestNrOfAvailableMoves = board[r][c].allowedValues.size();
				}
			}
		}

		std::vector<Square*> bestSquares;

		if (smallestNrOfAvailableMoves == 0) return bestSquares;

		for (uint8_t r = 0; r < 9; ++r)
		{
			for (uint8_t c = 0; c < 9; ++c)
			{
				if (board[r][c].allowedValues.size() == smallestNrOfAvailableMoves) bestSquares.push_back(&board[r][c]);
			}
		}

		return bestSquares;
	}

	bool isSolved()
	{
		size_t sum = 0;
		for (uint8_t r = 0; r < 9; ++r) for (uint8_t c = 0; c < 9; ++c) sum += board[r][c].value;
		return sum == 405;
	}

	void simplePlaceValue(uint8_t r, uint8_t c, uint8_t v)
	{
		Square *square = &board[r][c];

		// Process direct square
		square->value = v;
		square->allowedValues.clear();

		for (auto square : square->region->includedSquares)
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
			}
		}

		// Process row
		for (auto square : getRow(r))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
			}
		}

		// Process column
		for (auto square : getColumn(c))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
			}
		}

		std::vector<uint8_t> allowedValuesInRegion;
		for (uint8_t r = 0; r < 3; ++r)
		{
			for (uint8_t c = 0; c < 3; ++c)
			{
				Region* region = &regions[r][c];
				allowedValuesInRegion.clear();
				for (auto square : region->includedSquares) std::copy(square->allowedValues.begin(), square->allowedValues.end(), std::back_inserter(allowedValuesInRegion));
				for (uint8_t digit = 1; digit <= 9; ++digit)
				{
					if (std::count(allowedValuesInRegion.begin(), allowedValuesInRegion.end(), digit) == 1)
					{
						for (auto square : region->includedSquares)
						{
							if (std::find(square->allowedValues.begin(), square->allowedValues.end(), digit) != square->allowedValues.end())
							{
								square->allowedValues.clear();
								square->allowedValues.emplace_back(digit);
							}
						}
					}
				}
			}
		}
	}

	void placeValue(uint8_t r, uint8_t c, uint8_t v)
	{
		Square *square = &board[r][c];

		// Process direct square
		square->value = v;
		square->allowedValues.clear();

		// Process region
		for (auto square : square->region->includedSquares)
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
				if (square->allowedValues.empty()) console << "Found a dead end";
				if (square->allowedValues.size() == 1) placeValue(square->row, square->column, square->allowedValues[0]);
			}
		}

		// Process row
		for (auto square : getRow(r))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
				if (square->allowedValues.empty()) console << "Found a dead end";
				if (square->allowedValues.size() == 1) placeValue(square->row, square->column, square->allowedValues[0]);
			}
		}

		// Process column
		for (auto square : getColumn(c))
		{
			if (std::find(square->allowedValues.begin(), square->allowedValues.end(), v) != square->allowedValues.end())
			{
				square->allowedValues.erase(std::find(square->allowedValues.begin(), square->allowedValues.end(), v));
				if (square->allowedValues.empty()) console << "Found a dead end";
				if (square->allowedValues.size() == 1) placeValue(square->row, square->column, square->allowedValues[0]);
			}
		}

		std::vector<uint8_t> allowedValuesInRegion;
		for (uint8_t r = 0; r < 3; ++r)
		{
			for (uint8_t c = 0; c < 3; ++c)
			{
				Region* region = &regions[r][c];
				allowedValuesInRegion.clear();
				for (auto square : region->includedSquares) std::copy(square->allowedValues.begin(), square->allowedValues.end(), std::back_inserter(allowedValuesInRegion));
				for (uint8_t digit = 1; digit <= 9; ++digit)
				{
					if (std::count(allowedValuesInRegion.begin(), allowedValuesInRegion.end(), digit) == 1)
					{
						for (auto square : region->includedSquares)
						{
							if (std::find(square->allowedValues.begin(), square->allowedValues.end(), digit) != square->allowedValues.end())
							{
								placeValue(square->row, square->column, digit);
							}
						}
					}
				}
			}
		}
	}

	Square& operator ()(uint8_t r, uint8_t c) const
	{
		return board[r][c];
	}
};