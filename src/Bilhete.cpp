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
	a_venda = false;
}

bool Bilhete::adicionaProva(Prova* p){
	for (unsigned int i = 0; i < provasCompradas.size();i++)
		if (provasCompradas[i] == p)
			return false;

	provasCompradas.push_back(p);
	return true;
}


void Bilhete::adicionaProva(vector<Prova *> provas){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecione a prova que deseja associar ao bilhete:", provas);
		if (ch == -1)
			exit = true;
		else {
			adicionaProva(provas[ch]);
			return;
		}
	}
}


bool Bilhete::retiraProva(){
	if (provasCompradas.size() == 0)
		return false;
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Escolha a prova a retirar: ", provasCompradas);
		if (ch == -1)
			exit = true;
		else{
			provasCompradas.erase (provasCompradas.begin()+ch);
			return true;
		}
	}
	return true;
}

void Bilhete::setAVenda(bool avenda){
	a_venda = avenda;
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

bool Bilhete::getAVenda() const{
	return a_venda;
}

vector<Prova*> Bilhete::getProvasCompradas() const{
	return provasCompradas;
}

ostream & operator<<(ostream & o, const Bilhete & b){
	o << b.getEndereco() << ": " << b.getNome();
	return o;
}
