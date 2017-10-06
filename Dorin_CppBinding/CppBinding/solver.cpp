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
    int i, j;
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
                squares[i][j].i = i;
                squares[i][j].j = j;
                squares[i][j].value = 0;
                squares[i][j].region = &regions[i/3][j/3];
                squares[i][j].region->squares.insert(&squares[i][j]);
                for (int k = 1; k <= 9; ++k)
                {
                    squares[i][j].available.insert(k);
                }
            }
    }

    sudoku_board(const sudoku_board & board)
    {
        m_openSquares = board.m_openSquares;

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                squares[i][j].i = i;
                squares[i][j].j = j;
                squares[i][j].region = &regions[i / 3][j / 3];
                squares[i][j].region->squares.insert(&squares[i][j]);
            }

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                squares[i][j].value = board.squares[i][j].value;
                squares[i][j].available.clear();
                for (auto it = board.squares[i][j].available.begin(); it != board.squares[i][j].available.end(); ++it)
                {
                    squares[i][j].available.insert(*it);
                }
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                regions[i][j].available.clear();
                for (auto it = board.regions[i][j].available.begin(); it != board.regions[i][j].available.end(); ++it)
                {
                    regions[i][j].available.insert(*it);
                }
            }
    }

    sudoku_board & operator=(const sudoku_board & board)
    {
        m_openSquares = board.m_openSquares;

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                squares[i][j].value = board.squares[i][j].value;
                squares[i][j].available.clear();
                for (auto it = board.squares[i][j].available.begin(); it != board.squares[i][j].available.end(); ++it)
                {
                    squares[i][j].available.insert(*it);
                }
            }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                regions[i][j].available.clear();
                for (auto it = board.regions[i][j].available.begin(); it != board.regions[i][j].available.end(); ++it)
                {
                    regions[i][j].available.insert(*it);
                }
            }

        return *this;
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

    std::vector<std::tuple<int, int, int> > pick()
    {
        std::vector<std::tuple<int, int, int> > result;
        std::set<int> *availablePointer = NULL;
        int min = 10;
        int ii = -1, jj = -1;

        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
            {
                if (squares[i][j].value == 0
                &&  squares[i][j].available.size() < min)
                {
                    if (squares[i][j].available.size() == 0)
                    {
                        return result;
                    }

                    min = squares[i][j].available.size();
                    availablePointer = &squares[i][j].available;
                    ii = i;
                    jj = j;
                }
            }

        if (min > 1)
        {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    for (auto it = regions[i][j].available.begin(); it != regions[i][j].available.end(); ++it)
                    {
                        int posible_positions = 0;
                        auto x = -1, y = -1;
                        for (auto itt = regions[i][j].squares.begin(); itt != regions[i][j].squares.end(); ++itt)
                        {
                            auto square = *itt;
                            if (square->available.find(*it) != square->available.end())
                            {
                                ++posible_positions;
                                x = square->i;
                                y = square->j;
                            }
                        }
                        if (posible_positions == 1)
                        {
                            result.emplace_back(std::make_tuple(x, y, *it));
                            return result;
                        }
                    }
                }
        }

        for (int value : *availablePointer)
        {
            result.emplace_back(std::make_tuple(ii, jj, value));
        }

        return result;
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

bool solveBoardRecursive(sudoku_board & b)
{
    while (!b.solved())
    {
        auto result = b.pick();
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
                    board = bb;
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