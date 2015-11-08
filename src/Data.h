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

/**Class Data
 *
 * Represente uma Data
 *
 */
class Data{
	int ano, dia, mes;
public:
	Data();
	/**
	 * Inicializa os atributos
	 * @param a - ano
	 * @param m - mes
	 * @param d - dia
	 */
	Data(int a, int m, int d);

	/**
	 * imprime a data no formato DD/MM/AAAA
	 *
	 * @param o - stream de output
	 * @param d - uma hora
	 * @return o
	 */
	friend ostream & operator<<(ostream & o, const Data & d);
	/**
	 *
	 * @param c - uma data
	 * @return true as datas forem iguais, false caso contrario.
	 */
	bool operator== (const Data & data) const;
	/**
	 *
	 * @param data - uma data
	 * @return true se data for posterior a esta data, false se nao
	 */
	bool operator< (const Data & data) const;

	/**
	 *
	 * @param ano - um ano
	 * @return true se o ano for bissexto, false se nao
	 */
	bool scanAnoBissexto(int ano);
	/**
	 *
	 * @param ano - um ano
	 * @param mes - um mes
	 * @return o numero de dia do mes naquele ano
	 */
	int diasMes(int ano, int mes);

	/**
	 *
	 * @return ano
	 */
	int getAno() const;
	/**
	 *
	 * @return mes
	 */
	int getMes() const;
	/**
	 *
	 * @return dia
	 */
	int getDia() const;

	/**DataInvalida
	 *
	 * Uma expecao de quando a data for invalida ou nao estiver dentro dos limites
	 */
	class DataInvalida : public LoadProvasFail {
		int ano, dia, mes;
	public:
		DataInvalida(){}
		/**
		 *
		 * @param a - ano
		 * @param m - mes
		 * @param d - dia
		 */
		DataInvalida(int a, int m, int d) {ano = a;	mes = m; dia = d;}
		/**
		 * Constroi uma mensagem como a data
		 *
		 * @return uma string como uma mensagem
		 */
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

/**Hora
 *
 * Representa uma hora
 */
class Hora{
	int horas, minutos;
public:
	Hora();
	/**
	 *  * Inicializa os atributos
	 * @param h - horas
	 * @param m - minutos
	 */
	Hora(int h, int m);

	/**
	 * imprime a data no formato HH:MM
	 *
	 * @param o - stream de output
	 * @param h - uma hora
	 * @return o
	 */
	friend ostream & operator<<(ostream & o, const Hora & h);
	/**
	 *
	 * @param h - uma hora
	 * @return a soma das horas
	 */
	Hora operator+ (const Hora & h) const; //Nao pode passar das 24h
	/**
	 *
	 * @param h - uma hora
	 * @return true se h for maior que esta hora, false se nao
	 */
	bool operator< (const Hora & h) const;
	/**
	 *
	 * @param h - uma hora
	 * @return true se h for menor que esta hora, false se nao
	 */
	bool operator> (const Hora & h) const;

	/**
	 *
	 * @return horas
	 */
	int getHoras() const;
	/**
	 *
	 * @return minutos
	 */
	int getMinutos() const;

	/**DataInvalida
	 *
	 * Uma expecao de quando a hora for invalida ou nao estiver dentro dos limites
	 */
	class HoraInvalida : public LoadProvasFail {
		int horas, minutos;
	public:
		HoraInvalida(){}
		/**
		 *  * Inicializa os atributos
		 * @param h - horas
		 * @param m - minutos
		 */
		HoraInvalida(int h, int m){horas = h; minutos = m;}
		/**
				 * Constroi uma mensagem como a hora
				 *
				 * @return uma string como uma mensagem
				 */
		string getMessage() const{
			string h = int_to_string(horas);
			string m = int_to_string(minutos);
			string message = "A hora " + h + ":" + m + " e invalida!\n";
			return message;
		}
	};
};

#endif /* SRC_DATA_H_ */
