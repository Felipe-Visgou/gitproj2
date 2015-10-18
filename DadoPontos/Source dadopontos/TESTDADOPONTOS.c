/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico

*	Módulo modificado para operar matrizes que armazenam listas!
*
*  Arquivo gerado:              TESTDADOPONTOS.C
*  Letras identificadoras:      TDADPnt
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: 
			fvc	- Felipe Vieira Cortes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão

*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
		4.00   tbm	 23/08/2015 Módulo modificado para operar dadospontos
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Matriz:
*
*     =criardadoponto		<CondRet>				- Chama a função DADPnt_tpCondRet DADPnt_CriarDado(tppDadoPontos * DadoCriado);
*	  =destruirdadoponto	<CondRet>							  - Chama a função DADPnt_tpCondRet DADPnt_DestruirDado(tppDadoPontos Dado);
*     =obtervalorjogo		<valor Esperado>	<CondRet>		- Chama a função DADPnt_tpCondRet DADPnt_ValorPartida(tppDadoPontos Dado, int * valorjogo);
*	  =dobrardado			<cor>	<CondRet>	- Chama a função DADPnt_tpCondRet DADPnt_DobrarDado(tppDadoPontos DadoDobrar, char CorNovoDono);
*	  =obterdono			<cor esperada>		<CondRet>  - B Chama a função DADPnt_tpCondRet DADPnt_ObterDono(tppDadoPontos Dado, char * corRecebida);
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "lerparm.h"
#include	"DADOPONTOS.h"

/* Tabela dos nomes dos comandos de teste específicos */
#define MAX 5
#define     CRIAR_DADOPONTOS_CMD		"=criardadopontos"
#define     DESTRUIR_DADOPONTOS_CMD		"=destruirdadoponto"
#define     OBTER_VALORPARTIDA_CMD	    "=obtervalorpartida"
#define		DOBRAR_DADO_CMD				"=dobrardado"
#define		OBTER_DONO_CMD				"=obterdono"


tppDadoPontos DadoPnt;
/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TDADPnt Efetuar operações de teste específicas para o Modulo DadoPontos
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     DadoPontos sendo testado.
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

      int CondRetObtido   = DADPnt_CondRetOK ;
      int CondRetEsperada = DADPnt_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char corEsperada	= 'x';

      int  NumLidos = -1 ;
	  int i = 0;
	  int ValorPontos,valoresperado;
	  char corRecebida;
	
	  TST_tpCondRet Ret;
	
      /* Testar  TDADPnt &Criar Dado Pontos */
         if ( strcmp( ComandoTeste , CRIAR_DADOPONTOS_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
								&CondRetEsperada ) ;
            if ( NumLidos != 1)
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DADPnt_CriarDado(&DadoPnt);


            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar ao criar dadopontos." );

         } 
		 /* fim ativa: Testar  Criar Dado Pontos */

		 /* Testar  TDADPnt &Destruir DadoPontos */
		 else	if ( strcmp( ComandoTeste , DESTRUIR_DADOPONTOS_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "i" ,
									 &CondRetEsperada ) ;
            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = DADPnt_DestruirDado(DadoPnt) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir o dadopontos." );

         }
		/* fim ativa: Testar DadoPontos Destruir*/

		/* Testar TDADPnt &Obter Dono do DadoPonto */
		 else	if ( strcmp( ComandoTeste , OBTER_DONO_CMD	 ) == 0 )
         {

			NumLidos = LER_LerParametros( "ci" ,
								 &corEsperada ,&CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = DADPnt_ObterDono(DadoPnt,&corRecebida) ;

            Ret = TST_CompararChar( corRecebida , corEsperada ,
                         "Cor do jogador errado, diferente do esperado" ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararChar(CondRetObtido, CondRetEsperada, "Retorno errado ao obter o dono do dado");

         }
		 /* fim ativa: Testar Obter Dono do DadoPonto*/

		 /* Testar TDADPnt &Dadoponto DobrarDado */
         else if ( strcmp( ComandoTeste , DOBRAR_DADO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ci" ,
								&corEsperada, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DADPnt_DobrarDado(DadoPnt, corEsperada );

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao dobrar o valor do dadopontos." );

         } /* fim ativa: Fim Dobrar Dado */

		 /* Testar TDADPnt &Dadoponto Obter Valor */
         else if ( strcmp( ComandoTeste , OBTER_VALORPARTIDA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
								&valoresperado, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = DADPnt_ValorPartida(DadoPnt,&ValorPontos);

		    Ret = TST_CompararInt( valoresperado , ValorPontos , " Valor da Partida Errado" ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } 

            return TST_CompararInt( CondRetObtido, CondRetEsperada ,
                                    "Retorno errado ao obter valor do dado pontos." );

         } /* fim ativa: Fim Dobrar Dado */


      return TST_CondRetNaoConhec ;

   } /* Fim função: TDADPnt Efetuar operações de teste específicas para DadoPonto */