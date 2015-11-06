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

/*
 * Class Campeonato
 * Representa um campeonato
 */
class Campeonato{
	string nome; ///< Nome do campeonato
	vector<Desporto *> desportos; ///< Lista de Desportos/Modalidades
	vector<Equipa* > equipas; ///< Lista de Equipas
	vector<Prova *> provas;
	bool criado;
	Data inicio, fim;///< Data do inicio e do fim do campeonato, pode dar jeito
	Hora abertura, fecho;
public:
	Campeonato(string n, Data i, Data f, Hora a, Hora fe);
	bool adicionaProva(Prova p);
	bool criaDesportosCampeonato(string nome_ficheiro);
	bool criaEquipasCampeonato(string nome_ficheiro);

	vector<Desporto *> getDesportos() const;
	vector<Prova* > getProvas() const;
	bool isCriado() const {return criado;}

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
};

void atribuiPontuacao(Prova pro, vector<float> pontos);


#endif /* CAMPEONATO_H_ */
