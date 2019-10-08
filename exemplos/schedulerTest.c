
/*
 *	Programa de exemplo de uso da biblioteca cthread
 *
 *	Versao 1.0 - 14/04/2016
 *
 *	Sistemas Operacionais I - www.inf.ufrgs.br
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <time.h>
//#include <unistd.h>

void delay(int milliseconds)
{
    double end_time = ((double)clock()) / (CLOCKS_PER_SEC / 1000) + milliseconds;

    while (((double)clock()) / (CLOCKS_PER_SEC / 1000) < end_time);
}

void *thread2(void *arg)
{
    printf("3\n");
    return NULL;
}

void *thread1(void *arg)
{
    int id1 = ccreate(thread2, (void *)&id1, 0);
    printf("2\n");
    delay(2000); //sleep(2);
    cyield();
    printf("5\n");
    return NULL;
}

int main(int argc, char *argv[])
{

    int id0 = ccreate(thread1, (void *)&id0, 0);

    printf("Ordem dos prints:\n");
    printf("1\n");

    delay(1000); //sleep(1);

    cyield();
    printf("4\n");

    cjoin(id0);

    printf("6\n");

    return 0;
}