/*
 * Equipa.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_EQUIPA_H_
#define SRC_EQUIPA_H_

#include <string>
#include <vector>
#include "Prova.h"
#include "Desporto.h"

using namespace std;

struct Medalhas{
	int ouro;
	int prata;
	int bronze;
};

class Atleta;
class Prova;

/**Class Equipa
 *
 * Representa um conjunto de atletas
 */
class Equipa{
	string nome;
	vector<Atleta *> atletas;
	vector<Desporto *> desportos;
	Medalhas medalhas;
public:
	Equipa(){
		nome = "";
	}
	/**
	 * Inicializa o nome
	 *
	 * @param n - nome da equipa
	 */
	Equipa(string n);
	/**
	 *
	 * @return nome
	 */
	string getNome() const;
	/**
	 *
	 * @return atletas
	 */
	vector<Atleta *> getAtletas() const;
	/**
	 *
	 * @return desportos
	 */
	vector<Desporto *> getDesportos() const;

	/**
	 * Altera nome para n;
	 *
	 * @param n - nome da equipa
	 */
	void setNome(string n);
	/**
	 * Altera atletas para a;
	 *
	 * @param a - lista de atletas
	 */
	void setAtletas(vector <Atleta *> a) ;
	/**
	 * Altera desportos para d;
	 *
	 * @param d - lista de desportos
	 */
	void setDesportos(vector <Desporto *> d);
	//void setMedalhas();

	/**
	 * adiciona um novo atleta se este ainda nao estiver na equipa
	 * @param a - um atleta
	 * @return true se conseguir adicionar, false se nao
	 */
	bool adicionaAtleta(Atleta * a);
	/**
	 * adiciona um novo desporto se este ainda nao estiver na equipa
	 * @param d - um desporto
	 */
	void adicionaDesporto(Desporto * d);

	/**
	 *
	 * apaga a modalidade de indice i_modalidade de um atleta de indice i_atleta
	 * @param i_atleta - indice do atleta
	 * @param i_modalidade - indice da modalidade
	 */
	void apagaModalidade(int i_atleta, int i_modalidade);
	/**
	 * apaga o atleta de nome nome
	 * @param nome - nome do atleta
	 */
	void apagaAtleta(const string nome);
	void apagaProva(int i_atleta, int i_prova);

	/**
	 *
	 * @param c - uma equipa
	 * @return true se o nome de c e desta equipa forem iguais, false caso contrario.
	 */
	bool operator== (const Equipa & c) const;
	/**
	 * imprime o nome da equipa
	 *
	 * @param o - stream de output
	 * @param d - uma equipa
	 * @return o
	 */
	friend ostream & operator<<(ostream & o, const Equipa & d);
	/**
	 *
	 * @param a - uma equipa
	 * @return uma equipa igual a "a"
	 */
	Equipa & operator= (const Equipa & a);

	/**
	 * Abre uma lista de desportos a partir do vector DespList, e permite selecionar um , o qual e adicionado.
	 *
	 * @param DespList - Lista de desportos
	 */
	void adicionarDesporto(vector<Desporto*> DespList);

	/**
	 *  Abre a lista  a partir do vector desportos, e permite selecionar um , o qual e retirado.
	 */
	void retirarDesporto();

	/**
	 * Abre um menu com as seguintes opcoes: Alterar Nome, Alterar Atletas, Inscrever em Desporto e Desinscrever de Desporto
	 */
	void menu(vector<Desporto*> DespList);
	/**
	 * Abre uma lista de selecao com todos os atletas da equipa, e permite escolher um ou adicionar um novo
	 */
	void menuAtletas();

	/**
	 * Pede ao utilizador a informacao necessaria para criar um atleta, e cria-o.
	 */
	void adicionaAtleta();

	/**Classe AtletaExiste
	 *
	 * Uma excecao para o caso de tentarmos criar um atleta que ja exista
	 */
	class AtletaExiste{
		string nome;
	public:
		AtletaExiste(){};
		/**
		 * Inicializa o nome
		 * @param n - nome do atleta
		 */
		AtletaExiste(string n) {nome = n;}
		/**
		 *
		 * @return nome
		 */
		string getNome() const {return nome;}
	};

