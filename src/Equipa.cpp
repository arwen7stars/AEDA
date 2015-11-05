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
	pontos = 0;
}

string Equipa::getNome() const{
	return nome;
}

bool Equipa::operator== (const Equipa & c) const{
	if (c.nome == nome)
		return true;
	else
		return false;
}

ostream & operator<<(ostream & o, const Equipa & d){
	o << d.getNome();
	return o;
}

/*
------------------------------------------------------------------------------
								Class Atleta
------------------------------------------------------------------------------
*/

Atleta::Atleta(string n, Equipa e){
	nome = n;
	equipa = &e;
	pontos = 0;
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

int Atleta::getPontos() const{
	return pontos;
}
