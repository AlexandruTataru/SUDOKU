#include "solver.h"
#include "sudoku_board.h"

#include <string>

#if defined _DEBUG
    #include "Windows.h"
    #include <iostream>
#endif

class console
{
public:
    console()
    {
    #if defined _DEBUG
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        freopen_s(&m_pCout, "CON", "w", stdout);
    #endif
    }

    ~console()
    {
    #if defined _DEBUG
        fclose(m_pCout);
    #endif
    }

    template<typename T>
    console& operator << (const T & obj)
    {
    #if defined _DEBUG
        std::cout << obj;
    #endif
        return *this;
    }

private:
    FILE* m_pCout;
};

console cons;

sudoku_board board;

bool loadBoard(uint8_t *incomingBoard)
{
	for (int i = 0; i < 81; ++i)
	{
        if (incomingBoard[i] != 0)
        {
            board.add_value(i/9, i%9, incomingBoard[i]);
        }
	}

    cons << "Board loaded:\n";
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cons << board(i, j) << " ";
        }
        cons << "\n";
    }

    return true;
}

/// Backtracking
bool solveBoardRecursive(sudoku_board & b)
{
    while (!b.solved())
    {
        auto result = b.picks();
        if (result.size() == 0)
        {
            return false;
        }
        else if (result.size() == 1)
        {
            b.add_value(std::get<0>(result.at(0)), std::get<1>(result.at(0)), std::get<2>(result.at(0)));
        }
        else
        {
            for (const auto & tuple : result)
            {
                sudoku_board bb = b;
                bb.add_value(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple));
                if (solveBoardRecursive(bb))
                {
                    return true;
                }
            }
        }
    }

    if (b.solved())
    {
        board = b;
        return true;
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