	/**Classe AtletaExiste
	 *
	 * Uma excecao para o caso de o atleta em causa nao existir na equipa
	 */
	class EquipaInexistente{
		string nome;
	public:
		EquipaInexistente() {}
		/**
		 * Inicializa o nome
		 * @param n - nome do atleta
		 */
		EquipaInexistente(string n) { nome = n;}
		/**
		 *
		 * @return nome
		 */
		string getNome() const {return nome;}
	};

	Medalhas getMedalhas() const {return medalhas;}
	void addOuro(){medalhas.ouro++;}
	void addPrata(){medalhas.prata ++;}
	void addBronze(){medalhas.bronze++;}

};

/**Class Equipa
 *
 * Representa um atleta de uma equipa
 */
class Atleta{
	string nome;
	Equipa* equipa;
	vector<Prova *> provas;
	vector<Modalidade *> modalidades;
	bool genero;
	int pontos;
	Medalhas medalhas;
public:
	/**
	 * Inicializa os atributos
	 *
	 * @param n - nome do atleta
	 * @param e - equipa
	 * @param g - genero (true masculino, false feminino)
	 */
	Atleta(string n, Equipa* e, bool g);

	/**
	 *
	 * @return nome
	 */
	string getNome() const;
	/**
	 *
	 * @return equipa
	 */
	Equipa* getEquipa() const;
	/**
	 *
	 * @return pontos
	 */
	int getPontos() const;
	/**
	 *
	 * @return provas
	 */
	vector<Prova *> getProvas() const;
	/**
	 *
	 * @return modalidades
	 */
	vector<Modalidade *> getModalidades() const;
	Medalhas getMedalhas() const;
	/**
	 *
	 * @return genero
	 */
	bool getGenero() const;

	/**
	 * Muda genero para g
	 * @param g - genero (true feminino, false masculino)
	 */
	void setGenero(bool g);

	/**
	 * Muda nome para n
	 *
	 * @param n - nome do atleta
	 */
	void setNome( string n);

	/**
	 * Muda equipa para eq
	 * @param eq - uma equipa
	 */
	void setEquipa(Equipa & eq);

	/**
	 * Muda provas para p
	 *
	 * @param p - um vetor de provas
	 */
	void setProvas(vector <Prova *> p);
	/**
	 * Muda modalidadess para m
	 *
	 * @param m - um vetor de modalidades
	 */
	void setModalidades(vector <Modalidade *> m);
	/**
	 * Muda pontos para p
	 *
	 * @param p - numero de pontos
	 */
	void setpontos(int p); //no fim nao precisamos disto, e para testar

	/**
	 * Adiciona p ao vetor provas
	 * @param p - uma prova
	 */
	void adicionaProva(Prova * p);

	/**
	 * Adiciona m ao vetor modalidades
	 * @param m - uma modalidade
	 */
	void adicionaModalidade(Modalidade * m);
	/**
	 * Adiciona p a pontos
	 * @param p - um numero de pontos
	 */
	void adicionaPontuacao(int p);

	/**
	 * Apaga a modalidade de indice indice em modalidades
	 * @param indice - indice da modalidade
	 */
	void apagaModalidade(int indice);
	/**
	 * Apaga a prova de indice indice em prova
	 * @param indice - indice da prova
	 */
	void apagaProva(int indice);


	/**
	 * Menu de Interface de uma modalidade
	 *
	 * Mostra a seguinte opcao: (Alterar Nome)
	 */
	void menu();

	/**
	 *
	 * @param c - uma equipa
	 * @return true se o nome de c e desta equipa forem iguais, false caso contrario.
	 */
	bool operator== (const Atleta & c) const;
	/**
	 * imprime o nome da equipa
	 *
	 * @param o - stream de output
	 * @param d - um atleta
	 * @return o
	 */
	friend ostream & operator<<(ostream & o, const Atleta & d);

	/**
	 *
	 * @param a - um atleta
	 * @return true se os pontos de a forem maiores que o atleta em causa
	 */
	bool operator <(const Atleta & a) const;

	/**
	 *
	 * @param a - um atleta igual a "a"
	 * @return
	 */
	Atleta & operator= (const Atleta & a);
};


#endif /* SRC_EQUIPA_H_ */
