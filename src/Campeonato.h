/*
 * Campeonato.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef CAMPEONATO_H_
#define CAMPEONATO_H_

#include <string>
#include <vector>
#include <fstream>
#include "Desporto.h"
#include "Equipa.h"
#include "Data.h"
#include "Lists.h"

/*
 * Class Campeonato
 * Representa um campeonato
 */
class Campeonato{
	string nome; ///< Nome do campeonato
	vector<Desporto *> desportos; ///< Lista de Desportos/Modalidades
	vector<Equipa* > equipas; ///< Lista de Equipas
	vector<Prova *> provas;
	vector<ProvaTerminada> provasTerminadas;
	bool criado;
	Data inicio, fim;///< Data do inicio e do fim do campeonato, pode dar jeito
	Hora abertura, fecho;
public:
	Campeonato(string n, Data i, Data f, Hora a, Hora fe);
	bool adicionaDesporto(Desporto &d);
	bool adicionaEquipa(Equipa * eq);
	void adicionaProva(Prova &p);

	void loadDesportos(string nome_ficheiro);
	void loadEquipas(string nome_ficheiro);
	void loadModalidades(string nome_ficheiro);
	void loadProvas(string nome_ficheiro);

	void updateDesportos(string nome_ficheiro);
	void updateEquipas(string nome_ficheiro);
	void updateModalidades(string nome_ficheiro);
	void updateProvas(string nome_ficheiro);

	void apagaDesporto(string n);
	void apagaModalidade(string n);

	string getNome() const;
	Data getInicio() const;
	Data getFim() const;
	Hora getAbertura() const;
	Hora getFecho() const;
	vector<Desporto *> getDesportos() const;
	vector<Prova* > getProvas() const;
	vector<Equipa*> getEquipas() const;
	bool isCriado() const {return criado;}

	void menuApagar();
	void menuCriacao();
	void menuDesportos();
	void menuEquipas();
	void menuProvas();

	void adicionaDesporto();
	class DesportoExiste{
		string nome;
	public:
		DesportoExiste(){};
		DesportoExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};

	void adicionaEquipa();
	void adicionaEquipa(Equipa &eq);
	class EquipaExiste{
		string nome;
	public:
		EquipaExiste(){};
		EquipaExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};

	void adicionaProva();
	class DataInvalida{
		Data data;
	public:
		DataInvalida(){};
		DataInvalida(Data d) {data = d;}
		Data getData() const {return data;}
	};
	class HoraInvalida{
		Hora hora;
	public:
		HoraInvalida(){};
		HoraInvalida(Hora h) {hora = h;}
		Hora getHora() const {return hora;}
	};

	bool realizaProva(Prova & p, vector <float> pontuacoes);
	void listaDesportos() const;
	void listaProvasNaoRealizadas() const;
	void listaProvasRealizadas() const;
	void listaAtletas() const;
	void listaAtletasEquipa() const;
	void listaAtletasColocacao() const;
	void listaAtletasDesporto() const;
	void listaAtletasModalidade() const;
	void listaEquipasColocacao() const ;
};

void atribuiPontuacao(Prova pro, vector<float> pontos);


#endif /* CAMPEONATO_H_ */

