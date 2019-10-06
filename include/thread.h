#ifndef __THREAD_H__
#define __THREAD_H__

#include <signal.h>
#include <stdlib.h>
#include <ucontext.h>
#include "cdata.h"

TCB_t* createThread(ucontext_t context, int priority);

#endif