#include "solver.h"

char* getMessage() 
{ 
	char* message = new char[15];
	memcpy(message, "Hello World!", sizeof("Hello World!"));
	return message;
}