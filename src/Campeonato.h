/*
 * Campeonato.h
 *
 *  Created on: 14/10/2015
 *      Author: Filipe
 */

#ifndef CAMPEONATO_H_
#define CAMPEONATO_H_

#include <string>
#include <vector>
#include <fstream>
#include "Desporto.h"
#include "Equipa.h"
#include "Data.h"
#include "Lists.h"

/**Classe Campeonato
 * Gere todo o campeonato
 *
 * @author Claudia Marinho, Daniela Sa, Joao Costa
 * @date 08/11/2015
 */
class Campeonato{
	string nome; ///< Nome do campeonato
	vector<Desporto *> desportos; ///< Lista de Desportos/Modalidades
	vector<Equipa* > equipas; ///< Lista de Equipas
	vector<Prova *> provas;
	bool criado;
	Data inicio, fim;///< Data do inicio e do fim do campeonato, pode dar jeito
	Hora abertura, fecho;
public:
	/**Construtor de Campeonato
	 *
	 * Inicializa nome, inicio, fim, abertura e fecho
	 *
	 * @param n - Nome do campeonato
	 * @param i - Data de comeco do campeonato
	 * @param f - Data de fim do campeonato
	 * @param a - Hora diaria de abertura do campeonato
	 * @param fe - Hora diaria de fecho do campeonato
	 */
	Campeonato(string n, Data i, Data f, Hora a, Hora fe);
	/**Adiciona desporto ao campeonato
	 *
	 * Verifica se ja existe o desporto e adiciona-o ao vetor desportos se nao existir
	 *
	 * @param d - Desporto a adicionar ao campeonato
	 * @return true se adicionou o desporto, no caso contrario return false
	 */
	bool adicionaDesporto(Desporto &d);
	/**Adiciona equipa ao campeonato
	 *
	 * Verifica se ja existe a equipa e adiciona-o ao vetor equipas se nao existir
	 * @param eq - Equipa a dicionar ao campeonato
	 * @return true se conseguiu adicionar, caso contrario return false
	 */
	bool adicionaEquipa(Equipa * eq);
	/**Adiciona prova ao campeonato
	 *
	 * Verifica se ja existe a prova e adiciona-o ao vetor equipas se nao existir.
	 * Lanca excecao DataInvalida e HoraInvalida se data ou hora da prova se sobrepuserem a outra prova ja existente
	 * @param p - Prova a adicionar ao campeonato
	 */
	void adicionaProva(Prova &p);
/** Carrega os desportos do ficheiro para o campeonato
 *
 * O ficheiro .txt deve estar na pasta Debug do projeto e ter o seguinte formato:
 *
 * "nome do desporto
 * tipo de pontuacao / peso dos pontos", em que o peso dos pontos e C se o vencedor for que tiver mais pontos e D no caso contrario
 * @param nome_ficheiro - Nome do ficheiro de desportos na pasta Debug
 * @return flase se o ficheiro nao estiver formatado corretamente
 */
	bool loadDesportos(string nome_ficheiro);
	/**Carrega as equipas do ficheiro para o campeonato
 *
 * O ficheiro .txt deve estar na pasta Debug do projeto e ter o seguinte formato:
 *
 * "nome da equipa
 * - nome do jogador / genero", em que genero é M ou F consoante o atleta e do genero masculino ou do genero feminino
 *
 * @param nome_ficheiro - Nome do ficheiro de equipas na pasta Debug
 * @return false se o ficheiro nao estiver formatado corretamente
	 */
	bool loadEquipas(string nome_ficheiro);
	/**Carrega as modalidades do ficheiro para o campeonato
 *
 * O ficheiro .txt deve estar na pasta Debug do projeto e ter o seguinte formato:
 *
 * "nome do desporto
 *  nome da modalidade
 *  horas minutos", em que "horas" e "minutos" sao a duracao das provas dessa modalidade e sao escritos com digitos
 *
 * @param nome_ficheiro - Nome do ficheiro de modalidades na pasta Debug
 * @return false se o ficheiro nao estiver formatado corretamente
	 */
	bool loadModalidades(string nome_ficheiro);
	/**Carrega as modalidades do ficheiro para o campeonato
 *
 * O ficheiro .txt deve estar na pasta Debug do projeto e ter o seguinte formato:
 *
 * "nome da prova
 *  dia mes ano / hora minutos / genero
 *  - nome do atleta", em que "dia", "mes" e "ano" sao digitos a indicar a data da prova
 *                     "horas" e "minutos" sao digitos a indicar a duracao das provas dessa modalidade
 *                     "genero" e M ou F consoate o genero dos atletas na prova
 *                     e devem ser adicionados mais atletas seguindo o mesmo formato
 *
 * @param nome_ficheiro - Nome do ficheiro de equipas na pasta Debug
 * @return false se o ficheiro nao estiver formatado corretamente
	 */
	bool loadProvas(string nome_ficheiro);
/**Carrega as alteracoes ao vetor desportos para o ficheiro utilizado previamente
 *
 * Lanca a excecao FicheiroInexistente se o ficheiro nao existir
 *
 * @param nome_ficheiro - nome do ficheiro de desportos
 */
	void updateDesportos(string nome_ficheiro);//<----------------------------------------
	/**Carrega as alteracoes ao vetor equipas para o ficheiro utilizado previamente
 *
 * Lanca a excecao FicheiroInexistente se o ficheiro nao existir
 *
 * @param nome_ficheiro - nome do ficheiro de equipas
	 */
	void updateEquipas(string nome_ficheiro);
	/**Carrega as alteracoes ao vetor modalidades para o ficheiro utilizado previamente
 *
 * Lanca a excecao FicheiroInexistente se o ficheiro nao existir
 *
 * @param nome_ficheiro - nome do ficheiro de modalidades
	 */
	void updateModalidades(string nome_ficheiro);
	/**Carrega as alteracoes ao vetor provas para o ficheiro utilizado previamente
 *
 * Lanca a excecao FicheiroInexistente se o ficheiro nao existir
 *
 * @param nome_ficheiro - nome do ficheiro de provas
	 */
	void updateProvas(string nome_ficheiro);

