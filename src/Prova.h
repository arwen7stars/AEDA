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

class Prova{
protected:
	Modalidade* modalidade;
	Data data;
	Hora inicio, fim;
	vector<Atleta *> atletas;
	bool genero;
	bool realizada;
public:
	Prova(){};
	Prova(Modalidade* m, Data d, Hora i, char g);

	Hora getInicio() const;
	Hora getFim() const;
	Data getData() const;
	Modalidade* getModalidade() const;
	vector<Atleta*> getAtletas() const;
	bool getGenero() const;
	bool getRealizada() const;

	void apagaAtleta(string nome);

	void adicionaAtleta(Atleta * a);
	void adicionarAtleta(vector<Equipa*> TeamList, vector<Desporto*> DespList);
	void retirarAtleta();

	bool Simultaneo(Prova p);

	void menu(vector<Equipa*> TeamList, vector<Desporto*> DespList);

	friend ostream & operator<<(ostream & o, const Prova & p);
	bool operator < (const Prova &p2) const;
	bool operator == (const Prova &p2) const;

	class ProvasSimultaneas : public ExcecoesLoadProva {
		string mod1, mod2;
	public:
		ProvasSimultaneas() {}
		ProvasSimultaneas(string m1, string m2) : mod1(m1), mod2(m2) {}
		string getMessage() const{
			string m = "Provas " + mod1 + " e " + mod2 + " simultaneas\n";
			return m;
		}
	};
};

class ProvaTerminada: public Prova{ //Quando uma prova ja terminou, transformamola num ProvaTerminada
	vector<float> pontuacoes; //Vetor com as pontuacoes dos atletas, corresponde com o vector atletas
public:
	ProvaTerminada(Modalidade* m, Data d, Hora i, char g); //o ranking final so e atualizado durante o atribui pontuacoes, chamado em realizaProva
	Atleta* getPrimeiro() const;
	Atleta* getSegundo() const;
	Atleta* getTerceiro() const;
	vector < float> getPontuacoes() const;
	void setAtletas(vector<Atleta*> a);
	bool operator < (const ProvaTerminada &p) const;
};


#endif /* SRC_PROVA_H_ */
