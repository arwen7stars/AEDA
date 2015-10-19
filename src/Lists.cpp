/*
 * Lists.cpp
 *
 *  Created on: 19/10/2015
 *      Author: Filipe
 */


#include "Lists.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;


void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int wherey()
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   return csbi.dwCursorPosition.Y;
}



