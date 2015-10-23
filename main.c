#include <stdio.h>
#include <stdlib.h>
#include "BAR.h"
#include "DADO.H"
#include "DADOPONTOS.h"
#include "LISTA.H"
#include "PecasFinalizadas.h"
#include "TABULEIRO.H"
#include "PECA.h"
#include <Windows.h>
#define QUESTION (jogadordaVez == 'b')?
// funcao destruir valor

   static void DestruirValor( void * pValor ) ;
// Imprimir o estado do jogo

	void  displayJogo(LIS_tppLista estrutura);
	void corrigeCasas(LIS_tppLista pCasas);

int main (void)
{
	// variaveis
	LIS_tppLista Principal = LIS_CriarLista(DestruirValor);
	TAB_tppTabuleiro tabuleiro; // tabuleiro
	PF_tppFinalizadas pfbranca, pfpreta; // pecas finalizadas
	BAR_tppCapturadas barbranca, barpreta; // pecas capturadas
	LIS_tppLista casas, casa; // lista de casas auxiliar usada no jogo
	int dado1, dado2; // dados da partida
	tppDadoPontos dp;
	char preto = 'p', branco = 'b';
	int tampfb, tampfp, temp, tamanho; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo
	int casaEscolhida, opt[3] = {0,0,0}, contOpt = 0, i, j, k, opcao, opcaorestante;
	void* aux;
	char jogadordaVez, corObtida;
	tppPeca pecaAux;
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

	if(TAB_ObterCasas(tabuleiro, &casas)!= TAB_CondRetOK)
	{
		printf("Erro ao obter a lista de casas (mais) \n");
		return 0;
	}
	displayJogo(Principal);
	// jogar os dados para ver quem começa
JOGARDADO:
	if(DAD_NumPular(&dado1) != DAD_CondRetOK)
	{
		printf("Erro ao jogar o dado (main) \n");
		return 0;
	}
	Sleep(1);
	if(DAD_NumPular(&dado2) != DAD_CondRetOK)
	{
		printf("Erro ao jogar o dado (main) \n");
		return 0;
	}
	// se os dois valores forem iguais
	if(dado1 == dado2) goto JOGARDADO;
	// Dado1 corresponde ao jogador branco e dado2 corresponde ao jogador preto
	jogadordaVez = (dado1 > dado2)? 'b':'p';
	while(tampfp < 15 || tampfb < 15)
	{
LABEL1:
		printf("Jogador da vez eh o %s \n", (jogadordaVez == 'b')? "Branco" : "Preto");
		printf("Dados : %d %d \n", dado1, dado2);
		printf("Escolha de qual casa deseja andar \n");
ESCOLHADECASA:
		scanf("%d", &casaEscolhida);
		IrInicioLista(casas);
		LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
		// obter o valor da lista casa requerida
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		// obter o valor da peca
		aux = LIS_ObterValor(casa);
		// a casa é inválida
		while(aux == NULL)
		{
			PECANULL:
			printf("Esta casa esta desocupada, escolha outra casa \n");
			printf("Escolha de qual casa deseja andar \n");
			scanf("%d", &casaEscolhida);
			IrInicioLista(casas);
			LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
		}
		if(Pec_ObterCor((tppPeca)aux, &corObtida) != Pec_CondRetOK)
		{
			printf("Erro ao obter cor da peca (main) \n");
			return 0;
		}
		while(corObtida != jogadordaVez)
		{
			printf("Esta casa nao eh da sua cor, escolha outra casa \n");
			printf("Escolha de qual casa deseja andar \n");
			scanf("%d", &casaEscolhida);
			IrInicioLista(casas);
			LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
			if(aux == NULL) goto PECANULL;
			if(Pec_ObterCor((tppPeca)aux, &corObtida) != Pec_CondRetOK)
			{
				printf("Erro ao obter cor da peca (main) \n");
				return 0;
			}
		}
		// a casa é valida
		// agora é saber as opçoes que o jogador tem
		// ordena os dados, dado1 < dado2
		if(dado1 > dado2)
		{
			temp = dado1;
			dado1 = dado2;
			dado2 = temp;
		}
		LIS_AvancarElementoCorrente(casas, QUESTION dado1 : -dado1); // avanca para a posicao dado1
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		aux = LIS_ObterValor(casa);
		if(aux == NULL)
		{
			opt[contOpt] = dado1;
			contOpt++;
		}
		else
		{
			Pec_ObterCor((tppPeca)aux, &corObtida);
			if(corObtida == jogadordaVez)
			{
				opt[contOpt] = dado1;
				contOpt++;
			}
			else
			{
				tamanho = LIS_ObterTamanho(casa);
				if(tamanho == 1)
				{
					opt[contOpt] = dado1;
					contOpt++;
				}
			}
		}
		IrInicioLista(casas);
		LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
		LIS_AvancarElementoCorrente(casas,QUESTION dado2 : -dado2); // avanca para a posicao dado2
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		aux = LIS_ObterValor(casa);
		if(aux == NULL)
		{
			opt[contOpt] = dado2;
			contOpt++;
		}
		else
		{
			Pec_ObterCor((tppPeca)aux, &corObtida);
			if(corObtida == jogadordaVez)
			{
				opt[contOpt] = dado2;
				contOpt++;
			}
			else
			{
				tamanho = LIS_ObterTamanho(casa);
				if(tamanho == 1)
				{
					opt[contOpt] = dado2;
					contOpt++;
				}
			}
		}
		if(opt[0] == 0)
		{
			printf("Nao ha opcoes, escolha outra casa \n");
			goto ESCOLHADECASA;
		}
		for(i = 0; opt[i] != 0; i++)
		{
			printf("Opcao %d: Mover para a casa %d \n", i+1, QUESTION casaEscolhida + opt[i] : casaEscolhida-opt[i]);
		}
		IrInicioLista(casas);
		LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
		// As opçoes foram mostradas ao jogador
ESCOLHAOPCAO:
		scanf("%d", &opcao);
		if(opcao < 0 || opcao > 2)
		{
			printf("Opcao inválida, escolha novamente \n");
			goto ESCOLHAOPCAO;
		}
		else
		{
			LIS_AvancarElementoCorrente(casas, QUESTION opt[opcao-1] : -opt[opcao-1]);
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			tamanho = LIS_ObterTamanho(casa);
			aux = LIS_ObterValor(casas);
			if(tamanho == 1)
			{
				Pec_ObterCor((tppPeca)aux, &corObtida);
				if(corObtida != jogadordaVez) // se tamanho == 1 & a cor diferete da dele -> comer a peca do inimigo
				{
					if(LIS_ExcluirElemento(casa) != LIS_CondRetOK)
					{
						printf("Erro ao comer a peca (main) \n");
						return 0;
					}
					if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opt[opcao-1] - 1 : casaEscolhida - opt[opcao-1] - 1) != TAB_CondRetOK)
					{
						printf("Erro ao mover a peca 1 (main) \n");
						return 0; 
					}
					// adiciona uma peca com a corObtida no BAR
					BAR_AdicionarPeca(QUESTION barpreta : barbranca);
				}
				else // se é tamanho 1 mas com cor igual
				{
					if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opt[opcao-1] - 1 : casaEscolhida - opt[opcao-1] - 1) != TAB_CondRetOK)
					{
						printf("Erro ao mover a peca 1 (main) \n");
						return 0; 
					}
				}
			}
			else
			{
				if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opt[opcao-1] - 1: casaEscolhida - opt[opcao-1] - 1) != TAB_CondRetOK)
				{
					printf("Erro ao mover a peca 1 (main) \n");
					return 0; 
				}
			}
		}
		opt[opcao-1] = 0;
		displayJogo(Principal);
		for(i = 0; i < 3; i++)
		{
			if(opt[i] != 0)
			{
				opcaorestante = opt[i];
				break;
			}
		}
		if(i == 3)
			printf("Acabaram-se as opcoes \n");
		else
		{
			printf("Dado Restante : %d \n", opcaorestante);
			// jogador escolhe outra casa e repete-se o procedimento
ESCOLHADECASA1:
			printf("Escolha de qual casa deseja andar \n");
			scanf("%d", &casaEscolhida);
			IrInicioLista(casas);
			LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
			// obter o valor da lista casa requerida
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			// obter o valor da peca
			aux = LIS_ObterValor(casa);
			// a casa é inválida
			while(aux == NULL)
			{
PECANULL2:
				printf("Esta casa esta desocupada, escolha outra casa \n");
				printf("Escolha de qual casa deseja andar \n");
				scanf("%d", &casaEscolhida);
				IrInicioLista(casas);
				LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
				casa = (LIS_tppLista)LIS_ObterValor(casas);
				aux = LIS_ObterValor(casa);
			}
			if(Pec_ObterCor((tppPeca)aux, &corObtida) != Pec_CondRetOK)
			{
				printf("Erro ao obter cor da peca (main) \n");
				return 0;
			}
			while(corObtida != jogadordaVez)
			{
				printf("Esta casa nao eh da sua cor, escolha outra casa \n");
				printf("Escolha de qual casa deseja andar \n");
				scanf("%d", &casaEscolhida);
				IrInicioLista(casas);
				LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
				casa = (LIS_tppLista)LIS_ObterValor(casas);
				aux = LIS_ObterValor(casa);
				if(aux == NULL) goto PECANULL2;
				if(Pec_ObterCor((tppPeca)aux, &corObtida) != Pec_CondRetOK)
				{
					printf("Erro ao obter cor da peca (main) \n");
					return 0;
				}
			}
			// a casa é valida basta mover mostar a opcao e mover a peca
			//calcular as opçoes novamente
			LIS_AvancarElementoCorrente(casas, QUESTION opcaorestante : -opcaorestante);
			contOpt = 0;
			for(i = 0; i < 3; i++)
				opt[i] = 0;
			if(aux == NULL)
			{
				opt[contOpt] = dado1;
				contOpt++;
			}
			else
			{
				Pec_ObterCor((tppPeca)aux, &corObtida);
				if(corObtida == jogadordaVez)
				{
					opt[contOpt] = dado1;
					contOpt++;
				}
				else
				{
					tamanho = LIS_ObterTamanho(casa);
					if(tamanho == 1)
					{
						opt[contOpt] = dado1;
						contOpt++;
					}
				}
			}
			if(opt[0] == 0)
			{
				printf("Nao ha opcoes, escolha outra casa \n");
				goto ESCOLHADECASA1;
			}
			printf("Opcao 1: Mover peca para a casa %d \n",QUESTION casaEscolhida + opcaorestante : casaEscolhida - opcaorestante);
ESCOLHAOPCAO2:
			scanf("%d", &opcao);
			if(opcao < 0 || opcao > 2)
			{
				printf("Opcao inválida, escolha novamente \n");
				goto ESCOLHAOPCAO2;
			}
			else
			{
				IrInicioLista(casas);
				LIS_AvancarElementoCorrente(casas, casaEscolhida -1);
				LIS_AvancarElementoCorrente(casas, QUESTION opcaorestante : -opcaorestante);
				casa = (LIS_tppLista)LIS_ObterValor(casas);
				tamanho = LIS_ObterTamanho(casa);
				aux = LIS_ObterValor(casas);
				if(tamanho == 1)
				{
					Pec_ObterCor((tppPeca)aux, &corObtida);
					if(corObtida != jogadordaVez) // se tamanho == 1 & a cor diferete da dele -> comer a peca do inimigo
					{
						if(LIS_ExcluirElemento(casa) != LIS_CondRetOK)
						{
							printf("Erro ao comer a peca (main) \n");
							return 0;
						}
						if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opcaorestante - 1 : casaEscolhida - opcaorestante - 1) != TAB_CondRetOK)
						{
							printf("Erro ao mover a peca 1 (main) \n");
							return 0; 
						}
						BAR_AdicionarPeca(QUESTION barpreta : barbranca);
					}
					else // se é tamanho 1 mas com cor igual
					{
						if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opcaorestante - 1 : casaEscolhida - opcaorestante - 1) != TAB_CondRetOK)
						{
							printf("Erro ao mover a peca 1 (main) \n");
							return 0; 
						}
					}
				}
				else
				{
					if(TAB_MoverPeca(tabuleiro, casaEscolhida - 1, QUESTION casaEscolhida + opcaorestante - 1: casaEscolhida - opcaorestante - 1) != TAB_CondRetOK)
					{
						printf("Erro ao mover a peca 1 (main) \n");
						return 0; 
					}
				}
			}
		}
		displayJogo(Principal);
