#pragma once

#include <set>
#include <vector>
#include <tuple>

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
    // constructors
    sudoku_board();
    sudoku_board(const sudoku_board & board);
    // copy
    sudoku_board & operator=(const sudoku_board & board);

    // matrix element
    int operator()(int i, int j) const;

    bool solved() const;

    void add_value(int i, int j, int value);

    std::vector<std::tuple<int, int, int> > picks() const;

    void print();

private:
    square m_squares[9][9];
    region m_regions[3][3];

    int m_openSquares;
};