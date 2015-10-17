/*
 * Prova.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_PROVA_H_
#define SRC_PROVA_H_

#include <string>
#include <vector>
#include "Desporto.h"
#include "Equipa.h"
#include "Data.h"

using namespace std;

class Prova{
	Modalidade* modalidade;
	Data* data;
	Hora inicio, fim;
	vector<Atleta *> atletas;
public:
	Prova(Modalidade m, Data d, Hora i);
	void adicionaAtleta(Atleta *);
};

class ProvaTerminada: public Prova{ //Quando uma prova ja terminou, transformamola num ProvaTerminada
	vector<int> pontuacoes; //Vetor com as pontuacoes dos atletas, corresponde com o vector atletas
public:
};


#endif /* SRC_PROVA_H_ */
