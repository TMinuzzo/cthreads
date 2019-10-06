
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/signal.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/scheduler.h"
#include "../include/thread.h"

/*
	OBS: Todas as funções devem testar no começo se a chamada
	vem da main() - vide Seção 4 da definição do trabalho
*/
ucontext_t dispatcherContext;
char dispatcherStack[SIGSTKSZ];

/*
 * Creates a new thread
 * Parametes:
 * 	start: pointer to functwdaion the thread will run
 *  arg: general parametr
 *  prio: priority, should NOT b
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int ccreate(void *(*start)(void *), void *arg, int prio)
{
	initializeScheduler();
	ucontext_t newContext;
	getcontext(&newContext);

	newContext.uc_link = &dispatcherContext;
	newContext.uc_stack.ss_sp = malloc(SIGSTKSZ);
	newContext.uc_stack.ss_size = SIGSTKSZ;

	makecontext(&newContext, (void (*)(void))start, 1, arg);

	TCB_t *newThread = createThread(newContext, prio);

	int status = insertReadyQueue(newThread);
	if(status < 0)
		return -1;
	else
		return newThread->tid;
}

/*
 * Voluntary transfer
 * 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cyield(void)
{
	initializeScheduler();

	return yield();
}

/*
 * Parameters:
 * 	tid: thread identifier 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cjoin(int tid)
{
	initializeScheduler();
	//debugLog("\nJoin(): esperando thread  com id: %d\n", tid);
	
	return waitForThread(tid);
}

/* Initialize the csem_t structure, that represents a semaphore
 * Parameters:
 * 	csem_t: pointer to semaphore
 *  count: value to initialize semaphore. Represents how many resources the semaphore controls
 * 		   for a binary semaphore, count = 1
 * 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int csem_init(csem_t *sem, int count)
{
	initializeScheduler();

	if (sem == NULL)
		return -1;

	sem->count = count;
	sem->fila = initQueue();

	return 0;
}

/* 
 * Request a resource protected by semaphore, and manage a queue if the resource is being used
 * Parameters:
 * 	csem_t: pointer to semaphore
 * 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cwait(csem_t *sem)
{
	initializeScheduler();

	// Verifica se o semáforo existe e foi inicializado
	if(sem == NULL || sem->fila == NULL)
		return -1;

	(sem->count)--;

	if (sem->count < 0){
		//Busca a thread em execução e verifica se ela exeste
		TCB_t *thread = getRunningThread(); 
		if (thread == NULL)
			return -1;

		// Adiciona a thread atual fila do semáforo
		AppendFila2(sem->fila, (void *)(thread->tid));
		return blockThread();
	}
	return 0;
}

/*
 * Release a resource protected by semaphore
 * Parameters:
 * 	csem_t: pointer to semaphore
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int csignal(csem_t *sem)
{
	initializeScheduler();

	// Verifica se o semáforo existe e foi inicializado
	if (sem == NULL || sem->fila == NULL)
		return -1;

	(sem->count)++;

	if (sem->count < 1)
	{
		FirstFila2(sem->fila);
		int tid = (int)GetAtIteratorFila2(sem->fila);
		DeleteAtIteratorFila2(sem->fila);

		return unlockThread(tid);
	}
	return 0;
}

/*
 * 
 * Parameters:
 * 	name: pointer to memory area wich contains the names and card ids
 * Return:
 *	 0: Success
*/
int cidentify(char *name, int size)
{
	strncpy(name, "Gabriel Lando - 00291399\nLeonardo Lauryel - 00275616\nThayná Minuzzo - 00262525", size);
	return 0;
}