#include "Campeonato.h"
#include <iostream>
#include "Lists.h"
#include "Modalidade.h"
#include "insertionSort.h"
#include <algorithm>
#include <climits>

using namespace std;

Campeonato::Campeonato(string n, Data i, Data f, Hora a, Hora fe) : datas(Prova()){
	nome = n;
	inicio = i;
	fim = f;
	abertura = a;
	fecho = fe;
	criado = false;
}

Campeonato::Campeonato() : datas(Prova())
{
	nome = "";
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

bool Campeonato::adicionaDesporto(Desporto &d){
	int indice = -1;
	for(unsigned int i = 0; i < desportos.size(); i++)
		if (desportos[i]->getNome() == d.getNome())
			{
			indice = i;
			return false;
			}

	if (indice == -1)
		desportos.push_back(&d);
	return true;
}

bool Campeonato::adicionaEquipa(Equipa * eq)
{
	int indice = -1;
	for(unsigned int i = 0; i < equipas.size(); i++)
	{
		if (comparar_strings(eq->getNome(), equipas[i]->getNome()))
			{
			indice = i;
			return false;
			}
	}

	if(indice == -1)
		equipas.push_back(eq);
	return true;

}

void Campeonato::adicionaProva(Prova &p)
{

	bool tamanho_zero = false;
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
				tamanho_zero = true;
				provas.push_back(&p);
			}
			else
			{
				for (unsigned int i = 0; i < provas.size(); i++)
				{
					bool simultaneo = provas[i]->Simultaneo(p);

					if (simultaneo && comparar_strings(p.getModalidade()->getNome(),provas[i]->getModalidade()->getNome()))
						throw Prova::ProvasSimultaneas(p.getModalidade()->getNome(), provas[i]->getModalidade()->getNome());
				}
			}
		}
	}

	if (!tamanho_zero)
		provas.push_back(&p);

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

		if (barra != '/' && !in.eof())
			throw LoadFail(nome_ficheiro);

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
		string eq, str, at;
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
		int c = in.peek();

		if (!in.eof() && c != '\n')
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
					else if (genero == 'F')
						g = false;
					else throw CaraterInvalido(genero);

					Atleta * atleta = new Atleta(at, equipa, g);

					int indiceEquipa = -1;

					for (unsigned int i = 0; i < equipas.size(); i++)
					{
						if (comparar_strings(eq, equipas[i]->getNome()))
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

		Data * d = new Data(ano,mes,dia);
		Hora * h = new Hora(horas,minutos);

		Prova * p = new Prova(desportos[i_desporto]->getModalidades()[i_modalidade], *d, *h, genero);

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
	criaCalendario();
}

