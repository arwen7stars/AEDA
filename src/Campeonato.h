/*
 * Campeonato.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef CAMPEONATO_H_
#define CAMPEONATO_H_

#include <string>
#include <vector>
#include "Desporto.h"
#include "Equipa.h"
#include "Prova.h"
#include "Data.h"

class Campeonato{
	string nome; // Necessario?
	vector<Desporto *> desportos;
	vector<Equipa* > equipas;
	vector<Prova *> provas; //Conjunto das provas, tb funciona como calendario, se ordenamos
	Data inicio; // data do inicio do campeonato, pode dar jeito
public:

};



#endif /* CAMPEONATO_H_ */
