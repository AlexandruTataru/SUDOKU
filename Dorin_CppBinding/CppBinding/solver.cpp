#include "solver.h"

#include <string>
#include <vector>
#include <set>
#include <tuple>

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

struct region;

struct square
{
    int value;
    std::set<int> available;
    region *region;
};

struct region
{
    std::set<square*> squares;
    std::set<int> available;
};

class sudoku_board
{
public:
    square squares[9][9];
    region regions[3][3];

    sudoku_board()
    {
        m_openSquares = 81;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                for (int k = 1; k <= 9; ++k)
                {
                    regions[i/3][j/3].available.insert(k);
                }
                squares[i][j].value = 0;
                squares[i][j].region = &regions[i/3][j/3];
                squares[i][j].region->squares.insert(&squares[i][j]);
                for (int k = 1; k <= 9; ++k)
                {
                    squares[i][j].available.insert(k);
                }
            }
    }

    void add_value(int i, int j, int value)
    {
        m_openSquares -= 1;
        squares[i][j].value = value;
        squares[i][j].available.clear();
        squares[i][j].region->available.erase(value);
        for (const auto square : squares[i][j].region->squares)
        {
            square->available.erase(value);
        }
        for (int ii = 0; ii < 9; ++ii)
        {
            squares[ii][j].available.erase(value);
        }
        for (int jj = 0; jj < 9; ++jj)
        {
            squares[i][jj].available.erase(value);
        }
    }

    bool solved()
    {
        return m_openSquares == 0;
    }

    std::tuple<int, int, int> pick()
    {
        int ii = -1, jj = -1;
        int value = -1;
        int min = 10;
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                if (squares[i][j].value == 0
                &&  squares[i][j].available.size() < min)
                {
                    min = squares[i][j].available.size();
                    value = *(squares[i][j].available.begin());
                    ii = i;
                    jj = j;
                }
            }

        return std::make_tuple(ii, jj, value);
    }

private:
    int m_openSquares;
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
            cons << board.squares[i][j].value << " ";
        }
        cons << "\n";
    }

    return true;
}

bool solveBoard()
{
    while (!board.solved())
    {
        auto result = board.pick();
        board.add_value(std::get<0>(result), std::get<1>(result), std::get<2>(result));
    }

    return true;
}

bool retrieveSolvedBoard(uint8_t* solvedBoard)
{
    cons << "\nSolved board:\n";
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            cons << board.squares[i][j].value << " ";
        }
        cons << "\n";
    }

    for (int i = 0; i < 81; ++i)
    {
        solvedBoard[i] = board.squares[i/9][i%9].value;
    }

    return true;
}