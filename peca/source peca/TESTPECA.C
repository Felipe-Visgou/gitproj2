/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico

*	M�dulo modificado para operar matrizes que armazenam listas!
*
*  Arquivo gerado:              TESTPECA.C
*  Letras identificadoras:      TPec
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores:	fvc	- Felipe Vieira Cortes
*			tbm - T�ssio Borges de Miranda
*			db  - Daniela Braz�o
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
		4.00   fvc	 23/08/2015 M�dulo modificado para operar matrizes
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo Peca.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo Matriz:
*
*     =criarpeca		<inxpec>	<cor>	<CondRet>				- Chama a fun��o Pec_tpCondRet Pec_CriarPeca(tppPeca * PecCriado);
*	  =destruirpeca		<inxpec>	<CondRet>							  - Chama a fun��o Pec_tpCondRet Pec_DestruirPeca(tppPeca  Peca);
*     =obtercorpeca		<inxpec>	<cor Esperada> <CondRet	>			 - Chama a fun��o Pec_tpCondRet Pec_ObterCor(tppPeca  Peca, char *cor);
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"
#include	"PECA.h"


/* Tabela dos nomes dos comandos de teste espec�ficos */
#define MAX 5
#define     CRIAR_PECA_CMD     "=criarpeca"
#define     DESTRUIR_PECA_CMD    "=destruirpeca"
#define     OBTER_COR_CMD     "=obtercorpeca"

tppPeca P[MAX];
/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TPec Efetuar opera��es de teste espec�ficas para o Modulo Peca
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     Peca sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int CondRetObtido   = Pec_CondRetOK ;
      int CondRetEsperada = Pec_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char corEsperada	= 'x';

      int  NumLidos = -1 ;
	  int i = 0;
	  char corRecebida;
	  int inxpec;
	
	  TST_tpCondRet Ret;
	
      /* Testar  Pec Criar Peca */
         if ( strcmp( ComandoTeste , CRIAR_PECA_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,
                             &inxpec, &corRecebida,  &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			if(inxpec > 5 || inxpec < 0) return TST_CondRetErro;

            CondRetObtido = Pec_CriarPeca(&P[inxpec], corRecebida);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar a peca." );

         } /* fim ativa: Testar  Pec Criar Peca */

		 /* Testar  Pec Destruir Peca */
		 else	if ( strcmp( ComandoTeste , DESTRUIR_PECA_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "ii" ,
                              &inxpec, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = Pec_DestruirPeca(P[inxpec]) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir a peca." );

         } /* fim ativa: Testar  Pec Destruir Peca */

		/* Testar  Pec Obter cor da Peca */
		 else	if ( strcmp( ComandoTeste , OBTER_COR_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "ici" ,
                              &inxpec,&corEsperada, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = Pec_ObterCor(P[inxpec], &corRecebida) ;

            Ret = TST_CompararChar( corRecebida , corEsperada ,
                         "Valor do elemento errado, diferente do esperado" ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararChar(CondRetObtido, CondRetEsperada, "Retorno errado ao obter o valor da peca");

         } /* fim ativa: Testar  Pec Obter cor da Peca */
      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TPec Efetuar opera��es de teste espec�ficas para Peca */