#include "API.h"
#include "SimpleSolver.h"

SimpleSolver solver;

bool loadBoard(uint8_t *incomingBoard)
{
	return solver.loadBoard(incomingBoard);
}

bool solveBoard()
{
	return solver.solveBoard();
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
	return solver.retrieveSolvedBoard(solvedBoard);
}