#include "Campeonato.h"
#include <iostream>

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
		else  return false;
	}

	in.close();

	return true;
}

void atribuiPontuacao(Prova pro, vector< float> pontos){
	int primeiro =-1;
	int segundo = -1;
	int terceiro = -1;
	int menor = pontos[0];
	int segundoMenor = pontos[1];
	int terceiroMenor = pontos[2];
	int maior = pontos[0];
	int segundoMaior = pontos[1];
	int terceiroMaior = pontos[2];

	if (pro.getModalidade().getDesporto()->isCrescente()) {
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
