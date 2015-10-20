#if ! defined( BAR_ )
#define BAR_
/***************************************************************************
*
*  $MCD Módulo de definição: BAR  Lista de Peças Capturadas
*
*  Arquivo gerado:              BAR.h
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: fvc
			tbm
			db
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		1.0		fvc		18/10	  Começo da implementação
*
*  $ED Descrição do módulo
*     Implementa uma lista de peças do tabuleiro gamão.
*
***************************************************************************/
 
#if defined( BAR_OWN )
   #define BAR_EXT
#else
   #define BAR extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct BAR_tagCapturadas * BAR_tppCapturadas ;


/***********************************************************************
*
*  $TC Tipo de dados: BAR Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         BAR_CondRetOK ,
               /* Concluiu corretamente */

         BAR_CondRetVazia ,
               /* BAR não contém elementos */

		 BAR_CondRetErro,
				/* Não concluiu corretamente */

         BAR_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar a estrutura*/

   } BAR_tpCondRet ;

/***********************************************************************
*
*  $FC Função: BAR &Criar estrutura de peças capturadas
*
*  $ED Descrição da função
*     Cria uma estrutura para as peças capturadas do jogo de gamão
*
*  $EP Parâmetros
*	  pBAR  		- Ponteiro da estrutura de peças capturadas passada por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*		BAR_CondRetOk
*		BAR_CondRetFaltouMemoria
*
***********************************************************************/

   BAR_tpCondRet BAR_CriarBAR(BAR_tppCapturadas *pBAR, char cor,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Função: BAR Adicionar uma peça ao BAR
*
*  $ED Descrição da função
*		Adiciona uma peça à BAR
*
*  $EP Parâmetros
*	  PBar			- A BAR que será adicionada a peça

*  $FV Valor retornado
*		BAR_CondRetOk
*		BAR_CondRetErro
*
***********************************************************************/

   BAR_tpCondRet BAR_AdicionarPeca(BAR_tppCapturadas pBAR) ;

/***********************************************************************
*
*  $FC Função: BAR Remover uma peça ao BAR
*
*  $ED Descrição da função
*		Remover uma peça à BAR
*
*  $EP Parâmetros
*	  PBar			- A BAR que será removida a peça

*  $FV Valor retornado
*		BAR_CondRetOk
*		BAR_CondRetErro
*
***********************************************************************/

   BAR_tpCondRet BAR_RemoverPeca(BAR_tppCapturadas pBAR) ;

/***********************************************************************
*
*  $FC Função: BAR Obter tamanho da BAR
*
*  $ED Descrição da função
*		Obtem a quantidade de peças na BAR
*
*  $EP Parâmetros
*	  PBar			- A BAR que se deseja saber o tamanho
*	  *tam			- Ponteiro de referencia para o tamanho da BAR

*  $FV Valor retornado
*		BAR_CondRetOk
*		BAR_CondRetVazia
*		BAR_CondRetErro
*
***********************************************************************/

   BAR_tpCondRet BAR_ObterTamanhoBar(BAR_tppCapturadas pBAR, int *tam) ;

/***********************************************************************
*
*  $FC Função: BAR Obter Cor da BAR
*
*  $ED Descrição da função
*		Obtem a cor das peças da BAR
*
*  $EP Parâmetros
*	  PBar			- A BAR que se deseja saber a cor
	  *cor			- Cor esperada

*  $FV Valor retornado
*		BAR_CondRetOk
*		BAR_CondRetErro
*
***********************************************************************/

   BAR_tpCondRet BAR_ObterCorBar(BAR_tppCapturadas pBAR, char *cor) ;

#undef BAR_EXT

/********** Fim do módulo de definição: BAR  Lista de Peças Capturadas **********/

#else
#endif
