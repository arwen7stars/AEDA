#include "Campeonato.h"
#include <iostream>
#include "Lists.h"
#include "Modalidade.h"

using namespace std;

bool ficheiroExiste(const string &ficheiro)
{
	bool existe = false;
	ifstream ficheiro_tab;
	ficheiro_tab.open(ficheiro.c_str());		// abre o ficheiro...
	if (ficheiro_tab.is_open())			// ... e verifica se a abertura do ficheiro foi bem-sucedida
	{
		existe = true;
		ficheiro_tab.close();			// volta a fechar o ficheiro
	}
	return existe;
}

vector<Desporto *> Campeonato::getDesportos() const
{
	return desportos;
}

vector<Prova*> Campeonato::getProvas() const
{
	return provas;
}

Campeonato::Campeonato(string n, Data i, Data f, Hora a, Hora fe){
	nome = n;
	inicio = i;
	fim = f;
	abertura = a;
	fecho = fe;
}

bool Campeonato::adicionaProva(Prova p)
{

	if (p.getData() < inicio || fim < p.getData())
		return false;
	else
	{
		Hora abertura(8,0);
		Hora fecho(20,0);
		Hora fimProva = p.getInicio() + p.getModalidade()->getDuracao();

		if (p.getInicio() < abertura || fecho < fimProva)
			return false;
		else
		{
			if (provas.size() == 0)
			{
				provas.push_back(&p);
				return true;
			}
			else
			{
				for (unsigned int i = 0; i < provas.size(); i++)
				{
					bool simultaneo = provas[i]->Simultaneo(p);

					if (simultaneo)
						return false;
				}
			}
		}
	}

	provas.push_back(&p);
	return true;
}

bool Campeonato::criaDesportosCampeonato(string nome_ficheiro)
{
	int elementos_equipa;
	char barra;
	char crescente;
	bool c;
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
		return false;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string desporto = "";
		string tipo_de_pontuacao = "";

		in >> elementos_equipa;
		in >> barra;

		string extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					desporto = desporto + extraido;
			} while (extraido != "/");

		extraido = "";

		in >> tipo_de_pontuacao;
		in >> barra;
		in >> crescente;


		if (crescente == 'C')
			c = true;
		else if (crescente == 'D')
			c = false;
		else return false;

		if (elementos_equipa == 0)
			return false;
		else {
			Desporto ds (desporto, tipo_de_pontuacao, c, elementos_equipa);
			desportos.push_back(&ds);
		}
	}

	in.close();

	return true;
}


bool Campeonato::criaEquipasCampeonato(string nome_ficheiro)
{
	char barra;
	char genero;
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
	{
		cerr << "O ficheiro Equipas.txt nao existe!";
		return false;
	}

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string equipa = "";
		string atleta = "";

		string extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					equipa = equipa + extraido;
			} while (extraido != "/");

		extraido = "";

		if (!in.eof())
			do
			{
				in >> extraido;
				if (extraido != "/")
					atleta = atleta + extraido;
			} while (extraido != "/");

		in >> genero;

		Equipa * eq = new Equipa(equipa);
		Atleta * at = new Atleta(atleta, *eq);
		int indiceEquipa = -1;

		for (unsigned int i = 0; i < equipas.size(); i++)
		{
			if (equipa == equipas[i]->getNome())
				indiceEquipa = i;

		}

		if (indiceEquipa == -1)
		{
			equipas.push_back(eq);
			(*equipas[equipas.size()-1]).adicionaAtleta(at);
		}
		else
		{
			equipas[indiceEquipa]->adicionaAtleta(at);
		}

	}

	in.close();

	return true;
}



void Campeonato::menuCriacao(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Desportos");
		if(desportos.size() > 0){
			choices.push_back("Equipas");
			choices.push_back("Provas");
			choices.push_back("Salvar");
			choices.push_back("Terminar Planeamento");
		}

		int ch = fazMenu("Campeonato Polidesportivo - Planeamento", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0)
			menuDesportos();
		else if (ch == 1)
			menuEquipas();
		else if (ch == 2)
			menuProvas();
//		else if (ch == 3)
//			Salvar();
//		else
//			TerminarPlaneamento();
	}
}

void Campeonato::menuDesportos(){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Desportos:", desportos, "Novo Desporto");
		if (ch == -1)
			exit = true;
		else if (ch < desportos.size())
			desportos[ch]->menu();
		else{
			try{
				adicionaDesporto();
			}
			catch (DesportoExiste d){
				cout << "Desporto \"" << d.getNome() << "\" ja existe.";
				_getch();
			}

		}

	}
}

void Campeonato::menuEquipas(){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Equipas:", equipas, "Nova Equipa");
		if (ch == -1)
			exit = true;
		else if (ch < equipas.size())
			equipas[ch]->menu(desportos);
		else{
			try{
				adicionaEquipa();
			}
			catch (EquipaExiste eq){
				cout << "Equipa \"" << eq.getNome() << "\" ja existe.";
				_getch();
			}
		}
	}
}

void Campeonato::menuProvas(){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Provas:", provas, "Nova Prova");
		if (ch == -1)
			exit = true;
		else if (ch < provas.size())
			//equipas[ch]->menu();
			provas[ch]->getInicio();
		else
			adicionaProva();
	}
}

