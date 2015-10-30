#if ! defined( PF_ )
#define PF_

/***************************************************************************
 *
 *  $MCD Modulo de definicao: PF  Lista de Pecas Finalizadas
 *
 *  Arquivo gerado:              PecasFinalizadas.h
 *  Letras identificadoras:      PF
 *
 *  Nome da base de software:    Arcabouço para a automacao de testes de programas redigidos em C
 *
 *  Projeto: INF 1301 / 1628 Automatizacao dos testes de modulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: fvc
            tbm
            db
 *
 *  $HA Historico de evolucao:
 *     Versao  Autor    Data     Observacos
 *		1.0		fvc		18/10	  Comeco da implementacao
 *
 *  $ED Descricao do modulo
 *     Implementa uma lista de pecas do tabuleiro gamao.
 *
 ***************************************************************************/

#if defined( PF_OWN )
#define PF_EXT
#else
#define PF extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para a estrutura de pecas finalizadas */

typedef struct PF_tagFinalizadas * PF_tppFinalizadas;

/***********************************************************************
 *
 *  $TC Tipo de dados: PF &Condições de retorno
 *
 *  $ED Descricao do tipo
 *     Condicoes de retorno das funcoes do modulo de pecas finalizadas.
 *
 ***********************************************************************/

typedef enum {
    PF_CondRetOK,
    /* Concluiu corretamente */

    PF_CondRetVazia,
    /* PF nao contem elementos */

    PF_CondRetErro,
    /* Nao concluiu corretamente */

    PF_CondRetFaltouMemoria
    /* Faltou memoria ao tentar criar a estrutura */

} PF_tpCondRet;

/***********************************************************************
 *
 *  $FC Funcao: PF &Criar estrutura de pecas finalizadas
 * 
 *  $ED Descricao da funcao
 *     Cria uma estrutura para as pecas finalizadas do jogo de gamao.
 *
 *  $EP Parametros
 *     pPF           - Ponteiro da estrutura de pecas finalizadas passada por referencia.
 *     ExcluirValor  - Ponteiro para a funcao que processa a exclusao do valor referenciado 
 *                     pelo elemento a ser excluido.
 *                     Ver descricao do modulo.
 *
 *  $FV Valor retornado
 *		PF_CondRetOk
 *		PF_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro de ponteiro que referencia uma estrutura de pecas finalizadas passada por referencia, e do tipo PF_tppFinalizadas e aponta para uma posicao desconhecida de memoria.
 *     Existe uma variavel do tipo char que corresponde a cor das pecas finalizadas da estrutura de pecas finalizadas criada.
 *     Existe um ponteiro para a funcao que processa a exclusao do valor referenciado pelo elemento a ser excluido. 
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A estrutura de pecas finalizadas e criada.
 *      - A cor da estrutura de pecas finalizadas corresponde ao valor do parametro cor.
 *      - O numero de elementos na estrutura de pecas finalizadas corresponde a 0.
 * 
 *     Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
 * 
 ***********************************************************************/

PF_tpCondRet PF_CriarPF(PF_tppFinalizadas *pPF, char cor,
        void ( * ExcluirValor) (void * pDado));

/***********************************************************************
 *
 *  $FC Funcao: PF &Adicionar uma peca ao PF
 *
 *  $ED Descricao da funcao
 *		Adiciona uma peca a lista de pecas finalizadas
 *
 *  $EP Parametros
 *	  pPF   - A estrutura na qual sera adicionada a peca.
 * 
 *  $FV Valor retornado
 *		PF_CondRetOk
 *		PF_CondRetErro
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro que referencia uma estrutura de pecas finalizadas passada por referencia, e do tipo PF_tppFinalizadas e aponta para uma posicao desconhecida de memoria.
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A peca finalizada e criada e adicionada a PF.
 *      - O tamanho da PF e incrementado de uma unidade.
 * 
 *     Caso haja erro na criacao da peca finalizada ou na insercao da mesma na PF, e retornada a condicao de retorno correspondente a erro na execucao da funcao (PF_CondRetErro).
 * 
 ***********************************************************************/

PF_tpCondRet PF_AdicionarPecaPF(PF_tppFinalizadas pPF);

/***********************************************************************
 *
 *  $FC Funcao: PF &Obter tamanho da lista de pecas finalizadas
 *
 *  $ED Descricao da funcao
 *		Obtem a quantidade de pecas na lista.
 *
 *  $EP Parâmetros
 *	  pPF   - A estrutura da qual se deseja saber o tamanho.
 *	  *tam  - Ponteiro de referencia para o tamanho da PF.
 * 
 *  $FV Valor retornado
 *		PF_CondRetOk
 *		PF_CondRetVazia
 *		PF_CondRetErro
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro que referencia uma estrutura de pecas finalizadas passada por referencia, e do tipo PF_tppFinalizadas e aponta para uma posicao desconhecida de memoria.
 *     Existe um ponteiro de int vazio.
 * 
 *  $EAE Assertivas de Saida
 *     Caso tenha executado corretamente, o tamanho da PF e retornado no ponteiro int.
 * 
 *     Caso tam seja igual a NULL, e retornada a condicao de retorno correspondente a erro na execucao da funcao (PF_CondRetErro). 
 * 
 *     Caso o numero inteiro referenciado pelo ponteiro tam seja igual a 0 (PF vazia) e retornada a condicao de retorno correspondente. 
 * 
 ***********************************************************************/

PF_tpCondRet PF_ObterTamanhoPF(PF_tppFinalizadas pPF, int *tam);

/***********************************************************************
 *
 *  $FC Funcao: PF Obter Cor da PF
 *
 *  $ED Descricao da funcao
 *		Obtem a cor das pecas da PF.
 *
 *  $EP Parametros
 *	  pPF   - A PF da qual se deseja saber a cor.
 *        cor   - Cor esperada.
 * 
 *  $FV Valor retornado
 *		PF_CondRetOk
 *		PF_CondRetErro
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro que referencia uma estrutura de pecas finalizadas passada por referencia, e do tipo PF_tppFinalizadas e aponta para uma posicao desconhecida de memoria.
 *     Existe um ponteiro de char vazio.
 * 
 *  $EAE Assertivas de Saida
 *     Caso tenha executado corretamente, a cor da PF e retornado no ponteiro char.
 * 
 *     Caso cor seja igual a NULL, e retornada a condicao de retorno correspondente a erro na execucao da funcao (PF_CondRetErro). 
 * 
 ***********************************************************************/

PF_tpCondRet PF_ObterCorPF(PF_tppFinalizadas pPF, char *cor);

/***********************************************************************
*
*  $FC Função: PF Destruir PF
*
*  $ED Descrição da função
*		Destroi a lista de peças finalizadas
*
*  $EP Parâmetros
*	  pPF		    - A PF que se deseja destruir
*  $FV Valor retornado
*		PF_CondRetOk
*		PF_CondRetErro
* 
*  $EAE Assertivas de Entrada
*     Existe um ponteiro que referencia uma estrutura de pecas finalizadas passada por referencia, e do tipo PF_tppFinalizadas e aponta para uma posicao desconhecida de memoria.
* 
*  $EAE Assertivas de Saida
*     Caso tenha executado corretamente o endereço da estrutura é desalocado da memória principal
* 
***********************************************************************/

PF_tpCondRet PF_DestruirPF(PF_tppFinalizadas pPF);

#undef PF_EXT

/********** Fim do modulo de definicao: PF  Lista de Pecas Finalizadas **********/

#else
#endif