	.file	"MasterScheduler.cpp"
	.text
	.section	.text._ZNK8opendnp312UserPollTask11IsRecurringEv,"axG",@progbits,_ZNK8opendnp312UserPollTask11IsRecurringEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp312UserPollTask11IsRecurringEv
	.type	_ZNK8opendnp312UserPollTask11IsRecurringEv, @function
_ZNK8opendnp312UserPollTask11IsRecurringEv:
.LFB2445:
	.cfi_startproc
	movzbl	136(%rdi), %eax
	ret
	.cfi_endproc
.LFE2445:
	.size	_ZNK8opendnp312UserPollTask11IsRecurringEv, .-_ZNK8opendnp312UserPollTask11IsRecurringEv
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE
	.type	_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE, @function
_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE:
.LFB3172:
	.cfi_startproc
	movq	%rsi, (%rdi)
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
	movq	$0, 24(%rdi)
	ret
	.cfi_endproc
.LFE3172:
	.size	_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE, .-_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE
	.globl	_ZN8opendnp315MasterSchedulerC1ERNS_11ITaskFilterE
	.set	_ZN8opendnp315MasterSchedulerC1ERNS_11ITaskFilterE,_ZN8opendnp315MasterSchedulerC2ERNS_11ITaskFilterE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE, @function
_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE:
.LFB3175:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movq	8(%rdi), %r12
	movq	16(%rdi), %rax
	cmpq	%rax, %r12
	je	.L5
	leaq	16(%r12), %rbx
	movq	%rdi, %rbp
	movq	%rsi, %r13
	cmpq	%rax, %rbx
	je	.L5
	.p2align 4,,10
	.p2align 3
.L7:
	movq	(%rbx), %rdx
	movq	(%r12), %rsi
	movq	%r13, %rdi
	movq	0(%rbp), %rcx
	call	_ZN8opendnp314TaskComparison20SelectHigherPriorityERKN7openpal18MonotonicTimestampERKNS_11IMasterTaskES7_RNS_11ITaskFilterE@PLT
	cmpb	$1, %al
	cmove	%rbx, %r12
	addq	$16, %rbx
	cmpq	%rbx, 16(%rbp)
	jne	.L7
.L5:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3175:
	.size	_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE, .-_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler7GetNextERKN7openpal18MonotonicTimestampERS2_
	.type	_ZN8opendnp315MasterScheduler7GetNextERKN7openpal18MonotonicTimestampERS2_, @function
_ZN8opendnp315MasterScheduler7GetNextERKN7openpal18MonotonicTimestampERS2_:
.LFB3176:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdx, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rcx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rsi, %rbp
	movq	%rdx, %rsi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rbp, %rdi
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	call	_ZN8opendnp315MasterScheduler11GetNextTaskERKN7openpal18MonotonicTimestampE@PLT
	cmpq	%rax, 16(%rbp)
	je	.L35
	movq	(%rax), %rdi
	movq	%rax, %rbx
	call	_ZNK8opendnp311IMasterTask14ExpirationTimeEv@PLT
	movq	0(%rbp), %rdi
	cmpq	(%r14), %rax
	setle	%r14b
	movq	(%rbx), %rsi
	movq	(%rdi), %rax
	call	*(%rax)
	testb	%r14b, %r14b
	je	.L14
	testb	%al, %al
	je	.L35
	movq	8(%rbx), %r13
	movq	(%rbx), %r14
	testq	%r13, %r13
	je	.L15
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L54
	addl	$1, 8(%r13)
.L15:
	movq	16(%rbp), %rax
	addq	$16, %rbx
	cmpq	%rbx, %rax
	je	.L17
	movq	%rax, %rdx
	subq	%rbx, %rdx
	movq	%rdx, %r15
	sarq	$4, %r15
	testq	%rdx, %rdx
	jle	.L37
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	pxor	%xmm1, %xmm1
	je	.L24
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L21:
	addq	$16, %rbx
	subq	$1, %r15
	je	.L23
