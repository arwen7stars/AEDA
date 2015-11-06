/*
 * Prova.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_PROVA_H_
#define SRC_PROVA_H_

#include <iostream>
#include <string>
#include <vector>
#include "Desporto.h"
#include "Data.h"
#include "Modalidade.h"

using namespace std;

class Atleta;

class Prova{
protected:
	Modalidade* modalidade;
	Data* data;
	Hora inicio, fim;
	vector<Atleta *> atletas;
public:
	Prova(){};
	Prova(Modalidade* m, Data d, Hora i);

	Hora getInicio() const;
	Hora getFim() const;
	Data getData() const;
	Modalidade* getModalidade() const;
	vector<Atleta*> getAtletas() const;

	void adicionaAtleta(Atleta * a);
	bool Simultaneo(Prova p);

	friend ostream & operator<<(ostream & o, const Prova & p);
};

class ProvaTerminada: public Prova{ //Quando uma prova ja terminou, transformamola num ProvaTerminada
	vector<int> pontuacoes; //Vetor com as pontuacoes dos atletas, corresponde com o vector atletas
public:
	ProvaTerminada(Modalidade* m, Data d, Hora i);
	Atleta* getPrimeiro() const;
	Atleta* getSegundo() const;
	Atleta* getTerceiro() const;
};


#endif /* SRC_PROVA_H_ */
