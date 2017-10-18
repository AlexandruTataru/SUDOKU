#include "SimpleSolver.h"

#include <numeric>
#include <set>

const uint8_t CLEAR_TILE = 0;
const uint8_t MARKED_TILE = 1;

SimpleSolver::SimpleSolver()
{
}


SimpleSolver::~SimpleSolver()
{
}

bool SimpleSolver::loadBoard(uint8_t *incomingBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) board[row][column] = incomingBoard[i++];
	return true;
}

bool SimpleSolver::internal_isBoardSolved()
{
	size_t sum = 0;
	int row = 0, column = 0;
	for (; row < 9; ++row) for (column = 0; column < 9; ++column) sum += board[row][column];

	if (sum != 405) return false;

	for (uint8_t idx = 0; idx < 9; ++idx) if (!internal_isRowValid(idx) || !internal_isColumnValid(idx)) return false;

	return true;
}

bool SimpleSolver::internal_isRowValid(uint8_t row)
{
	std::set<uint8_t> values;
	for (uint8_t column = 0; column < 9; ++column) values.insert(board[row][column]);
	return std::accumulate(values.begin(), values.end(), 0) == 45;
}

bool SimpleSolver::internal_isColumnValid(uint8_t column)
{
	std::set<uint8_t> values;
	for (uint8_t row = 0; row < 9; ++row) values.insert(board[row][column]);
	return std::accumulate(values.begin(), values.end(), 0) == 45;
}

void SimpleSolver::markAlreadyUsedLocations(uint8_t tempBoard[][9])
{
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) if (board[row][column]) tempBoard[row][column] = 1;
}

void SimpleSolver::resetBoard(uint8_t board[][9], uint8_t resetDigit)
{
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) board[row][column] = resetDigit;
}

void SimpleSolver::printBoard(uint8_t board[][9])
{
	for (uint8_t row = 0; row < 9; ++row)
	{
		for (uint8_t column = 0; column < 9; ++column)
		{
			//console << (int)board[row][column] << " ";
		}
		//console << "\n";
	}
}

void SimpleSolver::markPositionDown(uint8_t tempBoard[][9], position pos)
{
	for (uint8_t idx = 0; idx < 9; ++idx)
	{
		tempBoard[pos.first][idx] = MARKED_TILE;
		tempBoard[idx][pos.second] = MARKED_TILE;
	}

	uint8_t startRow, endRow;
	if (pos.first <= 2) { startRow = 0; endRow = 2; }
	else if (pos.first >= 3 && pos.first <= 5) { startRow = 3; endRow = 5; }
	else if (pos.first >= 6 && pos.first <= 8) { startRow = 6; endRow = 8; }

	uint8_t startCol, endCol;
	if (pos.second <= 2) { startCol = 0; endCol = 2; }
	else if (pos.second >= 3 && pos.second <= 5) { startCol = 3; endCol = 5; }
	else if (pos.second >= 6 && pos.second <= 8) { startCol = 6; endCol = 8; }

	for (uint8_t row = startRow; row <= endRow; ++row)
	{
		for (uint8_t column = startCol; column <= endCol; ++column)
		{
			tempBoard[row][column] = MARKED_TILE;
		}
	}
}

bool SimpleSolver::digitIsSingleOnRow(uint8_t tempBoard[][9], uint8_t row, position& pos)
{
	int found = 0;
	for (uint8_t column = 0; column < 9; ++column)
	{
		if (tempBoard[row][column] == 0)
		{
			pos = std::make_pair(row, column);
			found++;
		}
	}

	return found == 1;
}

bool SimpleSolver::digitIsSingleOnColumn(uint8_t tempBoard[][9], uint8_t column, position& pos)
{
	int found = 0;
	uint8_t r, c;
	for (uint8_t row = 0; row < 9; ++row)
	{
		if (tempBoard[row][column] == 0)
		{
			r = row;
			c = column;
			found++;
		}
	}

	if (found == 1) pos = std::make_pair(r, c);

	return found == 1;
}

SimpleSolver::positions SimpleSolver::digitLocations(uint8_t digit)
{
	positions locations;
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) if (board[row][column] == digit) locations.push_back(std::make_pair(row, column));
	return locations;
}

bool SimpleSolver::solveBoard()
{
	while (!internal_isBoardSolved())
	{
		uint8_t tempBoard[9][9];
		for (uint8_t currentDigit = 1; currentDigit <= 9; ++currentDigit)
		{
			resetBoard(tempBoard, CLEAR_TILE);
			markAlreadyUsedLocations(tempBoard);
			positions digitPositions = digitLocations(currentDigit);
			for (auto position : digitPositions)
			{
				markPositionDown(tempBoard, position);
			}
			for (uint8_t entry = 0; entry < 9; ++entry)
			{
				position pos;
				bool inRow = digitIsSingleOnRow(tempBoard, entry, pos);
				bool inColumn = digitIsSingleOnColumn(tempBoard, entry, pos);
				if (inRow || inColumn)
				{
					board[pos.first][pos.second] = currentDigit;
				}
			}

		}
	}
	return true;
}

bool SimpleSolver::retrieveSolvedBoard(uint8_t* solvedBoard)
{
	size_t i = 0;
	for (uint8_t row = 0; row < 9; ++row) for (uint8_t column = 0; column < 9; ++column) solvedBoard[i++] = board[row][column];
	printBoard(board);
	return true;
}
