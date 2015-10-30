/***************************************************************************
*  $MCI Módulo de implementação: Gerador de numeroes aleatorios restrito ao
*								 numero de faces 
*
*  Arquivo gerado:              DADO.c
*  Letras identificadoras:      DAD
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
*     Versão  Autor			  Data     Observações
*	  1.0     tbm, fvc   02/set/2015	Início do desenvolvimento

*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DADO_OWN
#include "DADO.h"
#include <assert.h>
#undef DADO_OWN
#define RAN_MAX 0x7fff

/***************************************************************************
*
*  Função: DAD & gerar o numero de casas que devem ser puladas com 1 dado
*  ****/


/*****  Código das funções encapsuladas no módulo  *****/

int randint(int n);


/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: DAD  &Gera numero aleatório
*  ****/

DAD_tpCondRet DAD_NumPular(int *NumeroCasas)
{
	*NumeroCasas = randint(6);

	return DAD_CondRetOK;

}/*Fim da função DAD_NumPular */


/* Função usada pelo módulo */
/* Returns an integer in the range [1, n]*/
int randint(int n) {
  int r;
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {
    long end = RAND_MAX / n; // truncate skew
    assert (end > 0L);
    end *= n;
    while ((r = rand()) >= end);

	r = (r|time(NULL));

    return (r % n) +1;
  }
}
/*********** Fim do módulo de implementação: Módulo Dado **************/







