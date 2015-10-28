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
	LIS_tppLista carregaJogo(FILE** fp);
	void salvarJogo(LIS_tppLista estrutura);
	void finalizarPeca(TAB_tppTabuleiro *pTab, PF_tppFinalizadas *pPF, int num);
	/* Conta a quantidade de peças a partir da 'qtd'ultimas casas */	
	int contaUltimasCasas(TAB_tppTabuleiro *pTab, char cor, int qtd);
	int jogadordaVez;

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
	int flag = 0;
	char preto = 'p', branco = 'b';
	int tampfb = 0, tampfp = 0,tamanho, tambarb, tambarp, ultCasas; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo
	int casaEscolhida, opt[3] = {0,0,0}, contOpt = 0, i, k = 0; 
	int opcao, opcaorestante;
	void* aux;
	char jogadordaVez, corObtida;
	int resp;
	FILE* fp;
	tppPeca pecaAux;
	// Criar criar as estruturas e adicionalas na principal
	printf(" ----------------- menu -------------------- \n");
	printf(" 1: Novo Jogo \n");
	printf(" 2: Carregar Jogo \n");
	scanf("%d", &resp);
	if(resp == 2)
	{
		Principal = carregaJogo(&fp);
		IrInicioLista(Principal);
		tabuleiro = (TAB_tppTabuleiro)LIS_ObterValor(Principal);
		if(LIS_AvancarElementoCorrente(Principal, 1) != LIS_CondRetOK)
		{
			printf("Erro ao andar na estrutura principal (display) \n");
			exit(-1);
		}

		barbranca = (BAR_tppCapturadas)LIS_ObterValor(Principal);
		if(LIS_AvancarElementoCorrente(Principal, 1) != LIS_CondRetOK)
		{
			printf("Erro ao andar na estrutura principal (display) \n");
			exit(-1);
		}
		pfbranca = (PF_tppFinalizadas)LIS_ObterValor(Principal);
		if(LIS_AvancarElementoCorrente(Principal, 1) != LIS_CondRetOK)
		{
			printf("Erro ao andar na estrutura principal (display) \n");
			exit(-1);
		}

		barpreta = (BAR_tppCapturadas)LIS_ObterValor(Principal);
		if(LIS_AvancarElementoCorrente(Principal, 1) != LIS_CondRetOK)
		{
			printf("Erro ao andar na estrutura principal (display) \n");
			exit(-1);
		}
		pfpreta = (PF_tppFinalizadas)LIS_ObterValor(Principal);
		if(LIS_AvancarElementoCorrente(Principal, 1) != LIS_CondRetOK)
		{
			printf("Erro ao andar na estrutura principal (display) \n");
			exit(-1);
		}
		dp = (tppDadoPontos)LIS_ObterValor(Principal);
		goto JOGARDADO;
	}
	TAB_CriarTabuleiro(&tabuleiro, DestruirValor);
	PF_CriarPF(&pfbranca, branco, DestruirValor);
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
	// jogar os dados para ver quem começa
