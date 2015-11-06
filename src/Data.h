/*
 * Data.h
 *
 *  Created on: 16/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <iostream>

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

	class DataInvalida{
		int ano, dia, mes;
	public:
		DataInvalida(){}
		DataInvalida(int a, int m, int d) {ano = a;	mes = m; dia = d;}
		int getAno() const{return ano;}
		int getMes() const{return mes;}
		int getDia() const{return dia;}
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

	class HoraInvalida{
		int horas, minutos;
	public:
		HoraInvalida(){}
		HoraInvalida(int h, int m){horas = h; minutos = m;}
		int getHoras() const{return horas;}
		int getMinutos() const{return minutos;}
	};
};

#endif /* SRC_DATA_H_ */
