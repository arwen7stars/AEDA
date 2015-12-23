/*
 * Modalidade.cpp
 *
 *  Created on: 03/11/2015
 *      Author: Filipe
 */

#include "Data.h"
#include "Lists.h"
#include "Modalidade.h"
#include <string>
#include <vector>

using namespace std;

/*
------------------------------------------------------------------------------
								Class Modalidade
------------------------------------------------------------------------------
 */

Modalidade::Modalidade(){
	desporto = NULL;
}

Modalidade::Modalidade(string n, int h, int m, Desporto *d){
	nome = n;
	duracao = Hora(h, m);
	desporto = d;
}

string Modalidade::getNome() const{
	return nome;
}

Hora Modalidade::getDuracao() const{
	return duracao;
}

Desporto* Modalidade::getDesporto() const{
	return desporto;
}

bool Modalidade::operator== (const Modalidade & c) const{
	if (c.nome == nome)
		return true;
	else
		return false;
}

void Modalidade::menu(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Mudar Nome");

		cout << "Nome: " << nome << endl;
		cout << "Duracao: " << duracao << endl;
		int ch = fazMenu("Opcoes: ", choices);
		if (ch == -1)
			exit = true;
		else{
			system("cls");
			cout << "Novo nome: ";
			getline(cin, nome);
		}

	}
}

ostream & operator<<(ostream & o, const Modalidade & d){
	o << d.getNome();
	return o;
}







