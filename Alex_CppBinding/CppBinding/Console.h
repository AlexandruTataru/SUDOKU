#pragma once

#include <windows.h>
#include <iostream>
#include <stdio.h>

class Console
{
public:
	Console()
	{
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
	}

	~Console()
	{
		//FreeConsole();
	}

	template<class T>
	Console& operator << (const T& obj)
	{
		std::cout << obj;
		std::cout.flush();
		return *this;
	}
};