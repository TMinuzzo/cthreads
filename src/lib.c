
#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"

/*
	OBS: Todas as funções devem testar no começo se a chamada
	vem da main() - vide Seção 4 da definição do trabalho
*/


int ccreate (void* (*start)(void*), void *arg, int prio) {
	return -9;
}

int cyield(void) {
	return -9;
}

int cjoin(int tid) {
	return -9;
}

int csem_init(csem_t *sem, int count) {
	return -9;
}

int cwait(csem_t *sem) {
	return -9;
}

int csignal(csem_t *sem) {
	return -9;
}

int cidentify (char *name, int size) {
	strncpy (name, "Gabriel Lando - 00291399\nLeonardo Lauryel - XXXXXXXX\nThayná Minuzzo - XXXXXXXX", size);
	return 0;
}


