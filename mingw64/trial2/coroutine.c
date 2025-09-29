#include "coroutine.h"

void coroutine_init(struct coroutine_t *c, void (*func)(void*), void* arg,
                    void* stack_top, struct coroutine_t* main_context)
{
        uintptr_t *sp = (uintptr_t*)stack_top;

        /*
          Push in this order so that when coroutine_start pops,
          it gets func, arg, c (pointer to coroutine)
        */

        *(--sp) = (uintptr_t)c;
        *(--sp) = (uintptr_t)arg;
        *(--sp) = (uintptr_t)func;
        *(--sp) = (uintptr_t)coroutine_start; /* return address
                                                 => ret will jump to
                                                 coroutine_start */

        /*
          Set initial saved rbp (and other callee-saved placeholders)
          if needed:
          The coroutine_transit restores callee-saved registers by popping
          them from the stack, so you may want to push placeholders matching
          the number of pops if your coroutine_transit/pop sequence expects
          them on the stack.
          In our coroutine_transit, we pop r15..rbp (8 registers) before ret,
          so make sure the stack layout matches.
          If you don't push placeholders here, those popped registers will be
          read from whatever memory follows and could be junk.
          To be safe, push zero placeholders:
        */

        /* placeholders for r15,r14,r13,r12,rdi,rsi,rbx,rbp */
        for (int i = 0; i < 8; ++i) *(--sp) = 0;

        c->rsp = (void*)sp;
        c->rbp = 0;
        c->main_context = main_context;
        c->finished = 0;

        return;
}

void coroutine_resume(struct coroutine_t* c, struct coroutine_t* main_context)
{
        c->main_context = main_context;
        coroutine_transit(main_context, c);
}

void coroutine_yield(struct coroutine_t* c, struct coroutine_t* main_context)
{
        coroutine_transit(c, main_context);
}
