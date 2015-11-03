/*
 * Desporto.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Filipe
 */

#include "Desporto.h"
#include "Data.h"
#include "Lists.h"
#include <string>
#include <vector>
using namespace std;


/*
------------------------------------------------------------------------------
								 Desportos
------------------------------------------------------------------------------
*/

 Desporto::Desporto(){}

 Desporto::Desporto(string n){nome =n;}

Corrida::Corrida(Modalidade n, string pont, bool cresc){
	modalidades.push_back(&n);
	pontuacao.nome = pont;
	pontuacao.crescente = cresc;
}

string Corrida::getPontuacao() const{
	return pontuacao.nome;
}

bool Corrida::isCrescente() const{
	return pontuacao.crescente;
}

Natacao::Natacao(Modalidade n, string pont, bool cresc){
	modalidades.push_back(&n);
	pontuacao.nome = pont;
	pontuacao.crescente = cresc;
}

string Natacao::getPontuacao() const{
	return pontuacao.nome;
}

bool Natacao::isCrescente() const{
	return pontuacao.crescente;
}

Futebol::Futebol(Modalidade n, string pont, bool cresc){
	modalidades.push_back(&n);
	pontuacao.nome = pont;
	pontuacao.crescente = cresc;
}

string Futebol::getPontuacao() const{
	return pontuacao.nome;
}

bool Futebol::isCrescente() const{
	return pontuacao.crescente;
}

//Desporto::Desporto(){}
//
//Desporto::Desporto(string n, string pont, bool cresc){
//	nome = n;
//	pontuacao.nome = pont;
//	pontuacao.crescente = cresc;
//}
//
//string Desporto::getNome() const{
//	return nome;
//}
//
//string Desporto::getPontuacao() const{
//	return pontuacao.nome;
//}
//
//bool Desporto::isCrescente() const{
//	return pontuacao.crescente;
//}
//
//bool  Desporto::operator== (const Desporto & c) const{
//	if (c.nome == nome)
//		return true;
//	else
//		return false;
//}
//
//void Desporto::adicionaModalidade(){
//	string n;
//	int h, m;
//
//	system("cls");
//
//	cout << "Nome: ";
//	getline(cin, n);
//
//
//	cout << "Duracao(minutos): ";
//	cin >> m;
//	cin.ignore(10000,'\n');
//
//	h = m / 60;
//	m = m % 60;
//
//	Modalidade * mod = new Modalidade(n,h,m,this);
//	if (search(modalidades , *mod) != -1)
//		throw ModalidadeExiste(n);
//	modalidades.push_back(mod);
//}
//
//ostream & operator<<(ostream & o, const Desporto & d){
//	o << d.getNome();
//	return o;
//}
//
//ModalidadeExiste::ModalidadeExiste(){}
//
//ModalidadeExiste::ModalidadeExiste(string n){
//	nome = n;
//}
//
//string ModalidadeExiste::getNome() const{
//	return nome;
//}
//
//
//void Desporto::menuModalidades(){
//	bool exit = false;
//	while (!exit){
//		system("cls");
//		cout << "Desporto: " << nome << endl << endl;
//		int ch = fazMenu("Modalidades:", modalidades, "Nova Modalidade");
//		if (ch == -1)
//			exit = true;
//		else if (ch < modalidades.size())
//			modalidades[ch]->menu();
//		else{
//			try{
//				adicionaModalidade();
//			}
//			catch (ModalidadeExiste mod){
//				cout << "Modalidade \"" << mod.getNome() << "\" ja existe.";
//				_getch();
//			}
//
//		}
//
//	}
//}

/*
------------------------------------------------------------------------------
								Class Modalidade
------------------------------------------------------------------------------
 */

Modalidade::Modalidade(){}

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
	system("cls");
	cout << "Modalidade: " << nome << endl << endl;
	_getch();
}

ostream & operator<<(ostream & o, const Modalidade & d){
	o << d.getNome();
	return o;
}
