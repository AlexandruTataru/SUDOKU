#pragma once

#define DllExport extern "C" __declspec( dllexport ) 

#include <cstdint>

DllExport bool loadBoard(uint8_t*);
DllExport bool solveBoard();
DllExport bool retrieveSolvedBoard(uint8_t*);