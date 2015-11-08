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

class Atleta;
class Prova;

class Equipa{
	string nome;
	vector<Atleta *> atletas;
	vector<Desporto *> desportos;
public:
	Equipa(string n);
	string getNome() const;
	vector<Atleta *> getAtletas() const;
	vector<Desporto *> getDesportos() const;

	void setNome(string n);
	void setAtletas(vector <Atleta *> a) ;
	void setDesportos(vector <Desporto *> d);

	bool adicionaAtleta(Atleta * a);
	void adicionaDesporto(Desporto * d);

	bool operator== (const Equipa & c) const;
	friend ostream & operator<<(ostream & o, const Equipa & d);
	Equipa & operator= (const Equipa & a);

	void adicionarDesporto(vector<Desporto*> DespList);
	void retirarDesporto();
	void menu(vector<Desporto*> DespList);
	void menuAtletas();

	void adicionaAtleta();
	class AtletaExiste{
		string nome;
		public:
		AtletaExiste(){};
		AtletaExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};

	class EquipaInexistente{
		string nome;
	public:
		EquipaInexistente() {}
		EquipaInexistente(string n) { nome = n;}
		string getNome() const {return nome;}
	};
};


class Atleta{
	string nome;
	Equipa* equipa;
	vector<Prova *> provas;
	vector<Modalidade *> modalidades;
	bool genero;
	int pontos;
public:
	Atleta(string n, Equipa* e, bool g);

	string getNome() const;
	Equipa* getEquipa() const;
	int getPontos() const;
	vector<Prova *> getProvas() const;
	vector<Modalidade *> getModalidades() const;
	bool getGenero() const;

void setGenero(bool g);
	void setNome( string n);
	void setEquipa(Equipa & eq);
	void setProvas(vector <Prova *> p);
	void setModalidades(vector <Modalidade *> m);
	void setpontos(int p); //no fim nao precisamos disto, e para testar

	void adicionaProva(Prova * p);
	void adicionaModalidade(Modalidade * m);
	void adicionaPontuacao(int p);

	void menu();

	bool operator== (const Atleta & c) const;
	friend ostream & operator<<(ostream & o, const Atleta & d);
	bool operator <(const Atleta & a) const;
	Atleta & operator= (const Atleta & a);
};


#endif /* SRC_EQUIPA_H_ */