.L24:
	movdqu	(%rbx), %xmm0
	movq	-8(%rbx), %rdi
	movups	%xmm1, (%rbx)
	movups	%xmm0, -16(%rbx)
	testq	%rdi, %rdi
	je	.L21
	movl	8(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rdi)
	cmpl	$1, %eax
	jne	.L21
	movq	(%rdi), %rax
	movq	%rdi, 8(%rsp)
	call	*16(%rax)
	movq	8(%rsp), %rdi
	pxor	%xmm1, %xmm1
	movl	12(%rdi), %eax
	leal	-1(%rax), %edx
	cmpl	$1, %eax
	movl	%edx, 12(%rdi)
	jne	.L21
	movq	(%rdi), %rax
	call	*24(%rax)
	pxor	%xmm1, %xmm1
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L14:
	testb	%al, %al
	jne	.L55
	.p2align 4,,10
	.p2align 3
.L35:
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	movq	%rax, 0(%r13)
.L36:
	pxor	%xmm0, %xmm0
	movups	%xmm0, (%r12)
.L11:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L55:
	.cfi_restore_state
	movq	(%rbx), %rdi
	call	_ZNK8opendnp311IMasterTask14ExpirationTimeEv@PLT
	movq	%rax, 0(%r13)
	jmp	.L36
	.p2align 4,,10
	.p2align 3
.L23:
	movq	16(%rbp), %rbx
.L17:
	leaq	-16(%rbx), %rax
	movq	%rax, 16(%rbp)
	movq	-8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L29
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L56
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L31:
	cmpl	$1, %eax
	je	.L57
.L29:
	movq	%r14, %xmm0
	movq	%r13, %xmm2
	punpcklqdq	%xmm2, %xmm0
	movups	%xmm0, (%r12)
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L59:
	movq	(%rdi), %rax
	movq	%rdi, 8(%rsp)
	call	*16(%rax)
	movq	8(%rsp), %rdi
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rdi)
	pxor	%xmm1, %xmm1
	cmpl	$1, %eax
	je	.L58
	.p2align 4,,10
	.p2align 3
.L26:
	addq	$16, %rbx
	subq	$1, %r15
	je	.L23
.L18:
	movdqu	(%rbx), %xmm0
	movq	-8(%rbx), %rdi
	movups	%xmm1, (%rbx)
	movups	%xmm0, -16(%rbx)
	testq	%rdi, %rdi
	je	.L26
	lock subl	$1, 8(%rdi)
	jne	.L26
	jmp	.L59
	.p2align 4,,10
	.p2align 3
.L57:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L60
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L34:
	cmpl	$1, %eax
	jne	.L29
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L58:
	movq	(%rdi), %rax
	call	*24(%rax)
	pxor	%xmm1, %xmm1
	jmp	.L26
	.p2align 4,,10
	.p2align 3
.L56:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L54:
	lock addl	$1, 8(%r13)
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L60:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L37:
	movq	%rax, %rbx
	jmp	.L17
	.cfi_endproc
.LFE3176:
	.size	_ZN8opendnp315MasterScheduler7GetNextERKN7openpal18MonotonicTimestampERS2_, .-_ZN8opendnp315MasterScheduler7GetNextERKN7openpal18MonotonicTimestampERS2_
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler8ShutdownERKN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp315MasterScheduler8ShutdownERKN7openpal18MonotonicTimestampE, @function
_ZN8opendnp315MasterScheduler8ShutdownERKN7openpal18MonotonicTimestampE:
.LFB3190:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	8(%rdi), %r14
	movq	16(%rdi), %r12
	cmpq	%r12, %r14
	je	.L61
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	movq	%rdi, %r13
	movq	%r14, %rbx
	jne	.L63
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	jne	.L64
	.p2align 4,,10
	.p2align 3
.L66:
	addq	$16, %rbx
	cmpq	%rbx, %r12
	je	.L68
.L69:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L66
.L64:
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
	cmpl	$1, %eax
	jne	.L66
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
	cmpl	$1, %eax
	jne	.L66
	movq	0(%rbp), %rax
	addq	$16, %rbx
	movq	%rbp, %rdi
	call	*24(%rax)
	cmpq	%rbx, %r12
	jne	.L69
	.p2align 4,,10
	.p2align 3
.L68:
	movq	%r14, 16(%r13)
.L61:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L77:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	lock subl	$1, 12(%rbp)
	je	.L76
	.p2align 4,,10
	.p2align 3
.L71:
	addq	$16, %rbx
	cmpq	%rbx, %r12
	je	.L68
.L63:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L71
	lock subl	$1, 8(%rbp)
	jne	.L71
	jmp	.L77
	.p2align 4,,10
	.p2align 3
.L76:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L71
	.cfi_endproc
