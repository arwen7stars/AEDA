#include "Prova.h"

Prova::Prova(Modalidade m, Data d, Hora i)
{
	modalidade = &m;
	data = &d;
	inicio = i;
	fim = i + m.getDuracao();

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
	return *data;
}

Modalidade Prova::getModalidade() const{
	return *modalidade;
}

vector<Atleta*> Prova::getAtletas() const{
	return atletas;
}

bool Prova::Simultaneo(Prova p)
{
	if (p.getData() < *data || *data < p.getData())
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
	atletas.push_back(a);
}
