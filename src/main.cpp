/*
 * main.cpp
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#include <vector>
#include <iostream>
#include <fstream>
#include "Lists.h"
#include "Desporto.h"
#include "Data.h"
#include "Campeonato.h"

Campeonato loadCampeonato(){
	ifstream in;
	string campeonato = "Campeonato.txt";

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
	} catch(Data::DataInvalida d)
	{
		system("cls");
		cout << d.getMessage();
	}

	Data d1 (ini_ano,ini_mes,ini_dia);
	Data d2 (fim_ano,fim_mes,fim_dia);
	Hora h1 (h_abertura,m_abertura);
	Hora h2 (h_fecho,m_fecho);

	Campeonato c (nome, d1, d2,h1, h2);
	return c;
}


Campeonato load()
{
	try{
	loadCampeonato();
	} catch(FicheiroInexistente e)
	{
		cout << "O ficheiro " << e.getNome()<< " nao existe.\n";
	}
	Campeonato c = loadCampeonato();

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
		bool suc = c.loadDesportos(desportos);

		if (!suc)
			throw LoadFail(desportos);
	}
	catch(CaraterInvalido &e)
	{
		cout << "Ocorreu um erro ao fazer load do ficheiro Desportos.txt" << endl;
		cout << "O carater " << e.getChar() << " e invalido!\n";
	}

	try {
		bool suc = c.loadEquipas(equipas);

		if (!suc)
			throw LoadFail(equipas);
	} catch (Equipa::EquipaInexistente &e)
	{
		system("cls");
		cout << "A equipa " << e.getNome() << " nao existe!\n";
	}

	try{
		bool suc = c.loadModalidades(modalidades);

		if (!suc)
			throw LoadFail(modalidades);
	} catch(Hora::HoraInvalida e)
	{
		system("cls");
		cout << e.getMessage();
	}
	catch(Desporto::DesportoInexistente e)
	{
		system("cls");
		cout << e.getMessage();
	}

	try {
		bool suc = c.loadProvas(provas);

		if (!suc)
			throw LoadFail(provas);
	} catch(LoadProvasFail &e)
	{
		system("cls");
		cout << e.getMessage();
	}

	return c;

}


void menu(){
	vector<string> choices;
	choices.push_back("Novo Campeonato");
	choices.push_back("Carregar Campeonato");

	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Campeonato Polidesportivo", choices);
		if (ch == -1)
			exit = true;
		else{
			try{
				Campeonato C = load();
				C.menuCriacao();
			}
			catch(FicheiroInexistente e)
			{
				system("cls");
				cout << "O ficheiro " << e.getNome() << " nao existe.\n";
			}

			//			if(C.isCriado())
			//				cout << "Ola";
			//			else
		}
	}
}


int main(){
//	Desporto D;
//	D = Desporto("Atletismo", "Segundos", true);
//	cout << D.getNome() << endl;
//	cout << D.getPontuacao() << endl;
//	cout << D.isCrescente() << endl;
//	cout << endl;
//
//
//	Modalidade M;
//	M = Modalidade("Corrida de 100 Metros", 13, 35, D);
//	cout << M.getNome() << endl;
//	cout << M.getDesporto()->getNome() << endl;
//	cout << endl;
/*
	Data d1 (2015,11,1);
	Data d2 (2015,11,10);
	Hora h1(8,0);
	Hora h2(20,0);
	Campeonato c ("Campeonato A", d1, d2, h1,h2);
	*/
//
//
//	if (c.criaDesportosCampeonato("Desportos.txt"))
//		cout<< "correu bem\n";
//	else cout << "correu mal\n";


	//Hora h1(13,30), h2(13,50), h3(20,00);
	//cout << (h1 < h2) << (h1 < h3) << (h3 > h2);
