/*
 * Data.h
 *
 *  Created on: 16/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <iostream>
#include "Lists.h"

using namespace std;

class Hora;

class Data{
	int ano, dia, mes;
public:
	Data();
	Data(int a, int m, int d);

	friend ostream & operator<<(ostream & o, const Data & d);
	bool operator== (const Data & data) const;
	bool operator< (const Data & data) const;

	bool scanAnoBissexto(int ano);
	int diasMes(int ano, int mes);

	int getAno() const;
	int getMes() const;
	int getDia() const;

	class DataInvalida : public LoadProvasFail {
		int ano, dia, mes;
	public:
		DataInvalida(){}
		DataInvalida(int a, int m, int d) {ano = a;	mes = m; dia = d;}
		string getMessage() const
		{
			string d = int_to_string(dia);
			string m = int_to_string(mes);
			string a = int_to_string(ano);
			string message = "A data " + d + "/" + m + "/" + a + " e invalida!\n";
			return message;
		}
	};
};

class Hora{
	int horas, minutos;
public:
	Hora();
	Hora(int h, int m);

	friend ostream & operator<<(ostream & o, const Hora & h);
	Hora operator+ (const Hora & h) const; //Nao pode passar das 24h
	bool operator< (const Hora & h) const;
	bool operator> (const Hora & h) const;

	int getHoras() const;
	int getMinutos() const;

	class HoraInvalida : public LoadProvasFail {
		int horas, minutos;
	public:
		HoraInvalida(){}
		HoraInvalida(int h, int m){horas = h; minutos = m;}
		string getMessage() const{
			string h = int_to_string(horas);
			string m = int_to_string(minutos);
			string message = "A hora " + h + ":" + m + " e invalida!\n";
			return message;
		}
	};
};

#endif /* SRC_DATA_H_ */
