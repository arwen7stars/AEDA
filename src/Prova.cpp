#include "Prova.h"
#include "Lists.h"

Prova::Prova(Modalidade* m, Data d, Hora i, char g)
{
	modalidade = m;
	data = d;
	inicio = i;
	fim = i + m->getDuracao();
	if (g == 'M')
		genero = true;
	else genero = false;
}

Hora Prova::getInicio() const
{
	return inicio;
}

Hora Prova::getFim() const
{
	return fim;
}

Data Prova::getData() const
{
	return data;
}

Modalidade* Prova::getModalidade() const{
	return modalidade;
}

vector<Atleta*> Prova::getAtletas() const{
	return atletas;
}

bool  Prova::getGenero() const{
	return genero;
}

bool Prova::Simultaneo(Prova p)
{
	if (p.getData() < data || data < p.getData())
		return false;
	else
	{
		if (p.getInicio() < inicio)
			if (p.getFim() < inicio)
				return false;
		if (fim < p.getFim())
			if (fim < p.getInicio())
				return false;

	}
	Desporto * d1 = modalidade->getDesporto();
	Desporto * d2 = p.modalidade->getDesporto();

	if (*d1 == *d2)
		return true;
	else return false;

}

void Prova::adicionaAtleta(Atleta * a){
	int indice = -1;

	for (unsigned int i = 0; i < atletas.size(); i++)
		if (a->getNome() == atletas[i]->getNome())
			indice = i;
	if (indice == -1)
		atletas.push_back(a);
}

ostream & operator<<(ostream & o, const Prova & p){
	o << p.data << " " << p.inicio << "-" << p.fim << "  "<< p.modalidade->getNome();
	return o;
}


bool Prova::operator < (const Prova &p2) const{
	if (getData()< p2.getData())
		return true;
	return false;
}

void Prova::adicionarAtleta(vector<Equipa*> TeamList, vector<Desporto*> DespList){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecionar Equipa:", TeamList);
		if (ch == -1)
			exit = true;
		else{
			if (search(TeamList[ch]->getDesportos(), *modalidade->getDesporto()) == -1){
				cout << "A equipa " << TeamList[ch]->getNome() << " nao esta inscrita no desporto " << modalidade->getDesporto()->getNome() << ".\n";
				_getch();
			}
			else{
				bool exit2 = false;
				while (!exit2){
					system("cls");
					int ch2 = fazMenu("Selecionar Atleta:", TeamList[ch]->getAtletas());
					if (ch == -1)
						exit2 = true;
					else{
						if (search(atletas, *TeamList[ch]->getAtletas()[ch2]) == -1){
							atletas.push_back(TeamList[ch]->getAtletas()[ch2]);
							TeamList[ch]->getAtletas()[ch2]->adicionaProva(this);
						}
						else{
							cout << "O atleta " << TeamList[ch]->getAtletas()[ch2]->getNome() << "ja esta inscrito.\n";
							_getch();
						}

					}
				}
			}
			exit = true;
		}
	}
}

void Prova::retirarAtleta(){
	system("cls");
	if (atletas.size() == 0){
		cout << "Nao existem atletas inscritos.";
		_getch();
		return;
	}
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Selecionar Atletas:", atletas);
		if (ch == -1)
			exit = true;
		else{
			for (int i = 0; i < atletas[ch]->getProvas().size();i++){
				if (atletas[ch]->getProvas()[i]==this){
					atletas[ch]->getProvas().erase(atletas[ch]->getProvas().begin() + i);
					break;
				}
			}
//			int i = search(atletas[ch]->getProvas(), *this);
//			atletas[ch]->getProvas().erase(atletas[ch]->getProvas().begin() + i);
			atletas.erase(atletas.begin()+ch);
			exit = true;
		}
	}
}

void Prova::menu(vector<Equipa*> TeamList, vector<Desporto*> DespList){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Alterar Atletas");
		choices.push_back("Retirar Atletas");

		cout << *this;
		cout << endl;
		int ch = fazMenu("Opcoes", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0)
			adicionarAtleta(TeamList, DespList);
		else
			retirarAtleta();
	}
}
/*
------------------------------------------------------------------------------
						    Prova Terminada
------------------------------------------------------------------------------
 */

ProvaTerminada::ProvaTerminada(Modalidade* m, Data d, Hora i, char g):Prova(m,d,i,g){}

Atleta* ProvaTerminada::getPrimeiro() const{
	return atletas[0];
}

Atleta* ProvaTerminada::getSegundo() const{
	return atletas[1];
}

Atleta*ProvaTerminada:: getTerceiro() const{
	return atletas[2];
}


