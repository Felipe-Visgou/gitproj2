/***************************************************************************
*  $MCI Módulo de implementação: Gerador de numeroes aleatorios restrito ao
*								 numero de faces 
*
*  Arquivo gerado:              DADOPONTOS.c
*  Letras identificadoras:      DADPnt
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: 
*			fvc - Felipe Vieira Côrtes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  1.0     tbm   02/set/2015	Início do desenvolvimento
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h> 
#include <malloc.h>
#include <string.h>
#include "GENERICO.H"

#define DADO_OWN
#include "DADOPONTOS.h"
#undef DADO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: DADPnt Descritor do dados de ponto.
*
*  $ED Descrição do tipo
*		Descreve a estrutura do dados ponto
***********************************************************************/

   typedef struct tgDadoPontos {
		int valor;
		/*Valor atual do dado de pontos*/
		char CorDoJogador;
		/*Ponteiro para o jogador que pode usar o dado
		*$EED Assertivas Estruturais
		*	É NULL se o jogo esta no começo e ninguem fez nenhuma dobra */

   } tpDadoPontos ;

/*****  Dados encapsulados no módulo  *****/


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DADPnt Criar Dado de Pontos
*  ****/

DADPnt_tpCondRet DADPnt_CriarDado(tppDadoPontos * DadoPontoCriado)
{

	*DadoPontoCriado = (tpDadoPontos*)malloc(sizeof(tpDadoPontos));

	if(DadoPontoCriado == NULL)
		return DADPnt_CondRetFaltouMemoria;

	(*DadoPontoCriado)->valor = 2;
	/*Valor Inicial do Dado de Pontos*/
	(*DadoPontoCriado)->CorDoJogador = 's';
	/*Quando o dado é criado, todos os jogadores podem usa-lo o inicio
	 s determinado que qualquer jogador pode usar*/
	return  DADPnt_CondRetOK;
}
/***************************************************************************
*
*  Função: DADPnt Dobrar Dado de Pontos e Mudar "Dono" do Dado de Pontos
*  ****/

DADPnt_tpCondRet DADPnt_DobrarDado(tppDadoPontos DadoDobrar, char CorNovoDono)
{
	if(CorNovoDono == DadoDobrar->CorDoJogador)
		return DADPnt_CondRetErro;
	DadoDobrar->valor = DadoDobrar->valor * 2;
	/*Pega o valor atual do dado e multiplica por 2*/
	DadoDobrar->CorDoJogador = CorNovoDono;
	return  DADPnt_CondRetOK;
}

/***************************************************************************
*
*  Função: DADPnt Gerar Valor da Partida
*  ****/

DADPnt_tpCondRet DADPnt_ValorPartida(tppDadoPontos DadoAtual, int * valorjogo)
{
	if(DadoAtual->CorDoJogador == 's' )
		*valorjogo = 2;
	else
		*valorjogo = DadoAtual->valor;
	return DADPnt_CondRetOK;
}

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

DADPnt_tpCondRet DADPnt_ObterDono(tppDadoPontos DadoPonto, char * CorDonoAtual)
{
	*CorDonoAtual = DadoPonto->CorDoJogador;
	return DADPnt_CondRetOK;
}

/***************************************************************************
*
*  Função: DADPnt Destruir Dado de Pontos
*  ****/

DADPnt_tpCondRet DADPnt_DestruirDado(tppDadoPontos Dado)
{
	if(Dado == NULL)
		return DADPnt_CondRetDadoPontosNaoExiste;
	free(Dado);
	return DADPnt_CondRetOK;
}
/*********** Fim do módulo de implementação: Módulo DadoPontos **************/
