# trampoline.S
# void trampoline(void (*fn)(void *), void *arg, void *stack_top) ;
# rdi = fn
# rsi = arg
# rdx = stack_top

    .text
    .global trampoline
trampoline:
    movq %rcx, %rax # rax <= fn
    movq %r8, %rsp  # rsp <= stack_top (change another stack)

    # Align rsp to 16 bytes and make room for return address
    andq $-16, %rax
    subq $8, %rsp

    movq $0, (%rsp) # pushq $0

    movq %rdx, %rcx # move arg -> rcx (1st arg of fn on Win)
    call *%rax      # fn(arg)

    movq $0, %rcx   # exit code = 0
    call exit
