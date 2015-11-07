#include "Campeonato.h"
#include <iostream>
#include "Lists.h"
#include "Modalidade.h"
#include "insertionSort.h"

using namespace std;

Campeonato::Campeonato(string n, Data i, Data f, Hora a, Hora fe){
	nome = n;
	inicio = i;
	fim = f;
	abertura = a;
	fecho = fe;
	criado = false;
}

string Campeonato::getNome() const
{
	return nome;
}

Data Campeonato::getInicio() const
{
	return inicio;
}
Data Campeonato::getFim() const
{
	return fim;
}

Hora Campeonato::getAbertura() const
{
	return abertura;
}

Hora Campeonato::getFecho() const
{
	return fecho;
}

vector<Desporto *> Campeonato::getDesportos() const
{
	return desportos;
}

vector<Prova*> Campeonato::getProvas() const
{
	return provas;
}

vector<Equipa*> Campeonato::getEquipas() const
{
	return equipas;
}

bool Campeonato::adicionaProva(Prova &p)
{

	if (p.getData() < inicio || fim < p.getData())
		return false;
	else
	{
		Hora fimProva = p.getInicio() + p.getModalidade()->getDuracao();

		if (p.getInicio() < abertura || fecho < fimProva)
		{
			return false;
		}
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

bool Campeonato::loadDesportos(string nome_ficheiro)
{
	//int elementos_equipa;
	string desporto;
	string tipo_de_pontuacao;
	char barra;
	char crescente;
	bool c;
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
		return false;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{

		//in >> elementos_equipa;
		//in >> barra;

		in >> desporto;

		in >> barra;
		in >> tipo_de_pontuacao;
		in >> barra;
		in >> crescente;

		if (crescente == 'C')
			c = true;
		else if (crescente == 'D')
			c = false;
		else return false;

		Desporto * ds = new Desporto(desporto, tipo_de_pontuacao, c);

		if (!in.eof())
			desportos.push_back(ds);
	}

	in.close();

	return true;
}


bool Campeonato::loadEquipas(string nome_ficheiro)
{
	ifstream in;

	if (!ficheiroExiste(nome_ficheiro))
	{
		cerr << "O ficheiro Equipas.txt nao existe!";
		return false;
	}

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string equipa;
		string atleta;
		char genero;
		char barra;

		in >> equipa;
		in >> barra;
		in >> atleta;
		in >> barra;
		in >> genero;

		Equipa * eq = new Equipa(equipa);
		Atleta * at = new Atleta(atleta, eq, genero);
		int indiceEquipa = -1;

		for (unsigned int i = 0; i < equipas.size(); i++)
		{
			if (equipa == equipas[i]->getNome())
				indiceEquipa = i;
		}

		if (!in.eof())
		{	if (indiceEquipa == -1)
		{
			equipas.push_back(eq);
			(*equipas[equipas.size()-1]).adicionaAtleta(at);
		}
		else
		{
			equipas[indiceEquipa]->adicionaAtleta(at);
		}
		}
	}

	in.close();
	return true;
}

bool Campeonato::loadModalidades(string nome_ficheiro)
{
	ifstream in_mod;

	if(!ficheiroExiste(nome_ficheiro))
		return false;

	in_mod.open(nome_ficheiro.c_str());

	while (!in_mod.eof())
	{
		char barra;
		string desporto;
		string modalidade;
		int horas;
		int minutos;
		int indice = -1;

		in_mod >> desporto;
		in_mod >> barra;

		for (unsigned int i = 0; i < desportos.size(); i++)
			if (desportos[i]->getNome() == desporto)
				indice = i;

		if (indice == -1)
			{
			cerr << "Desporto inexistente. Nao e possivel criar modalidade!\n";
			return false;
			}

		in_mod >> modalidade;
		in_mod >> barra;

		in_mod >> horas;
		in_mod >> minutos;

		Modalidade * m = new Modalidade(modalidade, horas, minutos, desportos[indice]);
		desportos[indice]->adicionaModalidade(m);

	}
	in_mod.close();
	return true;
}

bool Campeonato::loadProvas(string nome_ficheiro)
{
	ifstream in_pro;
	unsigned int k = 0;
	string extraido = " ";

	if(!ficheiroExiste(nome_ficheiro))
		return false;

	in_pro.open(nome_ficheiro.c_str());

	while(!in_pro.eof())
	{
		string mod, at;
		int dia, mes, ano, horas, minutos;
		char genero, barra;

		int i_desporto = -1;
		int i_modalidade = -1;

		if (k == 0)
			{
			in_pro >> mod;
			}
		else
			{
			mod = extraido;
			}

		in_pro >> barra;
		k++;


		for (unsigned int i = 0; i < desportos.size(); i++)
		{
			for(unsigned int j = 0; j < desportos[i]->getModalidades().size(); j++)
			{
				if (mod == desportos[i]->getModalidades()[j]->getNome())
				{
					i_desporto = i;
					i_modalidade = j;
				}
			}
		}

		if (i_modalidade == -1)
		{
			cout << "Modalidade inexistente " << mod << endl;
			cerr << "Modalidade inexistente. Nao e possivel criar prova!\n";
			return false;
		}

		in_pro >> dia >> mes >> ano;
		in_pro >> barra;
		in_pro >> horas >> minutos;
		in_pro >> barra;
		in_pro >> genero;



		Data d(ano,mes,dia);
		Hora h(horas,minutos);

		Prova * p = new Prova(desportos[i_desporto]->getModalidades()[i_modalidade], d, h, genero);
		bool suc = adicionaProva(*p);

		if (!suc)
			return false;

		extraido = " ";


		if (!in_pro.eof())
			do{
				in_pro >> extraido;
				if (extraido == "-")
				{
					in_pro >> at;

				for(unsigned int i = 0; i < equipas.size();i++)
				{
					for(unsigned int j = 0; j < equipas[i]->getAtletas().size();j++)
					{
						if (at == equipas[i]->getAtletas()[j]->getNome())
						{
							equipas[i]->getAtletas()[j]->adicionaProva(p);
						}
					}
				}
				}
			} while(extraido == "-" && !in_pro.eof());

	}



	return true;
}

void Campeonato::menuApagar(){
	bool exit = false;
	int ch, ch2, ch3;

	system("cls");
	vector<string> choices;
	choices.push_back("Desportos");
	choices.push_back("Modalidades");
	choices.push_back("Equipas");
	choices.push_back("Atletas");
	choices.push_back("Provas");
	while (!exit){
		ch = fazMenu("Campeonato Polidesportivo - Planeamento", choices);
		if (ch == -1)
			exit = true;
		else if(ch == 0){
			bool exit2 = false;
			while (!exit2){
				system("cls");
				ch2 = fazMenu("Desportos:", desportos);
				if (ch2 == -1){
					exit2 = true;
					continue;
				}

				for (int i = 0; i < equipas.size(); i++)
					for (int j = 0; j < equipas[i]->getDesportos().size(); i++)
						if (equipas[i]->getDesportos()[j] == desportos[ch2]){
							system("cls");
							cout << "Ainda existem equipas subscritas a este desporto.";
							_getch();
							return;
						}

				if (desportos[ch2]->getModalidades().size() != 0){
					system("cls");
					cout << "Ainda existem modalidades neste desporto.";
					_getch();
					return;
				}

				desportos.erase(desportos.begin()+ch2);
				return;
			}
		}

		else if(ch == 1){
			bool exit2 = false;
			while (!exit2){
				system("cls");
				ch2 = fazMenu("Desportos:", desportos);
				if (ch2 == -1){
					exit2 = true;
					continue;
				}
				bool exit3 = false;
				while (!exit3){
					system("cls");
					ch3 = fazMenu("Modalidades:", desportos[ch2]->getModalidades());
					if (ch3 == -1){
						exit3 = true;
						continue;
					}
					for (int i = 0; i < provas.size(); i++)
						if (provas[i]->getModalidade() == desportos[ch2]->getModalidades()[ch3]){
							system("cls");
							cout << "Ainda existem provas desta modalidade.";
							_getch();
							return;
						}
					desportos[ch2]->getModalidades().erase(desportos[ch2]->getModalidades().begin()+ch3);
					return;
				}
			}
		}

		else if(ch == 2){
			bool exit2 = false;
			while (!exit2){
				system("cls");
				ch2 = fazMenu("Equipas:", equipas);
				if (ch2 == -1){
					exit2 = true;
					continue;
				}
				if (equipas[ch2]->getAtletas().size() != 0){
					system("cls");
					cout << "Ainda existem atletas desta equipa.";
					_getch();
					return;
				}

				equipas.erase(equipas.begin()+ch2);
				return;
			}
		}

		else if(ch == 3){
			bool exit2 = false;
			while (!exit2){
				system("cls");
				ch2 = fazMenu("Equipas:", equipas);
				if (ch2 == -1){
					exit2 = true;
					continue;
				}
				bool exit3 = false;
				while (!exit3){
					system("cls");
					ch3 = fazMenu("Atletas:", equipas[ch2]->getAtletas());
					if (ch3 == -1){
						exit3 = true;
						continue;
					}
					if (equipas[ch2]->getAtletas()[ch3]->getProvas().size() != 0){
						system("cls");
						cout << "Este atleta ainda esta inscrito em provas.";
						_getch();
						return;
					}
					equipas[ch2]->getAtletas().erase(equipas[ch2]->getAtletas().begin()+ch3);
					return;
				}
			}
		}

		else{
			bool exit2 = false;
			while (!exit2){
				system("cls");
				ch2 = fazMenu("Provas:", provas);
				if (ch2 == -1){
					exit2 = true;
					continue;
				}
				if (provas[ch2]->getAtletas().size() != 0){
					system("cls");
					cout << "Esta prova ainda tem atletas.";
					_getch();
					return;
				}
				provas.erase(provas.begin()+ch2);
				return;
			}
		}

	}
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
			choices.push_back("Apagar");
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
		else if (ch == 3)
			menuApagar();
		//		else if (ch == 4)
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
			provas[ch]->menu(equipas, desportos);
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

	Desporto *d = new Desporto(n, p, !ch);
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
		system("cls");
		ch = fazMenu("Desportos:", desportos);
		if (ch == -1)
			return;
		else{
			system("cls");
			ch2 = fazMenu("Modalidades:", desportos[ch]->getModalidades());
			if (ch2 != -1)
				break;
		}
	}

	Modalidade* mod = desportos[ch]->getModalidades()[ch2];

	int d, m, a, h, min;
	Data data;
	Hora hora;
	//Data---------------------
	while (true){
		system("cls");

		cout << "Ano: ";
		while (!(cin >> a)){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input invalido!\n";
			cout << "Ano: ";
		}
		cin.ignore(1000, '\n');

		cout << "Mes: ";
		while (!(cin >> m)){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input invalido!\n";
			cout << "Mes: ";
		}
		cin.ignore(1000, '\n');

		cout << "Dia: ";
		while (!(cin >> d)){
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input invalido!\n";
			cout << "Dia: ";
		}
		cin.ignore(1000, '\n');

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



	while (true){
		system("cls");
		cout << "Horas de Inicio: ";
		while (!(cin >> h))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input invalido!\n";
			cout << "Horas de Inicio: ";
		}
		cin.ignore(1000, '\n');

		cout << "Minutos: ";
		while (!(cin >> min))
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Input invalido!\n";
			cout << "Minutos: ";
		}
		cin.ignore(1000, '\n');


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

	int g;
	vector<string> choices;
	choices.push_back("Masculino");
	choices.push_back("Feminino");
	g = fazMenu("Genero?", choices);
	if (g == -1)
		return;


	Prova p(mod, data, hora,g);
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


void Campeonato::adicionaEquipa(Equipa &eq){
	equipas.push_back(&eq);
}

void Campeonato::adicionaDesporto(Desporto &d){
	desportos.push_back(&d);
}

void Campeonato::listaDesportos() const{
	vector<string> ndes;

	cout << "Desportos no campeonato: " << endl;

	for (unsigned int i = 0; i < desportos.size(); i++)
		ndes.push_back(desportos[i]->getNome());

	insertionSort<string>(ndes);

	for (unsigned int j = 0; j < desportos.size(); j++)
		cout << desportos[j]->getNome() << endl;
}

void Campeonato::listaProvas() const{
	vector<Prova> vprova;

	cout << "Provas no campeonato: " << endl;

	for (unsigned int j = 0; j < provas.size();j++)
		vprova.push_back(*provas[j]);

	insertionSort<Prova>(vprova);

	for (unsigned int i = 0; i < provas.size(); i++)
		cout << provas[i]->getData() << ": Prova de " << (*provas[i]->getModalidade()->getDesporto())
		<< "("<<(*provas[i]->getModalidade())<<")"
		<< " as " << provas[i]->getInicio() << endl;
}


void Campeonato::listaAtletas() const{
	vector<string> vat;

	cout << "Atletas no campeonato: " << endl;

	for (unsigned int j = 0; j < equipas.size();j++)
		for (unsigned int u = 0; u < equipas[j]->getAtletas().size(); u++)
			vat.push_back(equipas[j]->getAtletas()[u]->getNome());

	insertionSort<string>(vat);

	for (unsigned int i = 0; i < vat.size(); i++)
		cout << vat[i] << endl;
}

void Campeonato::listaAtletasEquipa() const{
	//vector<string> vat;

	cout << "Atletas no campeonato: " << endl;

	for (unsigned int j = 0; j < equipas.size(); j++) {
		vector<string> vat;
		cout << "Equipa " << equipas[j]->getNome() << ":" << endl;
		for (unsigned int u = 0; u < equipas[j]->getAtletas().size(); u++)
			vat.push_back(equipas[j]->getAtletas()[u]->getNome());

		insertionSort<string>(vat);

		for (unsigned int i = 0; i < vat.size(); i++)
			cout << vat[i] << endl;
	}

}

void Campeonato::listaAtletasColocacao() const {
	vector<Atleta> vat;

	cout << "Atletas no campeonato por colocacao: " << endl;

	for (unsigned int j = 0; j < equipas.size(); j++)
		for (unsigned int u = 0; u  < equipas[j]->getAtletas().size(); u++)
			vat.push_back((*equipas[j]->getAtletas()[u]));

	insertionSort<Atleta>(vat);

	for (unsigned int i = 0; i < vat.size(); i++)
		cout << vat[i] << "(" << vat[i].getPontos() << ")"<< endl;
}
