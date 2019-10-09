#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <sys/time.h>
#include <stdlib.h>
#include <ucontext.h>
#include "support.h"
#include "cthread.h"
#include "cdata.h"
#include "thread.h"

void my_startTimer();

unsigned int my_stopTimer();

FILA2 *initQueue();

int insertOrderedFila2(PFILA2 pFila, TCB_t *content);

TCB_t *getAndRemoveFirstThread(PFILA2 pFila);

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