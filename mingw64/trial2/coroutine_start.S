
	.text
	.global	coroutine_start

# coroutine_start(struct coroutine_t *c, void (*func)(void*), void *arg)

# coroutine_start: initial entry for new coroutine.
# When ret jumps here, the stack must be arranged so that:
# top-of-stack => func
#                 arg
#                 struct coroutine_t
# coroutine_start will pop them
# (func => %rax, arg => %rcx, struct coroutine_t => %rsi),
# call func(arg).
# After func returns, coroutine_start will set rcx <= from and rdx <= to,
# and jmp coroutine_transit.

coroutine_start:
	# pop func, arg, coroutine_t from stack
	popq	%rax		# func pointer
	popq	%rcx		# arg => rcx (1st arg of func)
	popq	%rsi		# struct coroutine_t => rsi

	# call func(arg)
	call	*%rax

	# func returned => switch back to main context:
	# rcx = from = current coroutine (we set rcx = rsi)
	# rdx = to   = main_context pointer at offset 16(%rsi)
	movq	%rsi, %rcx	# rcx = from (current coroutine pointer)
	movq	16(%rsi), %rdx	# rdx = to = coroutine_t->main_context
	jmp	coroutine_transit



