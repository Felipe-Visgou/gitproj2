/***************************************************************************
 *
 *  $MCD Modulo de definicao: Modulo Dado
 *
 *  Arquivo gerado:              Dado.H
 *  Letras identificadoras:      DAD
 *
 *  Nome da base de software:    Exemplo de teste automatizado
 *
 *  Projeto: Disciplinas INF 1628 / 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores:	fvc - Felipe Vieira Cortes
 *              tbm - Tassio Borges de Miranda
 *		db  - Daniela Brazao
 *
 *  $HA Historico de evolucao:
 *     Versao  Autor    Data     Observacoes
 *       1.00   fvc   15/08/2001 Início e termino do desenvolvimento
 *
 *  $ED Descricao do modulo
 *     Este modulo implementa um conjunto simples de funcoes para gerar o resultado
 *     do dado "lancado".
 *
 ***************************************************************************/

#if defined( DADO_OWN )
#define DADO_EXT
#else
#define DADO_EXT extern
#endif

/***********************************************************************
 *
 *  $TC Tipo de dados: DAD &Condicoes de retorno
 *
 ***********************************************************************/

typedef enum {
    DAD_CondRetOK = 0,
    /* Executou corretamente */

    DAD_CondRetErro = 1,
    /* Estrutura do DadoPontos esta errada */

    DAD_CondRetMatrizNaoExiste = 2,
    /* DadoPontos nao existe */

    DAD_CondRetFaltouMemoria = 3
    /* Faltou memoria ao alocar dados */

} DAD_tpCondRet;

/***********************************************************************
 *
 *  $FC Funcao: DAD  &Gerar o numero de casas a serem puladas
 *
 *  $ED Descricao da funcao
 *	  Retorna o numero de casas a serem percorridas.
 * 
 *  $FV Valor retonado
 *     DAD_CondRetOK            - Gera numero aleatorio de casas a serem percorridas.
 *     DAD_CondRetFaltouMemoria - Numero aleatorio de casas a serem percorridas nao foi gerado por falta de memoria.
 * 
 *  $EAE Assertivas de Entrada
 *   Existe um ponteiro de inteiro vazio.
 * 
 *  $EAS Assertivas de Saida
 *   Caso tenha executado corretamente, retorna no ponteiro de int um numero inteiro aleatorio de 1 a 6 correspondente ao numero de casas a serem puladas.
 * 
 *   Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
 * 
 ***********************************************************************/

DAD_tpCondRet DAD_NumPular(int *NumeroCasas);

#undef DADO_EXT

/*************** Fim do modulo de definicao: Modulo Dado ****************/