/*
 * 												TESTE DE ADICIONA PROVA
 *
 *
	Data dat1 (2015,11,1);
	Hora h3 (13,30);

	Desporto des1("Futebol", "Golos", true,11);
	Modalidade mod1("Final", 1,30, &des1);

	Prova p1(&mod1,dat1,h1);

	bool resultado1 = c.adicionaProva(p1);

	if (resultado1)
		cout << "correu bem!\n";
	else cout << "correu mal :(\n";

	Data dat2(2015,11,11);

	Desporto des2("FutebolAmericano", "Golos", true,11);
	Modalidade mod2("Meia-Final", 1,30, &des2);

	Prova p2(&mod2,dat2,h1);

	bool resultado2 = c.adicionaProva(p2);

	if (!resultado2)
		cout << "nao foi adicionada, pois dia e depois do fim do campeonato!\n";
	else cout << "correu mal :(\n";

	Hora h4(8,30);
	Data dat3(2015,10,31);

	Desporto des3("Corrida", "Segundos", true,1);
	Modalidade mod3("400 metros", 1,30, &des3);

	Prova p3(&mod3,dat3,h4);

	bool resultado3 = c.adicionaProva(p3);

	if (!resultado3)
		cout << "nao foi adicionada, pois dia e antes do inicio do campeonato!\n";
	else cout << "correu mal :(\n";

	Desporto des4("Corrida", "Segundos", true,1);
	Modalidade mod4("500 metros", 1,30, &des4);

	Prova p4(&mod4,dat1,h1);

	bool resultado4 = c.adicionaProva(p4);

	if (resultado4)
		cout << "foi adicionada, pois provas simultaneas mas de desportos diferentes!\n";
	else cout << "correu mal :(\n";

	Desporto des5("Corrida", "Segundos", true,1);
	Modalidade mod5("400 metros", 1,30, &des5);

	Prova p5(&mod5,dat1,h1);

	bool resultado5 = c.adicionaProva(p5);

	if (!resultado5)
		cout << "nao foi adicionada, pois provas simultaneas de desportos iguais!\n";
	else cout << "correu mal :(\n";

	Hora h5(9,30);
	Desporto des6("Corrida", "Segundos", true,1);
	Modalidade mod6("500 metros", 1,30, &des5);

	Prova p6(&mod6,dat1,h5);

	bool resultado6 = c.adicionaProva(p6);

	if (!resultado6)
		cout << "nao foi adicionada, pois provas simultaneas de desportos iguais!!!\n";
	else cout << "correu mal :(\n";

	Hora h6(11,59);
	Desporto des7("Corrida", "Segundos", true,1);
	Modalidade mod7("500 metros", 1,30, &des7);

	Prova p7(&mod7,dat1,h6);

	bool resultado7 = c.adicionaProva(p7);

	if (resultado7)
		cout << "foi adicionada!!!\n";
	else cout << "correu mal :(\n";

	Hora h7(15,01);
	Desporto des8("Corrida", "Segundos", true,1);
	Modalidade mod8("500 metros", 1,30, &des8);

	Prova p8(&mod8,dat1,h7);

	bool resultado8 = c.adicionaProva(p8);

	if (resultado8)
		cout << "foi adicionada!!!\n";
	else cout << "correu mal :(\n";

	Hora h8(14,00);
	Desporto des9("Corrida", "Segundos", true,1);
	Modalidade mod9("800 metros", 0,30, &des9);

	Prova p9(&mod9,dat1,h8);

	bool resultado9 = c.adicionaProva(p9);

	if (resultado9)
		cout << "foi adicionada!!!\n";
	else cout << "correu mal :(\n";
*/
	//menu();
/*
 * 												TESTE DA LISTA DE PROVAS
 *
 *
	Desporto D;
		D = Desporto("Atletismo", "Segundos", true,8);
		cout << D.getNome() << endl;
		cout << D.getPontuacao() << endl;
		cout << D.isCrescente() << endl;
		cout << endl;


		Modalidade M;
		M = Modalidade("Corrida de 100 Metros", 13, 35, &D);
		cout << M.getNome() << endl;
		cout << M.getDesporto()->getNome() << endl;
		cout << endl;

		Data d1 (2015,11,1);
		Data d2 (2015,11,10);
		Hora ha(8,0);
		Hora hb(19,30);

		Campeonato c ("Campeonato A", d1, d2,ha,hb);

	Data dat1 (2015,11,1);
		Hora h1 (13,30);

		Desporto des1("Futebol", "Golos", true,8);
		Modalidade mod1("Final", 1,30, &des1);

		Prova p1(&mod1,dat1,h1);

		bool resultado1 = c.adicionaProva(p1);

		if (resultado1)
			cout << "correu bem!\n";
		else cout << "correu mal :(\n";

		Desporto des2("FutebolAmericano", "Golos", true,2);
			Modalidade mod2("Meia-Final", 1,30, &des2);

	Desporto des4("Corrida", "Segundos", true,8);
		Modalidade mod4("500 metros", 1,30, &des4);

		Prova p4(&mod4,dat1,h1);

		bool resultado4 = c.adicionaProva(p4);

		if (resultado4)
			cout << "foi adicionada, pois provas simultaneas mas de desportos diferentes!\n";
		else cout << "correu mal :(\n";

	Hora h6(11,59);
		Desporto des7("Corrida", "Segundos", true,4);
		Modalidade mod7("500 metros", 1,30, &des7);

		Prova p7(&mod7,dat1,h6);

		bool resultado7 = c.adicionaProva(p7);

		if (resultado7)
			cout << "foi adicionada!!!\n";
		else cout << "correu mal :(\n";

		Hora h7(15,01);
		Desporto des8("Corrida", "Segundos", true,2);
		Modalidade mod8("500 metros", 1,30, &des8);

		Prova p8(&mod8,dat1,h7);

		bool resultado8 = c.adicionaProva(p8);

		if (resultado8)
			cout << "foi adicionada!!!\n";
		else cout << "correu mal :(\n";


		c.adicionaDesporto(D);
		c.adicionaDesporto(des1);
		c.adicionaDesporto(des2);
		c.listaDesportos();
		cout << endl;
		c.listaProvas();
*/


