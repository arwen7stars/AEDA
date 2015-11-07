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
	{
		throw Data::DataInvalida(p.getData().getAno(), p.getData().getMes(), p.getData().getDia());
	}
	else
	{
		Hora fimProva = p.getInicio() + p.getModalidade()->getDuracao();

		if (p.getInicio() < abertura || fecho < fimProva)
		{
			throw Hora::HoraInvalida(p.getInicio().getHoras(), p.getInicio().getMinutos());
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
						throw Prova::ProvasSimultaneas(p.getModalidade()->getNome(), provas[i]->getModalidade()->getNome());
				}
			}
		}
	}

	provas.push_back(&p);

	return true;
}

void Campeonato::adicionaEquipa(Equipa * eq)
{
	int indice = -1;
	for(unsigned int i = 0; i < equipas.size(); i++)
	{
		if (eq->getNome() == equipas[i]->getNome())
			indice = i;
	}
	if(indice == -1)
		equipas.push_back(eq);

}

void Campeonato::loadDesportos(string nome_ficheiro)
{
	//int elementos_equipa;
	string desporto;
	string tipo_de_pontuacao;
	char barra;
	char crescente;
	bool c;
	ifstream in;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		//in >> elementos_equipa;
		//in >> barra;

		getline(in, desporto);

		in >> tipo_de_pontuacao;
		in >> barra;
		in >> crescente;

		in.ignore(1000, '\n');
		in.ignore(1000, '\n');

		if (crescente == 'C')
			c = true;
		else if (crescente == 'D')
			c = false;
		else throw CaraterInvalido(crescente);

		Desporto * ds = new Desporto(desporto, tipo_de_pontuacao, c);

		if (desporto != "")
			desportos.push_back(ds);
	}

	in.close();
}


void Campeonato::loadEquipas(string nome_ficheiro)
{
	ifstream in;
	unsigned int k = 0;
	string extraido = " ";

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string eq, str,at;
		char genero;
		bool g;

		if (k == 0)
		{
			int c = in.peek();

			if (c == '\n')
				in.ignore(1000,'\n');

			getline(in, eq);
		}
		else
		{
			eq = extraido;

			int c = in.peek();

			if (c == '\n')
				in.ignore(1000,'\n');
			else
			{
				getline(in,str);
				eq = eq + str;
			}
		}
		k++;

		Equipa * equipa = new Equipa(eq);

		if (eq != "")
			adicionaEquipa(equipa);

		extraido = "";

		if (!in.eof())
			do{
				in >> extraido;
				if (extraido == "-")
				{
					int c = in.peek();
					if (c == '\n')
						in.ignore(1000,'\n');

					getline(in, str);
					genero = str[str.size()-1];
					at = str.substr(1,str.size()-3);


					if (genero == 'M')
						g= true;
					else g = false;

					Atleta * atleta = new Atleta(at, equipa, g);

					int indiceEquipa = -1;

					for (unsigned int i = 0; i < equipas.size(); i++)
					{
						if (eq == equipas[i]->getNome())
							indiceEquipa = i;
					}
					if (indiceEquipa == -1 && eq != "")
						throw Equipa::EquipaInexistente(eq);

					if (eq != "")
						equipas[indiceEquipa]->adicionaAtleta(atleta);
				}
					} while(extraido == "-" && !in.eof());
	}

	in.close();
}

void Campeonato::loadModalidades(string nome_ficheiro)
{
	ifstream in;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		string desporto, d;
		string modalidade;
		int horas;
		int minutos;
		int indice = -1;

		getline (in, desporto);

		desporto = tirar_espacos_fim(desporto);

		for (unsigned int i = 0; i < desportos.size(); i++)
			if (comparar_strings(desportos[i]->getNome(), desporto))
				indice = i;

		if (indice == -1 && desporto != "")
			{
			throw Desporto::DesportoInexistente(desporto);
			}

		getline(in, modalidade);
		modalidade = tirar_espacos_fim(modalidade);

		char c = in.peek();

		if (c == '\n')
			in.ignore(1000,'\n');

		in >> horas;
		in >> minutos;

		in.ignore(1000,'\n');
		in.ignore(1000,'\n');

		Modalidade * m = new Modalidade(modalidade, horas, minutos, desportos[indice]);
		if (desporto != "")
			desportos[indice]->adicionaModalidade(m);

	}
	in.close();
}

void Campeonato::loadProvas(string nome_ficheiro)
{
	ifstream in;
	unsigned int k = 0;
	string extraido = " ";

	in.open(nome_ficheiro.c_str());

	while(!in.eof())
	{
		string mod, at, str;
		int dia, mes, ano, horas, minutos;
		char genero, barra;

		int i_desporto = -1;
		int i_modalidade = -1;

		if (k == 0)
			{
			int c = in.peek();

			if (c == '\n')
				in.ignore(1000,'\n');

			getline(in, mod);
			}
		else
			{
			mod = extraido;

			int c = in.peek();

			if (c == '\n')
				in.ignore(1000,'\n');
			else
				{
				getline(in,str);
				mod = mod + str;
				}
			}

		mod = tirar_espacos_fim(mod);

		k++;


		for (unsigned int i = 0; i < desportos.size(); i++)
		{
			for(unsigned int j = 0; j < desportos[i]->getModalidades().size(); j++)
			{
				if (comparar_strings(mod,desportos[i]->getModalidades()[j]->getNome()))
				{
					i_desporto = i;
					i_modalidade = j;
				}
			}
		}

		if (i_modalidade == -1 && mod != "")
		{
			throw Modalidade::ModalidadeInexistente(mod);
		}

		in >> dia >> mes >> ano;
		in >> barra;
		in >> horas >> minutos;
		in >> barra;
		in >> genero;

		Data d(ano,mes,dia);
		Hora h(horas,minutos);

		Prova * p = new Prova(desportos[i_desporto]->getModalidades()[i_modalidade], d, h, genero);

		extraido = " ";

		if (!in.eof())
			do{
				in >> extraido;
				if (extraido == "-")
				{
					int c = in.peek();

					if (c == '\n')
						in.ignore(1000,'\n');

					getline(in, at);
					at = at.substr(1,at.size()-1);

					for(unsigned int i = 0; i < equipas.size();i++)
					{
						for(unsigned int j = 0; j < equipas[i]->getAtletas().size();j++)
						{
							if (comparar_strings(at,equipas[i]->getAtletas()[j]->getNome()) && at != "")
							{
								equipas[i]->getAtletas()[j]->adicionaProva(p);
								p->adicionaAtleta(equipas[i]->getAtletas()[j]);
								equipas[i]->adicionaDesporto(desportos[i_desporto]);
								equipas[i]->getAtletas()[j]->adicionaModalidade(desportos[i_desporto]->getModalidades()[i_modalidade]);
							}

						}
					}
				}
			} while(extraido == "-" && !in.eof());

		adicionaProva(*p);
	}

}

