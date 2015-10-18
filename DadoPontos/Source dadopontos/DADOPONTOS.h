/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Dado
*
*  Arquivo gerado:              DadoPontos.H
*  Letras identificadoras:      DADPnt
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: fvc - Felipe Vieira Côrtes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão

*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tbm   05/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para verificar o
*	  valor atual da partida e qual jogador pode utilizar o dado.
*
***************************************************************************/
 
#if defined( DADOPONTOS_OWN )
   #define DADOPONTOS_EXT
#else
   #define DADOPONTOS_EXT extern
#endif

#include "Generico.h"

typedef struct tgDadoPontos * tppDadoPontos;
typedef struct tgPlayers * tppPlayers;
/***********************************************************************
*
*  $TC Tipo de dados: DADPnt Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         DADPnt_CondRetOK = 0 ,
               /* Executou correto */

         DADPnt_CondRetErro = 1 ,
               /* Estrutura do DadoPontos está errada */

         DADPnt_CondRetDadoPontosNaoExiste = 2 ,
               /* DadoPontos não existe */

         DADPnt_CondRetFaltouMemoria = 3
               /* Faltou memória ao alocar dados */

   } DADPnt_tpCondRet ;


/***********************************************************************
*
*  $FC Função: DADPnt Criar Dado de Pontos
*
*  $ED Descrição da função
*	  Cria um novo dado de pontos
*  $FV Valor retonado
*     DADPnt_CondRetOK
*     DADPnt_CondRetFaltouMemoria
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_CriarDado(tppDadoPontos * DadoCriado);

/***************************************************************************
*
*  $FC Função: DADPnt Dobrar Dado de Pontos e Mudar "Dono" do Dado de Pontos
*
*  $ED Descrição da função
*	  Dobra o valor da partida e Muda o jogador que possa usar o Dado de Pontos
*  $FV Valor retonado
*     DADPnt_CondRetOK
*     DADPnt_CondRetFaltouMemoria
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_DobrarDado(tppDadoPontos DadoDobrar, char CorNovoDono);

/***************************************************************************
*
*  $FC Função: DADPnt Valor da partida
*
*  $ED Descrição da função
*	  Gera o valor atual da partida
*  $FV Valor retonado
*     DADPnt_CondRetOK
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_ValorPartida(tppDadoPontos Dado, int * valorjogo);

/***************************************************************************
*
*  $FC Função: DADPnt Obter "Dono" do dado de pontos atual
*
*  $ED Descrição da função
*	  Retorno o dono do Dado
*  $FV Valor retonado
*     DADPnt_CondRetOK
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_ObterDono(tppDadoPontos Dado, char * corRecebida);

/***************************************************************************
*
*  $FC Função: DADPnt Destroi o Dado de Pontos
*
*  $ED Descrição da função
*	  Destroi o Dado de Pontos
*  $FV Valor retonado
*     DADPnt_CondRetOK
*     DADPnt_CondRetFaltouMemoria
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_DestruirDado(tppDadoPontos Dado);

#undef DADOPONTOS_EXT

/*************** Fim do módulo de definição: Módulo DadoPontos ****************/
