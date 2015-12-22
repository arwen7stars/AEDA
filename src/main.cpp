/*
 * main.cpp
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include "Lists.h"
#include "Desporto.h"
#include "Data.h"
#include "Prova.h"
#include "Campeonato.h"

struct Load
{
	Campeonato campeonato;
	bool sucesso;
};

Load loadCampeonato(){
	Load l;
	ifstream in;
	string campeonato = "Campeonato.txt";
	l.sucesso = true;
	if(!ficheiroExiste(campeonato))
	{
		throw FicheiroInexistente(campeonato);
	}

	in.open(campeonato.c_str());

	string nome;

	int ini_dia;
	int ini_mes;
	int ini_ano;

	int fim_dia;
	int fim_mes;
	int fim_ano;

	int h_abertura;
	int m_abertura;

	int h_fecho;
	int m_fecho;

	string info;

	getline(in,nome);

	in >> info;
	in >> ini_dia;
	in >> ini_mes;
	in >> ini_ano;

	in >> info;
	in >> fim_dia;
	in >> fim_mes;
	in >> fim_ano;

	in >> info;
	in >> h_abertura;
	in >> m_abertura;
	in >> info;
	in >> h_fecho;
	in >> m_fecho;

	try{
		Data dat1 (ini_ano,ini_mes,ini_dia);
		Data dat2 (fim_ano,fim_mes,fim_dia);
	} catch(Data::DataInvalida &d)
	{
		system("cls");
		cout << d.getMessage();
		l.sucesso = false;
		_getch();
	}

	Data d1 (ini_ano,ini_mes,ini_dia);
	Data d2 (fim_ano,fim_mes,fim_dia);
	Hora h1 (h_abertura,m_abertura);
	Hora h2 (h_fecho,m_fecho);

	Campeonato c (nome, d1, d2,h1, h2);
	l.campeonato = c;

	return l;
}


Load load()
{
	Load l;

	try{
	loadCampeonato();
	} catch(FicheiroInexistente &e)
	{
		system("cls");
		cout << "O ficheiro " << e.getNome()<< " nao existe.\n";
		l.sucesso = false;
		_getch();
	}
	l = loadCampeonato();
	Campeonato c = l.campeonato;

	if (!l.sucesso)
		return l;

	string desportos = "Desportos.txt";
	string equipas = "Equipas.txt";
	string modalidades = "Modalidades.txt";
	string provas = "Provas.txt";

	if(!ficheiroExiste(desportos))
	{
		throw FicheiroInexistente(desportos);
	}
	else if(!ficheiroExiste(equipas))
	{
		throw FicheiroInexistente(equipas);
	}
	else if(!ficheiroExiste(modalidades))
	{
		throw FicheiroInexistente(modalidades);
	} else if(!ficheiroExiste(provas))
	{
		throw FicheiroInexistente(provas);
	}

	try{
		c.loadDesportos(desportos);
	}
	catch(CaraterInvalido &e)
	{
		system("cls");
		cout << "Ocorreu um erro ao fazer load do ficheiro Desportos.txt" << endl;
		cout << "O carater " << e.getChar() << " e invalido!\n";
		l.sucesso = false;
		_getch();
	}

	try {
		c.loadEquipas(equipas);
	} catch (Equipa::EquipaInexistente &e)
	{
		system("cls");
		cout << "A equipa " << e.getNome() << " nao existe!\n";
		l.sucesso = false;
		_getch();
	} catch (LoadFail &e)
	{
		system("cls");
		cout << "Ocorreu um erro ao abrir o ficheiro " << e.getNome() << "." << endl;
		l.sucesso = false;
		_getch();
	}

	try{
		c.loadModalidades(modalidades);
	} catch(Hora::HoraInvalida &e)
	{
		system("cls");
		cout << e.getMessage();
		l.sucesso = false;
		_getch();
	}
	catch(Desporto::DesportoInexistente &e)
	{
		system("cls");
		cout << e.getMessage();
		l.sucesso = false;
		_getch();
	}

	try {
		c.loadProvas(provas);
	} catch(LoadProvasFail &e)
	{
		system("cls");
		cout << e.getMessage();
		l.sucesso = false;
		_getch();
	}

	l.campeonato = c;

	return l;
}



void menu(){
	vector<string> choices;
	choices.push_back("Carregar Campeonato");

	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Campeonato Polidesportivo", choices);
		if (ch == -1)
			exit = true;
		else{
			try{
				Load l = load();
				Campeonato C = l.campeonato;
				if (l.sucesso){
					int v = C.provasSimultaneas();
					cout << v << endl;

					if (v > 3){
						system("cls");
						cout << "O campeonato tem mais de 3 provas simultaneas!\n";
						cout << "Mude a data de uma das provas simultaneas.\n";
						_getch();
						C.alterarDataInicio();
					}

					C.menuCriacao();
				}
				else
				{
					cout << "Ocorreu algum erro!" << endl;
					return;
				}
			}
			catch(FicheiroInexistente &e)
			{
				system("cls");
				cout << "O ficheiro " << e.getNome() << " nao existe.\n";
				_getch();
				return;
			}
		}
	}
}


int main(){

	try{
		menu();
	} catch(...)
	{
		cout << "Um erro inesperado ocorreu, o programa ira agora terminar.\n\nGAME OVER";
		_getch();
	}
	system("cls");
	cout << "Press any key to continue...";
	_getch();
	return 0;
}

