#if ! defined( BAR_ )
#define BAR_
/***************************************************************************
 *
 *  $MCD Modulo de definicao: BAR  Lista de Pecas Capturadas
 *
 *  Arquivo gerado:              BAR.h
 *  Letras identificadoras:      BAR
 *
 *  Nome da base de software:    Arcabouco para a automacao de testes de programas redigidos em C
 *
 *  Projeto: INF 1301 / 1628 Automatizacao dos testes de modulos C
 *  Gestor:  LES/DI/PUC-Rio
 *  Autores: fvc
             tbm
             db
 *
 *  $HA Historico de evolucao:
 *     Versao  Autor    Data     Observacoes
 *		1.0		fvc		18/10	  Comeco da implementacao
 *
 *  $ED Descricao do modulo
 *     Implementa uma lista de pecas do tabuleiro gamao.
 *
 ***************************************************************************/

#if defined( BAR_OWN )
#define BAR_EXT
#else
#define BAR extern
#endif

/***** Declaracoes exportadas pelo modulo *****/

/* Tipo referencia para uma lista */

typedef struct BAR_tagCapturadas * BAR_tppCapturadas;

/***********************************************************************
 *
 *  $TC Tipo de dados: BAR &Condicoes de retorno
 *
 *
 *  $ED Descricao do tipo
 *     Condicoes de retorno das funcoes da lista.
 *
 ***********************************************************************/

typedef enum {
    BAR_CondRetOK,
    /* Concluiu corretamente */

    BAR_CondRetVazia,
    /* BAR nao contem elementos */

    BAR_CondRetErro,
    /* Nao concluiu corretamente */

    BAR_CondRetFaltouMemoria
    /* Faltou memoria ao tentar criar a estrutura */

} BAR_tpCondRet;

/***********************************************************************
 *
 *  $FC Funcao: BAR &Criar estrutura de pecas capturadas
 *
 *  $ED Descrição da função
 *     Cria uma estrutura para as pecas capturadas do jogo de gamao.
 *
 *  $EP Parametros
 *     pBAR         - Ponteiro da estrutura de pecas capturadas passada por referencia.
 *     ExcluirValor - Ponteiro para a funcao que processa a exclusao do valor referenciado 
 *                    pelo elemento a ser excluido.
 *                    Ver descricao do modulo.
 *
 *  $FV Valor retornado
 *		BAR_CondRetOk
 *		BAR_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro de ponteiro que referencia uma estrutura de pecas capturadas passada por referencia, e do tipo BAR_tppCapturadas e aponta para uma posicao desconhecida de memoria.
 *     Existe uma variavel do tipo char que corresponde a cor da BAR.
 *     Existe um ponteiro para a funcao que processa a exclusao do valor referenciado pelo elemento a ser excluido. 
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A BAR e criada.
 *      - A cor da BAR corresponde ao valor do parametro cor.
 *      - O numero de elementos na BAR corresponde a 0.
 * 
 *     Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
 * 
 ***********************************************************************/

BAR_tpCondRet BAR_CriarBAR(BAR_tppCapturadas *pBAR, char cor,
        void ( * ExcluirValor) (void * pDado));

/***********************************************************************
 *
 *  $FC Funcao: BAR &Adicionar uma peca a BAR
 *
 *  $ED Descricao da funcao
 *		Adiciona uma peca a BAR.
 *
 *  $EP Parametros
 *	  PBar  - A BAR a qual sera adicionada uma peca.
 * 
 *  $FV Valor retornado
 *		BAR_CondRetOk
 *		BAR_CondRetErro
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro que referencia uma estrutura de pecas capturadas passada por referencia e aponta para uma posicao desconhecida de memoria.
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A peca e criada e adicionada a BAR.
 *      - O tamanho da BAR e incrementado de uma unidade.
 * 
 *     Caso haja erro na criacao da peca ou na insercao da mesma na BAR, e retornada a condicao de retorno correspondente a erro na execucao da funcao (BAR_CondRetErro).
 * 
 ***********************************************************************/

