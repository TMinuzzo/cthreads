/*

 * cdata.h: arquivo de inclusão de uso apenas na geração da libpithread
 *
 * VERSÃO: 29/03/2019
 *
 */
#ifndef __cdata__
#define __cdata__
#include "ucontext.h"

/* Estados das threads
*/

#define PROCST_NOVO 0		/* Processo criado */
#define	PROCST_APTO	1		/* Processo em estado apto a ser escalonado */
#define	PROCST_EXEC	2		/* Processo em estado de execu��o */
#define	PROCST_BLOQ	3		/* Processo em estado bloqueado */
#define	PROCST_TERMINO	4	/* Processo em estado de terminado */

 
typedef struct s_TCB { //thread control block
	/* OS CAMPOS ABAIXO NÃO PODEM SER ALTERADOS OU REMOVIDOS
	*/
	int		tid; 		// identificador da thread
	int		state;		// estado em que a thread se encontra (CONFORME DEFINES ANTERIORES)
	int 		prio;		// Prioridade associada a thread
	ucontext_t 	context;	// contexto de execução da thread (SP, PC, GPRs e recursos) 
	
	/* A PARTIR DESSE PONTO PODEM SER ACRESCENTADOS CAMPOS NECESSÁRIOS AO DESENVOLVIMENTO DA BIBLIOTECA
	*/
	
} TCB_t; 


#endif
