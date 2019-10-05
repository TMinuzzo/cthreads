#include "../include/scheduler.h"

// Filas para os 5 entados
PFILA2 novos, /*aptos,*/ executando, bloqueados, terminados;

// Aparentemente, o estado de apto tem q possuir diversas filas de prioridade

PFILA2 initFila2()
{
    PFILA2 returnFila = (PFILA2)malloc(sizeof(FILA2));
    if(CreateFila2(returnFila))
        return NULL;
    return returnFila;
}

bool initSchedulerFila2(){


    return true;
}

