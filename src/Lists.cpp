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
#include <algorithm>
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



bool comparar_strings(string s1, string s2)
{

	for(unsigned int i = 0; i < s1.size(); i++)
		s1[i] = toupper(s1[i]);

	for(unsigned int i = 0; i < s2.size(); i++)
		s2[i] = toupper(s2[i]);

	if (s1 == s2)
		return true;
	else return false;
}


int string_to_int(string s)
{
istringstream instr(s);
int n;
instr >> n;
return n;
}

string int_to_string(int n)
{
ostringstream outstr;
outstr << n;
return outstr.str(); //convert stringstream into string
}

bool ficheiroExiste(const string &ficheiro)
{
	bool existe = false;
	ifstream ficheiro_tab;
	ficheiro_tab.open(ficheiro.c_str());		// abre o ficheiro...
	if (ficheiro_tab.is_open())			// ... e verifica se a abertura do ficheiro foi bem-sucedida
	{
		existe = true;
		ficheiro_tab.close();			// volta a fechar o ficheiro
	}
	return existe;
}




