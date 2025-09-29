#include <stdio.h>
#include <stdint.h>

extern void trampoline(void (*fn)(void *), void *arg, void *stack_top);

void worker(void *arg)
{
        const char *msg = arg;
        for (int i=0; i<3; i++) {
                printf("worker: %s (%d)\n", msg, i);
        }

        // trampoline cannot return to caller, so exit
        printf("worker done, exiting...\n");
        fflush(stdout);
        _Exit(0);
}

int main(int argc, char *argv[])
{
        static uint8_t stack[64 * 1024];
        void *stack_top = stack + sizeof(stack);

        printf("main: start trampoline...\n");
        printf("worker = %p\n", (void *)worker);
        printf("stack_top = %p\n", stack_top);
        trampoline(worker, "hello", stack_top);

        // trampoline cannot return to caller, so it never come here
        printf("main: done\n");
        return 0;
}
