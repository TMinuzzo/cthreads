#include "../include/thread.h"

int tid = 0;

void createContext(ucontext_t *newContext, void *(*start)(void *), void *arg)
{
    ucontext_t *schedulerContext = malloc(sizeof(ucontext_t));

    getcontext(schedulerContext);
    schedulerContext->uc_stack.ss_sp = malloc(SIGSTKSZ);
    schedulerContext->uc_stack.ss_size = SIGSTKSZ;
    schedulerContext->uc_stack.ss_flags = 0;
    makecontext(schedulerContext, (void *)killThread, 0);

    getcontext(newContext);
    newContext->uc_stack.ss_sp = malloc(SIGSTKSZ);
    newContext->uc_stack.ss_size = SIGSTKSZ;
    newContext->uc_stack.ss_flags = 0;
    newContext->uc_link = schedulerContext;
    makecontext(newContext, (void *)start, 1, arg);
}

TCB_t* createThread(ucontext_t context, int priority)
{
    TCB_t *thread = malloc(sizeof(TCB_t));
    *thread = (TCB_t) {
        .tid = tid,
        .state = PROCST_APTO,
        .prio = priority,
        .context = context
    };
    tid++;
    return thread;
}