.LFE3190:
	.size	_ZN8opendnp315MasterScheduler8ShutdownERKN7openpal18MonotonicTimestampE, .-_ZN8opendnp315MasterScheduler8ShutdownERKN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE
	.type	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE, @function
_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE:
.LFB3191:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdx, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	(%rdx), %rdi
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	(%rdi), %rax
	movq	48(%rax), %rax
	cmpq	_ZNK8opendnp312UserPollTask11IsRecurringEv@GOTPCREL(%rip), %rax
	jne	.L79
	movzbl	136(%rdi), %eax
.L80:
	testb	%al, %al
	je	.L81
.L83:
	xorl	%eax, %eax
.L78:
	movq	8(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L86
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L81:
	.cfi_restore_state
	movq	(%rbx), %rdi
	call	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv@PLT
	movq	%rsp, %rdi
	movq	%rbp, %rsi
	movq	%rax, (%rsp)
	call	_ZN7openpalgtERKNS_18MonotonicTimestampES2_@PLT
	testb	%al, %al
	jne	.L83
	movq	0(%rbp), %rsi
	movq	(%rbx), %rdi
	call	_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE@PLT
	movl	$1, %eax
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L79:
	call	*%rax
	jmp	.L80
.L86:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3191:
	.size	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE, .-_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler21CheckTaskStartTimeoutERKN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp315MasterScheduler21CheckTaskStartTimeoutERKN7openpal18MonotonicTimestampE, @function
_ZN8opendnp315MasterScheduler21CheckTaskStartTimeoutERKN7openpal18MonotonicTimestampE:
.LFB3192:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	16(%rdi), %r13
	movq	8(%rdi), %rbx
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	movq	(%rsi), %rax
	movq	%rdi, 16(%rsp)
	movq	%r13, %r15
	movq	%rdi, 32(%rsp)
	subq	%rbx, %r15
	movq	%rax, 24(%rsp)
	movq	%rax, 40(%rsp)
	movq	%r15, %rax
	sarq	$6, %r15
	sarq	$4, %rax
	testq	%r15, %r15
	jle	.L88
	salq	$6, %r15
	leaq	40(%rsp), %rbp
	addq	%rbx, %r15
	jmp	.L91
	.p2align 4,,10
	.p2align 3
.L148:
	movq	%rbx, %r12
	movq	32(%rsp), %rdi
	addq	$16, %rbx
	movq	%rbp, %rsi
	movq	%rbx, %rdx
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L89
	leaq	32(%r12), %rbx
	movq	32(%rsp), %rdi
	movq	%rbp, %rsi
	movq	%rbx, %rdx
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L89
	leaq	48(%r12), %rbx
	movq	32(%rsp), %rdi
	movq	%rbp, %rsi
	movq	%rbx, %rdx
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L89
	leaq	64(%r12), %rbx
	cmpq	%r15, %rbx
	je	.L147
	movq	32(%rsp), %rdi
.L91:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	je	.L148
.L89:
	cmpq	%rbx, %r13
	je	.L87
	leaq	16(%rbx), %rbp
	cmpq	%rbp, %r13
	je	.L109
	leaq	24(%rsp), %r12
	.p2align 4,,10
	.p2align 3
.L108:
	movq	16(%rsp), %rdi
	movq	%rbp, %rdx
	movq	%r12, %rsi
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L100
	pxor	%xmm2, %xmm2
	movdqu	0(%rbp), %xmm0
	movups	%xmm2, 0(%rbp)
	movq	8(%rbx), %r15
	movups	%xmm0, (%rbx)
	testq	%r15, %r15
	je	.L102
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L149
	movl	8(%r15), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r15)
.L104:
	cmpl	$1, %eax
	je	.L150
.L102:
	addq	$16, %rbx
.L100:
	addq	$16, %rbp
	cmpq	%rbp, %r13
	jne	.L108
	cmpq	%rbx, %r13
	je	.L87
.L109:
	movq	16(%r14), %r15
	movq	%r15, %rax
	subq	%r13, %rax
	cmpq	%r15, %r13
	je	.L110
	movq	%rax, %rbp
	sarq	$4, %rbp
	testq	%rax, %rax
	jle	.L110
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L133
	movq	%rbx, %r15
	movq	%r13, %r12
	pxor	%xmm1, %xmm1
	jmp	.L117
	.p2align 4,,10
	.p2align 3
