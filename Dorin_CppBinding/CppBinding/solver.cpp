#include "solver.h"
#include "sudoku_board.h"
#include "Console.h"

#include <string>
#include <atomic>
#include <memory>

console cons;

sudoku_board board;

bool loadBoard(uint8_t *incomingBoard)
{
    sudoku_board b;
	for (int i = 0; i < 81; ++i)
	{
        if (incomingBoard[i] != 0)
        {
            b.add_value(i/9, i%9, incomingBoard[i]);
        }
	}
    board = b;

    cons << "Board loaded:\n";
    board.print();

    return true;
}

/// Backtracking
bool solveBoardRecursive(sudoku_board & b)
{
    if (b.solved())
    {
        board = b;
        return true;
    }

    auto result = b.picks();
    if (result.size() == 0)
    {
        return false;
    }
    else if (result.size() == 1)
    {
        b.add_value(std::get<0>(result.at(0)), std::get<1>(result.at(0)), std::get<2>(result.at(0)));
        return solveBoardRecursive(b);
    }
    else
    {
        for (const auto & tuple : result)
        {
            sudoku_board bb = b;
            bb.add_value(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
            if (solveBoardRecursive(bb)) return true;
        }
    }

    return false;
}


bool solveBoard()
{
    return solveBoardRecursive(board);
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
    cons << "\nSolved board:\n";
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cons << board(i, j) << " ";
        }
        cons << "\n";
    }

    for (int i = 0; i < 81; ++i)
    {
        solvedBoard[i] = board(i/9, i%9);
    }

    return true;
}