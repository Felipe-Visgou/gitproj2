/***************************************************************************
*  $MCI Módulo de implementação: BAR Peças Capturadas
*
*  Arquivo gerado:              BAR.c
*  Letras identificadoras:      BAR
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: fvc
			tbm
			db
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
	   1.0		fvc		18/10	 Começo do Desenvolvimento
*
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <malloc.h>
#include "LISTA.h"
#include "PECA.h"
#define BAR_OWN
#include "BAR.h"
#undef BAR_OWN


/***********************************************************************
*
*  $TC Tipo de dados: BAR Descritor da BAR
*
*
***********************************************************************/

typedef struct BAR_tagCapturadas {

	LIS_tppLista ListaCapturadas;
	/* Lista de Peças Capturadas*/

	char cor;
	/* A cor das peças do BAR */

	int tamanho ;
	/* Número de elementos no BAR*/

} BAR_tpCapturadas ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar BAR
*  ****/

BAR_tpCondRet BAR_CriarBAR(BAR_tppCapturadas *pBAR, char cor, void   ( * ExcluirValor ) ( void * pDado ) )
{

	*pBAR = (BAR_tppCapturadas)malloc(sizeof(BAR_tpCapturadas));

	if(*pBAR == NULL)
		return BAR_CondRetFaltouMemoria;

	(*pBAR)->ListaCapturadas = LIS_CriarLista(ExcluirValor);
	(*pBAR)->cor = cor;
	(*pBAR)->tamanho = 0;

	return BAR_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &Adicionar Peça
*  ****/

BAR_tpCondRet BAR_AdicionarPeca(BAR_tppCapturadas pBAR)
{
	char cor = pBAR->cor;
	tppPeca newPeca;
	if(Pec_CriarPeca(&newPeca, cor) != Pec_CondRetOK)
	{
		printf("Erro ao criar peca (BAR) \n");
		return BAR_CondRetErro;
	}
	if(LIS_InserirElementoApos(pBAR->ListaCapturadas, newPeca) != LIS_CondRetOK)
	{
		printf("Erro ao inserir peça na lista (BAR) \n");
		return BAR_CondRetErro;
	}
	pBAR->tamanho++;

	return BAR_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &RemoverPeça
*  ****/

BAR_tpCondRet BAR_RemoverPeca(BAR_tppCapturadas pBAR)
{
	if(LIS_ExcluirElemento(pBAR->ListaCapturadas) != LIS_CondRetOK)
	{
		printf("Erro ao excluir peca da lsita (BAR) \n");
		return BAR_CondRetErro;
	}

	return BAR_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &Obter Tamanho BAR
*  ****/

BAR_tpCondRet BAR_ObterTamanhoBar(BAR_tppCapturadas pBAR, int *tam)
{
	if(tam == NULL)
		return BAR_CondRetErro;

	*tam = pBAR->tamanho;

	if(*tam == 0)
		return BAR_CondRetVazia;

	return BAR_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &Obter cor BAR
*  ****/

BAR_tpCondRet BAR_ObterCorBar(BAR_tppCapturadas pBAR, char *cor)
{
	if(cor == NULL)
		return BAR_CondRetErro;

	*cor = pBAR->cor;

	return BAR_CondRetOK;
}

/******** Fim do Módulo de Implementação: BAR Lista de Peças Capturadas *************/