//	Campeonato c ("Campeonato A", d1, d2, h1,h2);

/*
 * 															TESTE DE LOAD()
 *
 * Campeonato c = load();

	cout << "Desportos.txt\n";
	for(unsigned int i = 0; i < c.getDesportos().size();i++)
	{
		cout << c.getDesportos()[i]->getNome() << " ";
		cout << c.getDesportos()[i]->getPontuacao() << " ";
		cout << c.getDesportos()[i]->isCrescente() << endl;
	}
	cout << endl;

	cout << "Atletas.txt\n";
	for(unsigned int i = 0; i < c.getEquipas().size();i++)
	{
		cout << c.getEquipas()[i]->getNome() << endl;
		Equipa * eq = c.getEquipas()[i];
		for(unsigned int j = 0; j < eq->getAtletas().size(); j++)
			{
			cout << eq->getAtletas()[j]->getNome() << " ";
			cout << eq->getAtletas()[j]->getGenero() << endl;
			}
		cout << endl;
	}

	menu();

	cout << "Campeonato.txt\n";
	cout << "Nome campeonato: " << c.getNome() << endl;
	cout << c.getInicio() << endl;
	cout << c.getFim() << endl;
	cout << c.getAbertura() << endl;
	cout << c.getFecho() << endl;
	cout << endl;

	cout << "Modalidades.txt\n";
	for(unsigned int i = 0; i < c.getDesportos().size();i++)
		{
			cout << c.getDesportos()[i]->getNome() << endl;
			Desporto * d = c.getDesportos()[i];
			for(unsigned int j = 0; j < d->getModalidades().size(); j++)
				{
				cout << d->getModalidades()[j]->getNome() << " ";
				cout << d->getModalidades()[j]->getDuracao() << endl;
				}
			cout << endl;
		}
*/
	//										TESTE DE LISTA DE ATLETAS
	//	Equipa A ("A");
	//	Equipa B ("B");
	//	Atleta a1 ("lui", &A, 'm');
	//	Atleta a2 ("panda", &B, 'm');
	//	Atleta a3 ("xtg", &A,'m');
	//	Atleta a4 ("coast", &B,'m');
	//	A.adicionaAtleta(&a1);
	//	A.adicionaAtleta(&a3);
	//	B.adicionaAtleta(&a2);
	//	B.adicionaAtleta(&a4);
	//	c.adicionaEquipa(A);
	//	c.adicionaEquipa(B);
	//a1.setpontos(1);
	//a2.setpontos(18);
	//a3.setpontos(4);
	//a4.setpontos(4);
	//	c.listaAtletasColocacao();
//
//	Equipa A ("A");
//	Equipa B ("B");
//	Atleta a1 ("lui", &A, 'm');
//	Atleta a2 ("panda", &B, 'm');
//	Atleta a3 ("xtg", &A,'m');
//	Atleta a4 ("coast", &B,'m');
//	A.adicionaAtleta(&a1);
//	A.adicionaAtleta(&a3);
//	B.adicionaAtleta(&a2);
//	B.adicionaAtleta(&a4);
//	c.adicionaEquipa(A);
//	c.adicionaEquipa(B);
//a1.setpontos(1);
//a2.setpontos(18);
//a3.setpontos(4);
//a4.setpontos(4);
//	c.listaAtletasColocacao();
/*
	 * 												NOTA IMPORTANTE
	 */
