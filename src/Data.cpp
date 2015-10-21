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