void Campeonato::updateDesportos(string nome_ficheiro)
{
	ofstream out;

	out.open(nome_ficheiro.c_str());

	if(!ficheiroExiste(nome_ficheiro))
		throw FicheiroInexistente(nome_ficheiro);

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

	if(!ficheiroExiste(nome_ficheiro))
		throw FicheiroInexistente(nome_ficheiro);

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

void Campeonato::updateProvas(string nome_ficheiro)
{
	ofstream out;
	out.open(nome_ficheiro.c_str());

	if(!ficheiroExiste(nome_ficheiro))
		throw FicheiroInexistente(nome_ficheiro);

	for(unsigned int i = 0; i < provas.size(); i++)
	{
		out << provas[i]->getModalidade()->getNome() << endl;
		out << provas[i]->getData().getDia() << " ";
		out << provas[i]->getData().getMes() << " ";
		out << provas[i]->getData().getAno() << " / ";
		out << provas[i]->getInicio().getHoras() << " ";
		out << provas[i]->getInicio().getMinutos() << " / ";
		if (provas[i]->getGenero())
			out << "M" << endl;
		else out << "F" << endl;

		for(unsigned int j = 0; j < provas[i]->getAtletas().size(); j++)
		{
			out << "- " << provas[i]->getAtletas()[j]->getNome() << endl;
		}
		out << endl;
	}
}

void Campeonato::update(){
	string desportos = "Desportos.txt";
	string equipas = "Equipas.txt";
	string modalidades = "Modalidades.txt";
	string provas = "Provas.txt";

	updateDesportos(desportos);
	updateEquipas(equipas);
	updateModalidades(modalidades);
	updateProvas(provas);

}

void Campeonato::apagaModalidade(string n)
{
	for (unsigned int i = 0; i < desportos.size(); i++)
	{
		for(unsigned int j = 0; j < desportos[i]->getModalidades().size();j++)
		{
			if (desportos[i]->getModalidades()[j]->getNome() == n)
			{
				desportos[i]->apagaModalidade(j);
				j--;
			}
		}
	}

	for(unsigned int i = 0; i < equipas.size(); i++)
	{
		for(unsigned int j= 0; j < equipas[i]->getDesportos().size(); j++)
		{
			for(unsigned int k = 0; k < equipas[i]->getDesportos()[j]->getModalidades().size(); k++)
			if (n == equipas[i]->getDesportos()[j]->getModalidades()[k]->getNome())
			{
				equipas[i]->apagaModalidade(j,k);
				k--;
			}
		}

		for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
		{
			for(unsigned int k = 0; k < equipas[i]->getAtletas()[j]->getModalidades().size(); k++)
			{
				if (equipas[i]->getAtletas()[j]->getModalidades()[k]->getNome() == n)
				{
					equipas[i]->apagaModalidade(j,k);
					k--;
				}
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
			choices.push_back("Calendario");
			choices.push_back("Listas");
			choices.push_back("Apagar");
			choices.push_back("Salvar");
			choices.push_back("Terminar Planeamento");

			vector<string> choices2;
			choices2.push_back("Realizar Prova");
			choices2.push_back("Listas");

			if (!criado)
			{
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
					menuCalendario();
				else if (ch == 4)
					menuListas();
				else if (ch == 5)
					menuApagar();
				else if (ch == 6)
					Salvar();
				else
					TerminarPlaneamento();
			}
			else {
				int ch = fazMenu("Campeonato Polidesportivo - Realizacao", choices2);
				if (ch == -1)
					exit = true;
				else if (ch == 0)
				{
					system("cls");
					Prova min = *provas[0];
					int indice = 0;

					for(unsigned int i = 0; i < provas.size(); i++)
					{
						if (*provas[i] < min)
						{
							min = *provas[i];
							indice = i;
						}
					}

					cout << *provas[indice] << endl;

					cout << "Pontuacoes dos atletas.\n" << endl;
					if (provas.size() != 0)
					{
						vector<float> pont;
						for(unsigned int i = 0; i < provas[indice]->getAtletas().size(); i++)
						{
							float num;
							cout << provas[indice]->getAtletas()[i]->getNome() << ": ";
							while (!(cin >> num))
							{
								cin.clear();
								cin.ignore(1000, '\n');
								cout << "Input invalido! O numero deve ser um float\n";
								cout << provas[0]->getAtletas()[i]->getNome() << ": ";
							}
							cin.ignore(1000, '\n');
							pont.push_back(num);
						}
						realizaProva(*provas[indice], pont);

					}
					else {
						cout << "As provas ja foram todas realizadas\n";
					}
					break;

				}
				else{
					system("cls");
					menuListas();
					_getch();
					exit = true;
				}
			}
		}
	}
	menuCriacao();
}

void Campeonato::menuDesportos(){
	bool exit = false;
	while (!exit){
		system("cls");
		int ch = fazMenu("Desportos:", desportos, "Novo Desporto");
		if (ch == -1)
			exit = true;
		else if ((unsigned)ch < desportos.size())
			desportos[ch]->menu();
		else{
			try{
				adicionaDesporto();
			}
			catch (DesportoExiste &d){
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
		else if ((unsigned)ch < equipas.size())
			equipas[ch]->menu(desportos);
		else{
			try{
				adicionaEquipa();
			}
			catch (EquipaExiste &eq){
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
		else if ((unsigned)ch < provas.size())
			provas[ch]->menu(equipas);
		else
			adicionaProva();
	}
}

void Campeonato::menuApagar(){
	bool exit = false;
	int ch;

	system("cls");
	vector<string> choices;
	choices.push_back("Desportos");
	choices.push_back("Modalidades");
	choices.push_back("Equipas");
	choices.push_back("Atletas");
	choices.push_back("Provas");
	while (!exit){
		system("cls");
		ch = fazMenu("Apagar", choices);
		if (ch == -1)
			exit = true;
		else if(ch == 0){
			menuApagarDesportos();
		}

		else if(ch == 1){
			menuApagarModalidades();
		}

		else if(ch == 2){
			menuApagarEquipas();
		}

		else if(ch == 3){
			menuApagarAtletas();
		}

		else{
			menuApagarProvas();
		}
	}
}

void Campeonato::menuApagarDesportos()
{
	int ch2, ch3;
	bool exit2 = false;
	if (desportos.size() != 0){
		while (!exit2){
			system("cls");
			ch2 = fazMenu("Desportos:", desportos);
			if (ch2 == -1){
				exit2 = true;
				continue;
			}

			vector<Equipa*> equipas_desp;

			for (unsigned int i = 0; i < equipas.size(); i++)
				for (unsigned int j = 0; j < equipas[i]->getDesportos().size(); j++)
					if (equipas[i]->getDesportos()[j] == desportos[ch2]){
						equipas_desp.push_back(equipas[i]);
					}

			if (equipas_desp.size() != 0)
			{
				system("cls");
				cout << "Ainda existem equipas subscritas a este desporto.\n";
				cout << endl;
				cout << "Por favor elimine as seguintes equipas:\n";

				for(unsigned int i = 0; i < equipas_desp.size(); i++)
				{
					cout << equipas_desp[i]->getNome() << endl;
				}

				_getch();
				return;
			} else if (desportos[ch2]->getModalidades().size() == 0)
			{
				desportos.erase(desportos.begin()+ch2);
				return;
			}

			if (desportos[ch2]->getModalidades().size() != 0)
			{
				bool exit3 = false;
				while (!exit3){
					system("cls");

					cout << desportos[ch2]->getNome();
					cout << " ainda tem modalidades.\n";
					cout << endl;

					ch3 = fazMenu("Modalidades a Retirar:", desportos[ch2]->getModalidades());
					if (ch3 == -1){
						exit3 = true;
						continue;
					}
					else{
						vector<Prova*> provas_mod;

						for (unsigned int i = 0; i < provas.size(); i++)
							if (provas[i]->getModalidade() == desportos[ch2]->getModalidades()[ch3]){
								provas_mod.push_back(provas[i]);
							}

						if (provas_mod.size() != 0)
						{
							system("cls");
							cout << "Ainda existem provas subscritas a ";
							cout << desportos[ch2]->getModalidades()[ch3]->getNome() << endl;
							cout << endl;
							cout << "Por favor elimine as seguintes provas:\n";

							for(unsigned int i = 0; i < provas_mod.size(); i++)
							{
								cout << *provas_mod[i] << endl;
							}

							_getch();
							return;

						} else{
							apagaModalidade(desportos[ch2]->getModalidades()[ch3]->getNome());
							if (desportos[ch2]->getModalidades().size() == 0)
								desportos.erase(desportos.begin()+ch2);
							return;
						}
					}
				}
			}
			return;
		}
	}
	else{
		cout << "Nao existem mais desportos para apagar!\n" << endl;
	}

}

void Campeonato::menuApagarModalidades()
{
	int ch2, ch3;
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

			if (desportos[ch2]->getModalidades().size() == 0)
			{
				system("cls");
				cout << "Nao existem mais modalidades neste desporto.";
				_getch();
				return;
			}else {
				ch3 = fazMenu("Modalidades:", desportos[ch2]->getModalidades());
				if (ch3 == -1){
					exit3 = true;
					continue;
				}
			}

			vector<Prova*> provas_mod;

			for (unsigned int i = 0; i < provas.size(); i++)
				if (provas[i]->getModalidade() == desportos[ch2]->getModalidades()[ch3]){
					provas_mod.push_back(provas[i]);
				}

			if (provas_mod.size() != 0)
			{
				system("cls");
				cout << "Ainda existem provas subscritas a esta modalidade.\n";
				cout << endl;
				cout << "Por favor elimine as seguintes provas:\n";

				for(unsigned int i = 0; i < provas_mod.size(); i++)
				{
					cout << *provas_mod[i] << endl;
				}

				_getch();
				return;

			}
			apagaModalidade(desportos[ch2]->getModalidades()[ch3]->getNome());
			return;
		}
	}
}

void Campeonato::menuApagarEquipas()
{
	int ch2, ch3;
	bool exit2 = false;
	if (equipas.size() != 0){
		while (!exit2){
			system("cls");
			ch2 = fazMenu("Equipas:", equipas);
			if (ch2 == -1){
				exit2 = true;
				continue;
			}
			else {
				if (equipas[ch2]->getAtletas().size() != 0)
				{
					bool exit3 = false;
					while (!exit3){
						system("cls");

						cout << equipas[ch2]->getNome();
						cout << " ainda tem atletas.\n";
						cout << endl;

						ch3 = fazMenu("Atletas a Retirar:", equipas[ch2]->getAtletas());
						if (ch3 == -1){
							exit3 = true;
							continue;
						}
						else{
							if (equipas[ch2]->getAtletas()[ch3]->getProvas().size() != 0)
							{
								system("cls");
								cout << equipas[ch2]->getAtletas()[ch3]->getNome();
								cout << " ainda esta inscrito nas seguintes provas:\n";
								for(unsigned int i = 0; i < equipas[ch2]->getAtletas()[ch3]->getProvas().size(); i++)
									cout << *equipas[ch2]->getAtletas()[ch3]->getProvas()[i] << endl;
								_getch();
								return;
							}
							else{
								equipas[ch2]->apagaAtleta(equipas[ch2]->getAtletas()[ch3]->getNome());
								if (equipas[ch2]->getAtletas().size() == 0)
									equipas.erase(equipas.begin()+ch2);
								return;
							}
						}
					}
				}
				else {
					equipas.erase(equipas.begin()+ch2);
					return;
				}
			}
		}
	}
	else{
		cout << "Nao existem mais equipas para apagar!\n" << endl;
	}
}

void Campeonato::menuApagarAtletas()
{
	int ch2, ch3;
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
			if (equipas[ch2]->getAtletas().size() == 0)
			{
				system("cls");
				cout << "Nao existem mais atletas nesta equipa.";
				_getch();
				return;
			} else{
				ch3 = fazMenu("Atletas:", equipas[ch2]->getAtletas());
				if (ch3 == -1){
					exit3 = true;
					continue;
				}
			}
			if (equipas[ch2]->getAtletas()[ch3]->getProvas().size() != 0){
				{
					system("cls");
					cout << equipas[ch2]->getAtletas()[ch3]->getNome();
					cout << " ainda esta inscrito nas seguintes provas:\n";
					for(unsigned int i = 0; i < equipas[ch2]->getAtletas()[ch3]->getProvas().size(); i++)
						cout << *equipas[ch2]->getAtletas()[ch3]->getProvas()[i] << endl;
					_getch();
					return;
				}
				return;
			}
		}
	}
}

void Campeonato::menuApagarProvas()
{
	int ch2, ch3;
	bool exit2 = false;
	if (provas.size() != 0){
		while (!exit2){
			system("cls");
			ch2 = fazMenu("Provas:", provas);
			if (ch2 == -1){
				exit2 = true;
				continue;
			}

			if (provas[ch2]->getAtletas().size() == 0)
			{
				provas.erase(provas.begin()+ch2);
				return;
			}

			if (provas[ch2]->getAtletas().size() != 0){
				{
					bool exit3 = false;
					while (!exit3 && provas[ch2]->getAtletas().size() != 0){
						system("cls");
						cout << *provas[ch2];
						cout << endl;
						cout << "Esta prova ainda tem atletas.\n";
						cout << endl;

						ch3 = fazMenu("Selecionar Atletas:", provas[ch2]->getAtletas());
						if (ch3 == -1)
						{
							exit3 = true;
							continue;
						}
						else{
							for(unsigned int i = 0; i < equipas.size(); i++)
								for(unsigned int j = 0; j <equipas[i]->getAtletas().size(); j++)
									for(unsigned int k = 0; k < equipas[i]->getAtletas()[j]->getProvas().size(); k++)
									{
										if (equipas[i]->getAtletas()[j]->getProvas()[k] == provas[ch2])
										{
											equipas[i]->apagaProva(j,k);
										}
									}

							provas[ch2]->apagaAtleta(provas[ch2]->getAtletas()[ch3]->getNome());
							if (provas[ch2]->getAtletas().size() == 0)
								provas.erase(provas.begin()+ch2);
							return;
						}
					}
				}
				return;
			}
		}
	}
	else {
		cout << "Nao existem mais provas para apagar!\n" << endl;
	}
	//return;
}

void Campeonato::Salvar() {
	update();
	system("cls");
	cout << "Ficheiros atualizados.";
	_getch();
	return;
}


void Campeonato::menuListas(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Desportos");
		choices.push_back("Modalidades");
		choices.push_back("Equipas");
		choices.push_back("Atletas");
		choices.push_back("Provas");

		int ch = fazMenu("Listas:", choices);
		if (ch == -1)
			exit = true;
		else if(ch == 0)
		{
			menuListasDesportos();
		}
		else if(ch == 1)
		{
			menuListasModalidades();
		}
		else if (ch == 2)
		{
			menuListasEquipas();
		}
		else if (ch == 3)
		{
			menuListasAtletas();
		}
		else if (ch == 4)
		{
			menuListasProvas();
		}
	}
}

void Campeonato::menuListasDesportos()
{
	bool exit1 = false;
	while (!exit1){
		system("cls");
		vector<string> choices;
		choices.push_back("Nome");

		int ch = fazMenu("Listagem de Desportos por:", choices);
		if (ch == -1)
			exit1 = true;
		else {
			system("cls");
			listaDesportos();
			_getch();
			return;
		}
	}
}

void Campeonato::menuListasModalidades()
{
	bool exit1 = false;
	while (!exit1){
		system("cls");
		vector<string> choices;
		choices.push_back("Nome");

		int ch = fazMenu("Listagem de Modalidades por:", choices);
		if (ch == -1)
			exit1 = true;
		else {
			system("cls");
			vector<string> nomes;

			for(unsigned int i = 0; i < desportos.size(); i++)
				for(unsigned int j = 0; j < desportos[i]->getModalidades().size(); j++)
					nomes.push_back(desportos[i]->getModalidades()[j]->getNome());

			insertionSort<string>(nomes);

			for(unsigned int i = 0; i < nomes.size(); i++)
				cout << nomes[i] << endl;

			_getch();
			return;
		}
	}
}

void Campeonato::menuListasEquipas(){
	bool exit1 = false;
	while (!exit1){
		system("cls");
		vector<string> choices;
		choices.push_back("Nome");
		choices.push_back("Colocacao");

		int ch = fazMenu("Listagem de Equipas por:", choices);
		if (ch == -1)
			exit1 = true;
		else if (ch == 0)
		{
			system("cls");
			vector<string> nomes;

			for(unsigned int i = 0; i < equipas.size(); i++)
				nomes.push_back(equipas[i]->getNome());
			insertionSort<string>(nomes);

			for(unsigned int i = 0; i < nomes.size(); i++)
				cout << nomes[i] << endl;
			_getch();
			return;
		}
		else {
			system("cls");
			if (criado)
				listaEquipasColocacao();
			else {
				cout << "O campeonato ainda nao foi realizado.\n";
			}
			_getch();
			return;
		}
	}
}

void Campeonato::menuListasAtletas()
{
	bool exit1 = false;
	while (!exit1){
		system("cls");
		vector<string> choices;
		choices.push_back("Nome");
		choices.push_back("Colocacao");
		choices.push_back("Desporto");
		choices.push_back("Modalidade");

		int ch = fazMenu("Listagem de Atletas por:", choices);
		if (ch == -1)
			exit1 = true;
		else if (ch == 0)
		{
			system("cls");
			listaAtletas();
			_getch();
			return;
		}
		else if (ch == 1){
			system("cls");

			if (criado)
				listaAtletasColocacao();
			else {
				cout << "O campeonato ainda nao foi realizado.\n";
			}

			_getch();
			return;
		}
		else if (ch == 2)
		{
			system("cls");
			listaAtletasEquipa();
			_getch();
			return;
		}
		else if (ch == 3)
		{
			system("cls");
			listaAtletasDesporto();
			_getch();
			return;
		}
		else {
			system("cls");
			listaAtletasModalidade();
			_getch();
			return;
		}
	}
}

void Campeonato::menuListasProvas(){
	bool exit1 = false;
		while (!exit1){
			system("cls");
			vector<string> choices;
			choices.push_back("Por Realizar");
			choices.push_back("Realizadas");

			int ch = fazMenu("Listagem de Provas:", choices);
			if (ch == -1)
				exit1 = true;
			else if (ch == 0)
			{
				system("cls");
				listaProvasNaoRealizadas();
				_getch();
				return;
			}
			else {
				system("cls");
				listaProvasRealizadas();
				_getch();
				return;
			}
		}
}

void Campeonato::TerminarPlaneamento()
{
	bool mod_vazio = false;
	bool atletas_vazio = false;
	bool desportos_vazio = false;
	bool provas_at_vazio = false;
	bool atletas_pro_vazio = false;

	for(unsigned int i = 0; i < desportos.size(); i++)
	{
		if (desportos[i]->getModalidades().size() == 0)
		{
			mod_vazio = true;
		}
	}

	for(unsigned int i = 0; i < equipas.size(); i++)
	{
		if (equipas[i]->getAtletas().size() == 0)
			atletas_vazio = true;
		if (equipas[i]->getDesportos().size() == 0)
			desportos_vazio = true;

		for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
		{
			if (equipas[i]->getAtletas()[j]->getProvas().size() == 0)
				provas_at_vazio = true;
		}
	}

	for(unsigned int i = 0; i < provas.size(); i++)
	{
		if (provas[i]->getAtletas().size() < 2)
			atletas_pro_vazio = true;
	}
	system("cls");

	if (mod_vazio)
	{
		cout << "Ainda ha desportos sem modalidades!";
		_getch();
		return;
	}else if(atletas_vazio)
	{
		cout << "Ainda ha equipas sem atletas!";
		_getch();
		return;
	}else if(desportos_vazio)
	{
		cout << "Ainda ha equipas sem desportos!";
		_getch();
		return;
	}else if(provas_at_vazio)
	{
		cout << "Ainda ha atletas sem provas!";
		_getch();
		return;
	}
	else if(atletas_pro_vazio)
	{
		cout << "Ainda ha provas sem atletas suficientes (minimo: 2)!";
		_getch();
		return;
	}
	else {
		criado = true;
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
		catch (Desporto::ModalidadeExiste &m){
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
		catch (Data::DataInvalida &D){
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
		catch (Hora::HoraInvalida &H){
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

void atribuiPontuacao(ProvaTerminada &pro, vector<float> pontos) {//ordena o vetor atletas por pontuacao e faz pushback das pontuacoes ordenadas no pontuacoes da provaTerminada
	//e faz push:_back dos atletas ordenados tb

	for (unsigned int i = 0; i < pontos.size() - 1; i++)
		for (unsigned int j = i; j < pontos.size(); j++) {
			if (pontos[i] < pontos[j]) {
				swap(pontos[i], pontos[j]); // ou assim paracido, seja como for trocarlos
				swap(pro.getAtletas()[i], pro.getAtletas()[j]); // assim os atletas tb sao ordenados
			}
		}

	if(pro.getModalidade()->getDesporto()->isCrescente())
			{if (pro.getAtletas().size() <= 2) {
		//cout << pro.getAtletas().size();
		pro.getAtletas()[0]->adicionaPontuacao(3);
	} else {
		pro.getAtletas()[0]->adicionaPontuacao(3);
		pro.getAtletas()[1]->adicionaPontuacao(2);
		pro.getAtletas()[2]->adicionaPontuacao(1);

	}

		for (unsigned int k = 0; k < pontos.size(); k++)
			{
			pro.getPontuacoes().push_back(pontos[k]);
			}
	} else {
		if (pro.getAtletas().size() <= 2) {
			pro.getAtletas()[pro.getAtletas().size() - 1]->adicionaPontuacao(3);
		} else {
			pro.getAtletas()[pro.getAtletas().size() - 1]->adicionaPontuacao(3);
			pro.getAtletas()[pro.getAtletas().size() - 2]->adicionaPontuacao(2);
			pro.getAtletas()[pro.getAtletas().size() - 3]->adicionaPontuacao(1);

		}
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

void Campeonato::listaDesportos() const{
	vector<string> ndes;

	cout << "Desportos no campeonato: " << endl;

	for (unsigned int i = 0; i < desportos.size(); i++)
		ndes.push_back(desportos[i]->getNome());

	insertionSort<string>(ndes);

	for (unsigned int j = 0; j < desportos.size(); j++)
		cout << desportos[j]->getNome() << endl;
}

void Campeonato::listaProvasNaoRealizadas() const{
	vector<Prova> vprova;

	cout << "Provas por realizar no campeonato: " << endl;

	for (unsigned int j = 0; j < provas.size();j++)
		if(provas[j]->getRealizada() == 0)
			vprova.push_back(*provas[j]);

	if (vprova.size() == 0)
		cout <<endl << "Ja foram realizadas todas as provas" <<endl <<endl;
	else{
	insertionSort<Prova>(vprova);

	for (unsigned int i = 0; i < vprova.size(); i++)
			cout << vprova[i].getData() << ": Prova de " << (*vprova[i].getModalidade()->getDesporto())
			<< "("<<(*vprova[i].getModalidade())<<")"
			<< " as " << vprova[i].getInicio() << endl;}
}

void Campeonato::listaProvasRealizadas() const{
	vector<Prova*> vprova;

	cout << "Provas ja realizadas no campeonato: " << endl;

	for (unsigned int j = 0; j < provas.size();j++)
		if(provas[j]->getRealizada() == 1)
			vprova.push_back(provas[j]);

	if (vprova.size() == 0)
		cout <<endl << "Ainda nao foram realizadas provas" <<endl <<endl;
	else {
		insertionSort<Prova*>(vprova);


		for (unsigned int i = 0; i < vprova.size(); i++)
			cout << vprova[i]->getData() << ": Prova de " << (*vprova[i]->getModalidade()->getDesporto())
			<< "("<<(*vprova[i]->getModalidade())<<")"
			<< " as " << vprova[i]->getInicio() << endl;
	}
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

	cout << "Atletas no campeonato: " << endl;

	for (unsigned int j = 0; j < desportos.size(); j++) {
		vector<Atleta> vatd;

		for (unsigned int u = 0; u < vat.size(); u++) //percorre os atletas
			for (unsigned int a = 0;
					a < vat[u].getEquipa()->getDesportos().size(); a++) //percorre os seus desportos
				if (desportos[j]->getNome()
						== vat[u].getEquipa()->getDesportos()[a]->getNome()) //desporto = desporto do a atleta
					vatd.push_back(vat[u]);

		if (vatd.size() == 0)
			cout <<endl << "Nao ha atletas em " << desportos[j]->getNome() <<endl;
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

	unsigned int i = 0;

	for (unsigned int a = 0; a < peq.size(); a++)
		for (unsigned int b = 0; b < peqb.size(); b++)
			if (peqb[b] == peq[a].first)
			{
				if (i < equipas.size())
					cout<< peq[b].second << endl;
				i++;
			}

}

void Campeonato::listaAtletasModalidade() const{
	vector<Atleta> vat;

	for (unsigned int j = 0; j < equipas.size(); j++)
		for (unsigned int u = 0; u < equipas[j]->getAtletas().size(); u++)
			vat.push_back((*equipas[j]->getAtletas()[u]));


	for (unsigned int j = 0; j < desportos.size(); j++) {
		vector<Atleta> vatm;
		for (unsigned int w = 0; w < desportos[j]->getModalidades().size(); w++) //percorre as modalidades todas
				{
			for (unsigned int u = 0; u < vat.size(); u++) //percorre os atletas
				for (unsigned int b = 0; b < vat[u].getModalidades().size();
						b++) // percorre modalidades dos atletas
						{
					if (desportos[j]->getModalidades()[w]->getNome()
							== vat[u].getModalidades()[b]->getNome())
						vatm.push_back(vat[u]);
				}

			if (vatm.size() == 0)
				cout << endl << "Nao ha atletas  em "
						<< desportos[j]->getModalidades()[w]->getNome() << endl;
			else {
				insertionSort<Atleta>(vatm);
				cout << endl << "Atletas em "
						<< desportos[j]->getModalidades()[w]->getNome() << " ("
						<< desportos[j]->getNome() << ") " << ":" << endl
						<< endl;
				for (unsigned int i = 0; i < vatm.size(); i++)
					cout << vatm[i] << endl;
			}
		}
	}
}

bool Campeonato::realizaProva(Prova &p , vector <float> pontuacoes){
	Hora hi (p.getInicio().getHoras(),p.getInicio().getMinutos());

	for (vector < Prova*>::iterator it = provas.begin(); it != provas.end();it++)
		if (*(*it) == p)
			{
			ProvaTerminada * nova = new ProvaTerminada(p.getModalidade(), p.getData(), hi, p.getGenero());
			nova->setAtletas(p.getAtletas());
			atribuiPontuacao(*nova, pontuacoes);

			it = provas.erase(it);
			provas.push_back(nova);

			return true;
			}
		else if ((!((*it) == &p))&& (it++)==provas.end())
			return false;
return false;

}

void Campeonato::criaCalendario(){
	vector<Prova> vprova;

	for (unsigned int j = 0; j < provas.size();j++)
		vprova.push_back(*(provas[j]));

	for (unsigned int i = 0; i < vprova.size(); i++)
	{
		datas.insert(vprova[i]);
	}
}

int Campeonato::provasSimultaneas(){
	unsigned int simul = 0;
	vector< vector<Prova> > vec;

	system("cls");

	for (unsigned int i = 0; i < provas.size(); i++){
		vector<Prova> sim;
		sim.push_back(*provas[i]);
		for(unsigned int j = i; j < provas.size(); j++)
			if (i != j){
				bool simultaneo = provas[i]->Simultaneo(*provas[j]);

				if (simultaneo){
					sim.push_back(*provas[j]);
				}
			}
		vec.push_back(sim);
	}


	for(unsigned int i = 0; i < vec.size(); i++){
		if (vec[i].size() > simul){
			simul = vec[i].size();
		}
	}

	return simul;
}

void Campeonato::alterarDataInicio(){
	system("cls");

	vector<Prova> vprova;
	BSTItrIn<Prova> itr(datas);

	while (!itr.isAtEnd())
	{
		vprova.push_back(itr.retrieve());
		itr.advance();
	}

	int ch;
		bool exit = false;
		while (!exit){
			system("cls");
			ch = fazMenu("Provas:", vprova);
			if (ch == -1){
				exit = true;
				continue;
			} else{
				system("cls");
				int d, m, a, horas, min;
				cout << "Nova data (entre " << inicio << " e " << fim << "):\n" << endl;
				cout << "Dia: ";
				while (!(cin >> d))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Input invalido! O numero deve ser um inteiro\n";
					cout << "Dia: ";
				}
				cin.ignore(1000, '\n');
				cout << "Mes: ";
				while (!(cin >> m))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Input invalido! O numero deve ser um inteiro\n";
					cout << "Mes: ";
				}
				cin.ignore(1000, '\n');
				cout << "Ano: ";
				while (!(cin >> a))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Input invalido! O numero deve ser um inteiro\n";
					cout << "Ano: ";
				}
				cin.ignore(1000, '\n');
				try{
					Data data(a,m,d);
				} catch(Data::DataInvalida &d){
					cout << endl << "Data invalida!\n";
					_getch();
					continue;
				}

				Data data(a,m,d);
				if (data < inicio || fim < data)
				{
					cout << endl << "Data fora dos limites!\n";
					_getch();
					continue;
				}

				cout << endl << "Nova hora (entre " << abertura << " e " << fecho << "):\n";
				cout << "Horas: ";
				while (!(cin >> horas))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Input invalido! O numero deve ser um inteiro\n";
					cout << "Horas: ";
				}
				cin.ignore(1000, '\n');
				cout << "Minutos: ";
				while (!(cin >> min))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Input invalido! O numero deve ser um inteiro\n";
					cout << "Minutos: ";
				}
				cin.ignore(1000, '\n');
				try{
					Hora hor(horas,min);
				} catch(Hora::HoraInvalida &h){
					cout << "Hora invalida!";
					_getch();
					continue;
				}
				Hora hor(horas,min);

				if (hor < abertura || fecho < hor){
					cout << endl << "Hora fora dos limites!\n";
					_getch();
					continue;
				}

				unsigned int indice = 0;
				Data d_anterior;
				Hora h_anterior;

				for(unsigned int i = 0; i < provas.size(); i++)
					if (*provas[i] == vprova[ch]){
						indice = i;
						d_anterior = provas[i]->getData();
						h_anterior = provas[i]->getInicio();

						provas[i]->setInicio(data,hor);
						break;
					}

				for(unsigned int i = 0; i < provas.size(); i++)
					if (indice != i){
						bool simultaneo = provas[indice]->Simultaneo(*provas[i]);
						if (simultaneo && (comparar_strings(provas[i]->getModalidade()->getNome(), provas[indice]->getModalidade()->getNome()))){
							cout << endl << "Duas provas simultaneas da mesma modalidade!\n";
							provas[indice]->setInicio(d_anterior,h_anterior);
							_getch();
							continue;
						}
					}

				for(unsigned int i = 0; i < equipas.size(); i++)
					for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
						for(unsigned int k = 0; k < equipas[i]->getAtletas()[j]->getProvas().size(); k++){
							if (*equipas[i]->getAtletas()[j]->getProvas()[k] == vprova[ch]){
								equipas[i]->getAtletas()[j]->getProvas()[k]->setInicio(data,hor);
							}
						}

				datas.remove(vprova[ch]);
				vprova[ch].setInicio(data,hor);
				datas.insert(vprova[ch]);

				int sim = provasSimultaneas();

				while(sim > 3){
					system("cls");
					cout << "Ainda ha " << sim << " provas simultaneas!";
					_getch();

					alterarDataInicio();
					sim = provasSimultaneas();
				}
				return;
			}
		}


}

void Campeonato::alterarData(){
	system("cls");

	vector<Prova> vprova;
	BSTItrIn<Prova> itr(datas);

	while (!itr.isAtEnd())
	{
		vprova.push_back(itr.retrieve());
		itr.advance();
	}

	int ch;
	bool exit = false;
	while (!exit){
		system("cls");
		ch = fazMenu("Provas:", vprova);
		if (ch == -1){
			exit = true;
			continue;
		} else{
			system("cls");
			int d, m, a, horas, min;
			cout << "Nova data (entre " << inicio << " e " << fim << "):\n" << endl;
			cout << "Dia: ";
			while (!(cin >> d))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input invalido! O numero deve ser um inteiro\n";
				cout << "Dia: ";
			}
			cin.ignore(1000, '\n');
			cout << "Mes: ";
			while (!(cin >> m))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input invalido! O numero deve ser um inteiro\n";
				cout << "Mes: ";
			}
			cin.ignore(1000, '\n');
			cout << "Ano: ";
			while (!(cin >> a))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input invalido! O numero deve ser um inteiro\n";
				cout << "Ano: ";
			}
			cin.ignore(1000, '\n');
			try{
				Data data(a,m,d);
			} catch(Data::DataInvalida &d){
				cout << endl << "Data invalida!\n";
				_getch();
				return;
			}

			Data data(a,m,d);
			if (data < inicio || fim < data)
			{
				cout << endl << "Data fora dos limites!\n";
				_getch();
				return;
			}

			cout << endl << "Nova hora (entre " << abertura << " e " << fecho << "):\n";
			cout << "Horas: ";
			while (!(cin >> horas))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input invalido! O numero deve ser um inteiro\n";
				cout << "Horas: ";
			}
			cin.ignore(1000, '\n');
			cout << "Minutos: ";
			while (!(cin >> min))
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Input invalido! O numero deve ser um inteiro\n";
				cout << "Minutos: ";
			}
			cin.ignore(1000, '\n');
			try{
				Hora hor(horas,min);
			} catch(Hora::HoraInvalida &h){
				cout << "Hora invalida!";
				_getch();
				return;
			}
			Hora hor(horas,min);

			if (hor < abertura || fecho < hor){
				cout << endl << "Hora fora dos limites!\n";
				_getch();
				return;
			}

			unsigned int indice = 0;
			Data d_anterior;
			Hora h_anterior;

			for(unsigned int i = 0; i < provas.size(); i++)
				if (*provas[i] == vprova[ch]){
					indice = i;
					d_anterior = provas[i]->getData();
					h_anterior = provas[i]->getInicio();

					provas[i]->setInicio(data,hor);
					break;
				}

			for(unsigned int i = 0; i < provas.size(); i++)
				if (indice != i){
					bool simultaneo = provas[indice]->Simultaneo(*provas[i]);
					if (simultaneo && (comparar_strings(provas[i]->getModalidade()->getNome(), provas[indice]->getModalidade()->getNome()))){
						cout << endl << "Duas provas simultaneas da mesma modalidade!\n";
						provas[indice]->setInicio(d_anterior,h_anterior);
						_getch();
						return;
					}
				}

			int sim = provasSimultaneas();

			if(sim > 3){
				cout << "Se mudar a data, fica-se com mais de 3 provas simultaneas!" << endl;
				_getch();
				provas[indice]->setInicio(d_anterior,h_anterior);
				return;
			}

			for(unsigned int i = 0; i < equipas.size(); i++)
				for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
					for(unsigned int k = 0; k < equipas[i]->getAtletas()[j]->getProvas().size(); k++){
						if (*equipas[i]->getAtletas()[j]->getProvas()[k] == vprova[ch]){
							equipas[i]->getAtletas()[j]->getProvas()[k]->setInicio(data,hor);
						}
					}

			datas.remove(vprova[ch]);
			vprova[ch].setInicio(data,hor);
			datas.insert(vprova[ch]);
			return;
		}
	}
}

