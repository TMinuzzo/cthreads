#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/thread.h"


// Filas respectivas a cada um dos estado (Executando, Bloqueado, Terminado, Apto)
FILA2 *runningQueue, *blockedQueue, *finishedQueue, *readyQueue;

// Fila para pares thread_pai/thread_filho para a operação JOIN
FILA2 *joinQueue;

TCB_t *mainThreadTCB;
ucontext_t mainThreadContext;

FILA2 *initQueue()
{
    PFILA2 queue = (PFILA2)malloc(sizeof(FILA2));
    CreateFila2(queue);

    return queue;
}

/*PRIO_QUEUE_t *initPriorityQueue()
{
    PRIO_QUEUE_t *queue = malloc(sizeof(PRIO_QUEUE_t));
    queue->high = initQueue();
    queue->medium = initQueue();
    queue->low = initQueue();

    return queue;
}*/

void initSchedulerQueues() //Changed func
{
    // State Queues
    readyQueue = initQueue();
    runningQueue = initQueue();
    blockedQueue = initQueue();
    finishedQueue = initQueue();

    // Join Pair Queue
    joinQueue = initQueue();
}

int initMainThread() //Changed func
{
    mainThreadTCB = (TCB_t *)malloc(sizeof(TCB_t));

    initSchedulerQueues();

    getcontext(&mainThreadContext);
    mainThreadTCB = createThread(mainThreadContext, 0);
    

    if (mainThreadTCB != NULL)
    {
        mainThreadTCB->state = PROCST_EXEC;
        AppendFila2(runningQueue, mainThreadTCB);
        return 0;
    }
    else
        return -1;
}

int insertReadyQueue(TCB_t *thread) //Changed func
{
    thread->state = PROCST_APTO;

    return insertOrderedFila2(readyQueue, thread);
}

// void runThread(TCB_t *thread) //Not changed
// {
//     startTimer();
//     thread->state = PROCST_EXEC;
//     AppendFila2(runningQueue, thread);
//     setcontext(&(thread->context));
// }

// TCB_t *getRunningThread() //Changed func
// {
//     TCB_t *thread = (TCB_t *)malloc(sizeof(TCB_t));
//     if (FirstFila2(runningQueue) != 0)
//         return NULL;

//     return GetAtIteratorFila2(runningQueue);
// }

// /*TCB_t *popPriorityThread(PRIO_QUEUE_t *queue) //Not used anymore
// {
//     TCB_t *thread = malloc(sizeof(TCB_t));

//     // Verifica se existe alguma thread de prioridade alta
//     if (FirstFila2(queue->high) == 0)
//     {
//         thread = GetAtIteratorFila2(queue->high);
//         DeleteAtIteratorFila2(queue->high);
//     }
//     else if (FirstFila2(queue->medium) == 0)
//     {
//         thread = GetAtIteratorFila2(queue->medium);
//         DeleteAtIteratorFila2(queue->medium);
//     }
//     else if (FirstFila2(queue->low) == 0)
//     {
//         thread = GetAtIteratorFila2(queue->low);
//         DeleteAtIteratorFila2(queue->low);
//     }
//     else
//         return NULL;

//     return thread;
// }*/

// int scheduleNewThread() //Changed func
// {
//     TCB_t *thread = (TCB_t *)malloc(sizeof(TCB_t));
//     thread = getAndRemoveFirstThread(readyQueue);

//     if (thread == NULL)
//         return -1;

//     runThread(thread);
//     return 0;
// }

// int blockThread() //Changed: add stopTimer()
// {
//     // Identifica a thread que está em execução
//     TCB_t *thread = getRunningThread();
//     int hasBeenBlocked = 0;

//     if (thread == NULL)
//         return -1;

//     FirstFila2(runningQueue);
//     DeleteAtIteratorFila2(runningQueue);
//     // Salva o contexto de execução da thread
//     getcontext(&(thread->context));

//     if (hasBeenBlocked == 0)
//     {
//         hasBeenBlocked = 1;
//         thread->state = PROCST_BLOQ;
//         thread->prio = (int)stopTimer();
//         AppendFila2(blockedQueue, thread);
//         scheduleNewThread();
//     }

//     return 0;
// }

// int yield() //Changed: add stopTimer()
// {
//     // Identifica a thread que está em execução
//     TCB_t *thread = getRunningThread();
//     int hasYielded = 0;

//     if (thread == NULL)
//         return -1;

//     FirstFila2(runningQueue);
//     DeleteAtIteratorFila2(runningQueue);
//     // Salva o contexto de execução da thread
//     getcontext(&(thread->context));

//     if (hasYielded == 0)
//     {
//         hasYielded = 1;
//         thread->state = PROCST_APTO;
//         thread->prio = (int)stopTimer();
//         insertReadyQueue(thread);
//         // Chama o escalonador para executar outra thread
//         scheduleNewThread();
//     }

//     return 0;
// }

