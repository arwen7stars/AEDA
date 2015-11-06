/*
 * Modalidade.h
 *
 *  Created on: 03/11/2015
 *      Author: Filipe
 */

#ifndef SRC_MODALIDADE_H_
#define SRC_MODALIDADE_H_

#include <string>
#include <vector>
#include "Data.h"

using namespace std;

class Desporto;

class Modalidade{
	string nome;
	Hora duracao;
	Desporto* desporto; //ja nao e preciso, certo? *Isto serve para quando tiveres a suar a modalidade ir buscar o desporto
//	//Em vez de uma modalidade ter um conjunto de provas, acho melhor uma prova ter uma modalidade.
public:
	Modalidade();
	Modalidade(string n, int h, int m, Desporto *d);

	string getNome() const;
	Hora getDuracao() const;
	Desporto* getDesporto() const;

	bool operator== (const Modalidade & c) const;
	friend ostream & operator<<(ostream & o, const Modalidade & d);

	void menu();
};



#endif /* SRC_MODALIDADE_H_ */

