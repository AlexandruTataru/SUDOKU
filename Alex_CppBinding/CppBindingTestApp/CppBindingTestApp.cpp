// CppBindingTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../CppBinding/API.h"
#include "../CppBinding/Board.h"

#include <iostream>
#include <cstdlib>

int main()
{
	uint8_t values[] = { 2, 6, 7, 1, 6, 8, 7, 9, 1, 9, 4, 5, 8, 2, 1, 4, 4, 6, 2, 9, 5, 3, 2, 8, 9, 3, 7, 4, 4, 5, 3, 6, 7, 3, 1, 8 };
	uint8_t positions[] = {3, 4, 6, 8, 9, 10, 13, 16, 18, 19, 23, 24, 27, 28, 30, 34, 38, 39, 41, 42, 46, 50, 52, 53, 56, 57, 61, 62, 64, 67, 70, 71, 72, 74, 76, 77};
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
	getchar();

    return 0;
}

