#include <stdint.h>

struct coroutine_t
{
        void* rsp;
        void* rbp;
        struct coroutine_t* main_context;
        int finished;
};

extern void coroutine_start(struct coroutine_t *c, void (*func)(void*), void *arg);
extern void coroutine_transit(struct coroutine_t *from, struct coroutine_t *to);
extern void coroutine_init(struct coroutine_t *c, void (*func)(void*),
                           void *arg, void *stack_top,
                           struct coroutine_t *main_context);
extern void coroutine_resume(struct coroutine_t* c, struct coroutine_t* main_context);
extern void coroutine_yield(struct coroutine_t* c, struct coroutine_t* main_context);
