// CppBindingTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../CppBinding/API.h"
#include "../CppBinding/Board.h"

#include <iostream>
#include <cstdlib>
#include <thread>

void threadMethod(Board& b, uint8_t r, uint8_t c, uint8_t value)
{
	b.simplePlaceValue(r, c, value);
	if (b.isSolved())
	{
		cout << "Solved the SUDOKU\n";
		b.printBoard();
	}
	processBoard(b);
}

bool processBoard(Board board)
{
	std::vector<Board::Square*> bestSquares = board.bestSquares();

	if (bestSquares.size() == 0) return false;

	for (auto& square : bestSquares)
	{
		for (auto& v : square->allowedValues)
		{
			Board tempBoard = board;
			//std::thread t(threadMethod, tempBoard, square->row, square->column, v);
			tempBoard.simplePlaceValue(square->row, square->column, v);
			if (tempBoard.isSolved())
			{
				cout << "Solved the SUDOKU\n";
				tempBoard.printBoard();
				return true;
			}
			if (processBoard(tempBoard)) return true;
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
				b.simplePlaceValue(row, column, value);
			}
			++i;
		}
	}
	processBoard(b);
	getchar();

    return 0;
}