JOGARDADO:
	if(TAB_ObterCasas(tabuleiro, &casas)!= TAB_CondRetOK)
	{
		printf("Erro ao obter a lista de casas (mais) \n");
		return 0;
	}
	displayJogo(Principal);
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
	while(tampfp < 15  ||  tampfb < 15)
	{
LABEL1:
		printf("Jogador da vez eh o %s \n", QUESTION "Branco" : "Preto");
		printf("1: Jogar dados \n0: Salvar e Sair \n");
		flag = 0;
		scanf("%d", &resp);
		if(resp == 0)
		{
			salvarJogo(Principal);
			printf("Obrigado por Jogar \n");
			Sleep(2);
			return 0;
		}
		if(resp > 1)
		{
			printf("Opcao errada, tente denovo \n");
			goto LABEL1;
		}
		displayJogo(Principal);
		printf("Jogador da vez eh o %s \n", QUESTION "Branco" : "Preto");
		if(dado1 == dado2)
			printf("Dados : %d %d %d %d \n", dado1, dado2, dado1, dado2);
		else
			printf("Dados : %d %d \n", dado1, dado2);
		// checa se a bar está com alguma peça, se sim, calcula as opções q ele tem com os dados jogados
		BAR_ObterTamanhoBar(barbranca, &tambarb);
		BAR_ObterTamanhoBar(barpreta,&tambarp);
DOBRADOBAR:
		if(((jogadordaVez == 'b') && (tambarb > 0)) || ((jogadordaVez == 'p') && (tambarp > 0))) // o jogador da vez tem peça no bar?
		{
			// calcula as opções do jogador
			QUESTION IrInicioLista(casas) : IrFinalLista(casas);
			LIS_AvancarElementoCorrente(casas, QUESTION dado1 - 1 : -dado1 + 1); // avanca para a posicao dado1
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
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
			QUESTION IrInicioLista(casas) : IrFinalLista(casas);
			LIS_AvancarElementoCorrente(casas, QUESTION dado2 - 1 : -dado2 + 1); // avanca para a posicao dado1
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
				printf("Nao ha opcoes, passando a vez \n");
				jogadordaVez = QUESTION 'p' : 'b';
				contOpt = 0;
				for(i = 0; i < 3; i++)
					opt[i] = 0;
				PF_ObterTamanhoPF(pfbranca, &tampfb);
				PF_ObterTamanhoPF(pfpreta, &tampfp);
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
				goto LABEL1;
			}
			for(i = 0; i < 2; i++)
			{
				if(opt[i] == 0) continue;
				printf("%d : Mover peca do BAR para a casa %d \n", i+1, QUESTION opt[i] : 25 - opt[i]);
			}
			printf("0 : Salvar e Sair \n");
ESCOLHAOPCAO3:
			scanf("%d", &opcao);
			if(opcao > 2)
			{
				printf("Opcao inválida, escolha novamente \n");
				goto ESCOLHAOPCAO3;
			}
			if(opcao == 0)
			{
				salvarJogo(Principal);
				printf("Obrigado por jogar! \n");
				Sleep(2);
				return 0;
			}
			QUESTION IrInicioLista(casas) : IrFinalLista(casas);
			LIS_AvancarElementoCorrente(casas,QUESTION opt[opcao-1] -1: -opt[opcao-1] +1 );
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
			tamanho = LIS_ObterTamanho(casa);
			Pec_CriarPeca(&pecaAux, QUESTION branco : preto);
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
					LIS_InserirElementoAntes(casa, pecaAux);
					// adiciona uma peca com a corObtida no BAR
					BAR_AdicionarPeca(QUESTION barpreta : barbranca);
					// remove a peça do bar
					BAR_RemoverPeca(QUESTION barbranca : barpreta);
				}
				else // se é tamanho 1 mas com cor igual
				{
					LIS_InserirElementoAntes(casa, pecaAux);
					BAR_RemoverPeca(QUESTION barbranca : barpreta);
				}
			}
			else
			{
				LIS_InserirElementoAntes(casa, pecaAux);
				BAR_RemoverPeca(QUESTION barbranca : barpreta);
			}
			// obtem o novo tamanho do BAR
			BAR_ObterTamanhoBar(barbranca, &tambarb);
			BAR_ObterTamanhoBar(barpreta,&tambarp);
			opt[opcao - 1] = 0;
			if(((jogadordaVez == 'b') && (tambarb > 0)) || ((jogadordaVez == 'p') && (tambarp > 0)))
			{
				displayJogo(Principal);
				for( i = 0; i < 2; i++)
				{
					if(opt[i] == 0) continue; else break;
				}
				if(i > 1)
				{
					printf("Acabaram-se as opções. passando a vez \n");
					jogadordaVez = QUESTION 'p' : 'b';
					contOpt = 0;
					for(i = 0; i < 3; i++)
						opt[i] = 0;
					PF_ObterTamanhoPF(pfbranca, &tampfb);
					PF_ObterTamanhoPF(pfpreta, &tampfp);
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
					goto LABEL1;
				}
				opcaorestante = (opt[opcao - 1] == dado1)? dado2 : dado1;
				if((dado1 == dado2) && !flag) printf("Dados Restantes : %d %d %d \n", dado1, dado2, dado2);
				else printf("Dado Restante : %d \n", opcaorestante);
				// mover a peça do bar para o tabuleiro
				printf("1: Mover a peca do BAR para a casa %d \n", QUESTION opcaorestante : 25 - opcaorestante);
ESCOLHAOPCAO4:
				scanf("%d", &opcao);
				if(opcao < 0 || opcao > 2)
				{
					printf("Opcao inválida, escolha novamente \n");
					goto ESCOLHAOPCAO4;
				}
				if(opcao == 0)
				{
					salvarJogo(Principal);
					printf("Obrigado por jogar! \n");
					Sleep(2);
					return 0;
				}
				QUESTION IrInicioLista(casas) : IrFinalLista(casas);
				LIS_AvancarElementoCorrente(casas,QUESTION opcaorestante -1: -opcaorestante +1 );
				casa = (LIS_tppLista)LIS_ObterValor(casas);
				aux = LIS_ObterValor(casa);
				Pec_CriarPeca(&pecaAux, QUESTION branco : preto);
				tamanho = LIS_ObterTamanho(casa);
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
						LIS_InserirElementoAntes(casa, pecaAux);
						// adiciona uma peca com a corObtida no BAR
						BAR_AdicionarPeca(QUESTION barpreta : barbranca);
						// remove a peça do bar
						BAR_RemoverPeca(QUESTION barbranca : barpreta);
					}
					else // se é tamanho 1 mas com cor igual
					{
						LIS_InserirElementoAntes(casa, pecaAux);
						BAR_RemoverPeca(QUESTION barbranca : barpreta);
					}
				}
				else
				{
					LIS_InserirElementoAntes(casa, pecaAux);
					BAR_RemoverPeca(QUESTION barbranca : barpreta);
				}
				// acabou a vez do jogador de tirar as peças do bar (trocar de jogador)
				BAR_ObterTamanhoBar(barbranca, &tambarb);
				BAR_ObterTamanhoBar(barpreta,&tambarp);
				if((dado1 == dado2) && !flag)
				{
					displayJogo(Principal);
					printf("Jogador da vez eh o %s \n", (jogadordaVez == 'b')? "Branco" : "Preto");
					printf("Dados : %d %d \n", dado1, dado2);
					flag = 1;
					for(i = 0; i < 2; i++) opt[i] = 0;
					goto DOBRADOBAR;
				}
				jogadordaVez = QUESTION 'p' : 'b';
				contOpt = 0;
				for(i = 0; i < 3; i++)
					opt[i] = 0;
				PF_ObterTamanhoPF(pfbranca, &tampfb);
				PF_ObterTamanhoPF(pfpreta, &tampfp);
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
				displayJogo(Principal);
				goto LABEL1;
			}
		goto OPCAORESTANTE;
		}
