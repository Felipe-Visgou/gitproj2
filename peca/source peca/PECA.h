/***************************************************************************
 *
 *  $MCD Modulo de definicao: Modulo Peca
 *
 *  Arquivo gerado:              PECA.H
 *  Letras identificadoras:      PEC
 *
 *  Nome da base de software:    Exemplo de teste automatizado
 *
 *  Projeto: Disciplinas INF 1628 / 1301
 *  Gestor:  DI/PUC-Rio
 *  Autores:	fvc - Felipe Vieira Cortes
 *		tbm - Tassio Borges de Miranda
 *		db  - Daniela Brazao
 *
 *  $HA Historico de evolucao:
 *     Versao  Autor    Data     Observacoes
 *       1.00   tbm   14/09/2015 Inicio do desenvolvimento
 *
 *  $ED Descricao do modulo
 *     Este modulo implementa um conjunto simples de funcoes para manipular a peca,
 *     alem de descrever sua estrutura.
 *
 ***************************************************************************/

#if defined( PECA_OWN )
#define PECA_EXT
#else
#define PECA_EXT extern
#endif

typedef struct tgPeca * tppPeca;

/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Condicoes de retorno
 *
 ***********************************************************************/

typedef enum {
    Pec_CondRetOK = 0,
    /* Executou corretamente */

    Pec_CondRetErro = 1,
    /* Estrutura do DadoPontos esta errada */

    Pec_CondRetMatrizNaoExiste = 2,
    /* DadoPontos nao existe */

    Pec_CondRetFaltouMemoria = 3
    /* Faltou memoria ao alocar dados */

} Pec_tpCondRet;

/***********************************************************************
 *
 *  $FC Funcao: PEC &Criar Peca
 *
 *  $ED Descricao da funcao
 *	  Cria uma nova peca.
 * 
 *  $FV Valor retonado
 *     Pec_CondRetOK
 *     Pec_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *     Existe um ponteiro que referencia uma peca a ser criada, e do tipo tppPeca e aponta para uma posicao desconhecida de memoria.
 *     Existe uma variavel do tipo char que corresponde a cor da nova peca.
 * 
 *  $EAS Assertivas de Saida
 *     Caso tenha executado corretamente:
 *      - A peca e criada.
 *      - A cor da peca corresponde ao valor do parametro CorDaNovaPeca.
 * 
 *     Caso nao haja memoria suficiente, e retornada a condicao de retorno correspondente.
 *
 ***********************************************************************/

Pec_tpCondRet Pec_CriarPeca(tppPeca * PecCriado1, char CorDaNovaPeca);

/***********************************************************************
 *
 *  $FC Funcao: PEC &Destruir Peca
 *
 *  $ED Descricao da funcao
 *	  Destroi uma peca.
 * 
 *  $FV Valor retonado
 *     Pec_CondRetOK
 *     Pec_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *     Existe uma variavel do tipo tppPeca que corresponde a peca a ser excluida.
 * 
 *  $EAS Assertivas de Saida
 *   Caso tenha executado corretamente, a memoria alocada dinamicamente para a peca que se deseja excluir e liberada.
 *
 ***********************************************************************/

Pec_tpCondRet Pec_DestruirPeca(tppPeca Peca);

/***********************************************************************
 *
 *  $FC Funcao: PEC &Obter Cor
 *
 *  $ED Descricao da funcao
 *	  Obtem cor de uma peca.
 * 
 *  $FV Valor retonado
 *     Pec_CondRetOK
 *     Pec_CondRetFaltouMemoria
 * 
 *  $EAE Assertivas de Entrada
 *     Existe uma variavel do tipo tppPeca que corresponde a uma peca.
 *     Existe um ponteiro vazio de char.
 * 
 *  $EAS Assertivas de Saida
 *   Caso tenha executado corretamente, a cor da peca e retornada no ponteiro de char.
 * 
 ***********************************************************************/
Pec_tpCondRet Pec_ObterCor(tppPeca Peca, char *cor);

/********** Fim do modulo de definicao: Pec Modulo Peca **********/