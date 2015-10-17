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

using namespace std;

class Equipa{
	string nome;
	vector<Atleta *> atletas;
public:
	Equipa(string n);
	string getNome();
	bool adicionaAtleta(Atleta *);
};

class Atleta{
	string nome;
	int firstPlace, secondPLace, thirdPlace; //numero de primeiros lugares, segundos lugares e terceiros lugares, respectivamente.
	vector<Prova *> provas;
public:
	Atleta(string n);
	string getNome();
	bool adicionaProva(Prova *);
};


#endif /* SRC_EQUIPA_H_ */
