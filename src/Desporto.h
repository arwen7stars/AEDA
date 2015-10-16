/*
 * Desporto.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DESPORTO_H_
#define SRC_DESPORTO_H_

#include <string>
#include <vector>
#include "Data.h"

using namespace std;

struct Pontuacao{
	string nome;
	bool crescente; // se a pontuacao e crescente ou nao
};

class Desporto{
	string nome;
	vector<Modalidade *> modalidades; // o stor tinha dito que era um conjunto de modalidades
	Pontuacao pontuacao; //fiz uma struct, mas se for preciso ser classe depois mudasse
public:

};

class Modalidade{
	string name;
	Hora duracao;
	//Em vez de uma modalidade ter um conjunto de provas, acho melhor uma prova ter uma modalidade.
public:

};

#endif /* SRC_DESPORTO_H_ */
