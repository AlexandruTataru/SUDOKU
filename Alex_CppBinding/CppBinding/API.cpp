#include "API.h"
#include "SimpleSolver.h"
#include "BruteForceSolver.h"

SimpleSolver solver1;
BruteForceSolver solver2;

bool loadBoard(uint8_t *incomingBoard)
{
	return solver1.loadBoard(incomingBoard);
}

bool solveBoard()
{
	return solver1.solveBoard();
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
	return solver1.retrieveSolvedBoard(solvedBoard);
}