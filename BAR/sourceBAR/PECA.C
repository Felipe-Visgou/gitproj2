/***************************************************************************
*  $MCI Módulo de implementação: PEC Estrutura Peca
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
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
*	  1.0     tbm   14/set/2015	Início do desenvolvimento
*
***************************************************************************/


#include   <stdio.h>
#include   <string.h>
#include   <malloc.h>

#define PECA_OWN
#include "PECA.h"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: PECPnt Descritor do dados de ponto.
*
*  $ED Descrição do tipo
*		Descreve a estrutura de peça
***********************************************************************/

typedef struct tgPeca{
	char cor;
} tpPeca;


/*****  Dados encapsulados no módulo  *****/

// vazio

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: Pec Criar Peça
*  ****/

Pec_tpCondRet Pec_CriarPeca(tppPeca * PecCriado, char CorDaNovaPeca)
{
	*PecCriado= (tppPeca)malloc(sizeof(struct tgPeca));

	if(PecCriado == NULL)
		return Pec_CondRetFaltouMemoria;

	(*PecCriado)->cor = CorDaNovaPeca;

	return Pec_CondRetOK;
}

/***************************************************************************
*
*  Função: PEC Destruir Peça
*  ****/

Pec_tpCondRet Pec_DestruirPeca(tppPeca  Peca)
{

	free(Peca);
	return Pec_CondRetOK;
}

/***************************************************************************
*
*  Função: PEC Obter Cor
*  ****/

Pec_tpCondRet Pec_ObterCor(tppPeca  Peca, char *cor)
{
	*cor = Peca->cor;
	return Pec_CondRetOK;
}

/*********** Fim do módulo de implementação: Módulo DadoPontos **************/
