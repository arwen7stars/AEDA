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
#include "Desporto.h"

using namespace std;

class Atleta;

class Equipa{
	string nome;
	vector<Atleta *> atletas;
	vector<Desporto *> desportos;
	int pontos;
public:
	Equipa(string n);
	string getNome() const;
	bool adicionaAtleta(Atleta * a);
	bool adicionaDesporto(Atleta * a);

	bool operator== (const Equipa & c) const;
	friend ostream & operator<<(ostream & o, const Equipa & d);

	void menu();

	class AtletaExiste{
		string nome;
		public:
		AtletaExiste(){};
		AtletaExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};
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
	int getPontos() const;
	bool adicionaProva(Prova * p);
	void adicionaPontuacao(int p);
};


#endif /* SRC_EQUIPA_H_ */
