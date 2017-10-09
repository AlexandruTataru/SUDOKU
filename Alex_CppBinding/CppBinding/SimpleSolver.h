#pragma once

#include "Console.h"

#include <cstdint>
#include <vector>

class SimpleSolver
{
	typedef std::pair<uint8_t, uint8_t> position;
	typedef std::vector<position> positions;

	uint8_t board[9][9];
	Console console;
public:
	SimpleSolver();
	~SimpleSolver();

	bool loadBoard(uint8_t*);
	bool solveBoard();
	bool retrieveSolvedBoard(uint8_t*);

private:
	positions digitLocations(uint8_t digit);
	bool digitIsSingleOnColumn(uint8_t tempBoard[][9], uint8_t column, position& pos);
	bool digitIsSingleOnRow(uint8_t tempBoard[][9], uint8_t row, position& pos);
	void markPositionDown(uint8_t tempBoard[][9], position pos);
	bool internal_isBoardSolved();
	bool internal_isRowValid(uint8_t row);
	bool internal_isColumnValid(uint8_t column);
	void markAlreadyUsedLocations(uint8_t tempBoard[][9]);
	void resetBoard(uint8_t board[][9], uint8_t resetDigit);
	void printBoard(uint8_t board[][9]);
};

