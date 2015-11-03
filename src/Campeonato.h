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
#include "Data.h"

/*
 * Class Campeonato
 * Representa um campeonato
 */
class Campeonato{
	string nome; ///< Nome do campeonato
	vector<Desporto *> desportos; ///< Lista de Desportos/Modalidades
	vector<Equipa* > equipas; ///< Lista de Equipas
	vector<Prova> provas;
	Data inicio; ///< Data do inicio do campeonato, pode dar jeito
public:
	bool adicionaProva(Modalidade m, Data d, Hora I);
};



#endif /* CAMPEONATO_H_ */
