#pragma once

#include <string>

uint8_t *board;

__declspec(dllexport) void readBoard(uint8_t*);
__declspec(dllexport) void solveBoard();
__declspec(dllexport) void retrieveSolvedBoard(uint8_t*);