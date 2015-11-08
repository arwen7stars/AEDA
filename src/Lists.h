/*
 * Lists.h
 *
 *  Created on: 19/10/2015
 *      Author: Filipe
 */

#ifndef SRC_LISTS_H_
#define SRC_LISTS_H_


#include "Lists.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27
using namespace std;

/**
 * Poe o cursor na linha y da consola, na posicao x.
 *
 * @param x - Localicacao do cursor na Consola na horizontal.
 * @param y - Localicacao do cursor na Consola na vertical.
 */
void gotoxy(int x, int y);

/**
 *
 * @return Localicacao do cursor na Consola na vertical (linha).
 */
int wherey();

/**
 * Imprime "titulo". De seguide, imprime todos os objectos apontados por options.
 *
 * Constroi uma seta que aponta para o primeiro objecto.
 * As seguintes teclas sao aceites como input:
 * Up - Sobe na lista.
 * Down - Desce na lista.
 * Esc - Sai da lista.
 * Enter - Sei da lista returnando o indice do objecto atual de options.
 *
 * @param titulo - titulo do menu
 * @param options -  vector de objectos que vao ser imprimidos como opcoes para escolher
 * @return -1 se for pressionado ESC, indice do objecto selecionado se for pressionado ENTER
 */
template <class T>
int fazMenu(string titulo, vector<T*> options);

/**
 * Imprime "titulo". De seguide, imprime todos os objectos de options.
 *
 * Constroi uma seta que aponta para o primeiro objecto.
 * As seguintes teclas sao aceites como input:
 * Up - Sobe na lista.
 * Down - Desce na lista.
 * Esc - Sai da lista.
 * Enter - Sei da lista returnando o indice do objecto atual de options.
 *
 * @param titulo - titulo do menu
 * @param options -  vector de objectos que vao ser imprimidos como opcoes para escolher
 * @return -1 se for pressionado ESC, indice do objecto selecionado se for pressionado ENTER
 */
template <class T>
int fazMenu(string titulo, vector<T> options);

/**
 * /**
 * Imprime "titulo". De seguide, imprime todos os objectos apontados por options. Depois, ainda imprime Op1.
 *
 * Constroi uma seta que aponta para o primeiro objecto.
 * As seguintes teclas sao aceites como input:
 * Up - Sobe na lista.
 * Down - Desce na lista.
 * Esc - Sai da lista.
 * Enter - Sei da lista returnando o indice do objecto atual. (Tamanho de options se a seta estiver em Op1)
 *
 * @param titulo - titulo do menu
 * @param options -  vector de objectos que vao ser imprimidos como opcoes para escolher
 * @param Op1 - uma ultima opcao
 * @return -1 se for pressionado ESC, indice do objecto selecionado se for pressionado ENTER
 */
template <class T>
int fazMenu(string titulo, vector<T*> options, string Op1);

/**
 * Procura no vector v, um apontador para um objecto que seja igual a x, e retorna o seu indice.
 *
 * @param v - um vector onde se vai procurar
 * @param x - um objecto para encontrar
 * @return -1 se nao encontrar nenhum, ou indice do elemento se encontrar.
 */
template <class T>
int search(const vector<T*> &v, T x);




//Menu implementation
template <class T>
int fazMenu(string titulo, vector<T*> options){
	cout << titulo << endl;
	int inicio = wherey();
	for (int i = 0; i < options.size(); i++)
		cout << "   " << (*options[i]) << endl;
	gotoxy(0, inicio);
	int op(0);

	while (true)
	{
		gotoxy(0, inicio + op);
		cout << "->";
		gotoxy(0, inicio + op);

		switch (_getch())
		{
		case KEY_ESC:
			return -1;
			break;
		case KEY_UP:
			if (op > 0)
				op--;
			break;
		case KEY_DOWN:
			if (op < options.size()-1)
				op++;
			break;
		case KEY_ENTER:
			return op;
			break;
		default:
			break;
		}

		cout << "  ";

	}
}

template <class T>
int fazMenu(string titulo, vector<T> options){
	cout << titulo << endl;
	int inicio = wherey();
	for (int i = 0; i < options.size(); i++)
		cout << "   " << (options[i]) << endl;
	gotoxy(0, inicio);
	int op(0);

	while (true)
	{
		gotoxy(0, inicio + op);
		cout << "->";
		gotoxy(0, inicio + op);

		switch (_getch())
		{
		case KEY_ESC:
			return -1;
			break;
		case KEY_UP:
			if (op > 0)
				op--;
			break;
		case KEY_DOWN:
			if (op < options.size()-1)
				op++;
			break;
		case KEY_ENTER:
			return op;
			break;
		default:
			break;
		}

		cout << "  ";

	}
}

template <class T>
int fazMenu(string titulo, vector<T*> options, string Op1){
	cout << titulo << endl;
	int inicio = wherey();
	for (int i = 0; i < options.size(); i++)
		cout << "   " << (*options[i]) << endl;
	cout << "   " << Op1 << endl;
	gotoxy(0, inicio);
	int op(0);

	while (true)
	{
		gotoxy(0, inicio + op);
		cout << "->";
		gotoxy(0, inicio + op);

		switch (_getch())
		{
		case KEY_ESC:
			return -1;
			break;
		case KEY_UP:
			if (op > 0)
				op--;
			break;
		case KEY_DOWN:
			if (op < options.size())
				op++;
			break;
		case KEY_ENTER:
			return op;
			break;
		default:
			break;
		}

		cout << "  ";

	}
}

template <class T>
int search(const vector<T*> &v, T x)
{
    for (unsigned int i = 0; i < v.size(); i++)
        if ((*v[i]) == x)
           return i;
    return -1;
}

inline string &tirar_espacos_fim(string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
	return s;
}

bool comparar_strings(string s1, string s2);

string int_to_string(int i);

bool ficheiroExiste(const string &ficheiro);

class FicheiroInexistente
{
	string nome;
public:
	FicheiroInexistente() {}
	FicheiroInexistente(string n) : nome(n) {}
	string getNome() { return nome; }
};

class LoadFail
{
	string nome;
public:
	LoadFail() {}
	LoadFail(string n) : nome(n) {}
	string getNome() { return nome; }
};

class LoadProvasFail{
public:
	virtual string getMessage() const = 0;
	virtual ~LoadProvasFail() {}
};

class CaraterInvalido{
public:
	char c;
	CaraterInvalido(char ch) {c = ch;}
	char getChar()
	{
		return c;
	}

};

#endif /* SRC_LISTS_H_ */
