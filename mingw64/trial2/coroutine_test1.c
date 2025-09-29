#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "coroutine.h"

#define STACK_SIZE (32*1024)
uint8_t stack[STACK_SIZE];
struct coroutine_t coroutine, main_context;
struct iter_t
{
        int x, y;
        int max_x, max_y;
        struct coroutine_t *context_self;
        struct coroutine_t *context_main;
} iter;

void iterate(void *arg);

int main(int argc, void *argv)
{
        iter.x = 0;
        iter.y = 0;
        iter.max_x = 2;
        iter.max_y = 3;
        iter.context_self = &coroutine;
        iter.context_main = &main_context;

        coroutine_init(&coroutine,
                       (void (*)(void*))iterate,
                       &iter,
                       &stack[0] + STACK_SIZE,
                       &main_context);

        while (1) {
                coroutine_resume(&coroutine, &main_context);
                printf("resume %s(): x=%d y=%d\n",__func__,iter.x,iter.y);

                if (iter.x >= iter.max_x && iter.y >= iter.max_y)
                        break;
        }
}


void iterate(void *arg)
{
        struct iter_t *it = (struct iter_t*)arg;

        for (it->x = 0; it->x < it->max_x; ++it->x) {
                for (it->y = 0; it->y < it->max_y; ++it->y) {
                        printf("yield  %s(): x=%d y=%d\n",__func__,it->x,it->y);
                        coroutine_yield(it->context_self, it->context_main);
                }
        }

        it->context_self->finished = 1;

        // coroutine will switch back to main
        // and set finished by main
}
