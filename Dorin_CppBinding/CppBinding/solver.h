#pragma once

#include <cstdint>

extern "C" __declspec(dllexport) bool loadBoard(uint8_t*);
extern "C" __declspec(dllexport) bool solveBoard();
extern "C" __declspec(dllexport) bool retrieveSolvedBoard(uint8_t*);