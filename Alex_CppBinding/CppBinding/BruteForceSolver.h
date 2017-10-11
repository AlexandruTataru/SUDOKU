#pragma once

#include "Board.h"

class BruteForceSolver
{
	Board board;
	Console console;
	
	bool processBoard(Board board);

public:
	BruteForceSolver();
	~BruteForceSolver();

	bool loadBoard(uint8_t*);
	bool solveBoard();
	bool retrieveSolvedBoard(uint8_t*);
};

