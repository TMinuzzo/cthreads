#include "../include/thread.h"

int tid = 0;

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