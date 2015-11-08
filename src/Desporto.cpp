/*
 * Desporto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Filipe
 */

#include "Desporto.h"
#include "Modalidade.h"
#include "Data.h"
#include "Lists.h"
#include <string>
#include <vector>
using namespace std;

// faz commit??

/*
------------------------------------------------------------------------------
								 Desportos
------------------------------------------------------------------------------
 */

//Desporto::Desporto(){}
//
//Desporto::Desporto(string n){nome =n;}
//
//Corrida::Corrida(Modalidade n, string pont, bool cresc){
//	modalidades.push_back(&n);
//	pontuacao.nome = pont;
//	pontuacao.crescente = cresc;
//}
//
//string Corrida::getPontuacao() const{
//	return pontuacao.nome;
//}
//
//bool Corrida::isCrescente() const{
//	return pontuacao.crescente;
//}
//
//Natacao::Natacao(Modalidade n, string pont, bool cresc){
//	modalidades.push_back(&n);
//	pontuacao.nome = pont;
//	pontuacao.crescente = cresc;
//}
//
//string Natacao::getPontuacao() const{
//	return pontuacao.nome;
//}
//
//bool Natacao::isCrescente() const{
//	return pontuacao.crescente;
//}
//
//Futebol::Futebol(Modalidade n, string pont, bool cresc){
//	modalidades.push_back(&n);
//	pontuacao.nome = pont;
//	pontuacao.crescente = cresc;
//}
//
//string Futebol::getPontuacao() const{
//	return pontuacao.nome;
//}
//
//bool Futebol::isCrescente() const{
//	return pontuacao.crescente;
//}

Desporto::Desporto(){}

Desporto::Desporto(string n, string pont, bool cresc){
	nome = n;
	pontuacao.nome = pont;
	pontuacao.crescente = cresc;
	//numeroAtletas = nAtletas;
}


string Desporto::getNome() const{
	return nome;
}

string Desporto::getPontuacao() const{
	return pontuacao.nome;
}

vector<Modalidade *> Desporto::getModalidades() const{
	return modalidades;
}
bool Desporto::isCrescente() const{
	return pontuacao.crescente;
}

void Desporto::apagaModalidade(int indice)
{
	modalidades.erase(modalidades.begin()+indice);
}

void Desporto::adicionaModalidade(){
	system("cls");

	cout << "Nova Modalidade de " << nome << "\n";
	string n;
	cout << "Nome: ";
	getline(cin, n);

	int h, m;
	cout << "Duracao(minutos): ";
	while (!(cin >> m))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Input invalido!\n";
		cout << "Duracao(minutos): ";
	}
	cin.ignore(1000, '\n');

	h = m / 60;
	m = m % 60;

	Modalidade * mod = new Modalidade(n,h,m,this);
	if (search(modalidades , *mod) != -1)
		throw ModalidadeExiste(n);
	modalidades.push_back(mod);
}

void Desporto::adicionaModalidade(Modalidade *m){

	int indice = -1;

	for(unsigned int i = 0; i < modalidades.size(); i++)
		if (modalidades[i]->getNome() == m->getNome())
			indice = i;

	if (indice == -1)
		modalidades.push_back(m);
}

bool  Desporto::operator== (const Desporto & c) const{
	if (c.nome == nome)
		return true;
	else
		return false;
}

ostream & operator<<(ostream & o, const Desporto & d){
	o << d.getNome();
	return o;
}


void Desporto::menu(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Mudar Nome");
		choices.push_back("Mudar Tipo de Pontuacao");
		choices.push_back("Mudar Hierarquia da Pontuacao");
		choices.push_back("Alterar Modalidades");

		cout << "Nome: " << nome << endl;
		cout << "Pontuacao: " << pontuacao.nome;
		if (pontuacao.crescente)
			cout << "(Crescente)\n";
		else
			cout << "(Decrescente)\n";
		int ch = fazMenu("Opcoes: ", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0){
			system("cls");
			cout << "Novo nome: ";
			getline(cin, nome);
		}
		else if (ch == 1){
			system("cls");
			cout << "Novo nome de pontuacao: ";
			getline(cin, pontuacao.nome);
		}
		else if (ch == 2){
			system("cls");
			int ch2;
			vector<string> choices2;
			choices2.push_back("Sim");
			choices2.push_back("Nao");
			ch = fazMenu("A pontuacao e crescente? (Valores maiores sao melhores?)", choices2);
			if (ch == -1)
				continue;
			pontuacao.crescente=!ch;
		}
		else{
			menuModalidades();
		}
	}
}

void Desporto::menuModalidades(){
	bool exit = false;
	while (!exit){
		system("cls");
		cout << "Desporto: " << nome << endl << endl;
		int ch = fazMenu("Modalidades:", modalidades, "Nova Modalidade");
		if (ch == -1)
			exit = true;
		else if (ch < modalidades.size())
			modalidades[ch]->menu();
		else{
			try{
				adicionaModalidade();
			}
			catch (ModalidadeExiste mod){
				cout << "Modalidade \"" << mod.getNome() << "\" ja existe.";
				_getch();
			}

		}

	}
}


//
//DesportoEquipa::DesportoEquipa(string n, string pont, bool cresc, int num): Desporto(n,pont,cresc){
//	numeroAtletas = num;
//}
//
//int DesportoEquipa::getNumeroAtletas() const{
//	return numeroAtletas;
//}
//
//
//
//DesportoSolo::DesportoSolo(string n, string pont, bool cresc): Desporto(n,pont,cresc){};