JOGARDADO1:
		if(DAD_NumPular(&dado1) != DAD_CondRetOK)
		{
			printf("Erro ao jogar o dado (main) \n");
			return 0;
		}
		Sleep(1);
		if(DAD_NumPular(&dado2) != DAD_CondRetOK)
		{
			printf("Erro ao jogar o dado (main) \n");
			return 0;
		}
		// se os dois valores forem iguais
		if(dado1 == dado2) goto JOGARDADO1;		
		jogadordaVez = QUESTION 'p' : 'b';
		contOpt = 0;
		for(i = 0; i < 3; i++)
			opt[i] = 0;
	}


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
			printf(" %c", 0xb0);
	}
	printf("  Branco : ");
	if(BAR_ObterTamanhoBar(barb, &tamanho) == BAR_CondRetErro)
	{
		printf("Erro ao obter o tamanho da lista BAR (display) \n");
		exit(-1);
	}
	if(tamanho == 0)
		printf(" empty\n");
	else
	{
		for(i = 0; i < tamanho; i++)
			printf(" %c", 0xb2);
		printf("\n");
	}
	printf("|------------------------------------------------------------- \n|");
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
void corrigeCasas(LIS_tppLista pCasas)
{
	int i;
	LIS_tppLista aux;
	void* a;
	IrInicioLista(pCasas);
	for(i = 0; i < 24; i++)
	{
		aux = (LIS_tppLista)LIS_ObterValor(pCasas);
		IrInicioLista(aux);
		LIS_AvancarElementoCorrente(pCasas, 1);
	}
}





			