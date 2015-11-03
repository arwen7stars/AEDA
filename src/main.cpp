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
#include "Data.h"

int main(){
//	Desporto D;
//	D = Desporto("Atletismo", "Segundos", true);
//	cout << D.getNome() << endl;
//	cout << D.getPontuacao() << endl;
//	cout << D.isCrescente() << endl;
//	cout << endl;
//
//
//	Modalidade M;
//	M = Modalidade("Corrida de 100 Metros", 13, 35, D);
//	cout << M.getNome() << endl;
//	cout << M.getDesporto()->getNome() << endl;
//	cout << endl;

	Hora h1(13,30), h2(13,50), h3(20,00);
	cout << (h1 < h2) << (h1 < h3) << (h3 > h2);

	_getch();
	return 0;
}

