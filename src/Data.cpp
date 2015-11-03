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
	ano = a;
	mes = m;
	dia = d;
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

	if (novoMinutos >= 24){
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

Hora::HoraInvalida::HoraInvalida(int h, int m){
	horas = h;
	minutos = m;
}
