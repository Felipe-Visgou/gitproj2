/***************************************************************************
*  $MCI Módulo de implementação: TAB Tabuleiro de Gamão
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:		TTAB
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores:	fvc	- Felipe Vieira Cortes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão
*
*  $HA Histórico de evolução:
*     Versão  Autor		  Data     Observações
*	  2		  fvc, tbm 	23/set/2015 término do deselvolvimento
*     1       fvc, tbm	21/set/2015 início desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Matriz:
*
*     =criartabuleiro		<CondRet>		- Chama a função    TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTab, void   ( * ExcluirValor ) ( void * pDado ) ) ;
*	  =destruirtabuleiro	<CondRet>		- Chama a função  TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTab );
*     =moverpeca			<casaOrig> <CasaDest>	<CondRet>	 - Chama a função TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro pTab, int casaOrigem, int casaDestino ) ;
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>
#include    "TST_ESPC.H"
#include    "GENERICO.h"
#include    "lerparm.h"

#include	"TABULEIRO.H"

/* Tabela dos nomes dos comandos de teste específicos */
#define     CRIAR_TABULEIRO_CMD			"=criartabuleiro"
#define     DESTRUIR_TABULEIRO_CMD      "=destruirtabuleiro"
#define     MOVER_PECA_CMD				"=moverpeca"

TAB_tppTabuleiro Tab;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TTAB Efetuar operações de teste específicas para o Modulo Tabuleiro
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     de Tabuleiro de gamão.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int CondRetObtido   = TAB_CondRetOK ;
      int CondRetEsperada = TAB_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char corEsperada	= 'x';

      int  NumLidos = -1 ;
	  int i = 0;
	  int PosicaoReferencia, PosicaoFinal;
	
      /* Testar  Criar Tabuleiro */
         if ( strcmp( ComandoTeste , CRIAR_TABULEIRO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
									 &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = TAB_CriarTabuleiro(&Tab, DestruirValor);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar o tabuleiro." );

         } /* fim ativa: Testar Criar Tabuleiro */

		 /* Testar  Destruir Tabuleiro*/
		 else	if ( strcmp( ComandoTeste , DESTRUIR_TABULEIRO_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "i" ,
                              &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_DestruirTabuleiro(Tab) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir o tabuleiro" );
			
         } /* fim ativa: Testar destruir tabuleiro */

		/* Testar  Tabuleiro Mover Peca*/
		 else	if ( strcmp( ComandoTeste , MOVER_PECA_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "iii" ,
                             &PosicaoReferencia,&PosicaoFinal , &CondRetEsperada ) ;
            if ( NumLidos != 3)
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = TAB_MoverPeca(Tab,  PosicaoReferencia, PosicaoFinal ) ;

			return TST_CompararInt(CondRetObtido, CondRetEsperada, "Retorno errado ao mover a peca");

         } /* fim ativa: Testar  Tabuleiro Mover Peca */
      return TST_CondRetNaoConhec ;

   } /* Fim função: Tab Efetuar operações de teste específicas para Tabuleiro */

   /***********************************************************************
*
*  $FC Função: TTAB -Destruir valor
*
***********************************************************************/

void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TTAB-Destruir valor */