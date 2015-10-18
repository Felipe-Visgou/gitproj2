/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTDADO.C
*  Letras identificadoras:      TDADO
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: fvc	- Felipe Vieira Cortes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
		1.00   fvc	 14/09/2015 Início e término do deselvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Dados, que gera um número aleatório de 1 a 6
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Matriz:
*
*     =jogardado		chama a função DAD_tpCondRet DAD_NumPular(int* NumPular) e retorna um valor inteiro de 1 a 6 e imprime na tela
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"
#include	"DADO.H"


/* Tabela dos nomes dos comandos de teste específicos */

#define     JOGAR_DADO_CMD     "=jogardado"

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TDADO Efetuar operações de teste específicas para um dado de 6 faces
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     Matriz sendo testado.
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

      int CondRetObtido   = DAD_CondRetOK ;
      int CondRetEsperada = DAD_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;

      int  NumLidos = -1 ;
	  int i = 0;
	  int valorDado;
      /* Testar DADO Jogar Dado */

         if ( strcmp( ComandoTeste , JOGAR_DADO_CMD ) == 0 )
         {

            if ( NumLidos != -1 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = DAD_NumPular(&valorDado) ;

			printf(" \n dado: %d\n", valorDado);

            return TST_CondRetOK;

         } /* fim ativa: Testar DADO Jogar Dado */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TDADO Efetuar operações de teste específicas para um dado de 6 faces*/