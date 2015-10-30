/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Peça
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Nome da base de software:    Exemplo de teste automatizado
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores:	fvc - Felipe Vieira Côrtes
*			tbm - Tássio Borges de Miranda
*			db  - Daniela Brazão

*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       1.00   tbm   14/09/2015 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para manipular a peça
*	alem de descrever sua estrutura.
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
*
***********************************************************************/

   typedef enum {

         Pec_CondRetOK = 0 ,
               /* Executou correto */

         Pec_CondRetErro = 1 ,
               /* Estrutura do DadoPontos está errada */

         Pec_CondRetMatrizNaoExiste = 2 ,
               /* DadoPontos não existe */

         Pec_CondRetFaltouMemoria = 3
               /* Faltou memória ao alocar dados */

   } Pec_tpCondRet ;

/***********************************************************************
*
*  $FC Função: PEC Criar Peça
*
*  $ED Descrição da função
*	  Cria uma nova peça
*  $FV Valor retonado
*     Pec_CondRetOK
*     Pec_CondRetFaltouMemoria
*
***********************************************************************/

  Pec_tpCondRet Pec_CriarPeca(tppPeca * PecCriado1, char CorDaNovaPeca);

/***********************************************************************
*
*  $FC Função: PEC Destruir Peça
*
*  $ED Descrição da função
*	  Destroi uma peça
*  $FV Valor retonado
*     Pec_CondRetOK
*     Pec_CondRetFaltouMemoria
*
***********************************************************************/

  Pec_tpCondRet Pec_DestruirPeca(tppPeca Peca);

/***********************************************************************
*
*  $FC Função: PEC Obter Cor
*
*  $ED Descrição da função
*	  Obtem cor de uma peca
*  $FV Valor retonado
*     Pec_CondRetOK
*     Pec_CondRetFaltouMemoria
*
***********************************************************************/
Pec_tpCondRet Pec_ObterCor(tppPeca Peca, char *cor);