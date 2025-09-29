	.text
	.global	coroutine_transit

# void coroutine_transit(struct coroutine_t *from, struct coroutine_t *to)
# Microsoft x64: rcx <= from, rdx <= to
coroutine_transit:
	# save: rbp, rbx, rsi, rdi, r12-r15
	pushq	%rbp
	pushq	%rbx
	pushq	%rsi
	pushq	%rdi
	pushq	%r12
	pushq	%r13
	pushq	%r14
	pushq	%r15

	# store current rsp/rbp into from (rcx)
	movq	%rsp, (%rcx)	# from->rsp = rsp
	movq	%rbp, 8(%rcx)	# from->rbp = rbp

	# load target rsp/rbp from to (rdx)
	movq	(%rdx), %rsp	# rsp = to->rsp
	movq	8(%rdx), %rbp	# rbp = to->rbp

	# restore callee-saved - reverse order of pushes
	popq	%r15
	popq	%r14
	popq	%r13
	popq	%r12
	popq	%rdi
	popq	%rsi
	popq	%rbx
	popq	%rbp

	ret
