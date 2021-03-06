#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: TAB Tabuleiro de Gam�o
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: fvc
			tbm
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor			 Data		   Observa��es
*	  2		  fvc, tbm		 23/set/2015   Ajustes e T�rmino do desenvolvimento	
*     1       fvc			 21/set/2015	in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*		O m�dulo implementa um simples tabuleiro de gam�o
*		e permite que pe�as sejam movimentadas pelo tabuleiro
*		sem nenhuma restri��o nem regras do gam�o.
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do Tabuleiro
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
*  $FC Fun��o: TAB  &Criar Tabuleiro
*
*  $ED Descri��o da fun��o
*     Cria um tabuleiro inicializado com as pe�as
*	  pretas e brancas no lugar correto como no in�cio
*	  de um jogo de gam�o
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*
*  $FV Valor retornado
*     Se executou corretamente retorna TAB_CondRetOK
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� TAB_CondRetErro
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTab,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: TAB  &Destruir Tabuleiro
*
*  $ED Descri��o da fun��o
*     Destr�i o Tabuleiro dado
*
*  $FV Valor retornado
*     TAB_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

   TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTab ) ;


/***********************************************************************
*
*  $FC Fun��o: TAB  &Mover Pe�a do Tabuleiro
*
*  $ED Descri��o da fun��o
*		Move a pe�a da casa de origem para a casa de destino.
*		As casas variam de 0 a 23.
*
*  $FV Valor retornado
*     TAB_CondRetOK    - Moveu sem problemas
*	  TAB_CondRetErro	   - Nao moveu a pe�a
*
***********************************************************************/

 TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro pTab, int casaOrigem, int casaDestino ) ;

 /***************************************************************************
*
*  $FC Fun��o: TAB Obter Casas
*
*  $ED Descri��o da fun��o
*		Retorna para o ponteiro casa o endere�o da casa do tabuleiro, apontado
*	pelo tabuleiro dado como parametro.
*
*  $FV Valor retornado
*     TAB_CondRetOK		   - Obteve  sem problemas
*	  TAB_CondRetErro	   - Nao moveu a pe�a
*
*  ****/

TAB_tpCondRet TAB_ObterCasas(TAB_tppTabuleiro pTab, LIS_tppLista *casas) ;

#undef TABULEIRO_EXT

/********** Fim do m�dulo de defini��o: TAB Tabuleiro de Gam�o **********/

#else
#endif