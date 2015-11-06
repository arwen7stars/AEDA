/*
 * Data.cpp
 *
 *  Created on: 21/10/2015
 *      Author: Filipe
 */

#include "Data.h"
using namespace std;

/*
------------------------------------------------------------------------------
								Class Data
------------------------------------------------------------------------------
*/

Data::Data(){}

Data::Data(int a, int m, int d){
	if (a < 0 || m < 0 || m > 12 || d < 0)
		throw DataInvalida(a,m,d);

	int diaMaximo = diasMes(a,m);

	if (d > diaMaximo)
		throw DataInvalida(a,m,d);

	ano = a;
	mes = m;
	dia = d;
}

bool Data::scanAnoBissexto(int ano)
{
	bool anoBissexto = false;

	if (ano % 4 == 0)
		if (ano % 100 != 0 || ano % 400 == 0)
			anoBissexto = true;

	return anoBissexto;
}

int Data::diasMes(int ano, int mes)
{
	int dias;

	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		dias = 31;
	else if (mes != 2)
		dias = 30;
	else if (scanAnoBissexto(ano))
		dias = 29;
	else dias = 28;

	return dias;
}

bool Data::operator== (const Data & data) const{
	if (data.ano == ano && data.mes == mes && data.dia == dia)
		return true;
	else
		return false;
}

bool Data::operator< (const Data & data) const{
	if (ano < data.ano)
		return true;
	else if (ano == data.ano)
	{
		if (mes < data.mes)
			return true;
		else if (mes == data.mes)
		{
			if (dia < data.dia)
				return true;
		}
	}
	return false;
}

/*
------------------------------------------------------------------------------
								Class Hora
------------------------------------------------------------------------------
*/

Hora::Hora(){}

Hora::Hora(int h, int m){
	if (h > 23 || h < 0 || m > 59 || m < 0)
		throw HoraInvalida(h,m);
	horas = h;
	minutos = m;
}

Hora Hora::operator+ (const Hora & h) const{
	int novoMinutos = minutos + h.minutos;
	int novaHoras = horas + h.horas;
	if (novoMinutos >= 60){
		novoMinutos %= 60;
		novaHoras++;
	}

	// if (novosMinutos >= 24) -> Daqui fala a Claudia-sama, esta cena mandou-me uma hora invalida quando eu criei uma prova as 12:00
	// com duracao de 1:30 e nao percebi porque, mas ao alterar 24 para 60, isto deu certo!
	if (novoMinutos >= 60){
		throw HoraInvalida(novaHoras, novoMinutos);
	}
	return Hora(novaHoras, novoMinutos);

}

bool Hora::operator< (const Hora & h) const{
	if (horas < h.horas)
		return true;
	else if (horas == h.horas && minutos < h.minutos)
		return true;
	else
		return false;
}

bool Hora::operator> (const Hora & h) const{
	if (horas > h.horas)
		return true;
	else if (horas == h.horas && minutos > h.minutos)
		return true;
	else
		return false;
}

int Hora::getHoras() const
{
	return horas;
}

int Hora::getMinutos() const
{
	return minutos;
}
