/***************************************************************************
*  $MCI Módulo de implementação: TAB   Tabuleiro de Gamão
*
*  Arquivo gerado:             TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: fvc	- Felipe Vieira Cortes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão
*
*  $HA Histórico de evolução:
*     Versão  Autor		  Data     Observações
*	  2		  fvc, tbm 	23/set/2015 término do deselvolvimento
*     1       fvc, tbm	21/set/2015 início desenvolvimento
 
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#define TABULEIRO_OWN
#include "LISTA.H"
#include "GENERICO.H"
#include "PECA.h"
#include "TABULEIRO.H"

#undef TABULEIRO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Tabuleiro
*
*
***********************************************************************/

typedef struct TAB_tagTabuleiro {

	LIS_tppLista Casas;


} TAB_tpTabuleiro;


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: TAB  &Criar Tabuleiro
*  ****/

TAB_tpCondRet TAB_CriarTabuleiro(TAB_tppTabuleiro * pTab,
	void   ( * ExcluirValor ) ( void * pDado ) )
{
	LIS_tppLista vtCasa[24]; // vetor de casas auxiliar
	tppPeca vtPecaB[15]; // vetor de peças brancas
	tppPeca vtPecaP[15]; //vetor de peças pretas
	int i, jb = 0,jp = 0;

	*pTab = (TAB_tppTabuleiro)malloc(sizeof(TAB_tpTabuleiro));
	(*pTab)->Casas = LIS_CriarLista(ExcluirValor);

	/* Cria 15 peças brancas */
	for(i = 0; i < 15; i++)
	{
		if(Pec_CriarPeca(&vtPecaB[i], 'b')!=Pec_CondRetOK)
			return TAB_CondRetErro;
	}
	/* Cria 15 peças pretas */
	for(i = 0; i < 15; i++)
	{
		if(Pec_CriarPeca(&vtPecaP[i], 'p')!=Pec_CondRetOK)
			return TAB_CondRetErro;
	}
	/* Cria 24 listas que representam cada casa do tabuleiro*/
	for(i = 0; i < 24; i++)
		vtCasa[i] = LIS_CriarLista(ExcluirValor);

	// Pretas
	LIS_InserirElementoApos(vtCasa[23], vtPecaP[jp]); jp++;
	LIS_InserirElementoApos(vtCasa[23], vtPecaP[jp]); jp++;
	// Brancas
	LIS_InserirElementoApos(vtCasa[0], vtPecaB[jb]); jb++;
	LIS_InserirElementoApos(vtCasa[0], vtPecaB[jb]); jb++;
	for(i = 0; i < 5; i++)
	{
		// Pretas
		LIS_InserirElementoApos(vtCasa[5], vtPecaP[jp]); jp++;
		LIS_InserirElementoApos(vtCasa[12], vtPecaP[jp]); jp++;
		// Brancas
		LIS_InserirElementoApos(vtCasa[11], vtPecaB[jb]); jb++;
		LIS_InserirElementoApos(vtCasa[18], vtPecaB[jb]); jb++;
	}
	for(i = 0; i < 3; i++)
	{
		// Pretas
		LIS_InserirElementoApos(vtCasa[7], vtPecaP[jp]); jp++;
		// Brancas
		LIS_InserirElementoApos(vtCasa[16], vtPecaB[jb]); jb++;
	}
	// Alocar as 24 casas na lista do tabuleiro
	for(i = 0; i < 24; i++)
		LIS_InserirElementoApos((*pTab)->Casas, vtCasa[i]);

	return TAB_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &Destruir Tabuleiro
*  ****/

TAB_tpCondRet TAB_DestruirTabuleiro (TAB_tppTabuleiro pTab)
{

	LIS_DestruirLista(pTab->Casas);
	// Libera o ponteiro para o  tabuleiro
	free(pTab);

	return TAB_CondRetOK;
}

/***************************************************************************
*
*  Função: TAB  &Mover Peças tabuleiro
*  ****/

TAB_tpCondRet TAB_MoverPeca( TAB_tppTabuleiro pTab, int casaOrigem, int casaDestino ) 
{
	tppPeca pecatemp1, pecatemp2;
	char cor;
	LIS_tppLista listatemp;
	int  mov = casaDestino - casaOrigem;

	// Checa a validade das casas de origem e destino
	if((casaOrigem < 0) || (casaOrigem > 23))
	{
		printf("casaOrigem inválida \n");
		return TAB_CondRetErro;
	}
	if((casaDestino < 0) || (casaDestino > 23))
	{
		printf("casaDestino inválida \n");
		return TAB_CondRetErro;
	}

	// Ir para a casa de origem
	IrInicioLista(pTab->Casas);
	LIS_AvancarElementoCorrente(pTab->Casas, casaOrigem);

	// Obter referência para a lista nela armazenada
	listatemp = (LIS_tppLista)LIS_ObterValor(pTab->Casas);

	// Obter a cor da peca na lista temp
	pecatemp1 = (tppPeca)LIS_ObterValor(listatemp);

	// se pecatemp1 == NULL entao a lista está vazia
	if(pecatemp1 == NULL)
	{
		printf("casa de origem esta vazia \n");
		return TAB_CondRetErro;
	}
	else // se nao
	{
		Pec_ObterCor(pecatemp1, &cor);
	}

	// Excluir uma peça da lista temp
	if(LIS_ExcluirElemento(listatemp) != LIS_CondRetOK)
	{
		printf("Erro ao excluir peca da casa de orgiem\n");
		return TAB_CondRetErro;
	}

	// Avança para a casa destino.
	LIS_AvancarElementoCorrente(pTab->Casas, mov);

	// Obtem a referencia para a lista nela armazenada
	listatemp = (LIS_tppLista)LIS_ObterValor(pTab->Casas);

	// Criar uma peça com a mesma cor q a peça antiga
	if(Pec_CriarPeca(&pecatemp2, cor) != Pec_CondRetOK)
	{
		printf("Erro ao criar a peca na casa destino \n");
		return TAB_CondRetErro;
	}

	// Adiciona esta peça na casa de destino
	if(LIS_InserirElementoApos(listatemp, pecatemp2) != LIS_CondRetOK)
	{
		printf("Erro ao adicionar peca na casa destino \n");
		return TAB_CondRetErro;
	}

	return TAB_CondRetOK;
}

TAB_tpCondRet TAB_ObterCasas(TAB_tppTabuleiro pTab, LIS_tppLista *casas)
{
	*casas = pTab->Casas;
	if(casas == NULL || *casas == NULL)
	{
		printf("Ponterio para casas eh nulo (obterCasas) \n");
		return TAB_CondRetErro;
	}
	return TAB_CondRetOK;
}









	   


