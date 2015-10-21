#include <stdio.h>
#include <stdlib.h>
#include "BAR.h"
#include "DADO.H"
#include "DADOPONTOS.h"
#include "LISTA.H"
#include "PecasFinalizadas.h"
#include "TABULEIRO.H"
#include "PECA.h"
// funcao destruir valor

   static void DestruirValor( void * pValor ) ;
// Imprimir o estado do jogo

	void  displayJogo(LIS_tppLista estrutura);

int main (void)
{
	// variaveis
	LIS_tppLista Principal = LIS_CriarLista(DestruirValor);
	TAB_tppTabuleiro tabuleiro; // tabuleiro
	PF_tppFinalizadas pfbranca, pfpreta; // pecas finalizadas
	BAR_tppCapturadas barbranca, barpreta; // pecas capturadas
	int dado1, dado2; // dados da partida
	tppDadoPontos dp;
	char preto = 'p', branco = 'b';
	int tampfb, tampfp; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo

	// Criar criar as estruturas e adicionalas na principal

	TAB_CriarTabuleiro(&tabuleiro, DestruirValor);
	PF_CriarPF(&pfbranca, preto, DestruirValor);
	PF_CriarPF(&pfpreta, preto, DestruirValor);
	BAR_CriarBAR(&barbranca, branco, DestruirValor);
	BAR_CriarBAR(&barpreta, preto, DestruirValor);
	DADPnt_CriarDado(&dp);

	LIS_InserirElementoApos(Principal, tabuleiro);
	LIS_InserirElementoApos(Principal, barbranca);
	LIS_InserirElementoApos(Principal, pfbranca);
	LIS_InserirElementoApos(Principal, barpreta);
	LIS_InserirElementoApos(Principal, pfpreta);
	LIS_InserirElementoApos(Principal, dp);

	PF_ObterTamanhoPF(pfbranca, &tampfb);
	PF_ObterTamanhoPF(pfpreta, &tampfp);

	while(tampfb < 12 || tampfp < 12)
	{
		displayJogo(Principal);
		// jogar
	}
	//fim de jogo
}
void  displayJogo(LIS_tppLista estrutura)
{
	// variaveis
	TAB_tppTabuleiro tab; // tabuleiro
	PF_tppFinalizadas pfb, pfp; // pecas finalizadas
	BAR_tppCapturadas barb, barp; // pecas capturadas
	tppDadoPontos dp;
	char preto = 'p', branco = 'b', corpeca;
	int tampfb, tampfp, tamanho; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo
	LIS_tppLista casas, listaAux;
	tppPeca peca;
	int flag[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
	int i, j, valorpartida;
	char valor, v[12][12], dono;

	// obter o valor de cada estrutura
	IrInicioLista(estrutura);
	system("cls");
	tab = (TAB_tppTabuleiro)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (display) \n");
		exit(-1);
	}

	barb = (BAR_tppCapturadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (display) \n");
		exit(-1);
	}
	pfb = (PF_tppFinalizadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (display) \n");
		exit(-1);
	}

	barp = (BAR_tppCapturadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (display) \n");
		exit(-1);
	}
	pfp = (PF_tppFinalizadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (display) \n");
		exit(-1);
	}
	dp = (tppDadoPontos)LIS_ObterValor(estrutura);

	printf("|13 - 14 - 15 - 16 - 17 - 18 - 19 - 20 - 21 - 22 - 23 - 24   | \n ");
	if(TAB_ObterCasas(tab, &casas) != TAB_CondRetOK)
	{
		printf("Erro ao obter as casas (display) \n");
		exit(-1);
	}
	IrInicioLista(casas);
	for(i = 0; i < 24; i++)
	{
		listaAux = (LIS_tppLista)LIS_ObterValor(casas);
		IrInicioLista(listaAux);
		LIS_AvancarElementoCorrente(casas, 1);
	}
	/************/
	IrFinalLista(casas);
	LIS_AvancarElementoCorrente(casas, -11);
	/***********/
	for(i = 0; i < 12; i++)
	{
		for(j = 0; j < 12; j++)
		{
			listaAux = (LIS_tppLista)LIS_ObterValor(casas);
			peca = (tppPeca)LIS_ObterValor(listaAux);
			if(peca ==  NULL)
			{
				LIS_AvancarElementoCorrente(casas, 1);
				printf("     ");
				continue;
			}
			Pec_ObterCor(peca, &corpeca);
			if(!flag[j])
				valor = ' ';
			else if(LIS_AvancarElementoCorrente(listaAux, 1) == LIS_CondRetFimLista)
			{
				printf("%c    ", (corpeca == preto)? 0xb0 : 0xb2);
				flag[j] = 0;
				LIS_AvancarElementoCorrente(casas, 1);
				continue;
			}
			else if(corpeca == preto)
				valor = 0xb0;
			else if(corpeca == branco)
				valor = 0xb2;
			printf("%c    ", valor);
			LIS_AvancarElementoCorrente(casas, 1);
		}
		printf("|\n|");
		IrFinalLista(casas);
		LIS_AvancarElementoCorrente(casas, -11);
	}
	// a outra parte do tabuleiro (+12 iterações)... 
	// colocar nos vetores a quantidade de pecas
	IrInicioLista(casas);
	LIS_AvancarElementoCorrente(casas, 11);
	for(i = 0; i < 12; i++)
	{
		listaAux = (LIS_tppLista)LIS_ObterValor(casas);
		/*if(*/tamanho = LIS_ObterTamanho(listaAux);/* != LIS_CondRetOK)
		{
			printf("Erro ao obter o tamanho da lista (display) \n");
			exit(-1);
		}*/
		peca = (tppPeca)LIS_ObterValor(listaAux);
		if(peca == NULL)
		{
			for(j = 0; j < 12; j++)
				v[i][j] = 0;
		}
		else
		{
			Pec_ObterCor(peca, &corpeca);
			if(corpeca == preto)
			{
				for(j = 0; j < tamanho; j++)
					v[i][j] = preto;
			}
			else
			{
				for(j = 0; j < tamanho; j++)
					v[i][j] = branco;
			}
			for(j = tamanho; j < 12; j++)
				v[i][j] = 0;
		}
		LIS_AvancarElementoCorrente(casas, -1);
	}
	printf("------------------------------BAR---------------------------- \n");
	printf("Preto : ");
	if(BAR_ObterTamanhoBar(barp, &tamanho) == BAR_CondRetErro)
	{
		printf("Erro ao obter o tamanho da lista BAR (display) \n");
		exit(-1);
	}
	if(tamanho == 0)
		printf(" empty");
	else
	{
		for(i = 0; i < tamanho; i++)
			printf(" %c", 0xb2);
	}
	printf("\n");

	printf("Branco : ");
	if(BAR_ObterTamanhoBar(barb, &tamanho) == BAR_CondRetErro)
	{
		printf("Erro ao obter o tamanho da lista BAR (display) \n");
		exit(-1);
	}
	if(tamanho == 0)
		printf(" empty \n|");
	else
	{
		for(i = 0; i < tamanho; i++)
			printf(" %c", 0xb0);
	}
	for(j = 11; j >= 0; j--)
	{
		for( i = 0; i < 12; i++)
		{
			if(v[i][j] == 0)
				valor = ' ';
			else if(v[i][j] == preto)
				valor = 0xb0;
			else if(v[i][j] == branco)
				valor = 0xb2;
			printf("%c    ", valor);
		}
		printf("|\n|");
	}
	printf("12 - 11 - 10 - 9  - 8  - 7  - 6  - 5  - 4  - 3  - 2  - 1    | \n");
	DADPnt_ValorPartida(dp, &valorpartida);
	DADPnt_ObterDono(dp, &dono);
	PF_ObterTamanhoPF(pfp, &tampfp);
	printf("\nValor da partida : %d        Pecas pretas finalizadas : %d \n", valorpartida, tamanho);
	PF_ObterTamanhoPF(pfb, &tampfb);
	printf("\nDono do DadoPontos : %c      Pecas brancas finalizadas : %d \n", dono, tamanho);
}
void DestruirValor( void * pValor )
{

      free( pValor ) ;
}





			