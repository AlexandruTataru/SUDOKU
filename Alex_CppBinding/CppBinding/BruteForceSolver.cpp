#include "BruteForceSolver.h"

BruteForceSolver::BruteForceSolver()
{
}


BruteForceSolver::~BruteForceSolver()
{
}

bool BruteForceSolver::loadBoard(uint8_t* incomingBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row)
	{
		for (uint8_t column = 0; column < 9; ++column)
		{
			uint8_t value = incomingBoard[i];
			if(value != 0) board.placeValue(row, column, value);
			++i;
		}
	}
	return false;
}

bool BruteForceSolver::processBoard(Board board)
{
	cout << "Board has " << (int)board.getNrEmptyCells() << " empty cells\n";
	if ((int)board.getNrEmptyCells() == 0)
	{
		board.printBoard();
		bool isSolved = board.isSolved();
		return board.isSolved();
	}
	for (uint8_t r = 0; r < 9; ++r)
	{
		for (uint8_t c = 0; c < 9; ++c)
		{
			if (board(r, c).allowedValues.size() != 0)
			{
				Board::Square& freeSquare = board(r,c);
				for (auto allowedValue : freeSquare.allowedValues)
				{
					Board tempBoard = board;
					tempBoard.placeValue(freeSquare.row, freeSquare.column, allowedValue);
					if (tempBoard.isSolved())
					{
						console << "Solved the SUDOKU\n";
						return true;
					}
					if (processBoard(tempBoard)) return true;
				}
			}
		}
	}
	
	return false;
}

bool BruteForceSolver::solveBoard()
{
	return processBoard(board);
}

bool BruteForceSolver::retrieveSolvedBoard(uint8_t* solvedBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) solvedBoard[i++] = board(row, column).value;
	return false;
}
