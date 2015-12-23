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

/**Class Data
 *
 * Represente um possessor de entradas para as provas
 *
 */
class Bilhete{
	string endereco;
	string nome;
	string morada;
	vector<Prova*> provasCompradas;
	bool a_venda;
public:
	Bilhete(){};
	/**
	 * Inicializa os atributos
	 * @param endereco - endereco do comprador
	 * @param nome - nome do comprador
	 * @param morada - morada do comprador
	 */
	Bilhete(string endereco, string nome, string morada);
	/**
	 * Adiciona todas as provas do vetor provas ao vetor provasCompradas do bilhete
	 * @param provas - vetor de provas a adicionar ao bilhete
	 */
	void adicionaProva(vector<Prova *> provas);
	/**
	 * Adiciona a prova p ao vetor provasCompradas do bilhete
	 * @param p - apontodor para a prova a adicionar
	 * @return false se p ja existir, false se nao e a prova for adionada com sucesso
	 */
	bool adicionaProva(Prova* p);
	/**
	 * Mostra a lista de provas do bilhete e permite selecionar uma delas.
	 * A prova selecionada e apagado do bilhete.
	 * @return false se o bilhete nao tiver provas, true caso contrario
	 */
	bool retiraProva();
	void setAVenda(bool avenda);
	string getEndereco() const;
	string getNome() const;
	string getMorada() const;
	bool getAVenda() const;
	vector<Prova*> getProvasCompradas() const;
	friend ostream & operator<<(ostream & o, const Bilhete & b);
};

struct BilhetesHash {
	int operator() (const Bilhete & bilhete) const {
		int h = bilhete.getEndereco().size() % 10;
		h *= 10;
		h += bilhete.getMorada().size() % 10;
		h *= 10;
		h += bilhete.getEndereco().size() % 100;
		return h;
	}
};

struct eqbil {
	bool operator() (const Bilhete & bilhete1, const Bilhete & bilhete2) const {
		if (bilhete1.getEndereco() == bilhete2.getEndereco())
			return true;
		return false;
	}
};

typedef tr1::unordered_set<Bilhete, BilhetesHash, eqbil> tabHBilhetes;

#endif
