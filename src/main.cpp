/*
 * main.cpp
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#include <vector>
#include <iostream>
#include "Lists.h"
#include "Desporto.h"

int main(){

	Desporto D;
	D = Desporto("Atletismo", "Segundos", true);
	cout << D.getNome() << endl;
	cout << D.getPontuacao() << endl;
	cout << D.isCrescente() << endl;
	cout << endl;

	_getch();
	D.menuModalidades();

	_getch();
	return 0;
}