BAR_tpCondRet BAR_AdicionarPeca(BAR_tppCapturadas pBAR);

/***********************************************************************
 *
 *  $FC Funcao: BAR &Remover uma peca da BAR
 *
 *  $ED Descricao da funcao
 *		Remover uma peca da BAR.
 *
 *  $EP Parametros
 *	  PBar  - A BAR na qual sera removida uma peca.
 * 
 *  $FV Valor retornado
 *		BAR_CondRetOk
 *		BAR_CondRetErro
 * 
 *  $EAE Assertivas de Entrada 
 *     Existe um ponteiro que referencia uma estrutura de pecas capturadas passada por referencia e aponta para uma posicao desconhecida de memoria.
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A peca e excluida da BAR.
 *      - O tamanho da BAR e decrementado de uma unidade.
 * 
 *     Caso haja erro ao excluir a peca da lista (BAR), e retornada a condicao de retorno correspondente a erro na execucao da funcao (BAR_CondRetErro). 
 * 
 ***********************************************************************/

BAR_tpCondRet BAR_RemoverPeca(BAR_tppCapturadas pBAR);

/***********************************************************************
 *
 *  $FC Funcao: BAR &Obter tamanho da BAR
 *
 *  $ED Descricao da funcao
 *		Obtem a quantidade de peças na BAR.
 *
 *  $EP Parametros
 *	  PBar  - A BAR da qual se deseja saber o tamanho.
 *	  *tam  - Ponteiro de referencia para o tamanho da BAR.
 * 
 *  $FV Valor retornado
 *		BAR_CondRetOk
 *		BAR_CondRetVazia
 *		BAR_CondRetErro
 * 
 *  $EAE Assertivas de Entrada 
 *     Existe um ponteiro que referencia uma estrutura de pecas capturadas passada por referencia e aponta para uma posicao desconhecida de memoria.
 *     Existe um ponteiro de inteiro vazio. 
 *
 *  $EAE Assertivas de Saida
 *     Caso tenha executado corretamente, o tamanho da BAR e retornado no ponteiro int.
 * 
 *     Caso tam seja igual a NULL, e retornada a condicao de retorno correspondente a erro na execucao da funcao (BAR_CondRetErro). 
 * 
 *     Caso o numero inteiro referenciado pelo ponteiro tam seja igual a 0 (BAR vazia) e retornada a condicao de retorno correspondente. 
 * 
 ***********************************************************************/

BAR_tpCondRet BAR_ObterTamanhoBar(BAR_tppCapturadas pBAR, int *tam);

/***********************************************************************
 *
 *  $FC Funcao: BAR &Obter Cor da BAR
 *
 *  $ED Descricao da funcao
 *		Obtem a cor das peças da BAR.
 *
 *  $EP Parametros
 *	  PBar  - A BAR da qual se deseja saber a cor.
 *        cor   - Cor esperada.
 * 
 *  $FV Valor retornado
 *		BAR_CondRetOk
 *		BAR_CondRetErro
 *
 *  $EAE Assertivas de Entrada 
 *     Existe um ponteiro que referencia uma estrutura de pecas capturadas passada por referencia e aponta para uma posicao desconhecida de memoria.
 *     Existe um ponteiro de char vazio.
 * 
 *  $EAE Assertivas de Saida
 *     Caso tenha executado corretamente, a cor da BAR e retornada no ponteiro char.
 * 
 *     Caso cor seja igual a NULL, e retornada a condicao de retorno correspondente a erro na execucao da funcao (BAR_CondRetErro). 
 * 
 ***********************************************************************/

BAR_tpCondRet BAR_ObterCorBar(BAR_tppCapturadas pBAR, char *cor);

/********************************************************************/

#undef BAR_EXT

/********** Fim do modulo de definicao: BAR  Lista de Pecas Capturadas **********/

#else
#endif