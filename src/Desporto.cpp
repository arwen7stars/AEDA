/*
 * Desporto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Filipe
 */

#include "Desporto.h"
#include "Data.h"
#include <string>
#include <vector>
using namespace std;

/*
------------------------------------------------------------------------------
								Class Desporto
------------------------------------------------------------------------------
*/

Desporto::Desporto(){}

Desporto::Desporto(string n, string pont, bool cresc){
	nome = n;
	pontuacao.nome = pont;
	pontuacao.crescente = cresc;
}

string Desporto::getNome() const{
	return nome;
}

string Desporto::getPontuacao() const{
	return pontuacao.nome;
}

bool Desporto::isCrescente() const{
	return pontuacao.crescente;
}

/*
------------------------------------------------------------------------------
								Class Modalidade
------------------------------------------------------------------------------
*/

Modalidade::Modalidade(){}

Modalidade::Modalidade(string n, int h, int m, Desporto d){
	nome = n;
	duracao = Hora(h, m);
	desporto = &d;
}

string Modalidade::getNome() const{
	return nome;
}

Hora Modalidade::getDuracao() const{
	return duracao;
}

Desporto* Modalidade::getDesporto() const{
	return desporto;
}
