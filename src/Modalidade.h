/*
 * Modalidade.h
 *
 *  Created on: 03/11/2015
 *      Author: Filipe
 */

#ifndef SRC_MODALIDADE_H_
#define SRC_MODALIDADE_H_

#include <string>
#include <vector>
#include "Data.h"

using namespace std;

class Desporto;

/**Classe Modalidade
 * Gere um tipo de prova, isto e uma modalidade.
 *
 * @author Claudia Marinho, Daniela Sa, Joao Costa
 * @date 08/11/2015
 */
class Modalidade{
	string nome;
	Hora duracao;
	Desporto* desporto;
public:
	Modalidade();
	/**
	 *
	 * @param n - nome da modalidade
	 * @param h - numero de horas que dura uma prova da modalidade
	 * @param m - numero de minutos que dura uma prova da modalidade
	 * @param d - desporto ao qual pertence a modalidade
	 */
	Modalidade(string n, int h, int m, Desporto *d);

	/**
	 *
	 * @return nome
	 */
	string getNome() const;
	/**
	 *
	 * @return duracao
	 */
	Hora getDuracao() const;
	/**
	 *
	 * @return desporto
	 */
	Desporto* getDesporto() const;

	/**
	 *
	 * @param c - uma modalidade
	 * @return true se o nome de c e desta modalidade forem iguais, false caso contrario.
	 */
	bool operator== (const Modalidade & c) const;
	friend ostream & operator<<(ostream & o, const Modalidade & d);

	/**
	 * Menu de Interface de uma modalidade
	 *
	 * Mostra a seguinte opcao: (Alterar Nome)
	 */
	void menu();

	/**Classe ModalidadeInexistente
	 *
	 * Uma expecao de nao existir uma modalidade em causa
	 *
	 */
	class ModalidadeInexistente : public LoadProvasFail {
		string nome;
	public:
		ModalidadeInexistente() {}
		/**
		 * Inicializa nome
		 * @param n - nome da modalidade
		 */
		ModalidadeInexistente(string n) : nome(n) {}
		/**
		 * Constroi uma mensagem como o nome da modalidade
		 *
		 * @return uma string como uma mensagem
		 */
		string getMessage() const{
			string message = "A modalidade " + nome + " nao existe!\n";
			return message;
		}
	};
};



#endif /* SRC_MODALIDADE_H_ */

