#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/thread.h"
#include "../include/scheduler.h"

int tid = 1;

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