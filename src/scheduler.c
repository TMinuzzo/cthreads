#include "../include/scheduler.h"

// Filas respectivas a cada um dos estado (Apto, Executando, Bloqueado, Terminado)
PFILA2 readyQueue = NULL, runningQueue = NULL, blockedQueue = NULL, finishedQueue = NULL;

// Fila para pares thread_pai/thread_filho para a operação JOIN
PFILA2 joinQueue = NULL;

TCB_t *mainThreadTCB = NULL;
ucontext_t mainThreadContext;

int schedulerInitialized = 0;

ucontext_t dispatcherContext;

FILA2 *initQueue() //Inicializa uma fila
{
    PFILA2 queue = (PFILA2)malloc(sizeof(FILA2));
    CreateFila2(queue);

    return queue;
}

ucontext_t* getDispatcherContext() 
{
    return &dispatcherContext;
}

int insertOrderedFila2(PFILA2 pFila, TCB_t *content) //Insere elementos de forma ordenada na fila (usado para a fila de Aptos)
{
    if (pFila == NULL)
        return -1;

    TCB_t *thread = NULL;

    FirstFila2(pFila); //Volta a fila para o primeiro elemento

    if (GetAtIteratorFila2(pFila) != NULL) //Verifica se a fila não está vazia
    {
        do //Ordena a fila da prioridade de menor valor para a de maior
        {
            thread = (TCB_t *)GetAtIteratorFila2(pFila);
            if (thread == NULL)
                return AppendFila2(pFila, (void *)content);
            if ((unsigned)content->prio < (unsigned)thread->prio) //Verifica a ordem de acordo com a prioridade
                return InsertBeforeIteratorFila2(pFila, (void *)content);
        } while (NextFila2(pFila) == 0);

        return AppendFila2(pFila, (void *)content); // Caso a prioridade seja maior que a de todos os elementos da fila
    }

    return AppendFila2(pFila, (void *)content); //Se a fila estiver vazia, insire um elemento nela
}

TCB_t *getAndRemoveFirstThread(PFILA2 pFila) //Remove e retorna o primeiro elemento da fila (faz um "pop" na fila)
{
    TCB_t *thread = NULL;
    if (FirstFila2(pFila) == 0)
    {
        thread = (TCB_t *)GetAtIteratorFila2(pFila);
        DeleteAtIteratorFila2(pFila);
    }
    return thread;
}

void initSchedulerQueues() //Inicializa todas as filas
{
    // State Queues
    readyQueue = initQueue();
    runningQueue = initQueue();
    blockedQueue = initQueue();
    finishedQueue = initQueue();

    // Join Pair Queue
    joinQueue = initQueue();
}

int initMainThread() //Cria um contexto para a função Main e adiciona ela na fila de execução
{
    initSchedulerQueues();

    getcontext(&mainThreadContext);


    mainThreadTCB = createThread(mainThreadContext, 0);

    if (mainThreadTCB != NULL)
    {
        startTimer(); //Inicia o contador no momento que o contexto é criado para a main
        mainThreadTCB->state = PROCST_EXEC;
        AppendFila2(runningQueue, mainThreadTCB);
        return 0;
    }
    else
        return -1;
}

int insertReadyQueue(TCB_t *thread) //Insere uma thread na fila de aptos
{
    thread->state = PROCST_APTO;
    return insertOrderedFila2(readyQueue, thread);
}

void runThread(TCB_t *thread) //Executa uam thread e inicia o contador de tempo da sua execução
{
    startTimer();
    thread->state = PROCST_EXEC;
    AppendFila2(runningQueue, thread);
    setcontext(&(thread->context));
}

TCB_t *getRunningThread() //Retorna o TCB da thread que está em execução
{
    if (FirstFila2(runningQueue) != 0)
        return NULL;

    return GetAtIteratorFila2(runningQueue);
}

int scheduleNewThread() //Retira a primeira thread da fila de aptos e a inicia
{
    TCB_t *thread = getAndRemoveFirstThread(readyQueue);

    if (thread == NULL)
        return -1;

    runThread(thread);
    return 0;
}

int blockThread() //Interrompe a thread atual e salva o seu tempo de execução no campo "prio"
{
    // Identifica a thread que está em execução
    TCB_t *thread = getAndRemoveFirstThread(runningQueue);
    int hasBeenBlocked = 0;

    if (thread == NULL)
        return -1;

    // Salva o contexto de execução da thread
    getcontext(&(thread->context));

    if (hasBeenBlocked == 0)
    {
        hasBeenBlocked = 1;
        thread->state = PROCST_BLOQ;
        thread->prio = (int)stopTimer();
        AppendFila2(blockedQueue, thread); //Adiciona a fila de bloqueados
        scheduleNewThread();               //Chama o escalonador para executar outra thread
    }

    return 0;
}

