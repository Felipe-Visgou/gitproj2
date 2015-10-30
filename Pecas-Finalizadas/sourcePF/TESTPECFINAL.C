/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico

*	Módulo criado para operar com listas
*
*  Arquivo gerado:              TESTBAR.C
*  Letras identificadoras:      TBar
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores:	fvc	- Felipe Vieira Cortes
*			tbm - Tássio Borges de Miranda
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*		4.00   tbm	 23/10/2015  Módulo criado para operar com listas
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo peças finalizadas.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo BAR:

*	 =criarpf				<inxpec>	<cor>	<CondRet>		    - Chama a função BAR_tpCondRet BAR_CriarBAR() 
*	 =obtercorpf			<inxpec>	<cor Esperada> <CondRet>	- Chama a função BAR_tpCondRet BAR_AdicionarPeca(BAR_tppCapturadas pBAR)
*	 =obtertamanhopf		<inxpec>	<tamaho Esperado> <CondRet>	- Chama a função BAR_tpCondRet BAR_RemoverPeca(BAR_tppCapturadas pBAR)
*    =addpf					<inxpec>	<CondRet>					- Chama a função BAR_tpCondRet BAR_ObterCorBar(BAR_tppCapturadas pBAR, char *cor)
*	 =destruirpf			<inxpec>	<CondRet>					- Chama a função BAR_tpCondRet Bar_DestruirBar(BAR_tppCapturadas pBAR)
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include	"PecasFinalizadas.h"
#include	"LISTA.H"
#include	"GENERICO.H"
#include	"LERPARM.H"
#include	"PECA.h"
#include	"TST_ESPC.H"


/* Tabela dos nomes dos comandos de teste específicos */
#define		MAX 5
#define		DIM_VET_PF			2
#define     CRIAR_PF_CMD       "=criarpf"
#define     OBTER_COR_PF_CMD   "=obtercorpf"
#define		ADD_PF_CMD			"=addpf"
#define		OBTER_TAM_PF_CMD	"=obtertamanhopf"
#define		DESTRUIR_PF_CMD		"=destruirpf"

PF_tppFinalizadas PecFinal [DIM_VET_PF];

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

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

      int CondRetObtido   = PF_CondRetOK ;
      int CondRetEsperada = PF_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
	  char corEsperada	= 'x';
	  char corRecebida;
      int  NumLidos = -1 ;
	  int i = 0;
	  int inxpec, tamanhopf,tamanhopfresp;
	
	  TST_tpCondRet Ret;
	  TST_tpCondRet CondRet;
	
      /* Testar  Bar Criar Bar */
         if ( strcmp( ComandoTeste , CRIAR_PF_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici" ,&inxpec, &corRecebida,  &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

			if(inxpec > 5 || inxpec < 0) return TST_CondRetErro;

            CondRetObtido = PF_CriarPF(&PecFinal[inxpec],corRecebida,DestruirValor);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar BAR." );

         } /* fim ativa: Testar  BAR Criar BAr */

		/* Testar  Bar Obter cor da Bar */
		 else	if ( strcmp( ComandoTeste , OBTER_COR_PF_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "ici",&inxpec,&corEsperada, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			CondRetObtido = PF_ObterCorPF(PecFinal[inxpec],&corRecebida) ;

            Ret = TST_CompararChar( corRecebida , corEsperada ,
                         "Valor do elemento errado, diferente do esperado" ) ;

			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

			return TST_CompararChar(CondRetObtido, CondRetEsperada, "Retorno errado ao obter o cor do BAR.");

         } /* fim ativa: Testar  Bar Obter cor da Bar */

		 /* Testar  Bar AddBar */
		 else	if ( strcmp( ComandoTeste , ADD_PF_CMD ) == 0 )
         {

			NumLidos = LER_LerParametros( "ii" , &inxpec, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRetObtido = PF_AdicionarPecaPF(PecFinal[inxpec]) ;

			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter cor da BAR." );

         }
		 /*Fim da ativa: Testar Bar addbar*/

		 /* Testar obter tamanho BAR*/
		 else if( strcmp ( ComandoTeste , OBTER_TAM_PF_CMD) == 0)
		 {
			NumLidos = LER_LerParametros( "iii" , &inxpec,&tamanhopfresp, &CondRetEsperada);
			if ( NumLidos != 3 )
				return TST_CondRetParm;

			CondRetObtido = PF_ObterTamanhoPF(PecFinal[inxpec],&tamanhopf);

			CondRet = TST_CompararInt(tamanhopfresp,tamanhopf,"Tamanho do elemento errado, diferente do esperado");

			if ( CondRet != TST_CondRetOK )
				return CondRet;

			return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao obter tamanho bar.");
		 }
		 /*Fim da ativa: Testar Bar tamanhoBAR*/

		 /*Testar Destruir Bar*/

		 else if( strcmp ( ComandoTeste , DESTRUIR_PF_CMD) == 0)
		 {
			NumLidos = LER_LerParametros( "ii" , &inxpec, &CondRetEsperada);
			if ( NumLidos != 2 )
				return TST_CondRetParm;

			CondRetObtido = PF_DestruirPF(PecFinal[inxpec]);

			return TST_CompararInt( CondRetEsperada , CondRetObtido, "Retorno errado ao destruir BAR.");
		 }

		 /*Fim da ativa: Testar Destuir Bar*/
      return TST_CondRetNaoConhec ;
   } /* Fim função: TPec Efetuar operações de teste específicas para Peca */

void DestruirValor( void * pValor )
   {
      free( pValor ) ;
   }