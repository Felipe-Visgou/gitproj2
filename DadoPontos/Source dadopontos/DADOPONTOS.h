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
*  $FC Função: DADPnt &Criar Dado de Pontos
*
*  $ED Descrição da função
*	  Cria um novo dado de pontos.
* 
*  $FV Valor retonado
*     DADPnt_CondRetOK            - Dado de Pontos foi criado com sucesso.
*     DADPnt_CondRetFaltouMemoria - Dado de Pontos não foi criado por falta de memória.
* 
* $EAE Assertivas de Entrada
*  Existe um ponteiro para o Dado de Pontos criado que aponta para uma região desconhecida na memória. 
* 
* $EAS Assertivas de Saída
*  Caso tenha executado corretamente, é criado um novo Dado de Pontos.
*  Caso não haja memória suficiente, é retornada a condição de retorno correspondente.
* 
***********************************************************************/

DADPnt_tpCondRet DADPnt_CriarDado(tppDadoPontos * DadoCriado);

/***************************************************************************
*
*  $FC Função: DADPnt &Dobrar Dado de Pontos e Mudar "Dono" do Dado de Pontos
*
*  $ED Descrição da função
*	  Dobra o valor da partida e Muda o jogador que pode usar o Dado de Pontos.
* 
*  $FV Valor retonado
*     DADPnt_CondRetOK            - O valor da partida foi dobrado e o Dado de Pontos passou a pertencer ao jogador que dobrou a partida.
*     DADPnt_CondRetFaltouMemoria - O valor da partida não foi dobrado e o dono do Dado de Pontos não mudou.
* 
* $EAE Assertivas de Entrada
*  Existe uma variável do tipo tppDadoPontos que corresponde ao Dado de Pontos criado previamente.
*  Existe uma variável na qual guarda-se o caractere que correponde ao novo dono do Dado de Pontos. 
* 
* $EAS Assertivas de Saída
*  Caso tenha executado corretamente, o valor da partida armazenado no Dado de Pontos é dobrado e o Dado de Pontos passa a pertencer ao jogador que realizou o redobre.
*  Caso não haja memória suficiente, é retornada a condição de retorno correspondente.
*
***********************************************************************/

DADPnt_tpCondRet DADPnt_DobrarDado(tppDadoPontos DadoDobrar, char CorNovoDono);

/***************************************************************************
*
*  $FC Função: DADPnt Valor da partida
*
*  $ED Descrição da função
*	  Gera o valor atual da partida.
* 
*  $FV Valor retonado
*     DADPnt_CondRetOK - Obteve o valor atual da partida.
* 
* $EAE Assertivas de Entrada
*  Existe uma variável do tipo tppDadoPontos que corresponde ao Dado de Pontos.
*  Existe um ponteiro para o número inteiro correspondente ao valor da partida que aponta para uma região desconhecida na memória. 
* 
* $EAE Assertivas de Saída
*  O valor atual da partida é atribuído a *valorJogo.
* 
***********************************************************************/

DADPnt_tpCondRet DADPnt_ValorPartida(tppDadoPontos Dado, int * valorjogo);

/***************************************************************************
*
*  $FC Função: DADPnt &Obter "Dono" do dado de pontos atual
*
*  $ED Descrição da função
*	  Retorna o dono do Dado.
* 
*  $FV Valor retonado
*     DADPnt_CondRetOK - Obteve o dono atual do Dado de Pontos.
*
* $EAE Assertivas de Entrada
* 
* $EAE Assertivas de Saída
* 
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
