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
	pontos = 0;
}

string Equipa::getNome() const{
	return nome;
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

void Equipa::menuAtletas(){

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

Atleta::Atleta(string n, Equipa e){
	nome = n;
	equipa = &e;
	pontos = 0;
}

string Atleta::getNome() const{
	return nome;
}

Equipa* Atleta::getEquipa() const{
	return equipa;
}

void Atleta::adicionaPontuacao(int p){
	pontos += p;
}

int Atleta::getPontos() const{
	return pontos;
}



