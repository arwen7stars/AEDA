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
//#include "Modalidade.h"

using namespace std;

struct Pontuacao{
	string nome;
	bool crescente; // se a pontuacao e crescente ou nao
};

class Modalidade;

class Desporto{
	string nome;
	vector<Modalidade *> modalidades;
	Pontuacao pontuacao;
	//int numeroAtletas;
public:
	Desporto();
	Desporto(string n, string pont, bool cresc);

	string getNome() const;
	string getPontuacao() const;
	vector<Modalidade *> getModalidades() const;
	bool isCrescente() const;

	bool operator== (const Desporto & c) const;
	friend ostream & operator<<(ostream & o, const Desporto & d);

	void menu();
	void menuModalidades();

	void adicionaModalidade();
	void adicionaModalidade(Modalidade *m);
	class ModalidadeExiste{
		string nome;
	public:
		ModalidadeExiste(){};
		ModalidadeExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};
};


//class DesportoEquipa: public Desporto{
//	int numeroAtletas;
//public:
//	DesportoEquipa(){}
//	DesportoEquipa(string n, string pont, bool cresc, int num);
//	int getNumeroAtletas() const;
//};
//
//class DesportoSolo: public Desporto{
//public:
//	DesportoSolo(){};
//	DesportoSolo(string n, string pont, bool cresc);
//};


#endif
