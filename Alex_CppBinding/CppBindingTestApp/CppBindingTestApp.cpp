// CppBindingTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../CppBinding/API.h"
#include "../CppBinding/Board.h"

#include <iostream>
#include <cstdlib>

bool processBoard(Board board, size_t depth)
{
	bool isSolved = board.isSolved();
	//cout << "Depth: " << board.getNrEmptyCells() << "solved: " << std::boolalpha << isSolved << "\n";
	if (isSolved) getchar();
	/*if ((int)board.getNrEmptyCells() == 0)
	{
		board.printBoard();
		bool isSolved = board.isSolved();
		return board.isSolved();
	}*/
	for (uint8_t r = 0; r < 9; ++r)
	{
		for (uint8_t c = 0; c < 9; ++c)
		{
			if (board(r, c).allowedValues.size() != 0)
			{
				Board::Square& freeSquare = board(r, c);
				for (auto allowedValue : freeSquare.allowedValues)
				{
					Board tempBoard = board;
					tempBoard.placeValue(freeSquare.row, freeSquare.column, allowedValue);
					if (tempBoard.isSolved())
					{
						cout << "Solved the SUDOKU\n";
						return true;
					}
					if (processBoard(tempBoard, ++depth)) return true;
				}
			}
		}
	}

	return false;
}

int main()
{
	uint8_t values[] = { 6, 1, 2, 7, 9, 1, 5, 6, 4, 8, 2, 6, 7, 5, 9, 4, 5, 9, 3, 8, 3, 6, 1, 7 };
	uint8_t positions[] = { 0, 2, 5, 7, 10, 12, 15, 23, 26, 28, 34, 38, 42, 46, 52, 54, 57, 65, 68, 70, 73, 75, 78, 80 };
	uint8_t board[81];
	uint8_t solvedBoard[81];
	for (auto& elem : board) elem = 0;
	for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); ++i) board[positions[i]] = values[i];


	/*loadBoard(board);
	solveBoard();
	retrieveSolvedBoard(solvedBoard);
	int idx = 0;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			std::cout << (int)solvedBoard[idx++] << " ";
		}
		std::cout << "\n";
	}*/

	Board b;
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row)
	{
		for (uint8_t column = 0; column < 9; ++column)
		{
			uint8_t value = board[i];
			if (value != 0)
			{
				b.placeValue(row, column, value);
				b.printBoard();
			}
			++i;
		}
	}
	//b.printBoard();
	processBoard(b, 0);
	getchar();

    return 0;
}

