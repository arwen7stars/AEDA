#include "Campeonato.h"

using namespace std;

Campeonato::Campeonato(string n, vector<Desporto *> d, vector<Equipa*> e, vector<Prova> p, Data i, Data f)
{
	nome = n;
	desportos = d;
	equipas = e;
	provasCampeonato = p;
	inicio = i;
	fim = f;
}

bool Campeonato::adicionaProvaCampeonato(Modalidade m, Data d, Hora I)
{

}
