// Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "solver.h"

#include <iostream>
#include <chrono>

int main()
{
    // easy
    // uint8_t *data = new uint8_t[81]{ 0, 0, 0, 2, 6, 0, 7, 0, 1, 6, 8, 0, 0, 7, 0, 0, 9, 0, 1, 9, 0, 0, 0, 4, 5, 0, 0, 8, 2, 0, 1, 0, 0, 0, 4, 0, 0, 0, 4, 6, 0, 2, 9, 0, 0, 0, 5, 0, 0, 0, 3, 0, 2, 8, 0, 0, 9, 3, 0, 0, 0, 7, 4, 0, 4, 0, 0, 5, 0, 0, 3, 6, 7, 0, 3, 0, 1, 8, 0, 0, 0 };
    // medium
    // uint8_t *data = new uint8_t[81]{ 6, 0, 1, 0, 0, 2, 0, 7, 0, 0, 9, 0, 1, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 4, 0, 8, 0, 0, 0, 0, 0, 2, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 5, 0, 0, 0, 0, 0, 9, 0, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 3, 0, 8, 0, 0, 3, 0, 6, 0, 0, 1, 0, 7 };
    // hard
    uint8_t *data = new uint8_t[81]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 8, 5, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 5, 0, 7, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 7, 3, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 9 };
    
    std::chrono::microseconds sum;
    for (int i = 0; i < 1000; ++i)
    {
        auto start = std::chrono::steady_clock::now();
        loadBoard(data);
        solveBoard();
        retrieveSolvedBoard(data);
        sum += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start);
    }

    std::cout << (double)sum.count() / 1000000000 << " seconds" << std::endl;

    std::getchar();

    return 0;
}

