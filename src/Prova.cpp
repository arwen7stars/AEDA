#include "Prova.h"

Prova::Prova(Modalidade m, Data d, Hora i)
{
	modalidade = &m;
	data = &d;
	inicio = i;
	fim = i + m.getDuracao();

}