void Campeonato::updateDesportos(string nome_ficheiro)
{
	ofstream out;

	out.open(nome_ficheiro.c_str());

	for(unsigned int i = 0; i < desportos.size(); i++)
	{
		out << desportos[i]->getNome() << endl;
		out << desportos[i]->getPontuacao() << " / ";
		if (desportos[i]->isCrescente())
			out << "C" << endl;
		else out << "D" << endl;
		out << endl;
	}
}

void Campeonato::updateEquipas(string nome_ficheiro)
{
	ofstream out;
	out.open(nome_ficheiro.c_str());

	for(unsigned int i = 0; i < equipas.size();i++)
	{
		out << equipas[i]->getNome() << endl;
		for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
		{
			out << "- " << equipas[i]->getAtletas()[j]->getNome() << " ";
			if (equipas[i]->getAtletas()[j]->getGenero())
				out << "M" << endl;
			else out << "F" << endl;
		}
		out << endl;
	}
}

void Campeonato::updateModalidades(string nome_ficheiro)
{
	ofstream out;
	out.open(nome_ficheiro.c_str());

	if(!ficheiroExiste(nome_ficheiro))
		throw FicheiroInexistente(nome_ficheiro);

	for(unsigned int i = 0; i < desportos.size();i++)
	{
		for(unsigned int j = 0; j < desportos[i]->getModalidades().size(); j++)
		{
			out << desportos[i]->getNome() << endl;
			out << desportos[i]->getModalidades()[j]->getNome() << endl;
			out << desportos[i]->getModalidades()[j]->getDuracao().getHoras() << " ";
			out << desportos[i]->getModalidades()[j]->getDuracao().getMinutos() << endl;
			out << endl;
		}
	}
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
			cout << D.getMessage();
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
			cout << H.getMessage();
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
	int indice = -1;
	for(unsigned int i = 0; i < equipas.size(); i++)
	{
		if (equipas[i]->getNome() == eq.getNome())
			indice = i;
	}

	if (indice == -1)
		equipas.push_back(&eq);
}

void Campeonato::adicionaDesporto(Desporto &d){
	int indice = -1;
	for(unsigned int i = 0; i < desportos.size(); i++)
		if (desportos[i]->getNome() == d.getNome())
			indice = i;

	if (indice == -1)
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

void Campeonato::listaAtletasDesporto() const {
	vector<Atleta> vat;

	for (unsigned int j = 0; j < equipas.size(); j++)
		for (unsigned int u = 0; u < equipas[j]->getAtletas().size(); u++)
			vat.push_back((*equipas[j]->getAtletas()[u]));

	cout << "Atletas no campeonato: " << endl << endl;

	for (unsigned int j = 0; j < desportos.size(); j++) {
		vector<Atleta> vatd;

		for (unsigned int u = 0; u < vat.size(); u++) //percorre os atletas
			for (unsigned int a = 0;
					a < vat[u].getEquipa()->getDesportos().size(); a++) //percorre os seus desportos
				if (desportos[j]->getNome()
						== vat[u].getEquipa()->getDesportos()[a]->getNome()) //desporto = desporto do a atleta
					vatd.push_back(vat[u]);

		if (vatd.size() == 0)
			cout <<endl << "Nao ha atletas  em " << desportos[j]->getNome() <<endl;
		else {
			insertionSort<Atleta>(vatd);
			cout <<endl<< "Atletas em " << desportos[j]->getNome() << ":" << endl << endl;
			for (unsigned int i = 0; i < vatd.size(); i++)
				cout << vatd[i] << endl;
		}
	}
}

void Campeonato::listaEquipasColocacao() const {
	vector<pair<int, string> > peq (equipas.size(), make_pair(0, ""));
	vector<int> peqb (equipas.size());

	for (unsigned int i = 0; i < equipas.size(); i++) {

		peq[i].second = equipas[i]->getNome();
		for (unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++) {

			peq[i].first += equipas[i]->getAtletas()[j]->getPontos();
			peqb[i] += equipas[i]->getAtletas()[j]->getPontos();
		}
	}
	insertionSort<int>(peqb);

	cout << "Ranking de Equipas :" << endl << endl;

	for (unsigned int a = 0; a < peq.size(); a++)

		for (unsigned int b = 0; b < peqb.size(); b++)
			if (peqb[b] == peq[a].first)
				cout<< peq[b].second << endl;

}
