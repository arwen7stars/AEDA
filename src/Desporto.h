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

using namespace std;

class Desporto{
	string nome;
	vector<Modalidade> modalidades;
public:

};

class Modalidade{
	string name;
	unsigned int duracao;
public:

};

#endif /* SRC_DESPORTO_H_ */
