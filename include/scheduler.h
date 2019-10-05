#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ucontext.h"
#include "support.h"

FILA2 *initQueue();

void initSchedulerQueues();

int initMainThread();

int insertReadyQueue(TCB_t *thread);

void runThread(TCB_t *thread);

TCB_t *getRunningThread();

int scheduleNewThread();

int blockThread();

int yield();

int unlockThread(int tid);

void killThread();

TCB_t *findReadyThreadByTID(int tid);

int waitForThread(int tid);

int insertOrderedFila2(PFILA2 pFila, s_TCB *content);

s_TCB *getAndRemoveFirstThread(PFILA2 pFila);

#endif


