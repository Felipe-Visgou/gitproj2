#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: TAB Tabuleiro de Gamão
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: fvc
			tbm
*
*  $HA Histórico de evolução:
*     Versão  Autor			 Data		   Observações
*	  2		  fvc, tbm		 23/set/2015   Ajustes e Término do desenvolvimento	
*     1       fvc			 21/set/2015	início desenvolvimento
*
*  $ED Descrição do módulo
*		O módulo implementa um simples tabuleiro de gamão
*		e permite que peças sejam movimentadas pelo tabuleiro
*		sem nenhuma restrição nem regras do gamão.
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Tabuleiro
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK ,
               /* Concluiu corretamente */
		 TAB_CondRetErro,

		 TAB_CondRetFaltouMemoria,

   } TAB_tpCondRet ;




/***********************************************************************
*
*  $FC Função: TAB  &Criar Tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro inicializado com as peças
*	  pretas e brancas no lugar correto como no início
*	  de um jogo de gamão
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*
*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOK
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará TAB_CondRetErro
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTab,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: TAB  &Destruir Tabuleiro
*
*  $ED Descrição da função
*     Destrói o Tabuleiro dado
*
*  $FV Valor retornado
*     TAB_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTab ) ;


/***********************************************************************
*
*  $FC Função: TAB  &Mover Peça do Tabuleiro
*
*  $ED Descrição da função
*		Move a peça da casa de origem para a casa de destino.
*		As casas variam de 0 a 23.
*
*  $FV Valor retornado
*     TAB_CondRetOK    - Moveu sem problemas
*	  TAB_CondRetErro	   - Nao moveu a peça
*
***********************************************************************/

 TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro pTab, int casaOrigem, int casaDestino ) ;

/***********************************************************************/

 /*****************************************/
 TAB_tpCondRet TAB_ObterCasas(TAB_tppTabuleiro pTab, LIS_tppLista *casas);
 /******************************************/
#undef TABULEIRO_EXT

/********** Fim do módulo de definição: TAB Tabuleiro de Gamão **********/

#else
#endif