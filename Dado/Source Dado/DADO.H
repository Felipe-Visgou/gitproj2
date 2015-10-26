/***************************************************************************
*
*  $MCD Módulo de definição: Módulo Dado
*
*  Arquivo gerado:              Dado.H
*  Letras identificadoras:      DAD
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
*       1.00   fvc   15/08/2001 Início e término do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para gerar o resultado
*	  do dado "lançado".
*
***************************************************************************/
 
#if defined( DADO_OWN )
   #define DADO_EXT
#else
   #define DADO_EXT extern
#endif

/***********************************************************************
*
*  $TC Tipo de dados: DAD Condicoes de retorno
*
***********************************************************************/

   typedef enum {

         DAD_CondRetOK = 0 ,
               /* Executou correto */

         DAD_CondRetErro = 1 ,
               /* Estrutura do DadoPontos está errada */

         DAD_CondRetMatrizNaoExiste = 2 ,
               /* DadoPontos não existe */

         DAD_CondRetFaltouMemoria = 3
               /* Faltou memória ao alocar dados */

   } DAD_tpCondRet ;

/***********************************************************************
*
*  $FC Função: DAD  &Gerar o numero de casas a serem puladas.
*
*  $ED Descrição da função
*	  Retorna o numero de casas a serem percorridas.
* 
*  $FV Valor retonado
*     DAD_CondRetOK            - Gera numero aleatorio de casas a serem percorridas.
*     DAD_CondRetFaltouMemoria - Numero aleatorio de casas a serem percorridas nao foi gerado por falta de memoria.
* 
*  $EAE Assertivas de Entrada
*   Existe um ponteiro para o número inteiro de casas a serem caminhadas que aponta para uma regiao desconhecida na memoria.
* 
*  $EAS Assertivas de Saída
*   Caso nao haja memoria suficiente, é retornada a condicao de retorno correspondente.
* 
***********************************************************************/

DAD_tpCondRet DAD_NumPular(int *NumeroCasas) ;

#undef DADO_EXT

/*************** Fim do módulo de definição: Módulo Dado ****************/
