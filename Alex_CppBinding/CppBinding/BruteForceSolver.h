#pragma once

#include <cstdint>
#include <set>

class BruteForceSolver
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
	
public:
	BruteForceSolver();
	~BruteForceSolver();

	bool loadBoard(uint8_t*);
	bool solveBoard();
	bool retrieveSolvedBoard(uint8_t*);
};

