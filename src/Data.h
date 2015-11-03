/*
 * Data.h
 *
 *  Created on: 16/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_

using namespace std;

class Hora;

class Data{
	int ano, dia, mes;
public:
	Data();
	Data(int a, int m, int d);
	bool operator== (const Data & data) const;
	bool operator< (const Data & data) const;
};

class Hora{
	int horas, minutos;
public:
	Hora();
	Hora(int h, int m);
	Hora operator+ (const Hora & h) const; //Nao pode passar das 24h
	bool operator< (const Hora & h) const;
	bool operator> (const Hora & h) const;
	class HoraInvalida{
		public:
		int horas, minutos;
		HoraInvalida(int h, int m);
	};
};

#endif /* SRC_DATA_H_ */
