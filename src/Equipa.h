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
	string name;
	vector<Atleta *> atletas;
public:

};

class Atleta{
	string name;
	int firstPlace, secondPLace, thirdPlace; //numero de primeiros lugares, segundos lugares e terceiros lugares, respectivamente.
	vector<Prova *> provas;
public:

};


#endif /* SRC_EQUIPA_H_ */
