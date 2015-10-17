/*
 * Data.h
 *
 *  Created on: 16/10/2015
 *      Author: Filipe
 */

#ifndef SRC_DATA_H_
#define SRC_DATA_H_

using namespace std;

class Data{
	int ano, dia, mes;
public:
	Data(int a, int m, int d);
	bool operator== (const Hora & h) const;
};

class Hora{
	int horas, minutos;
public:
	Hora(int h, int m);
	Hora operator+ (const Hora & h) const; //Nao pode passar das 24h
	bool operator< (const Hora & h) const;
	bool operator> (const Hora & h) const;
};

#endif /* SRC_DATA_H_ */
