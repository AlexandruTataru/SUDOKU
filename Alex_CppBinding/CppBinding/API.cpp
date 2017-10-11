#include "API.h"
#include "SimpleSolver.h"
#include "BruteForceSolver.h"

SimpleSolver solver1;
BruteForceSolver solver2;

bool loadBoard(uint8_t *incomingBoard)
{
	return solver2.loadBoard(incomingBoard);
}

bool solveBoard()
{
	return solver2.solveBoard();
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
	return solver2.retrieveSolvedBoard(solvedBoard);
}