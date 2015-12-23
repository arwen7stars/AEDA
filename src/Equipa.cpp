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
	medalhas.ouro = 0;
	medalhas.prata = 0;
	medalhas.bronze = 0;
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
			return false;
		}
	}

	atletas.push_back(a);
	return true;
}

void Equipa::adicionaDesporto(Desporto * d)
{
	int indice = -1;

	for(unsigned int i = 0; i < desportos.size(); i++)
		if (d->getNome() == desportos[i]->getNome())
		{
			indice = i;
		}

	if (indice == -1)
	{
		desportos.push_back(d);
	}
}

void Equipa::apagaModalidade(int i_atleta, int i_modalidade)
{
	atletas[i_atleta]->apagaModalidade(i_modalidade);
}

void Equipa::apagaAtleta(const string nome){
	for(unsigned int i = 0; i < atletas.size(); i++)
	{
		if (atletas[i]->getNome() == nome)
			{
			atletas.erase(atletas.begin()+i);
			i--;
			}
	}
}
void Equipa::apagaProva(int i_atleta, int i_prova){
	atletas[i_atleta]->apagaProva(i_prova);
}

void Equipa::adicionaAtleta(){
	system("cls");
	string n;
	cout << "Nome: ";
	getline(cin, n);

	cout << "Duracao(minutos): ";

	int g;
	vector<string> choices;
	choices.push_back("Masculino");
	choices.push_back("Feminino");
	g = fazMenu("Genero?", choices);
	if (g == -1)
		return;

	Atleta * A = new Atleta(n,this,g);

	if (search(atletas , *A) != -1)
		throw AtletaExiste(n);
	atletas.push_back(A);
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

void Equipa::menuAtletas(){
	bool exit = false;
	while (!exit){
		system("cls");
		cout << "Equipa: " << nome << endl << endl;
		int ch = fazMenu("Atletas:", atletas, "Novo Atleta");
		if (ch == -1)
			exit = true;
		else if ((unsigned)ch < atletas.size())
			atletas[ch]->menu();
		else{
			try{
				adicionaAtleta();
			}
			catch (AtletaExiste &a){
				cout << "Atleta \"" << a.getNome() << "\" ja existe.";
				_getch();
			}

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

void Equipa::setNome(string n) {
	nome = n;
}
void Equipa::setAtletas(vector<Atleta *> a) {
	for (unsigned int i = 0; i < a.size(); i++)
		atletas[i] = a[i];
}
void Equipa::setDesportos(vector<Desporto *> d) {
	for (unsigned int i = 0; i < d.size(); i++)
		desportos[i] = d[i];
}
/*
void Equipa::setMedalhas(){
	for(unsigned int i = 0; i < atletas.size(); i++){
		medalhas.ouro += atletas[i]->getMedalhas().ouro;
		medalhas.prata += atletas[i]->getMedalhas().prata;
		medalhas.bronze += atletas[i]->getMedalhas().bronze;
	}
}
*/
Equipa & Equipa::operator= (const Equipa & e){
	setNome(e.getNome());
	setAtletas(e.getAtletas());
	setDesportos(e.getDesportos());
	return *this;
}

bool Equipa::operator < (Equipa &eq1){
	if(getMedalhas().ouro<eq1.getMedalhas().ouro)
		return true;
	if(getMedalhas().prata<eq1.getMedalhas().prata)
		return true;
	if(getMedalhas().bronze<eq1.getMedalhas().bronze)
		return true;
	return false;
}

/*
------------------------------------------------------------------------------
								Class Atleta
------------------------------------------------------------------------------
 */

Atleta::Atleta(string n, Equipa* e, bool g){
	nome = n;
	equipa = e;
	pontos = 0;
	genero = g;
	medalhas.ouro = 0;
	medalhas.prata = 0;
	medalhas.bronze = 0;
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

vector<Modalidade *> Atleta::getModalidades() const{
	return modalidades;
}

Medalhas Atleta::getMedalhas() const{
	return medalhas;
}

void Atleta::apagaModalidade(int indice)
{
	modalidades.erase(modalidades.begin()+indice);
}

void Atleta::apagaProva(int indice)
{
	provas.erase(provas.begin()+indice);
}

void Atleta::setNome( string n){
	nome = n;
}

void Atleta::setEquipa(Equipa & eq){
	equipa = &eq;
}

void Atleta::setProvas(vector <Prova *> p) {
	for (unsigned int i = 0; i< p.size(); i++)
		provas[i]=p[i];
}

void Atleta::setModalidades(vector <Modalidade *> m) {
	for (unsigned int i = 0; i< m.size(); i++)
			modalidades[i]=m[i];
}

void Atleta::setGenero(bool g){
	genero = g;
}

bool  Atleta::getGenero() const{
	return genero;
}


void Atleta::adicionaPontuacao(int p){
	pontos += p;

	if (p==3){
		equipa->addOuro();
		medalhas.ouro++;
	}
	else if (p == 2){

		medalhas.prata++;
	}
		else {
			medalhas.bronze++;
		}
}

void Atleta::adicionaProva(Prova * p){
	provas.push_back(p);
}

void Atleta::adicionaModalidade(Modalidade * m)
{
	int indice = -1;

	for(unsigned int i = 0; i < modalidades.size(); i++)
		if( m->getNome() == modalidades[i]->getNome())
			indice = i;

	if (indice == -1)
		modalidades.push_back(m);
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
		if (genero)
			cout << "Genero: Feminino\n";
		else
			cout << "Genero: Masculino\n";

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

Atleta & Atleta::operator=(const Atleta & a) {
	setNome(a.nome);
	setEquipa(*a.getEquipa());
	setProvas(a.getProvas());
	setModalidades(a.getModalidades());
	setpontos(a.getPontos());
	setGenero(a.getGenero());
return *this;
}

void Atleta::setpontos(int p){
	pontos = p;
}
