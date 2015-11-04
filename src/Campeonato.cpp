#include "Campeonato.h"

using namespace std;

Campeonato::Campeonato(string n, Data i, Data f)
{
	nome = n;
	inicio = i;
	fim = f;
}

bool Campeonato::adicionaProva(Modalidade m, Data d, Hora i)
{
	Prova p(m,d,i);

	if (d < inicio || fim < d)
		return false;
	else
	{
		Hora abertura(8,0);
		Hora fecho(20,0);
		Hora fimProva = i + m.getDuracao();

		if (i < abertura || fecho < fimProva)
			return false;
		else
		{
			if (provas.size() == 0)
				{
				provas.push_back(p);
				return true;
				}
			else
			{
				for (unsigned int i = 0; i < provas.size(); i++)
				{
					bool simultaneo = provas[i].Simultaneo(p);

					if (simultaneo)
						return false;
				}
			}
		}
	}

	provas.push_back(p);
	return true;
}

bool Campeonato::criaDesportosCampeonato(string nome_ficheiro)
{
	int elementos_equipa;
	char barra;
	string desporto = "";
	string tipo_de_pontuacao = "";
	char crescente;
	bool c;
	ifstream in;

	in.open(nome_ficheiro.c_str());

	while (!in.eof())
	{
		in >> elementos_equipa;
		in >> barra;

		string extraido = "";

		do
		{
			in >> extraido;
			if (extraido != "/")
				desporto = desporto + " " + extraido;
		}
		while (extraido != "/");

		extraido = "";

		do
		{
			in >> extraido;
			if (extraido != "/")
				tipo_de_pontuacao = tipo_de_pontuacao + " " + extraido;
		}
		while (extraido != "/");

		in >> crescente;

		if (crescente == 'C')
			c = true;
		else if (crescente == 'D')
			c = false;
		else return false;

		if (elementos_equipa > 1)
		{
			DesportoEquipa de(desporto, tipo_de_pontuacao, c, elementos_equipa);
			desportos.push_back(&de);
		}
		else if (elementos_equipa == 1)
		{
			DesportoSolo ds(desporto, tipo_de_pontuacao, c);
			desportos.push_back(&ds);
		}
		else return false;
	}

	return true;
}