/*	Ao fazer load, usar isto para apanhar excecao


	try
	{
		load();
	} catch(FicheiroInexistente e)
	{
		cout << "Ficheiro " << e.getNome() << "inexistente";
	}
*/
/*
	Campeonato c = load();

	c.loadProvas("Provas.txt");


	cout << "Provas.txt\n";

	for(unsigned int i = 0; i < c.getProvas().size();i++)
		{
			cout << c.getProvas()[i]->getModalidade()->getNome() << endl;
			cout << c.getProvas()[i]->getData() << endl;
			cout << c.getProvas()[i]->getInicio() << endl;
			if (c.getProvas()[i]->getGenero())
				cout << "M" << endl;
			else cout << "F" << endl;
			cout << endl;
		}
		cout << endl;

	for(unsigned int i = 0; i < c.getProvas().size();i++)
	{
		cout << c.getProvas()[i]->getModalidade()->getNome() << endl;
		for(unsigned int j = 0; j < c.getProvas()[i]->getAtletas().size(); j++)
		{
			cout << c.getProvas()[i]->getAtletas()[j]->getNome() << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "Atletas.txt\n";
		for(unsigned int i = 0; i < c.getEquipas().size();i++)
		{
			cout << c.getEquipas()[i]->getNome() << endl;
			Equipa * eq = c.getEquipas()[i];
			cout << endl;
			for(unsigned int j = 0; j < eq->getAtletas().size(); j++)
				{
				Atleta * at = eq->getAtletas()[j];
				cout << at->getNome() << endl;

				for(unsigned int k = 0; k < at->getProvas().size(); k++)
				{
					cout << at->getProvas()[k]->getModalidade()->getNome() << endl;
				}
				cout << endl;
				}
			cout << endl;
		}


	cout << "Equipas.txt\n";
		for(unsigned int i = 0; i < c.getEquipas().size();i++)
		{
			cout << c.getEquipas()[i]->getNome() << endl;
			Equipa * eq = c.getEquipas()[i];
			for(unsigned int j = 0; j < eq->getAtletas().size(); j++)
				{
				cout << eq->getAtletas()[j]->getNome() << " ";
				cout << eq->getAtletas()[j]->getGenero() << endl;
				}
			cout << endl;
		}

*/

	//cout << "Provas.txt\n";

	//Campeonato c = load();
	/*cout << endl << "Vetor de provas de campeonato\n" << endl;
	for(unsigned int i = 0; i < c.getProvas().size();i++)
	{
		cout << c.getProvas()[i]->getModalidade()->getNome() << endl;
		cout << c.getProvas()[i]->getData() << endl;
		cout << c.getProvas()[i]->getInicio() << endl;
		if (c.getProvas()[i]->getGenero())
			cout << "M" << endl;
		else cout << "F" << endl;
		cout << endl;
	}

	cout << endl;
	cout << endl << "Vetor de atletas para cada prova do campeonato\n" << endl;
	for(unsigned int i = 0; i < c.getProvas().size();i++)
	{
		cout << c.getProvas()[i]->getModalidade()->getNome() << endl;
		for(unsigned int j = 0; j < c.getProvas()[i]->getAtletas().size(); j++)
		{
			cout << c.getProvas()[i]->getAtletas()[j]->getNome() << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "Vetor de provas de cada atleta do campeonato\n" << endl;
	for (unsigned int i = 0; i < c.getEquipas().size(); i++)
	{
		cout << c.getEquipas()[i]->getNome() << endl;
		for (unsigned int j = 0; j < c.getEquipas()[i]->getAtletas().size(); j++)
		{
			cout << c.getEquipas()[i]->getAtletas()[j]->getNome() << endl;
			for(unsigned int k = 0; k < c.getEquipas()[i]->getAtletas()[j]->getProvas().size(); k++)
			{
				cout << c.getEquipas()[i]->getAtletas()[j]->getProvas()[k]->getModalidade()->getNome() << endl;
			}
			cout << endl;
		}
		cout << endl;
	}

*/
/*
	cout << endl << "Vetor de desportos para cada equipa do campeonato\n" << endl;
	for(unsigned int i = 0; i < c.getEquipas().size();i++)
	{
		cout << c.getEquipas()[i]->getNome() << endl;
		Equipa * eq = c.getEquipas()[i];

		for(unsigned int j = 0; j < eq->getDesportos().size(); j++)
		{
			cout << eq->getDesportos()[j]->getNome() << endl;
		}
		cout << endl;
	}
*/
	/*cout << endl << "Vetor de modalidades de equipas\n" << endl;
		for(unsigned int i = 0; i < c.getEquipas().size();i++)
		{
			cout << "eq: " << c.getEquipas()[i]->getNome() << endl;
			Equipa * eq = c.getEquipas()[i];

			for(unsigned int j = 0; j < eq->getAtletas().size(); j++)
			{
				cout << " at: " << eq->getAtletas()[j]->getNome() << endl;
				//cout << eq->getAtletas()[j]->getModalidades().size() << endl;
				for(unsigned int k = 0; k < eq->getAtletas()[j]->getModalidades().size(); k++)
				{
					cout << "mod: " << eq->getAtletas()[j]->getModalidades()[k]->getNome() << endl;
				}
				cout << endl;
			}
			cout << endl;

		}
*/

	//menu();