void Campeonato::adicionaDesporto(){
	system("cls");

	cout << "Novo Desporto\n";

	string n;
	cout << "Nome: ";
	getline(cin, n);
//	cin.ignore(10000,'\n');

	string p;
	cout << "Tipo de pontuacao: ";
	getline(cin, p);
//	cin.ignore(10000,'\n');

	int ch;
	vector<string> choices;
	choices.push_back("Sim");
	choices.push_back("Nao");
	ch = fazMenu("A pontuacao e crescente? (Valores maiores sao melhores?)", choices);
	if (ch == -1)
		return;

	Desporto *d = new Desporto(n, p, !ch, 1);
	if (search(desportos , *d) != -1)
		throw DesportoExiste(n);
	while(true){
		try{
			d->adicionaModalidade();
			break;
		}
		catch (Desporto::ModalidadeExiste m){
			cout << "A modalidade " << m.getNome() << " ja existe.\n";
		}
	}
	desportos.push_back(d);
}

void Campeonato::adicionaEquipa(){
	system("cls");

	cout << "Nova Equipa\n";

	string n;
	cout << "Nome: ";
	getline(cin, n);

	Equipa *eq = new Equipa(n);
	if (search(equipas , *eq) != -1)
		throw EquipaExiste(n);
	equipas.push_back(eq);
}

void Campeonato::adicionaProva(){
	system("cls");
	int ch, ch2;
	while(true){
		ch = fazMenu("Desportos:", desportos);
		if (ch == -1)
			return;
		else{
			ch2 = fazMenu("Modalidades:", desportos[ch]->getModalidades());
			if (ch2 != -1)
				break;
		}
	}

	Modalidade* mod = desportos[ch]->getModalidades()[ch2];

	int d, m, a, h, min;

	cout << "Ano: ";
	cin >> a;
	cin.ignore(10000,'\n');


	cout << "Mes: ";
	cin >> m;
	cin.ignore(10000,'\n');

	cout << "Dia: ";
	cin >> d;
	cin.ignore(10000,'\n');

	Data data;
	while (true){
		try{
			data = Data(a,m,d);
			if (data < inicio || fim < data)
				throw Data::DataInvalida(a,m,d);
			break;
		}
		catch (Data::DataInvalida D){
			cout << "A data " << D.getDia() << "/" << D.getMes() << "/" << D.getAno() << " nao e valida.\n";
			cout << "Datas validas sao desde " << inicio << " ate " << fim << ".\n";
			_getch();
		}
	}



	cout << "Horas de Inicio: ";
	cin >> a;
	cin.ignore(10000,'\n');

	cout << "Minutos: ";
	cin >> a;
	cin.ignore(10000,'\n');

	Hora hora;
	while (true){
		try{
			hora = Hora(h,min);
			if (hora < abertura || fecho < hora+mod->getDuracao())
				throw Hora::HoraInvalida(h,min);
			break;
		}
		catch (Hora::HoraInvalida H){
			cout << "A hora " << H.getHoras() << ":" << H.getMinutos() << "nao e valida.\n";
			cout << "Datas validas sao desde " << abertura << " ate " << fecho << ".\n";
			_getch();
		}
	}


	Prova p(mod, data, hora);
	for (unsigned int i = 0; i < provas.size(); i++){
		if (provas[i]->Simultaneo(p)){
			cout << "Ja existem provas do mesmo tipo de desporto para o horario marcado.\n";
			_getch();
		}

	}
	provas.push_back(&p);

}

void atribuiPontuacao(Prova pro, vector< float> pontos){
	int primeiro = -1;
	int segundo = -1;

	if (pontos.size() < 3) {
		cout <<"-2";
		if (pro.getModalidade()->getDesporto()->isCrescente())
			if (pontos[0] > pontos[1])
				primeiro = 0;
			else
				primeiro = 1;

		else {
			if (pontos[0] > pontos[1])
				primeiro = 1;
			else
				primeiro = 0;
		}

		// nao e preciso devolver nada
		//	vector<Atleta> rankingProva;
		//
		//	rankingProva.push_back(pro.getAtletas()[primeiro]);
		//	rankingProva.push_back(pro.getAtletas()[segundo]);
		//	rankingProva.push_back(pro.getAtletas()[terceiro]);

		pro.getAtletas()[primeiro]->adicionaPontuacao(3);
	}
	else {
		cout << "+2";
		int terceiro = -1;

		int menor = pontos[0];
		int segundoMenor = pontos[1];
		int terceiroMenor = pontos[2];

		int maior = pontos[0];
		int segundoMaior = pontos[1];
		int terceiroMaior = pontos[2];

		if (pro.getModalidade()->getDesporto()->isCrescente()) {
			for (unsigned int i = 0; i < pontos.size(); i++)
				if (pontos[i] > maior) {
					terceiroMaior = segundoMaior;
					segundoMaior = maior;
					maior = pontos[i];
					terceiro = segundo;
					segundo = primeiro;
					primeiro = i;
				} else if (pontos[i] > segundoMaior) {
					terceiroMaior = segundoMaior;
					segundoMaior = pontos[i];
					terceiro = segundo;
					segundo = i;
				}
		} else
			for (unsigned int i = 0; i < pontos.size(); i++)
				if (pontos[i] < menor) {
					terceiroMenor = segundoMenor;
					segundoMenor = menor;
					menor = pontos[i];
					terceiro = segundo;
					segundo = primeiro;
					primeiro = i;
				} else if (pontos[i] < segundoMenor) {
					terceiroMenor = segundoMenor;
					segundoMenor = pontos[i];
					terceiro = segundo;
					segundo = i;
				}

		// nao e preciso devolver nada
		//	vector<Atleta> rankingProva;
		//
		//	rankingProva.push_back(pro.getAtletas()[primeiro]);
		//	rankingProva.push_back(pro.getAtletas()[segundo]);
		//	rankingProva.push_back(pro.getAtletas()[terceiro]);

		pro.getAtletas()[primeiro]->adicionaPontuacao(3);
		pro.getAtletas()[segundo]->adicionaPontuacao(2);
		pro.getAtletas()[terceiro]->adicionaPontuacao(1);

	}
}