.L114:
	addq	$16, %r12
	addq	$16, %r15
	subq	$1, %rbp
	je	.L116
.L117:
	movdqu	(%r12), %xmm0
	movups	%xmm1, (%r12)
	movq	8(%r15), %rdi
	movups	%xmm0, (%r15)
	testq	%rdi, %rdi
	je	.L114
	movl	8(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rdi)
	cmpl	$1, %eax
	jne	.L114
	movq	(%rdi), %rax
	movq	%rdi, 8(%rsp)
	call	*16(%rax)
	movq	8(%rsp), %rdi
	pxor	%xmm1, %xmm1
	movl	12(%rdi), %eax
	leal	-1(%rax), %edx
	cmpl	$1, %eax
	movl	%edx, 12(%rdi)
	jne	.L114
	movq	(%rdi), %rax
	addq	$16, %r12
	addq	$16, %r15
	call	*24(%rax)
	pxor	%xmm1, %xmm1
	subq	$1, %rbp
	jne	.L117
	.p2align 4,,10
	.p2align 3
.L116:
	movq	16(%r14), %r15
	movq	%r15, %rax
	subq	%r13, %rax
.L110:
	addq	%rax, %rbx
	cmpq	%r15, %rbx
	je	.L87
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L134
	movq	%rbx, %rbp
	jmp	.L128
	.p2align 4,,10
	.p2align 3
.L125:
	addq	$16, %rbp
	cmpq	%rbp, %r15
	je	.L127
.L128:
	movq	8(%rbp), %r12
	testq	%r12, %r12
	je	.L125
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
	cmpl	$1, %eax
	jne	.L125
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
	cmpl	$1, %eax
	jne	.L125
	movq	(%r12), %rax
	addq	$16, %rbp
	movq	%r12, %rdi
	call	*24(%rax)
	cmpq	%rbp, %r15
	jne	.L128
	.p2align 4,,10
	.p2align 3
.L127:
	movq	%rbx, 16(%r14)
.L87:
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L151
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L150:
	.cfi_restore_state
	movq	(%r15), %rax
	movq	%r15, %rdi
	call	*16(%rax)
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L152
	movl	12(%r15), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r15)
.L107:
	cmpl	$1, %eax
	jne	.L102
	movq	(%r15), %rax
	movq	%r15, %rdi
	call	*24(%rax)
	jmp	.L102
	.p2align 4,,10
	.p2align 3
.L149:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r15)
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L147:
	movq	%r13, %rax
	subq	%rbx, %rax
	sarq	$4, %rax
.L88:
	leaq	40(%rsp), %rbp
	cmpq	$2, %rax
	je	.L92
	cmpq	$3, %rax
	je	.L93
	leaq	40(%rsp), %rbp
	cmpq	$1, %rax
	jne	.L87
.L94:
	movq	32(%rsp), %rdi
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	je	.L87
	jmp	.L89
	.p2align 4,,10
	.p2align 3
.L152:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r15)
	jmp	.L107
.L93:
	leaq	40(%rsp), %rbp
	movq	32(%rsp), %rdi
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L89
	addq	$16, %rbx
.L92:
	movq	32(%rsp), %rdi
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	_ZN8opendnp315MasterScheduler10IsTimedOutERKN7openpal18MonotonicTimestampERKSt10shared_ptrINS_11IMasterTaskEE@PLT
	testb	%al, %al
	jne	.L89
	addq	$16, %rbx
	jmp	.L94
	.p2align 4,,10
	.p2align 3
.L134:
	movq	%rbx, %r12
	jmp	.L122
	.p2align 4,,10
	.p2align 3
.L130:
	addq	$16, %r12
	cmpq	%r12, %r15
	je	.L127
.L122:
	movq	8(%r12), %rbp
	testq	%rbp, %rbp
	je	.L130
	lock subl	$1, 8(%rbp)
	jne	.L130
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	lock subl	$1, 12(%rbp)
	jne	.L130
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L130
	.p2align 4,,10
	.p2align 3
.L133:
	movq	%rbx, %rax
	movq	%r13, %r15
	pxor	%xmm1, %xmm1
	jmp	.L111
	.p2align 4,,10
	.p2align 3
.L119:
	addq	$16, %r15
	addq	$16, %rax
	subq	$1, %rbp
	je	.L116
