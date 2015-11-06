/*
 * Equipa.cpp
 *
 *  Created on: 26/10/2015
 *      Author: Filipe
 */
#include "Desporto.h"
#include "Equipa.h"
#include "Lists.h"
/*
------------------------------------------------------------------------------
								Class Equipa
------------------------------------------------------------------------------
 */

Equipa::Equipa(string n){
	nome = n;
}

string Equipa::getNome() const{
	return nome;
}

vector<Atleta *> Equipa::getAtletas() const{
	return atletas;
}

vector<Desporto *> Equipa::getDesportos() const{
	return desportos;
}

bool Equipa::operator== (const Equipa & c) const{
	if (c.nome == nome)
		return true;
	else
		return false;
}

ostream & operator<<(ostream & o, const Equipa & d){
	o << d.getNome();
	return o;
}

bool Equipa::adicionaAtleta(Atleta * a)
{
	for (unsigned int i = 0; i < atletas.size(); i++)
	{
		if (a->getNome() == atletas[i]->getNome())
		{
			cerr << "Atleta com o nome " << a->getNome() << "ja existe na equipa " << nome << endl;
			return false;
		}
	}

	atletas.push_back(a);
	return true;
}

void Equipa::adicionaAtleta(){
	system("cls");
	string n;
	char g;
	cout << "Nome: ";
	getline(cin, n);
	cout << "Duracao(minutos): ";

	while (!(cin >> g) || (g != 'M' && g!= 'F'))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Genero invalido\n";
			cout << "Genero (M ou F): ";
		}

	Atleta * A = new Atleta(n,this,g);
	if (search(atletas , *A) != -1)
		throw AtletaExiste(n);
	atletas.push_back(A);
}


void Equipa::menuAtletas(){
	bool exit = false;
	while (!exit){
		system("cls");
		cout << "Equipa: " << nome << endl << endl;
		int ch = fazMenu("Atletas:", atletas, "Novo Atleta");
		if (ch == -1)
			exit = true;
		else if (ch < atletas.size())
			atletas[ch]->menu();
		else{
			try{
				adicionaAtleta();
			}
			catch (AtletaExiste a){
				cout << "Atleta \"" << a.getNome() << "\" ja existe.";
				_getch();
			}

		}

	}
}

void Equipa::adicionarDesporto(vector<Desporto*> DespList){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecionar Desporto:", DespList);
		if (ch == -1)
			exit = true;
		else{
			if(search(desportos, *DespList[ch]) != -1){
				system("cls");
				cout << DespList[ch]->getNome() << " ja foi subscrito.";
				_getch();
			}
			else
				desportos.push_back(DespList[ch]);
		}
		exit = true;
	}
}

void Equipa::retirarDesporto(){
	system("cls");
	if (desportos.size() == 0){
		cout << "Nao existem desportos subscritos.";
		_getch();
		return;
	}
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecionar Desportos:", desportos);
		if (ch == -1)
			exit = true;
		else{
			desportos.erase(desportos.begin()+ch);
			exit = true;
		}
	}
}

void Equipa::menu(vector<Desporto*> DespList){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Mudar Nome");
		choices.push_back("Alterar Atletas");
		choices.push_back("Inscrever em Desporto");
		choices.push_back("Desinscrever em Desporto");

		cout << "Nome: " << nome << endl;
		cout << "Numero de Membros: " << atletas.size() << endl;
		int ch = fazMenu("Opcoes", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0){
			system("cls");
			cout << "Novo nome: ";
			getline(cin, nome);
		}
		else if (ch == 1)
			menuAtletas();
		else if (ch == 2)
			adicionarDesporto(DespList);
		else
			retirarDesporto();
	}
}

//void Equipa::menuEquipas(){
//	bool exit = false;
//	while (!exit){
//		system("cls");
//		int ch = fazMenu("Equipas:", equipas, "Nova Equipa");
//		if (ch == -1)
//			exit = true;
//		else if (ch < equipas.size())
//			//equipas[ch]->menu();
//			equipas[ch]->getNome();
//		else{
//			try{
//				adicionaEquipa();
//			}
//			catch (EquipaExiste eq){
//				cout << "Equipa \"" << eq.getNome() << "\" ja existe.";
//				_getch();
//			}
//
//		}
//
//	}
//}


/*
------------------------------------------------------------------------------
								Class Atleta
------------------------------------------------------------------------------
 */

Atleta::Atleta(string n, Equipa* e, char g){
	nome = n;
	equipa = e;
	pontos = 0;
	genero = g;
}

string Atleta::getNome() const{
	return nome;
}

Equipa* Atleta::getEquipa() const{
	return equipa;
}

vector<Prova *> Atleta::getProvas() const{
	return provas;
}

char Atleta::getGenero() const
{
	return genero;
}

void Atleta::adicionaPontuacao(int p){
	pontos += p;
}

void Atleta::adicionaProva(Prova * p){
	provas.push_back(p);
}

int Atleta::getPontos() const{
	return pontos;
}

void Atleta::menu(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Mudar Nome");

		cout << "Nome: " << nome << endl;
		cout << "Equipa: " << equipa->getNome() << endl;
		int ch = fazMenu("Opcoes", choices);
		if (ch == -1)
			exit = true;
		else{
			system("cls");
			cout << "Novo nome: ";
			getline(cin, nome);
		}
	}
}

bool Atleta::operator== (const Atleta & c) const{
	if (c.nome == nome)
		return true;
	else
		return false;
}

ostream & operator<<(ostream & o, const Atleta & d){
	o << d.getNome();
	return o;
}

bool Atleta::operator <(const Atleta & a) const{
	if (pontos > a.getPontos())
		return true;
	else return false;
}

void Atleta::setpontos(int p){
	pontos = p;
}
