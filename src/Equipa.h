/*
 * Equipa.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_EQUIPA_H_
#define SRC_EQUIPA_H_

#include <string>
#include <vector>
#include "Prova.h"

using namespace std;

class Atleta;

class Equipa{
	string nome;
	vector<Atleta *> atletas;
	int pontos;
public:
	Equipa(string n);
	string getNome() const;
	bool adicionaAtleta(Atleta * a);
};

class Atleta{
	string nome;
	Equipa* equipa;
	vector<Prova *> provas;
	int pontos;
public:
	Atleta(string n, Equipa e);
	string getNome() const;
	Equipa* getEquipa() const;
	bool adicionaProva(Prova * p);
	void adicionaPontuacao(int p);
};


#endif /* SRC_EQUIPA_H_ */
