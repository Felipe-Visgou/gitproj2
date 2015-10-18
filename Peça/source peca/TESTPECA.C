/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico

*	Módulo modificado para operar matrizes que armazenam listas!
*
*  Arquivo gerado:              TESTPECA.C
*  Letras identificadoras:      TPec
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
*     Versão  Autor    Data     Observações
		4.00   fvc	 23/08/2015 Módulo modificado para operar matrizes
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Peca.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Matriz:
*
*     =criarpeca		<inxpec>	<cor>	<CondRet>				- Chama a função Pec_tpCondRet Pec_CriarPeca(tppPeca * PecCriado);
*	  =destruirpeca		<inxpec>	<CondRet>							  - Chama a função Pec_tpCondRet Pec_DestruirPeca(tppPeca  Peca);
*     =obtercorpeca		<inxpec>	<cor Esperada> <CondRet	>			 - Chama a função Pec_tpCondRet Pec_ObterCor(tppPeca  Peca, char *cor);
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"
#include	"PECA.h"


/* Tabela dos nomes dos comandos de teste específicos */
#define MAX 5
#define     CRIAR_PECA_CMD     "=criarpeca"
#define     DESTRUIR_PECA_CMD    "=destruirpeca"
#define     OBTER_COR_CMD     "=obtercorpeca"

tppPeca P[MAX];
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPec Efetuar operações de teste específicas para o Modulo Peca
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     Peca sendo testado.
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

   } /* Fim função: TPec Efetuar operações de teste específicas para Peca */