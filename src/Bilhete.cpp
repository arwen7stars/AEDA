/*
 * Bilhete.cpp
 *
 *  Created on: 20/12/2015
 *      Author: Filipe
 */

#include "Bilhete.h"
#include "Lists.h"

Bilhete::Bilhete(string endereco, string nome, string morada){
	this->endereco = endereco;
	this->nome = nome;
	this->morada = morada;
}

bool Bilhete::adicionaProva(Prova* p){
	for (int i = 0; i < provasCompradas.size();i++)
		if (provasCompradas[i] == p)
			return false;

	provasCompradas.push_back(p);
	return true;
}


void Bilhete::adicionaProva(vector<Prova *> provas){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Provas:", provas);
		if (ch == -1)
			exit = true;
		else
			adicionaProva(provas[ch]);
	}
}


bool Bilhete::retiraProva(){
	if (provasCompradas.size() == 0)
		return false;
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Provas:", provasCompradas);
		if (ch == -1)
			exit = true;
		else
			provasCompradas.erase (provasCompradas.begin()+ch);
	}
	return true;
}

string Bilhete::getEndereco() const{
	return endereco;
}
string Bilhete::getNome() const{
	return nome;
}
string Bilhete::getMorada() const{
	return morada;
}

ostream & operator<<(ostream & o, const Bilhete & b){
	o << b.getEndereco() << ": " << b.getNome();
	return o;
}
