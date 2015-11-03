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
