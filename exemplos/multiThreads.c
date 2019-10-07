
/*
 *	Programa de teste da biblioteca cthread
 *
 *	Esse programa cria NUM_THREADS threads:
 *		- Apos a craicao das threads, uma mensagem eh exibida
 *		no console informando que as threads foram criadas.
 *		- A Main cede voluntariamente a CPU e vai para o fim
 *		da fila de aptos (cyield).
 *		- Cada thread imprime a sua ID e termina.
 *		- Novamente, uma mensagem eh exibida informando que a
 *		thread da Main voltou a ser executada.
 *
 * 	Novamente, sao criadas NUM_THREADS threads:
 * 		- Apos a craicao das threads, uma mensagem eh exibida
 *		no console informando que as threads foram criadas.
 *		- A Main chama a funcao cjoin() para aguardar a
 *		execucao de cada uma das threads.
 *		- Cada thread imprime a sua ID e termina.
 *		- Novamente, uma mensagem eh exibida informando que a
 *		thread da Main voltou a ser executada.
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

#define NUM_THREADS 50

void *func(void *arg) {
	printf("Thread ID%d running.\n", *((int *)arg));
	return NULL;
}

int main(int argc, char *argv[]) {

	int id[NUM_THREADS] = { 0 };
	int i = 0;

	for (i = 0; i < NUM_THREADS; i++)
		id[i] = ccreate(func, (void *)&id[i], 0);

	printf("Main after threads are created for the first time.\n");

	cyield();

	printf("Main returns to rerun the process.\n");

	for (i = 0; i < NUM_THREADS; i++)
		id[i] = ccreate(func, (void *)&id[i], 0);

	printf("Main after threads are created for the second time.\n");

	for (i = 0; i < NUM_THREADS; i++)
		cjoin(id[i]);

	printf("Main returns to finish the process.\n");

	return 0;
}