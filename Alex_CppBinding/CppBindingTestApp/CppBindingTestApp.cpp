// CppBindingTestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../CppBinding/Board.h"

#include <iostream>
#include <cstdlib>

int main()
{
	Board b;
	b.placeValue(5, 5, 8);
	b.printBoard();
	getchar();
    return 0;
}

