#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "ucontext.h"
#include "support.h"

int insertOrderedFila2(PFILA2 pFila, TCB_t *content);

TCB_t *getAndRemoveFirstThread(PFILA2 pFila);

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

void initializeScheduler();

#endif