// int unlockThread(int tid) //Not changed
// {
//     // Percorre a fila de threads bloqueadas
//     TCB_t *thread = (TCB_t *)malloc(sizeof(TCB_t));
//     FirstFila2(blockedQueue);
//     do
//     {
//         thread = (TCB_t *)GetAtIteratorFila2(blockedQueue);
//         if (thread == NULL)
//             break;
//         if (thread->tid == tid)
//         {
//             // Se encontrar a thread, transfera da fila bloqueados para a fila aptos
//             DeleteAtIteratorFila2(blockedQueue);
//             thread->state = PROCST_APTO;
//             insertReadyQueue(thread);
//             return 0;
//         }
//     } while (NextFila2(blockedQueue) == 0);

//     return -1;
// }

// void killThread()
// {
//     // Identifica a thread que está em execução
//     TCB_t *thread = getRunningThread();

//     stopTimer();

//     // Remove a thread da fila "executando"
//     FirstFila2(runningQueue);
//     DeleteAtIteratorFila2(runningQueue);
//     // Atualiza o estado da thread
//     thread->state = PROCST_TERMINO;

//     // Verifica se existe alguma thread esperando pela thread finalizada
//     JOIN_PAIR_t *joinPair = (JOIN_PAIR_t *)malloc(sizeof(JOIN_PAIR_t));
//     FirstFila2(joinQueue);
//     do
//     {
//         joinPair = (JOIN_PAIR_t *)GetAtIteratorFila2(joinQueue);
//         if (joinPair == NULL)
//             break;
//         if (joinPair->tid_running_thread == thread->tid)
//         {
//             DeleteAtIteratorFila2(joinQueue);
//             unlockThread(joinPair->tid_blocked_thread);
//         }
//     } while (NextFila2(joinQueue) == 0);

//     AppendFila2(finishedQueue, thread);
//     scheduleNewThread();
// }

// /*int setRunningThreadPriority(int prio)
// {
//     TCB_t *thread = getRunningThread();

//     if (thread == NULL)
//         return -1;

//     thread->prio = prio;
//     return 0;
// }*/

// TCB_t *findReadyThreadByTID(int tid) //changed func
// {
//     // Percorre a fila de aptos
//     TCB_t *thread = (TCB_t *)malloc(sizeof(TCB_t));
//     FirstFila2(readyQueue);
//     do
//     {
//         thread = (TCB_t *)GetAtIteratorFila2(readyQueue);
//         if (thread == NULL)
//             break;
//         if (thread->tid == tid)
//             return thread;  // Se encontrar a thread, retorna um ponteiro para o seu TCB
//     } while (NextFila2(readyQueue) == 0);

//     // Se não encontrar a thread, retorna NULL
//     return NULL;
// }

// int waitForThread(int tid)
// {
//     // Thread em execução
//     TCB_t *thread = getRunningThread();

//     // Verifica se a thread a ser bloqueada existe
//     if (thread == NULL)
//         return -1;

//     // Verifica se a thread bloqueante existe
//     if (findReadyThreadByTID(tid) == NULL)
//         return -3;

//     // Verifica se a thread bloqueante já bloqueia outra thread
//     JOIN_PAIR_t *joinPair = malloc(sizeof(JOIN_PAIR_t));
//     if (FirstFila2(joinQueue) == 0)
//     {
//         do
//         {
//             joinPair = (JOIN_PAIR_t *)GetAtIteratorFila2(joinQueue);
//             if (joinPair == NULL)
//                 break;
//             if (joinPair->tid_running_thread == tid)
//                 return -4;
//         } while (NextFila2(joinQueue) == 0);
//     }

//     joinPair->tid_blocked_thread = thread->tid;
//     joinPair->tid_running_thread = tid;
//     AppendFila2(joinQueue, joinPair);

//     blockThread();
//     return 0;
// }

int insertOrderedFila2(PFILA2 pFila, TCB_t *content) //New func
{
    if (pFila == NULL)
        return -1;

    TCB_t *thread = (TCB_t *)malloc(sizeof(TCB_t));

    if (FirstFila2(pFila) == 0) //Volta a fila para o primeiro elemento
    {
        do //Ordena a fila da prioridade de menor valor para a de maior
        {
            thread = (TCB_t *)GetAtIteratorFila2(pFila);
            if (thread == NULL)
                return AppendFila2(pFila, (void *)content);
            if ((unsigned)content->prio < (unsigned)thread->prio)
                return InsertBeforeIteratorFila2(pFila, (void *)content);
        } while (NextFila2(pFila) == 0);

        return AppendFila2(pFila, (void *)content);
    }

    return -1;
}

// s_TCB *getAndRemoveFirstThread(PFILA2 pFila) //New func
// {
//     s_TCB *thread = (TCB_t *)malloc(sizeof(TCB_t));
//     if (FirstFila2(pFila) == 0)
//     {
//         thread = (s_TCB *)GetAtIteratorFila2(pFila);
//         DeleteAtIteratorFila2(pFila);
//     }
//     return thread;
// }