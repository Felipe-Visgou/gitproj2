/***************************************************************************
 *
 *  $MCD Modulo de definicao: Modulo Dado
 *
 *  Arquivo gerado:              DadoPontos.H
 *  Letras identificadoras:      DADPnt
 *
 *  Nome da base de software:    Exemplo de teste automatizado
 *
 *  Projeto: Disciplinas INF 1628 / 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores: fvc - Felipe Vieira Cortes
 *           tbm - Tassio Borges de Miranda
 *           db  - Daniela Brazao
 *
 *  $HA Historico de evolucao:
 *     Versao  Autor    Data     Observacoes
 *       1.00   tbm   05/09/2015 Inicio do desenvolvimento
 *
 *  $ED Descricao do modulo
 *     Este modulo implementa um conjunto simples de funcoes para verificar o
 *     valor atual da partida e qual jogador pode utilizar o dado.
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
 *  $TC Tipo de dados: DADPnt &Condicoes de retorno
 *
 ***********************************************************************/

typedef enum {
    DADPnt_CondRetOK = 0,
    /* Executou corretamente */

    DADPnt_CondRetErro = 1,
    /* Estrutura do DadoPontos esta errada */

    DADPnt_CondRetDadoPontosNaoExiste = 2,
    /* DadoPontos nao existe */

    DADPnt_CondRetFaltouMemoria = 3
    /* Faltou memoria ao alocar dados */

} DADPnt_tpCondRet;

/***********************************************************************
 *
 *  $FC Funcao: DADPnt &Criar Dado de Pontos
 *
 *  $ED Descricao da funcao
 *	  Cria um novo dado de pontos.
 * 
 *  $FV Valor retonado
 *     DADPnt_CondRetOK            - Dado de Pontos foi criado com sucesso.
 *     DADPnt_CondRetFaltouMemoria - Dado de Pontos nao foi criado por falta de memoria.
 * 
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro do tipo tppDadoPontos que referencia o Dado de Pontos criado e aponta para uma posicao desconhecida de memoria. 
 * 
 *  $EAS Assertivas de Saida
 *   Caso tenha executado corretamente, um novo Dado de Pontos e criado.
 * 
 *   Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
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
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro do tipo tppDadoPontos que referencia o Dado de Pontos criado e aponta para uma posicao desconhecida de memoria. 
 *   Existe uma variavel que contem o caractere que correponde ao novo dono do Dado de Pontos. 
 * 
 *  $EAS Assertivas de Saida
 *   Caso tenha executado corretamente, o valor da partida armazenado no Dado de Pontos e dobrado e o mesmo passa a pertencer ao jogador que realizou o redobre.
 *  
 *   Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
 *
 ***********************************************************************/

DADPnt_tpCondRet DADPnt_DobrarDado(tppDadoPontos DadoDobrar, char CorNovoDono);

/***************************************************************************
 *
 *  $FC Função: DADPnt &Valor da partida
 *
 *  $ED Descrição da funcao
 *	  Gera o valor atual da partida.
 * 
 *  $FV Valor retonado
 *     DADPnt_CondRetOK - Obteve o valor atual da partida.
 * 
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro do tipo tppDadoPontos que referencia o Dado de Pontos criado e aponta para uma posicao desconhecida de memoria. 
 *   Existe um ponteiro de inteiro vazio. 
 * 
 *  $EAE Assertivas de Saida
 *   Caso tenha executado corretamente, o valor atual da partida e retornado no ponteiro de int.
 * 
 ***********************************************************************/

DADPnt_tpCondRet DADPnt_ValorPartida(tppDadoPontos Dado, int * valorjogo);

/***************************************************************************
 *
 *  $FC Funcao: DADPnt &Obter "Dono" do dado de pontos atual
 *
 *  $ED Descricao da funcao
 *	  Retorna o dono do Dado.
 * 
 *  $FV Valor retonado
 *     DADPnt_CondRetOK - Obteve o dono atual do Dado de Pontos.
 *
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro do tipo tppDadoPontos que referencia o Dado de Pontos criado e aponta para uma posicao desconhecida de memoria. 
 *   Existe um ponteiro de char vazio. 
 * 
 *  $EAE Assertivas de Saida
 *   Caso tenha executado corretamente, a cor do dono atual do Dado de Pontos e retornada no ponteiro de char.
 * 
 ***********************************************************************/

DADPnt_tpCondRet DADPnt_ObterDono(tppDadoPontos Dado, char * corRecebida);

/***************************************************************************
 *
 *  $FC Funcao: DADPnt &Destroi o Dado de Pontos
 *
 *  $ED Descricao da funcao
 *	  Destroi o Dado de Pontos.
 * 
 *  $FV Valor retonado
 *     DADPnt_CondRetOK
 *     DADPnt_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro do tipo tppDadoPontos que referencia o Dado de Pontos criado e aponta para uma posicao desconhecida de memoria. 
 * 
 *  $EAE Assertivas de Saida
 *   Caso tenha executado corretamente, a memoria alocada dinamicamente para o Dado de Pontos e liberada.
 *
 *   Caso o Dado de Pontos nao exista (Dado igual a NULL), e retornada a condicao de retorno correspondente.
 * 
 ***********************************************************************/

DADPnt_tpCondRet DADPnt_DestruirDado(tppDadoPontos Dado);

#undef DADOPONTOS_EXT

/*************** Fim do modulo de definicao: Modulo DadoPontos ****************/