DOBRADO:
		ultCasas = contaUltimasCasas(&tabuleiro, jogadordaVez, 6);
		if((ultCasas + QUESTION tampfb : tampfp) == 15)
		{
			// ve se pode finalizar
			IrInicioLista(casas);
			LIS_AvancarElementoCorrente(casas, QUESTION dado1 -1 : -dado1 + 1);
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
			contOpt = 2;
			if(aux != NULL)
			{
				Pec_ObterCor((tppPeca)aux, &corObtida);
				if(corObtida == jogadordaVez)
				{
					opt[contOpt] = dado1;
					contOpt++;
				}
			}
			if((aux == NULL) || corObtida != jogadordaVez)
			{
				ultCasas = contaUltimasCasas(&tabuleiro, jogadordaVez, dado1);
				if((ultCasas + QUESTION tampfb : tampfp) == 15)
				{
					while((aux == NULL) || corObtida != jogadordaVez)
					{
						LIS_AvancarElementoCorrente(casas, QUESTION 1 : -1);
						casa = (LIS_tppLista)LIS_ObterValor(casas);
						aux = LIS_ObterValor(casa);
						k++;
					}
					opt[contOpt] = k;
					contOpt++;
				}
			}
			IrInicioLista(casas);
			LIS_AvancarElementoCorrente(casas, QUESTION dado2 -1 : -dado2 + 1);
			casa = (LIS_tppLista)LIS_ObterValor(casas);
			aux = LIS_ObterValor(casa);
			if(aux != NULL)
			{
				Pec_ObterCor((tppPeca)aux, &corObtida);
				if(corObtida == jogadordaVez)
				{
					opt[contOpt] = dado2;
					contOpt++;
				}
			}
			if((aux == NULL) || corObtida != jogadordaVez)
			{
				ultCasas = contaUltimasCasas(&tabuleiro, jogadordaVez, dado2);
				if((ultCasas + QUESTION tampfb : tampfp) == 15)
				{
					while((aux == NULL) || corObtida != jogadordaVez)
					{
						LIS_AvancarElementoCorrente(casas, QUESTION 1 : -1);
						casa = (LIS_tppLista)LIS_ObterValor(casas);
						aux = LIS_ObterValor(casa);
						k++;
					}
					opt[contOpt] = k;
					contOpt++;
				}
			}
		}
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
		LIS_AvancarElementoCorrente(casas, QUESTION dado1 : -dado1); // avanca para a posicao dado1
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		aux = LIS_ObterValor(casa);
		contOpt = 0;
		// obtem as opcoes possiveis
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
		// o bizu está aqui,... para finalziar as peças
		for(i = 0; i < 3; i++)
		{
			if(((jogadordaVez == 'b') && (opt[i] + casaEscolhida  > 24)) || ((casaEscolhida - opt[i] < 1) && (jogadordaVez == 'p')))
				opt[i] = 0;
		}
		if((opt[0] == 0) && (opt[1] == 0))
		{
			printf("Nao ha opcoes, escolha outra casa \n");
			goto ESCOLHADECASA;
		}
		if((opt[0] == 0) && (opt[1] != 0))
		{
			opt[0] = opt[1];
			opt[1] = 0;
		}
		for(i = 0; opt[i] != 0; i++)
		{
			if(opt[i] == 0) continue;
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
			aux = LIS_ObterValor(casa);
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
OPCAORESTANTE:
		displayJogo(Principal);
		opcaorestante = (opt[opcao - 1] == dado1)? dado2 : dado1;
		if((dado1 == dado2) && !flag) printf("Dados Restantes : %d %d %d\n", dado1, dado2, dado1);
		else	printf("Dado Restante : %d \n", opcaorestante);
		opt[opcao-1] = 0;
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
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		aux = LIS_ObterValor(casa);
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
		for(i = 0; i < 3; i++)
		{
			if(((jogadordaVez == 'b') && (opt[i] + casaEscolhida  > 24)) || ((casaEscolhida - opt[i] < 1) && (jogadordaVez == 'p')))
				opt[i] = 0;
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
			aux = LIS_ObterValor(casa);
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
		displayJogo(Principal);
		if((dado1 == dado2) && !flag)
		{
			printf("Dados : %d %d \n", dado1, dado2);
			flag = 1;
			for(i = 0; i < 2; i++) opt[i] = 0;
			goto DOBRADO;
		}
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
		jogadordaVez = QUESTION 'p' : 'b';
		contOpt = 0;
		for(i = 0; i < 3; i++)
			opt[i] = 0;
		PF_ObterTamanhoPF(pfbranca, &tampfb);
		PF_ObterTamanhoPF(pfpreta, &tampfp);
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

void salvarJogo(LIS_tppLista estrutura)
{
	TAB_tppTabuleiro tab; // tabuleiro
	PF_tppFinalizadas pfb, pfp; // pecas finalizadas
	BAR_tppCapturadas barb, barp; // pecas capturadas
	tppDadoPontos dp;
	char  corpeca;
	int tamanho; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo
	LIS_tppLista casas, listaAux;
	tppPeca peca;
	int i, valorpartida;
	char  dono;
	FILE* fp = fopen("game.txt", "w");

	// obter o valor de cada estrutura
	IrInicioLista(estrutura);
	system("cls");
	tab = (TAB_tppTabuleiro)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (save) \n");
		exit(-1);
	}

	barb = (BAR_tppCapturadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (save) \n");
		exit(-1);
	}
	pfb = (PF_tppFinalizadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (save) \n");
		exit(-1);
	}

	barp = (BAR_tppCapturadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (save) \n");
		exit(-1);
	}
	pfp = (PF_tppFinalizadas)LIS_ObterValor(estrutura);
	if(LIS_AvancarElementoCorrente(estrutura, 1) != LIS_CondRetOK)
	{
		printf("Erro ao andar na estrutura principal (save) \n");
		exit(-1);
	}
	dp = (tppDadoPontos)LIS_ObterValor(estrutura);

	if(TAB_ObterCasas(tab, &casas) != TAB_CondRetOK)
	{
		printf("Erro ao obter as casas (display) \n");
		exit(-1);
	}
	// anda pelas casas do tabuleiro obtendo a cor e quantidade de peças e guarda num arquivo
	IrInicioLista(casas);
	for(i = 0; i < 24; i++)
	{
		listaAux = (LIS_tppLista)LIS_ObterValor(casas);
		IrInicioLista(listaAux);
		peca = (tppPeca)LIS_ObterValor(listaAux);
		tamanho = LIS_ObterTamanho(listaAux);
		if(tamanho == 0) 
		{
			fprintf(fp, "%d", tamanho);
			fprintf(fp,"\n");
			LIS_AvancarElementoCorrente(casas, 1);
			continue;
		}
		Pec_ObterCor(peca, &corpeca);
		fprintf(fp, "%d", tamanho);
		fprintf(fp, "%c", corpeca);
		fprintf(fp,"\n");
		LIS_AvancarElementoCorrente(casas, 1);
	}
	BAR_ObterTamanhoBar(barb, &tamanho);
	fprintf(fp, "%d", tamanho);
	fprintf(fp,"\n");
	PF_ObterTamanhoPF(pfb, &tamanho);
	fprintf(fp, "%d", tamanho);
	fprintf(fp,"\n");
	BAR_ObterTamanhoBar(barp, &tamanho);
	fprintf(fp, "%d", tamanho);
	fprintf(fp,"\n");
	PF_ObterTamanhoPF(pfp, &tamanho);
	fprintf(fp, "%d", tamanho);
	fprintf(fp,"\n");
	DADPnt_ValorPartida(dp, &valorpartida);
	fprintf(fp, "%d", valorpartida);
	fprintf(fp,"\n");
	DADPnt_ObterDono(dp, &dono);
	fprintf(fp, "%c", dono);
	fprintf(fp,"\n");
	fclose(fp);
}
LIS_tppLista carregaJogo(FILE** fp)
{
	TAB_tppTabuleiro tab; // tabuleiro
	PF_tppFinalizadas pfb, pfp; // pecas finalizadas
	BAR_tppCapturadas barb, barp; // pecas capturadas
	tppDadoPontos dp;
	LIS_tppLista estrutura = LIS_CriarLista(DestruirValor);
	char  corpeca, branco = 'b', preto = 'p';
	int tamanho; // tamanho da estrutura de pecas finalizadas, elas que determinam o termino do jogo
	LIS_tppLista casas, listaAux;
	tppPeca peca;
	int i, j,valorpartida, novovalor = 2;
	char  dono;
	*fp = fopen("game.txt", "r");
	if(*fp == NULL) {printf("erro ao abrir arquivo \n"); return ;}

	TAB_CriarTabuleiro(&tab, DestruirValor);
	PF_CriarPF(&pfb, branco, DestruirValor);
	PF_CriarPF(&pfp, preto, DestruirValor);
	BAR_CriarBAR(&barb, branco, DestruirValor);
	BAR_CriarBAR(&barp, preto, DestruirValor);
	DADPnt_CriarDado(&dp);
	TAB_ObterCasas(tab, &casas);
	IrInicioLista(casas);
	// esvaziar as casas do tabuleiro criado
	for(i = 0; i < 24; i++)
	{
		listaAux = (LIS_tppLista)LIS_ObterValor(casas);
		LIS_EsvaziarLista(listaAux);
		LIS_AvancarElementoCorrente(casas, 1);
	}
	IrInicioLista(casas);
	for( i = 0; i < 24; i++)
	{
		listaAux = (LIS_tppLista)LIS_ObterValor(casas);
		fscanf(*fp, "%d", &tamanho);
		if(tamanho == 0)
		{
			LIS_AvancarElementoCorrente(casas, 1);
			fscanf(*fp, "\n");
			continue;
		}
		fscanf(*fp, "%c", &corpeca);
		for(j = 0; j < tamanho; j++)
		{
			Pec_CriarPeca(&peca, corpeca);
			LIS_InserirElementoApos(listaAux, peca);
		}
		fscanf(*fp, "\n");
		LIS_AvancarElementoCorrente(casas, 1);
	}
	fscanf(*fp, "%d", &tamanho);
	fscanf(*fp, "\n");
	for(i = 0; i < tamanho; i++)
	{
		BAR_AdicionarPeca(barb);
	}
	fscanf(*fp, "%d", &tamanho);
	fscanf(*fp, "\n");
	for(i = 0; i < tamanho; i++)
	{
		PF_AdicionarPeca(pfb);
	}
	fscanf(*fp, "%d", &tamanho);
	fscanf(*fp, "\n");
	for(i = 0; i < tamanho; i++)
	{
		BAR_AdicionarPeca(barp);
	}
	fscanf(*fp, "%d", &tamanho);
	fscanf(*fp, "\n");
	for(i = 0; i < tamanho; i++)
	{
		PF_AdicionarPeca(pfp);
	}
	fscanf(*fp, "%d", &valorpartida);
	fscanf(*fp, "\n");
	fscanf(*fp, "%c", &dono);
	while(novovalor != valorpartida)
	{
		DADPnt_DobrarDado(dp, dono);
		valorpartida*=2;
	}
	LIS_InserirElementoApos(estrutura, tab);
	LIS_InserirElementoApos(estrutura, barb);
	LIS_InserirElementoApos(estrutura, pfb);
	LIS_InserirElementoApos(estrutura, barp);
	LIS_InserirElementoApos(estrutura, pfp);
	LIS_InserirElementoApos(estrutura, dp);
	return estrutura;
	fclose(*fp);
}
void finalizarPeca(TAB_tppTabuleiro *pTab, PF_tppFinalizadas *pPF, int num)
{
	LIS_tppLista casas, casa;
	char corpf;
	TAB_ObterCasas(*pTab, &casas);
	PF_ObterCorPF(*pPF, &corpf);
	(corpf == 'b')? IrInicioLista(casas) : IrFinalLista(casas);
	LIS_AvancarElementoCorrente(casas,(corpf == 'b')? num - 1 : -num + 1);
	casa = (LIS_tppLista)LIS_ObterValor(casas);
	LIS_ExcluirElemento(casa);
	PF_AdicionarPeca(*pPF);
}
int contaUltimasCasas(TAB_tppTabuleiro *pTab, char cor, int qtd)
{
	int cont = 0, i;
	LIS_tppLista casa, casas;
	TAB_ObterCasas(*pTab, &casas);
	(cor == 'b')? IrInicioLista(casas) : IrFinalLista(casas);
	for(i = 0; i < qtd; i++)
	{
		casa = (LIS_tppLista)LIS_ObterValor(casas);
		cont += LIS_ObterTamanho(casa);
		LIS_AvancarElementoCorrente(casas, (cor == 'b')? 1:-1);
	}
	return cont;
}









			