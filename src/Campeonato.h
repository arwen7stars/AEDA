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
	Campeonato();
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
void loadDesportos(string nome_ficheiro);
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
void loadEquipas(string nome_ficheiro);
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
	void loadModalidades(string nome_ficheiro);
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
void loadProvas(string nome_ficheiro);
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
/**Update dos ficheiros originais com as alteracoes efetuadas aos atributos de campeonato
 *
 * Chama updateDesportos, updateEquipas, etc...
 *
 */
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
	void menuApagarDesportos();
	void menuApagarModalidades();
	void menuApagarEquipas();
	void menuApagarAtletas();
	void menuApagarProvas();
	/**Menu na interface para apagar atributos no campeonato
		 *
		 * Na fase inicial, mostra as opcoes por onde escolher o que criar (desporto, modalidade, etc)
		 * numa segunda fase pede ao utilizador para introduzir os dados necessarios
		 *
		 */
	void menuCriacao();
	/**Menu na interface para alterar atributos de um Desporto
	 *
	 * Mostra opcoes por onde escolher o que alterar, entre os atributos de um Desporto (modalidades, tipo de pontuacao, etc)
	 */
	void menuDesportos();
	/**Menu na interface para alterar atributos de uma Equipa
	 *
	 * Mostra opcoes por onde escolher o que alterar, entre os atributos de uma Equipa (atletas, provas, etc)
	 */
	void menuEquipas();
	/**Menu na interface para alterar atributos de uma Equipa
		 *
		 * Mostra opcoes por onde escolher o que alterar, entre os atributos de uma Prova (data, hora, etc)
		 */
	void menuProvas();
		/**Menu na interface para mostrar listas com os atributos do campeonato
		 *
		 * O utilizador pode escolher entre que listas quer ver, e serao mostradas mais opcoes de listas consoante a opcao
		 *
		 */
		void menuListas();
		/**Menu na interface para mostrar listas de desportos
		 *
		 * A unica opcao para listar desportos e por ordem alfabetica
		 *
		 */
		void menuListasDesportos();
		/**Menu na interface para mostrar listas de modalidades
			 *
			 * A unica opcao para listar modalidade e por ordem alfabetica
			 *
			 */
		void menuListasModalidades();
		/**Menu na interface para mostrar listas de equipas
			 *
			 * O utilizador pode escolher listar as equipas por ordem alfabetica ou por colocacao
			 *
			 */
		void menuListasEquipas();
		/**Menu na interface para mostrar listas de atletas
			 *
			 * O utilizador pode escolher listar os atletas por ordem alfabetica, ordem alfabetica dividida
			 * por desportos ou modalidades, e por colocacao
			 *
			 */
		void menuListasAtletas();
		/**Menu na interface para mostrar listas de provas
			 *
			 * O utilizador pode escolher listar as provas por ordem cronologica, divididas em provas realizadas
			 * e por realizar
			 *
			 */
		void menuListasProvas();
		/**Salva o estado do campeonatp
		 *
		 * chama update() para exportar os vetores atuais para os ficheiros correspondentes
		 *
		 */
		void Salvar();
		/**Verifica se o campeonato esta completamente importado
		 *
		 *Imprime mensagens de erro se nao houverem provas, equipas, atletas, etc
		 *Se estiver tudo correto, altera o membro dado "criado" para true
		 *
		 */
	void TerminarPlaneamento();
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
				 * @param n - nome do desporto que causou a excecao
				 */
		DesportoExiste(string n) {nome = n;}
		string getNome() const {return nome;}
	};
	/**Adiciona equipa ao vetor Equipas do campeonato
	 *
	 *Pede ao utilizador o nome da nova equipa. Se ja existir lanca a excecao EquipaExistente, caso contrario adiciona
	 *
	 */
	void adicionaEquipa();
	/**Adiciona a equipa fornecida ao vetor equipas, se ainda nao existir (criado para testes)
		 *
		 * @param eq - equipa a adicionar
		 */
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
						 * @param n - nome da equipa que causou a excecao
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
						 * @param d - Data que causou a excecao
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
							 * @param h - Hora que causou a excecao
							 */
		HoraInvalida(Hora h) {hora = h;}
		Hora getHora() const {return hora;}
	};
/**Converte Prova para ProvaTerminada
 *
 * Cria uma ProvaTerminada, chama atribuiPontuacoes e setAtletas, retira a Prova p do vetor provas e adiciona-lhe
 * a nova ProvaTerminada
 *
 * @param p - prova agora realizada
 * @param pontuacoes - vetor com as pontuacoes dos atletas, pela ordem que estao em Proa p
 * @return true se conseguiu adicionar, false se a p nao existir em provas
 */
	bool realizaProva(Prova & p, vector <float> pontuacoes);
	/**Lista no terminal os desportos no vetor desportos por ordem alfabetica
	 *
	 */
	void listaDesportos() const;
	/**Lista no terminal as ProvasTerminadas no vetor provas por ordem cronologica
		 *
		 */
	void listaProvasNaoRealizadas() const;
	/**Lista no terminal as Provas no vetor provas por ordem cronologica
	 *
	 */
	void listaProvasRealizadas() const;
	/**Lista no terminal os atletas no vetor equipas por ordem alfabetica
		 *
		 */
	void listaAtletas() const;
	/**Lista no terminal os atletas no vetor equipas por ordem alfabetica, divididos por Equipas
		 *
		 */
	void listaAtletasEquipa() const;
	/**Lista no terminal os atletas no vetor equipas por ordem decrescente de colocacao
		 *
		 */
	void listaAtletasColocacao() const;
	/**Lista no terminal os atletas no vetor equipas por ordem alfabetica, divididos por Desporto
		 *
		 */
	void listaAtletasDesporto() const;
	/**Lista no terminal os atletas no vetor equipas por ordem alfabetica, divididos por Modalidade
		 *
		 */
	void listaAtletasModalidade() const;
	/**Lista no terminal as equipas no vetor equipas por ordem decrescente de colocacao
		 *
		 */
	void listaEquipasColocacao() const ;
};

/**Atribui pontos aos atletas que venceram a Prova
 *
 * Ordena o vetor atleta da ProvaTerminada
 * Da 3 pontos ao atleta em 1o lugar, 2 pontos ao atleta em 2o lugar e 1 ponto ao atleta em 3o lugar
 * Preenche o vetor pontuacoes da ProvaTerminada com os resultados dos atletas, pela ordem do ranking
 *
 * @param pro - prova agora realizada
 * @param pontos - resultados da prova, em posicoes correspondentes a cada atleta
 */
void atribuiPontuacao(Prova pro, vector<float> pontos);


#endif /* CAMPEONATO_H_ */
