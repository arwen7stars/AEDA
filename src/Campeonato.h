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
#include <fstream>
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
	Data inicio, fim; ///< Data do inicio e do fim do campeonato, pode dar jeito
public:
	Campeonato(string n, Data i, Data f);
	bool adicionaProva(Prova p);
	bool criaDesportosCampeonato(string nome_ficheiro);
	vector<Desporto *> getDesportos() const;
	vector<Prova> getProvas() const;
};



#endif /* CAMPEONATO_H_ */