.L111:
	movdqu	(%r15), %xmm0
	movups	%xmm1, (%r15)
	movq	8(%rax), %r12
	movups	%xmm0, (%rax)
	testq	%r12, %r12
	je	.L119
	lock subl	$1, 8(%r12)
	jne	.L119
	movq	(%r12), %rdx
	movq	%rax, 8(%rsp)
	movq	%r12, %rdi
	call	*16(%rdx)
	lock subl	$1, 12(%r12)
	pxor	%xmm1, %xmm1
	movq	8(%rsp), %rax
	jne	.L119
	movq	(%r12), %rdx
	movq	%r12, %rdi
	call	*24(%rdx)
	movq	8(%rsp), %rax
	pxor	%xmm1, %xmm1
	jmp	.L119
.L151:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3192:
	.size	_ZN8opendnp315MasterScheduler21CheckTaskStartTimeoutERKN7openpal18MonotonicTimestampE, .-_ZN8opendnp315MasterScheduler21CheckTaskStartTimeoutERKN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv
	.type	_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv, @function
_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv:
.LFB3194:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rdi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	leaq	8(%rsp), %r14
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	movq	8(%r13), %rbx
	movq	16(%r13), %rbp
	movq	%rax, 8(%rsp)
	cmpq	%rbp, %rbx
	je	.L154
	movq	_ZNK8opendnp312UserPollTask11IsRecurringEv@GOTPCREL(%rip), %r12
	leaq	8(%rsp), %r14
	leaq	16(%rsp), %r15
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L158:
	addq	$16, %rbx
	cmpq	%rbx, %rbp
	je	.L154
.L159:
	movq	(%rbx), %rdi
	movq	(%rdi), %rax
	movq	48(%rax), %rax
	cmpq	%r12, %rax
	jne	.L155
	movzbl	136(%rdi), %eax
.L156:
	testb	%al, %al
	jne	.L158
	movq	(%rbx), %rdi
	call	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv@PLT
	movq	%r14, %rsi
	movq	%r15, %rdi
	movq	%rax, 16(%rsp)
	call	_ZN7openpalltERKNS_18MonotonicTimestampES2_@PLT
	testb	%al, %al
	je	.L158
	movq	(%rbx), %rdi
	addq	$16, %rbx
	call	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv@PLT
	movq	%rax, 8(%rsp)
	cmpq	%rbx, %rbp
	jne	.L159
	.p2align 4,,10
	.p2align 3
.L154:
	movq	0(%r13), %rdi
	movq	%r14, %rsi
	movq	(%rdi), %rax
	call	*8(%rax)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L168
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L155:
	.cfi_restore_state
	call	*%rax
	jmp	.L156
.L168:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3194:
	.size	_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv, .-_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv
	.section	.rodata._ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_.str1.1,"aMS",@progbits,1
.LC0:
	.string	"vector::_M_realloc_insert"
	.section	.text._ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_,"axG",@progbits,_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_
	.type	_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_, @function
_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_:
.LFB3649:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movabsq	$576460752303423487, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %r15
	movq	(%rdi), %r12
	movq	%r15, %rax
	subq	%r12, %rax
	sarq	$4, %rax
	cmpq	%r14, %rax
	je	.L196
	movq	%rsi, %rbx
	movq	%rdx, %rsi
	movl	$1, %edx
	movq	%rax, %rcx
	testq	%rax, %rax
	movq	%rdx, %rax
	movq	%rbx, %rdx
	movq	%rdi, %r13
	cmovne	%rcx, %rax
	addq	%rcx, %rax
	setc	%cl
	subq	%r12, %rdx
	movzbl	%cl, %ecx
	testq	%rcx, %rcx
	jne	.L185
	testq	%rax, %rax
	jne	.L174
	movl	$16, %ecx
	xorl	%r14d, %r14d
	xorl	%ebp, %ebp
.L184:
	movdqu	(%rsi), %xmm3
	movq	8(%rsi), %rax
	movups	%xmm3, 0(%rbp,%rdx)
	testq	%rax, %rax
	je	.L175
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L197
	addl	$1, 8(%rax)
.L175:
	cmpq	%r12, %rbx
	je	.L177
.L198:
	leaq	-16(%rbx), %rcx
	xorl	%eax, %eax
	xorl	%edx, %edx
	subq	%r12, %rcx
	shrq	$4, %rcx
	addq	$1, %rcx
	.p2align 4,,10
	.p2align 3
