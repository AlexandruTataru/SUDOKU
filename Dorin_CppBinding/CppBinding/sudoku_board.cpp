#include "sudoku_board.h"

/// Constructor
sudoku_board::sudoku_board()
{
    m_openSquares = 81;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 1; k <= 9; ++k)
            {
                m_regions[i/3][j/3].available.insert(k);
            }
            m_squares[i][j].i = i;
            m_squares[i][j].j = j;
            m_squares[i][j].value = 0;
            m_squares[i][j].region = &m_regions[i/3][j/3];
            m_squares[i][j].region->squares.insert(&m_squares[i][j]);
            for (int k = 1; k <= 9; ++k)
            {
                m_squares[i][j].available.insert(k);
            }
        }
}

/// Copy assignment
sudoku_board::sudoku_board(const sudoku_board & board)
{
    m_openSquares = board.m_openSquares;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            m_squares[i][j].i = i;
            m_squares[i][j].j = j;
            m_squares[i][j].region = &m_regions[i/3][j/3];
            m_squares[i][j].region->squares.insert(&m_squares[i][j]);
        }

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            m_squares[i][j].value = board.m_squares[i][j].value;
            m_squares[i][j].available.clear();
            for (auto it = board.m_squares[i][j].available.begin(); it != board.m_squares[i][j].available.end(); ++it)
            {
                m_squares[i][j].available.insert(*it);
            }
        }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            m_regions[i][j].available.clear();
            for (auto it = board.m_regions[i][j].available.begin(); it != board.m_regions[i][j].available.end(); ++it)
            {
                m_regions[i][j].available.insert(*it);
            }
        }
}

/// matrix element
int sudoku_board::operator()(int i, int j) const
{
    return m_squares[i][j].value;
}

/// Copy
sudoku_board & sudoku_board::operator=(const sudoku_board & board)
{
    m_openSquares = board.m_openSquares;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            m_squares[i][j].value = board.m_squares[i][j].value;
            m_squares[i][j].available.clear();
            for (auto it = board.m_squares[i][j].available.begin(); it != board.m_squares[i][j].available.end(); ++it)
            {
                m_squares[i][j].available.insert(*it);
            }
        }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            m_regions[i][j].available.clear();
            for (auto it = board.m_regions[i][j].available.begin(); it != board.m_regions[i][j].available.end(); ++it)
            {
                m_regions[i][j].available.insert(*it);
            }
        }

    return *this;
}

/// Add a new value on board at position i, j
void sudoku_board::add_value(int i, int j, int value)
{
    m_openSquares -= 1;
    m_squares[i][j].value = value;
    m_squares[i][j].available.clear();
    m_squares[i][j].region->available.erase(value);
    for (const auto square : m_squares[i][j].region->squares)
    {
        square->available.erase(value);
    }
    for (int ii = 0; ii < 9; ++ii)
    {
        m_squares[ii][j].available.erase(value);
    }
    for (int jj = 0; jj < 9; ++jj)
    {
        m_squares[i][jj].available.erase(value);
    }
}

/// check if solved
bool sudoku_board::solved() const
{
    return m_openSquares == 0;
}

/// pick posible values to add to board
/// the tuple is formed from position i, j and value
std::vector<std::tuple<int, int, int> > sudoku_board::picks() const
{
    std::vector<std::tuple<int, int, int> > result;
    const std::set<int> *availablePointer = NULL;
    int min = 10;
    int ii = -1, jj = -1;

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
        {
            if (m_squares[i][j].value == 0
                && m_squares[i][j].available.size() < min)
            {
                if (m_squares[i][j].available.size() == 0)
                {
                    return result;
                }

                min = m_squares[i][j].available.size();
                availablePointer = &m_squares[i][j].available;
                ii = i;
                jj = j;
            }
        }

    if (min > 1)
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
            {
                for (auto it = m_regions[i][j].available.begin(); it != m_regions[i][j].available.end(); ++it)
                {
                    int posible_positions = 0;
                    auto x = -1, y = -1;
                    for (auto itt = m_regions[i][j].squares.begin(); itt != m_regions[i][j].squares.end(); ++itt)
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
