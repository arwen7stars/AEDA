/*
 * Prova.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef SRC_PROVA_H_
#define SRC_PROVA_H_

#include <iostream>
#include <string>
#include <vector>
#include "Desporto.h"
#include "Data.h"
#include "Modalidade.h"
#include "Equipa.h"

using namespace std;

class Atleta;
class Equipa;

/**Class Prova
 *
 * Representa um evento de uma modalidade
 */
class Prova{
protected:
	Modalidade* modalidade;
	Data data;
	Hora inicio, fim;
	vector<Atleta *> atletas;
	bool genero;
	bool realizada;
public:
	Prova(){
		realizada = false;
		genero = false;
		modalidade = NULL;
	};
	/**
	 *
	 * @param m - modalidade
	 * @param d - data
	 * @param i - hora
	 * @param g - genero
	 */
	Prova(Modalidade* m, Data d, Hora i, char g);

	/**
	 *
	 * @return inicio
	 */
	Hora getInicio() const;
	/**
	 *
	 * @return fim
	 */
	Hora getFim() const;
	/**
	 *
	 * @return data
	 */
	Data getData() const;
	/**
	 *
	 * @return modalidades
	 */
	Modalidade* getModalidade() const;
	/**
	 *
	 * @return atletas
	 */
	vector<Atleta*> getAtletas() const;
	/**
	 *
	 * @return genero
	 */
	bool getGenero() const;
	/**
	 *
	 * @return realizada
	 */
	bool getRealizada() const;

	/**
	 * Apaga o atleta de nome nome do vetor atletas
	 * @param nome - nome do atleta
	 */
	void apagaAtleta(string nome);

	/**
	 * Adiciona atleta ao vetor atletas
	 * @param a - atleta
	 */
	void adicionaAtleta(Atleta * a);
	/**
	 * Permite ao utilizador escolher um atleta
	 * @param TeamList - Lista de equipas
	 * @param DespList - Lista de desportos
	 */
	void adicionarAtleta(vector<Equipa*> TeamList);

	/**
	 * Permite ao utilizador escolher um atleta para apagar
	 */
	void retirarAtleta();

	/**
	 *
	 * @param p - prova
	 * @return true se p e esta prova pertencerem ao mesmo desporto e forem em simultaneo
	 */
	bool Simultaneo(Prova p);

	/**
	 * Mostra as seguintes opcoes: (Alterar Atletas e Retirar Atletas)
	 * @param TeamList - Lista de equipas
	 * @param DespList - Lista de desportos
	 */
	void menu(vector<Equipa*> TeamList);

	/**
	 * imprime uma prova
	 *
	 * @param o - stream de output
	 * @param p - uma proba
	 * @return o
	 */
	friend ostream & operator<<(ostream & o, const Prova & p);
	/**
	 *
	 * @param p2 - prova
	 * @return true se occorer antes p2, false se nao
	 */
	bool operator < (const Prova &p2) const;
	/**
	 *
	 * @param p2 - prova
	 * @return true se forem iguais, false se nao
	 */
	bool operator == (const Prova &p2) const;

	/**
	 * Uma expecao para quando duas provas sao incompativeis
	 */
	void setInicio(Data d, Hora i);
	void setRealizada(bool r);
	class ProvasSimultaneas : public LoadProvasFail {
		string mod1, mod2;
	public:
		ProvasSimultaneas() {}
		/**
		 *
		 * @param m1 - modalidade
		 * @param m2 - outra modalidade
		 */
		ProvasSimultaneas(string m1, string m2) : mod1(m1), mod2(m2) {}
		/**
		 * cria uma mensagem com os nomes de m1 e m2
		 * @return uma mensagem de erro
		 */
		string getMessage() const{
			string m = "Provas " + mod1 + " e " + mod2 + " simultaneas\n";
			return m;
		}
	};

	class ProvaInexistente {
		Prova * prova;
	public:
		ProvaInexistente() {prova=NULL;}
		ProvaInexistente(Prova * p) : prova(p) {}
		/**
		 * Constroi uma mensagem como o nome da modalidade
		 *
		 * @return uma string como uma mensagem
		 */
		string getMessage() const{
			string ano = int_to_string(prova->getData().getAno());
			string mes = int_to_string(prova->getData().getMes());
			string dia = int_to_string(prova->getData().getDia());
			string horas = int_to_string(prova->getInicio().getHoras());
			string minutos = int_to_string(prova->getInicio().getMinutos());

			string message = "A prova da modalidade " + prova->getModalidade()->getNome() + " na data ";
			message += ano + "/" + mes + "/" + dia;
			message += " as " + horas + ":" + minutos + " nao existe!\n";
			return message;
		}
	};
};

/**class ProvaTerminada
 *
 * Representa uma prova que ja ocorreu
 */
class ProvaTerminada: public Prova{ //Quando uma prova ja terminou, transformamola num ProvaTerminada
	vector<float> pontuacoes; //Vetor com as pontuacoes dos atletas, corresponde com o vector atletas
public:
	/**
	 *
	 * @param m - modalidade
	 * @param d - data
	 * @param i - hora
	 * @param g - genero
	 */
	ProvaTerminada(Modalidade* m, Data d, Hora i, char g);
	/**
	 *
	 * @return o atleta em primeiro lugar
	 */
	Atleta* getPrimeiro() const;
	/**
	 *
	 * @return o atleta em segundo lugar
	 */
	Atleta* getSegundo() const;
	/**
	 *
	 * @return o atleta em terceiro lugar
	 */
	Atleta* getTerceiro() const;
	/**
	 *
	 * @return pontuacoes
	 */
	vector < float> getPontuacoes() const;
	/**
	 * Muda atletas para a;
	 * @param a - um vetor de atletas
	 */
	void setAtletas(vector<Atleta*> a);
	void setPontuacoes(vector<float> pont);
	/**
	 *
	 * @param p2 - prova
	 * @return true se occorer antes p2, false se nao
	 */
	bool operator < (const ProvaTerminada &p) const;
};


#endif /* SRC_PROVA_H_ */