.L178:
	movdqu	(%r12,%rax), %xmm1
	addq	$1, %rdx
	movups	%xmm1, 0(%rbp,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rcx
	ja	.L178
	movq	%rbx, %rax
	subq	%r12, %rax
	leaq	16(%rbp,%rax), %rcx
	cmpq	%r15, %rbx
	je	.L179
.L180:
	movq	%r15, %rax
	xorl	%edx, %edx
	subq	%rbx, %rax
	leaq	-16(%rax), %rsi
	xorl	%eax, %eax
	shrq	$4, %rsi
	addq	$1, %rsi
	.p2align 4,,10
	.p2align 3
.L182:
	movdqu	(%rbx,%rax), %xmm2
	addq	$1, %rdx
	movups	%xmm2, (%rcx,%rax)
	addq	$16, %rax
	cmpq	%rsi, %rdx
	jb	.L182
	subq	%rbx, %r15
	addq	%r15, %rcx
.L181:
	testq	%r12, %r12
	je	.L183
.L179:
	movq	16(%r13), %rsi
	movq	%r12, %rdi
	movq	%rcx, (%rsp)
	subq	%r12, %rsi
	call	_ZdlPvm@PLT
	movq	(%rsp), %rcx
.L183:
	movq	%rbp, %xmm0
	movq	%rcx, %xmm4
	movq	%r14, 16(%r13)
	punpcklqdq	%xmm4, %xmm0
	movups	%xmm0, 0(%r13)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L174:
	.cfi_restore_state
	cmpq	%r14, %rax
	cmovbe	%rax, %r14
	salq	$4, %r14
.L173:
	movq	%r14, %rdi
	movq	%rsi, 8(%rsp)
	movq	%rdx, (%rsp)
	call	_Znwm@PLT
	movq	(%rsp), %rdx
	movq	8(%rsp), %rsi
	movq	%rax, %rbp
	addq	%rax, %r14
	leaq	16(%rax), %rcx
	jmp	.L184
	.p2align 4,,10
	.p2align 3
.L185:
	movabsq	$9223372036854775792, %r14
	jmp	.L173
	.p2align 4,,10
	.p2align 3
.L197:
	lock addl	$1, 8(%rax)
	cmpq	%r12, %rbx
	jne	.L198
	.p2align 4,,10
	.p2align 3
.L177:
	cmpq	%r15, %rbx
	jne	.L180
	jmp	.L181
.L196:
	leaq	.LC0(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE3649:
	.size	_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_, .-_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315MasterScheduler8ScheduleERKSt10shared_ptrINS_11IMasterTaskEE
	.type	_ZN8opendnp315MasterScheduler8ScheduleERKSt10shared_ptrINS_11IMasterTaskEE, @function
_ZN8opendnp315MasterScheduler8ScheduleERKSt10shared_ptrINS_11IMasterTaskEE:
.LFB3174:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rdx
	movq	%rdi, %rbp
	movq	16(%rdi), %rsi
	cmpq	24(%rdi), %rsi
	je	.L200
	movq	(%rdx), %rax
	movq	%rax, (%rsi)
	movq	8(%rdx), %rax
	movq	%rax, 8(%rsi)
	testq	%rax, %rax
	je	.L201
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L208
	addl	$1, 8(%rax)
.L201:
	addq	$16, %rsi
	movq	%rbp, %rdi
	movq	%rsi, 16(%rbp)
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv@PLT
	.p2align 4,,10
	.p2align 3
.L200:
	.cfi_restore_state
	leaq	8(%rdi), %rdi
	call	_ZNSt6vectorISt10shared_ptrIN8opendnp311IMasterTaskEESaIS3_EE17_M_realloc_insertIJRKS3_EEEvN9__gnu_cxx17__normal_iteratorIPS3_S5_EEDpOT_@PLT
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315MasterScheduler27RecalculateTaskStartTimeoutEv@PLT
	.p2align 4,,10
	.p2align 3
.L208:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	movq	16(%rdi), %rsi
	jmp	.L201
	.cfi_endproc
.LFE3174:
	.size	_ZN8opendnp315MasterScheduler8ScheduleERKSt10shared_ptrINS_11IMasterTaskEE, .-_ZN8opendnp315MasterScheduler8ScheduleERKSt10shared_ptrINS_11IMasterTaskEE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
