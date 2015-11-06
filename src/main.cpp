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
		cout << "A data ";
		cout << d.getDia() << "/" << d.getMes() << "/" << d.getAno();
		cout << " nao e valida"<< endl;
	}

	Data d1 (ini_ano,ini_mes,ini_dia);
	Data d2 (fim_ano,fim_mes,fim_dia);
	Hora h1 (h_abertura,m_abertura);
	Hora h2 (h_fecho,m_fecho);

	Campeonato c (nome, d1, d2,h1, h2);
	return c;
}

bool loadModalidades(Campeonato &c)
{
	string modalidades = "Modalidades.txt";
	ifstream in_mod;
	vector<Desporto*> d = c.getDesportos();

	if(!ficheiroExiste(modalidades))
		return false;

	in_mod.open(modalidades.c_str());

	while (!in_mod.eof())
	{
		char barra;
		string desp = "";
		string mod = "";
		int horas;
		int minutos;
		int indice = -1;

		string extraido = "";

		if (!in_mod.eof())
			do
			{
				in_mod >> extraido;
				if (extraido != "/")
					desp = desp + extraido;
			} while (extraido != "/");

		for (unsigned int i = 0; i < d.size(); i++)
			if (d[i]->getNome() == desp)
				indice = i;

		if (indice == -1)
			return false;

		extraido = "";

		if (!in_mod.eof())
			do
			{
				in_mod >> extraido;
				if (extraido != "/")
					mod = mod + extraido;
			} while (extraido != "/");

		in_mod >> horas;
		in_mod >> barra;
		in_mod >> minutos;
		if (!in_mod.eof())
		{
			Modalidade * m = new Modalidade(mod, horas, minutos, d[indice]);
			d[indice]->adicionaModalidade(m);
		}
	}
	return true;
}


Campeonato load()
{
	Campeonato c = loadCampeonato();

	bool suc_des;
	string desportos = "Desportos.txt";
	suc_des = c.criaDesportosCampeonato(desportos);

	if(!suc_des)
		cerr << "Erro ao abrir Desportos.txt";			// excecao ficheiro inexistente

	bool suc_eq;
	string equipas = "Atletas.txt";
	suc_eq = c.criaEquipasCampeonato(equipas);

	if(!suc_eq)
		cerr << "Erro ao abrir Atletas.txt";

	bool suc_mod;
	suc_mod = loadModalidades(c);

	if(suc_mod)
		cerr << "Erro ao abrir Modalidades.txt";

	return c;

}


void menuNovoCampeonato(){}

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
		else if (ch == 0)
			menuNovoCampeonato();
		else{
			Campeonato C = loadCampeonato();
//			if(C.isCriado())
//				cout << "Ola";
//			else
				C.menuCriacao();
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


//	Data d1 (2015,11,1);
//	Data d2 (2015,11,10);
//	Hora h1(8,00);
//	Hora h2(20,0);
//	Campeonato c ("Campeonato A", d1, d2, h1,h2);
//
//	if (c.criaDesportosCampeonato("Desportos.txt"))
//		cout<< "correu bem\n";
//	else cout << "correu mal\n";
//	cout << endl;
//
//	for(unsigned int i = 0; i < c.getDesportos().size();i++)
//	{
//		cout << c.getDesportos()[i]->getNome() << endl;
//	}
//	cout << endl;
//
//	if(c.criaEquipasCampeonato("Atletas.txt"))
//		cout<< "correu bem\n";
//	else cout << "correu mal\n";
//	cout << endl;
//
//	for(unsigned int i = 0; i < c.getDesportos().size();i++)
//	{
//		cout << c.getEquipas()[i]->getNome() << endl;
//		Equipa * eq = c.getEquipas()[i];
//		for(unsigned int j = 0; j < eq->getAtletas().size(); j++)
//			cout << eq->getAtletas()[j]->getNome() << endl;
//		cout << endl;
//	}
//
//	Campeonato c1 = loadCampeonato();
//	cout << "Nome campeonato: " << c1.getNome() << endl;
//	cout << c1.getInicio() << endl;
//	cout << c1.getFim() << endl;
//	cout << c1.getAbertura() << endl;
//	cout << c1.getFecho() << endl;

	menu();


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

	cout << "Press any key to continue...";
	_getch();
	return 0;
}

