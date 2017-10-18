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
bool solveBoardRecursive(sudoku_board & input, sudoku_board & output)
{
    if (input.solved())
    {
        output = input;
        return true;
    }

    auto result = input.picks();
    if (result.size() == 0)
    {
        return false;
    }
    else if (result.size() == 1)
    {
        input.add_value(std::get<0>(result.at(0)), std::get<1>(result.at(0)), std::get<2>(result.at(0)));
        return solveBoardRecursive(input, output);
    }
    else
    {
        for (const auto & tuple : result)
        {
            sudoku_board b = input;
            b.add_value(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
            if (solveBoardRecursive(b, output)) return true;
        }
    }

    return false;
}


bool solveBoard()
{
    return solveBoardRecursive(board, board);
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
    cons << "\nSolved board:\n";
    board.print();
    cons << "\n";

    for (int i = 0; i < 81; ++i)
    {
        solvedBoard[i] = board(i/9, i%9);
    }

    return true;
}