	void update();

/**Apaga a modalidade de nome n do vetor de desportos, modalidades e modalidades de atletas
 *
 * @param n - nome da modalidade
 */
	void apagaModalidade(string n);

	string getNome() const;
	Data getInicio() const;
	Data getFim() const;
	Hora getAbertura() const;
	Hora getFecho() const;
	vector<Desporto *> getDesportos() const;
	vector<Prova* > getProvas() const;
	vector<Equipa*> getEquipas() const;
	bool isCriado() const {return criado;}

	/**Menu na interface para apagar atributos no campeonato
	 *
	 * Na fase inicial, mostra as opcoes por onde escolher o que apagar (desporto, modalidade, etc)
	 * numa segunda fase mostra os dados especificos a apagar (lista de desportos, de modalidades, etc).
	 * O utilizador seleciona o que apagar
	 *
	 */
	void menuApagar();
	/**Menu na interface para apagar atributos no campeonato
		 *
		 * Na fase inicial, mostra as opcoes por onde escolher o que criar (desporto, modalidade, etc)
		 * numa segunda fase pede ao utilizador para introduzir os dados necessarios
		 *
		 */
	void menuCriacao();
	void menuDesportos();
	void menuEquipas();
	void menuProvas();
	void menuListas();
	void menuListasDesportos();
	void menuListasModalidades();
	void menuListasEquipas();
	void menuListasAtletas();
	void menuListasProvas();
	void Salvar();
/**Adiciona desporto ao vetor desportos do campeonato
 *
 * Lanca excepcao DesportoExiste se o desporto ja existir no vetor.
 *
 */
	void adicionaDesporto();
	/**Classe DesportoExiste
	 *
	 * Uma excecao para o caso de tentarmos adicionar um Desporto que ja exista no vetor desportos
	 *
	 */
	class DesportoExiste{
		string nome;
	public:
		/** Construtor default
		 *
		 */
		DesportoExiste(){};
		/** Construtor DesportoExiste
				 *
				 * @param n - nome do desporto que ja existe
				 */
		DesportoExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};

	void adicionaEquipa();
	void adicionaEquipa(Equipa &eq);
	/**Classe EquipaExiste
		 *
		 * Uma excecao para o caso de tentarmos adicionar uma Equipa que ja exista no vetor equipas
		 *
		 */
	class EquipaExiste{
		string nome;
	public:
		/** Construtor default
				 *
				 */
		EquipaExiste(){};
		/** Construtor EquipaExiste
						 *
						 * @param n - nome da equipa que ja existe
						 */
		EquipaExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};

	void adicionaProva();
	/**Classe DataInvalida
		 *
		 * Uma excecao para o caso de tentarmos criar uma Data fora dos limites do campeonato ou com dias/meses inexistentes
		 *
		 */
	class DataInvalida{
		Data data;
	public:
		/** Construtor default
				 *
				 */
		DataInvalida(){};
		/** Construtor DataInvalida
						 *
						 * @param d - Data que ja existe
						 */
		DataInvalida(Data d) {data = d;}
		Data getData() const {return data;}
	};
	/**Classe HoraInvalida
		 *
		 * Uma excecao para o caso de tentarmos criar uma Hora fora dos limites do campeonato ou com horas/minutos invalidos
		 *
		 */
	class HoraInvalida{
		Hora hora;
	public:
		/** Construtor default
				 *
				 */
		HoraInvalida(){};
		/** Construtor HoraInvalida
							 *
							 * @param h - Hora que ja existe
							 */
		HoraInvalida(Hora h) {hora = h;}
		Hora getHora() const {return hora;}
	};

	bool realizaProva(Prova & p, vector <float> pontuacoes);
	void listaDesportos() const;
	void listaProvasNaoRealizadas() const;
	void listaProvasRealizadas() const;
	void listaAtletas() const;
	void listaAtletasEquipa() const;
	void listaAtletasColocacao() const;
	void listaAtletasDesporto() const;
	void listaAtletasModalidade() const;
	void listaEquipasColocacao() const ;
};

void atribuiPontuacao(Prova pro, vector<float> pontos);


#endif /* CAMPEONATO_H_ */
