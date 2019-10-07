#ifndef __THREAD_H__
#define __THREAD_H__

#include <signal.h>
#include <stdlib.h>
#include <ucontext.h>
#include "cdata.h"
#include "scheduler.h"

void createContext(ucontext_t *newContext, void *(*start)(void *), void *arg);

TCB_t* createThread(ucontext_t context, int priority);

#endif