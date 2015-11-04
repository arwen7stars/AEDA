/*
 * Equipa.cpp
 *
 *  Created on: 26/10/2015
 *      Author: Filipe
 */

#include "Equipa.h"

/*
------------------------------------------------------------------------------
								Class Equipa
------------------------------------------------------------------------------
*/

Equipa::Equipa(string n){
	nome = n;
}

string Equipa::getNome() const{
	return nome;
}


/*
------------------------------------------------------------------------------
								Class Atleta
------------------------------------------------------------------------------
*/

Atleta::Atleta(string n, Equipa e){
	nome = n;
	equipa = &e;
}

string Atleta::getNome() const{
	return nome;
}

Equipa* Atleta::getEquipa() const{
	return equipa;
}

void Atleta::adicionaPontuacao(int p){
 pontos += p;
}