/*
	for(unsigned int i = 0; i < c.getDesportos().size(); i++)
	{
		cout << c.getDesportos()[i]->getNome() << endl;

		for(unsigned int j = 0; j < c.getDesportos()[i]->getModalidades().size(); j++)
			cout << "<" << c.getDesportos()[i]->getModalidades()[j]->getNome() << ">" << endl;
		cout << endl;
	}
*/

	//Campeonato c = load();
/*
	Equipa e("Finlandia");
	Atleta * gui = new Atleta("Teemu Mantysaari", &e, true);
	Atleta voc("Jaari Maenpaa", &e, true);
	c.adicionaEquipa(e);

	c.getEquipas()[c.getEquipas().size()-1]->adicionaAtleta(gui);
	c.getEquipas()[c.getEquipas().size()-1]->adicionaAtleta(&voc);

	c.updateEquipas("Equipas.txt");

	Desporto d("Artes Marciais", "Pontos", true);
	c.adicionaDesporto(d);
	Desporto h("Kung Fu", "Pontos", true);
	c.adicionaDesporto(h);
	Modalidade m("Anything Goes Martial Arts", 1, 30, &d);
	c.getDesportos()[c.getDesportos().size()-1]->adicionaModalidade(&m);

	c.updateModalidades("Modalidades.txt");
	c.updateDesportos("Desportos.txt");
	*/

	//menu();
/*
	Campeonato c = load();
	Equipa e("Finlandia");
	Atleta * gui = new Atleta("Teemu Mantysaari", &e, true);
	Atleta voc("Jaari Maenpaa", &e, true);

	Data dat(2015,12,15);
	Hora h(13,0);
	Desporto d("Artes Marciais", "Pontos", true);
	Modalidade m("Anything Goes Martial Arts", 1, 30, &d);
	Prova p(&m, dat, h, false);

	c.adicionaDesporto(d);
	c.getDesportos()[c.getDesportos().size()-1]->adicionaModalidade(&m);
	c.adicionaProva(p);
	c.getProvas()[c.getProvas().size()-1]->adicionaAtleta(gui);
	c.updateDesportos("Desportos.txt");
	c.updateModalidades("Modalidades.txt");
	c.updateProvas("Provas.txt");
*/
	//Campeonato c = load();
/*	c.apagaModalidade("Finais");

	c.updateModalidades("Modalidades.txt");
	c.updateProvas("Provas.txt");
	*/

/*
	cout << endl << "Vetor de provas de campeonato\n" << endl;
		for(unsigned int i = 0; i < c.getProvas().size();i++)
		{
			cout << *c.getProvas()[i] << endl;
			if (c.getProvas()[i]->getGenero())
				cout << "M" << endl;
			else cout << "F" << endl;
			cout << endl;
		}
		*/
/*

				for(unsigned int i = 0; i < c.getDesportos().size(); i++)
					{
						cout << c.getDesportos()[i]->getNome() << endl;

						for(unsigned int j = 0; j < c.getDesportos()[i]->getModalidades().size(); j++)
							cout << "<" << c.getDesportos()[i]->getModalidades()[j]->getNome() << ">" << endl;
						cout << endl;
					}


				for(unsigned int i = 0; i < c.getEquipas().size(); i++)
					{
						cout << "Eq: " << c.getEquipas()[i]->getNome() << endl;

						for(unsigned int j = 0; j < c.getEquipas()[i]->getAtletas().size(); j++)
							{
							cout << "At: " << c.getEquipas()[i]->getAtletas()[j]->getNome() << endl;
							for(unsigned int k = 0; k < c.getEquipas()[i]->getAtletas()[j]->getModalidades().size(); k++)
							{
								cout << "Desp: "<< c.getEquipas()[i]->getAtletas()[j]->getModalidades()[k]->getDesporto()->getNome() << endl;
								cout << "Mod: " <<c.getEquipas()[i]->getAtletas()[j]->getModalidades()[k]->getNome() << endl << endl;
							}
							}

						cout << endl;
					}

 */
	try{
		menu();
	} catch(...)
	{
		cout << "Um erro inesperado ocorreu, o programa irá agora terminar.\n\nGAME OVER";
		_getch();
	}

	cout << "Press any key to continue...";
	_getch();
	return 0;
}

