// CppBindingTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../CppBinding/API.h"
#include "../CppBinding/Board.h"
#include "NorvicSudoku.h"

#include <iostream>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <ppltasks.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

bool processBoard(Board& board)
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

std::atomic<int> nrThreads = 0;

void threadMethod(Board& b)
{
	++nrThreads;
	processBoard(b);
	//--nrThreads;
	cout << "Still running threads " << nrThreads << endl;
}

int main()
{
	uint8_t values[] = { 3, 8, 5, 1, 2, 5, 7, 4, 1, 9, 5, 7, 3, 2, 1, 4, 9 };
	uint8_t positions[] = { 14, 16, 17, 20, 22, 30, 32, 38, 42, 46, 54, 61, 62, 65, 67, 76, 80 };
	uint8_t board[81];
	uint8_t solvedBoard[81];
	for (auto& elem : board) elem = 0;
	for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); ++i) board[positions[i]] = values[i];


	Sudoku::init();
	string line(81, '.');
	for (int i = 0; i < sizeof(positions) / sizeof(positions[0]); ++i) line[positions[i]] = (char)(values[i] + 48);
	cout << line << endl;
	if (auto S = solve(unique_ptr<Sudoku>(new Sudoku(line)))) {
		S->write(cout);
	}
	else {
		cout << "No solution";
	}
	cout << "Entered recursively just " << enters << " times" << endl;
	cout << endl;

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

	/*Board b;
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

	PTP_POOL pool = NULL;
	TP_CALLBACK_ENVIRON CallBackEnviron;
	InitializeThreadpoolEnvironment(&CallBackEnviron);
	pool = CreateThreadpool(NULL);
	SetThreadpoolThreadMaximum(pool, 300);
	SetThreadpoolThreadMinimum(pool, 1);

	size_t nrThreads = 0;
	for (uint8_t row = 0; row < 9; ++row)
	{
		for (uint8_t column = 0; column < 9; ++column)
		{
			Board::Square& s = b(row, column);
			if (s.isAvailable())
			{
				Board tempBoard = b;
				for (auto& v : s.allowedValues)
				{
					tempBoard.simplePlaceValue(row, column, v);
					//std::thread t(threadMethod, tempBoard);
					//t.detach();
					concurrency::create_task([&tempBoard]()
					{
						threadMethod(tempBoard);
					});
				}
			}
		}
	}
	cout << "Finished creating all " << nrThreads << " threads" << endl;

	getchar();*/

    return 0;
}

