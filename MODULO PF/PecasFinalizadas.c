/***************************************************************************
*  $MCI Módulo de implementação: PF Peças Finalizadas
*
*  Arquivo gerado:              PF.c
*  Letras identificadoras:      PF
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
#include	"LISTA.h"
#include	"PECA.h"

#define PF_OWN
#include "PecasFinalizadas.h"
#undef PF_OWN


/***********************************************************************
*
*  $TC Tipo de dados: PF Descritor da estrutura de peças finalizadas
*
*
***********************************************************************/

typedef struct PF_tagFinalizadas {

	LIS_tppLista ListaFinalizadas;
	/* Lista de Peças Finalizadas*/

	char cor;
	/* A cor das peças da estrutura */

	int tamanho ;
	/* Número de elementos na lista */

} PF_tpFinalizadas ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: PF &Criar PF
*  ****/

PF_tpCondRet PF_CriarPF(PF_tppFinalizadas *pPF, char cor,
             void   ( * ExcluirValor ) ( void * pDado ) )
{

	*pPF = (PF_tppFinalizadas)malloc(sizeof(PF_tpFinalizadas));

	if(*pPF == NULL)
		return PF_CondRetFaltouMemoria;

	(*pPF)->ListaFinalizadas = LIS_CriarLista(ExcluirValor);
	(*pPF)->cor = cor;
	(*pPF)->tamanho = 0;

	return PF_CondRetOK;
}

/***************************************************************************
*
*  Função: PF  &Adicionar Peça
*  ****/

PF_tpCondRet PF_AdicionarPecaPF(PF_tppFinalizadas pPF)
{
	char cor = pPF->cor;
	tppPeca newPeca;
	if(Pec_CriarPeca(&newPeca, cor) != Pec_CondRetOK)
	{
		printf("Erro ao criar peca (PF) \n");
		return PF_CondRetErro;
	}
	if(LIS_InserirElementoApos(pPF->ListaFinalizadas, newPeca) != LIS_CondRetOK)
	{
		printf("Erro ao inserir peça na lista (PF) \n");
		return PF_CondRetErro;
	}
	pPF->tamanho++;

	return PF_CondRetOK;
}


/***************************************************************************
*
*  Função: PF  &Obter Tamanho PF
*  ****/

PF_tpCondRet PF_ObterTamanhoPF(PF_tppFinalizadas pPF, int *tam)
{
	if(tam == NULL)
		return PF_CondRetErro;

	*tam = pPF->tamanho;

	if(*tam == 0)
		return PF_CondRetVazia;

	return PF_CondRetOK;
}

/***************************************************************************
*
*  Função: PF  &Obter cor PF
*  ****/

PF_tpCondRet PF_ObterCorPF(PF_tppFinalizadas pPF, char *cor)
{
	if(cor == NULL)
		return PF_CondRetErro;

	*cor = pPF->cor;

	return PF_CondRetOK;
}

/***************************************************************************
*
*  Função: PF  &Destruir PF
*  ****/

PF_tpCondRet PF_DestruirPF(PF_tppFinalizadas pPF)
{
	LIS_DestruirLista(pPF->ListaFinalizadas);
	free(pPF);
	return PF_CondRetOK;
}


/******** Fim do Módulo de Implementação: PF Lista de Peças Finalizadas *************/