
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

/*
	OBS: Todas as funções devem testar no começo se a chamada
	vem da main() - vide Seção 4 da definição do trabalho
*/
int tid = 0;

/*
 * Creates a new thread
 * Parametes:
 * 	start: pointer to function the thread will run
 *  arg: general parameter
 *  prio: priority, should NOT be used, will always be zero
 * 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int ccreate (void* (*start)(void*), void *arg, int prio) 
{
	// TODO: create context to pass int he TCB_t struct
	TCB_t *newThread = malloc(sizeof(TCB_t));
	 *newThread = (TCB_t) { 
		 .tid = tid,
        .state = PROCST_APTO,
        .prio = prio,
        //.context = context
	 };
	tid++;
	// TODO: insert newThread in 'fila de aptos'
	return -1;
}

/*
 * Voluntary transfer
 * 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cyield(void) {
	// TODO: idenfity which thread is running (EXECUTANDO) and release it, sending to APTO state
	// TODO: call scheduler to choose the new thread to go to EXECUTANDO
	return -9;
}

/*
 * Parameters:
 * 	tid: thread identifier 
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cjoin(int tid) {
	// TODO: identify which thread is running (EXECUTANDO) and send it BLOQUEADO
	// TODO: use the tid to identify which thread should wait to finish execution
	// should return when identified that the thread finished
	return -9;

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
int csem_init(csem_t *sem, int count) {
	// TODO: initialize csem_t before using it's value in cwait and csignal
	// TODO: csem_t receives as a second parameter a queue with all the blocked threads
	return -9;	
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
int cwait(csem_t *sem) {
	// TODO: verify if the requested resource is free.
	// 		 YES: assigns the resource to the running thread
	//		 NO: blocks the running thread, and send it to a queue that waits for the resource (semaphore queue)
	// TODO: decrement the csem_t count variable: (sem->count)--				
	return -9;
}

/*
 * Release a resource protected by semaphore
 * Parameters:
 * 	csem_t: pointer to semaphore
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int csignal(csem_t *sem) {
	// TODO: 
	// TODO: increment the csem_t count variable: (sem->count)++
	return -9;
}

/*
 * 
 * Parameters:
 * 	name: pointer to memory area wich contains the names and card ids
 * Return:
 *	 0: Success
 *	-1: Error  
*/
int cidentify (char *name, int size) {
	strncpy (name, "Gabriel Lando - 00291399\nLeonardo Lauryel - XXXXXXXX\nThayná Minuzzo - 00262525", size);
	return 0;
}


