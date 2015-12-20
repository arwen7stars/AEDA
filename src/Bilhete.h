/*
 * Bilhete.h
 *
 *  Created on: 20/12/2015
 *      Author: Filipe
 */

#ifndef SRC_BILHETE_H_
#define SRC_BILHETE_H_

#include <string>
#include <vector>
#include "Prova.h"
#include <tr1/unordered_set>
using namespace std;

class Bilhete{
	string endereco;
	string nome;
	string morada;
	vector<Prova*> provasCompradas;
public:
	Bilhete(){};
	Bilhete(string endereco, string nome, string morada);
	void adicionaProva(vector<Prova *> provas);
	bool adicionaProva(Prova* p);
	bool retiraProva();
	string getEndereco() const;
	string getNome() const;
	string getMorada() const;
};

struct BilhetesHash{
	int operator() (const Bilhete & bilhete){
		int h = bilhete.getEndereco().size() % 10;
		h *= 10;
		h += bilhete.getMorada().size() % 10;
		h *= 10;
		h += bilhete.getEndereco().size() % 100;
		return h;
	}

	bool operator() (const Bilhete & bilhete1, const Bilhete & bilhete2){
		if (bilhete1.getEndereco() == bilhete2.getEndereco())
			return true;
		return false;
	}
};

typedef tr1::unordered_set<Bilhete, BilhetesHash, BilhetesHash> tabHBilhetes;

#endif
