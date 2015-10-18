#if ! defined( PF_ )
#define PF_
/***************************************************************************
*
*  $MCD Módulo de definição: OF  Lista de Peças Finalizadas
*
*  Arquivo gerado:              PecasFinalizadas.h
*  Letras identificadoras:      PF
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
 
#if defined( PF_OWN )
   #define PF_EXT
#else
   #define PF extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para a estrutura de pecas finalizadas */

typedef struct PF_tagFinalizadas * PF_tppFinalizadas;


/***********************************************************************
*
*  $TC Tipo de dados: PF Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo de peças Finalizadas
*
***********************************************************************/

   typedef enum {

         PF_CondRetOK ,
               /* Concluiu corretamente */

         PF_CondRetVazia ,
               /* PF não contém elementos */

		 PF_CondRetErro,
				/* Não concluiu corretamente */

         PF_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar a estrutura*/

   } PF_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PF &Criar estrutura de peças Finalizadas

*  $ED Descrição da função
*     Cria uma estrutura para as peças Finalizadas do jogo de gamão
*
*  $EP Parâmetros
*	  pPF		- Ponteiro da estrutura de peças finalizadas passada por referência
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*		PF_CondRetOk
*		PF_CondRetFaltouMemoria
*
***********************************************************************/

   PF_tpCondRet PF_CriarPF(PF_tppFinalizadas *pPF, char cor,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;

/***********************************************************************
*
*  $FC Função: PF Adicionar uma peça ao PF
*
*  $ED Descrição da função
*		Adiciona uma peça a lista de peças finalizadas
*
*  $EP Parâmetros
*	  pPF			- A estrutura que será adicionada a peça

*  $FV Valor retornado
*		PF_CondRetOk
*		PF_CondRetErro
*
***********************************************************************/

   PF_tpCondRet PF_AdicionarPeca(PF_tppFinalizadas pPF) ;

/***********************************************************************
*
*  $FC Função: PF Obter tamanho da lista de peças finalizadas
*
*  $ED Descrição da função
*		Obtem a quantidade de peças na lista
*
*  $EP Parâmetros
*	  pPF			- A estrutura que se deseja saber o tamanho
*	  *tam			- Ponteiro de referencia para o tamanho da PF

*  $FV Valor retornado
*		PF_CondRetOk
*		PF_CondRetVazia
*		PF_CondRetErro
*
***********************************************************************/

   PF_tpCondRet PF_ObterTamanho(PF_tppFinalizadas pPF, int *tam) ;

/***********************************************************************
*
*  $FC Função: PF Obter Cor da PF
*
*  $ED Descrição da função
*		Obtem a cor das peças da PF
*
*  $EP Parâmetros
*	  pPF		    - A PF que se deseja saber a cor
	  *cor			- Cor esperada

*  $FV Valor retornado
*		PF_CondRetOk
*		PF_CondRetErro
*
***********************************************************************/

   PF_tpCondRet PF_ObterCor(PF_tppFinalizadas pPF, char *cor) ;

#undef PF_EXT

/********** Fim do módulo de definição: PF  Lista de Peças Finalizadas **********/

#else
#endif
