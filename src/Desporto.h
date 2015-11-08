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
#include "Lists.h"
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
	/**Construtor default
	 *
	 */
	Desporto();
	/**Construtor de Desporto
	 *
	 * inicializa nome, pontuacao.nome, pontuacao.crescente
	 *
	 * @param n - nome do desporto
	 * @param pont - tipo de pontuacao do desporto
	 * @param cresc - true se a pontuacao e crecente ( se o vencedor é quem tem mais pontos)
	 */
	Desporto(string n, string pont, bool cresc);

	string getNome() const;
	string getPontuacao() const;
	vector<Modalidade *> getModalidades() const;
	bool isCrescente() const;

	/**Retira modalidade do vetor de modalidades do desporto
	 *
	 * Procura a modalidade de indice indice e retira-a o vetor modalidades
	 *
	 * @param indice - indice da modalidade em modalidades
	 */
	void apagaModalidade(int indice);
/**Compara dois desportos
 *
 * Verifica se os dois desportos tem o mesmo nome
 *
 * @param c - desporto a comparar
 * @return true se os dois desportos tiverem o mesmo nome
 */
	bool operator== (const Desporto & c) const;
	/**Devolve um ostream com o nome do desporto
	 *
	 * Preenche o com o nome do desporto
	 *
	 * @param o - ostream a alterar
	 * @param d - desporto cujo nome vai para o
	 * @return o, com o nome do desporto
	 */
	friend ostream & operator<<(ostream & o, const Desporto & d);
/**Mostra na interface um menu para o utilizador escolher que atributos do desporto quer mudar
 *
 * O utilizador pode escolher entre mudar as modalidades, o tipo ou a hierarquia da pontuacao e o nome do desporto
 *
 */
	void menu();
	/**Mostra na interface um menu para o utilizador alterar as modalidades do campeonato
	 *
	 * O utilizador pode escolher entre alterar as modalidades existentes (é chamada a funcao menuModalidades)
	 * e criar uma nova modalidade (e chamado o adicionaModalidade)
	 *
	 */
	void menuModalidades();

	void adicionaModalidade();
	void adicionaModalidade(Modalidade *m);

	class DesportoInexistente {
		string nome;
	public:
		DesportoInexistente() {}
		DesportoInexistente(string n) { nome = n;}
		string getMessage() const {
			string m = "O desporto " + nome + " nao existe!\n";
			return m;
		}
	};

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