void Campeonato::cancelarProva(){
	system("cls");

	vector<Prova> vprova;
	BSTItrIn<Prova> itr(datas);

	while (!itr.isAtEnd())
	{
		vprova.push_back(itr.retrieve());
		itr.advance();
	}

	int ch;
	bool exit = false;
	while (!exit){
		system("cls");
		ch = fazMenu("Provas:", vprova);
		if (ch == -1){
			exit = true;
			continue;
		} else{
			for(unsigned int i = 0; i < provas.size(); i++)
				if (*provas[i] == vprova[ch]){
					provas.erase(provas.begin()+i);
					break;
				}

			for(unsigned int i = 0; i < equipas.size(); i++)
				for(unsigned int j = 0; j < equipas[i]->getAtletas().size(); j++)
					for(unsigned int k = 0; k < equipas[i]->getAtletas()[j]->getProvas().size(); k++){
						if (*equipas[i]->getAtletas()[j]->getProvas()[k] == vprova[ch]){
							equipas[i]->getAtletas()[j]->apagaProva(k);
						}
					}
			datas.remove(vprova[ch]);
			return;
		}
	}
}

void Campeonato::verCalendario(){
	system("cls");
	datas.printTree();
	_getch();
}

void Campeonato::menuCalendario(){
	bool exit = false;
	while (!exit){
		system("cls");
		vector<string> choices;
		choices.push_back("Alterar data");
		choices.push_back("Cancelar prova");
		choices.push_back("Ver calendario");

		int ch = fazMenu("Campeonato Polidesportivo - Calendario", choices);
		if (ch == -1)
			exit = true;
		else if (ch == 0)
			alterarData();
		else if (ch == 1)
			cancelarProva();
		else
			verCalendario();
	}
}