int yield() //Interrupção voluntária da thread atual, é salvo o seu tempo de execução no campo "prio"
{
    // Identifica a thread que está em execução
    TCB_t *thread = getAndRemoveFirstThread(runningQueue);
    int hasYielded = 0;

    if (thread == NULL)
        return -1;

    // Salva o contexto de execução da thread
    getcontext(&(thread->context));

    if (hasYielded == 0)
    {
        hasYielded = 1;
        thread->prio = (int)stopTimer();
        insertReadyQueue(thread); //Adiciona a fila de Aptos (liberação voluntária)
        scheduleNewThread();      //Chama o escalonador para executar outra thread
    }

    return 0;
}

int unlockThread(int tid) //Uma thread bloqueada volta para a fila de Aptos
{
    // Percorre a fila de threads bloqueadas
    TCB_t *thread = NULL;
    FirstFila2(blockedQueue);
    do
    {
        thread = (TCB_t *)GetAtIteratorFila2(blockedQueue);
        if (thread == NULL)
            break;
        if (thread->tid == tid)
        {
            // Se encontrar a thread, transfere da fila bloqueados para a fila aptos
            DeleteAtIteratorFila2(blockedQueue);
            insertReadyQueue(thread);
            return 0;
        }
    } while (NextFila2(blockedQueue) == 0);

    return -1;
}

void killThread() //Remove a thread atual e, caso haja alguma thread aguardando ela, essa thread volta para a fila de aptos
{
    stopTimer();
    // Identifica a thread que está em execução e remove ele da fila "executando"
    TCB_t *thread = getAndRemoveFirstThread(runningQueue);

    // Atualiza o estado da thread
    thread->state = PROCST_TERMINO;

    // Verifica se existe alguma thread esperando pela thread finalizada
    JOIN_PAIR_t *joinPair = NULL;
    FirstFila2(joinQueue);
    do
    {
        joinPair = (JOIN_PAIR_t *)GetAtIteratorFila2(joinQueue);
        if (joinPair == NULL)
            break;
        if (joinPair->tid_running_thread == thread->tid)
        {
            DeleteAtIteratorFila2(joinQueue);
            unlockThread(joinPair->tid_blocked_thread);
        }
    } while (NextFila2(joinQueue) == 0);

    AppendFila2(finishedQueue, thread);
    scheduleNewThread();
}

TCB_t *findReadyThreadByTID(int tid) //Busca uma thread através da sua ID
{
    // Percorre a fila de aptos
    TCB_t *thread = NULL;
    FirstFila2(readyQueue);
    do
    {
        thread = (TCB_t *)GetAtIteratorFila2(readyQueue);
        if (thread == NULL)
            break;
        if (thread->tid == tid)
            return thread; // Se encontrar a thread, retorna um ponteiro para o seu TCB
    } while (NextFila2(readyQueue) == 0);

    // Se não encontrar a thread, retorna NULL
    return NULL;
}

int waitForThread(int tid) //Coloca a thread atual na fila de bloqueados até que a thread filha seja encerrada
{
    // Busca a thread em execução
    TCB_t *thread = (TCB_t *)getRunningThread();

    // Verifica se a thread a ser bloqueada existe e se a thread cujo tid existe
    if (thread == NULL || findReadyThreadByTID(tid) == NULL)
        return -1;

    // Verifica se a thread bloqueante já bloqueia outra thread
    JOIN_PAIR_t *joinPair = (JOIN_PAIR_t *)malloc(sizeof(JOIN_PAIR_t));
    if (FirstFila2(joinQueue) == 0)
    {
        do
        {
            joinPair = (JOIN_PAIR_t *)GetAtIteratorFila2(joinQueue);
            if (joinPair == NULL)
                break;
            if (joinPair->tid_running_thread == tid)
                return -1;
        } while (NextFila2(joinQueue) == 0);
    }

    joinPair->tid_blocked_thread = thread->tid;
    joinPair->tid_running_thread = tid;
    AppendFila2(joinQueue, joinPair);

    blockThread();
    return 0;
}

void initializeScheduler()
{
    if (schedulerInitialized)
        return;

    schedulerInitialized = 1;
    initMainThread();

    getcontext(&dispatcherContext);
    dispatcherContext.uc_link = 0;
    dispatcherContext.uc_stack.ss_sp = malloc(SIGSTKSZ);
    dispatcherContext.uc_stack.ss_size = SIGSTKSZ;
    makecontext(&dispatcherContext, (void (*)(void))killThread, 0);
    return;
}