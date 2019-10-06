#ifndef __thread__
#define __thread__

#include <signal.h>
#include "cdata.h"


TCB_t* createThread(ucontext_t context, int priority);

#endif