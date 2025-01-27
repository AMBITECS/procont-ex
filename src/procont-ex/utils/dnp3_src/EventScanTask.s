	.file	"EventScanTask.cpp"
	.text
	.section	.text._ZNK8opendnp311IMasterTask10IsAuthTaskEv,"axG",@progbits,_ZNK8opendnp311IMasterTask10IsAuthTaskEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.type	_ZNK8opendnp311IMasterTask10IsAuthTaskEv, @function
_ZNK8opendnp311IMasterTask10IsAuthTaskEv:
.LFB2433:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE2433:
	.size	_ZNK8opendnp311IMasterTask10IsAuthTaskEv, .-_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.section	.rodata._ZNK8opendnp312PollTaskBase4NameEv.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Application Poll"
	.section	.text._ZNK8opendnp312PollTaskBase4NameEv,"axG",@progbits,_ZNK8opendnp312PollTaskBase4NameEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp312PollTaskBase4NameEv
	.type	_ZNK8opendnp312PollTaskBase4NameEv, @function
_ZNK8opendnp312PollTaskBase4NameEv:
.LFB2435:
	.cfi_startproc
	leaq	.LC0(%rip), %rax
	ret
	.cfi_endproc
.LFE2435:
	.size	_ZNK8opendnp312PollTaskBase4NameEv, .-_ZNK8opendnp312PollTaskBase4NameEv
	.section	.text._ZNK8opendnp313EventScanTask11IsRecurringEv,"axG",@progbits,_ZNK8opendnp313EventScanTask11IsRecurringEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp313EventScanTask11IsRecurringEv
	.type	_ZNK8opendnp313EventScanTask11IsRecurringEv, @function
_ZNK8opendnp313EventScanTask11IsRecurringEv:
.LFB2436:
	.cfi_startproc
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2436:
	.size	_ZNK8opendnp313EventScanTask11IsRecurringEv, .-_ZNK8opendnp313EventScanTask11IsRecurringEv
	.section	.text._ZNK8opendnp313EventScanTask8PriorityEv,"axG",@progbits,_ZNK8opendnp313EventScanTask8PriorityEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp313EventScanTask8PriorityEv
	.type	_ZNK8opendnp313EventScanTask8PriorityEv, @function
_ZNK8opendnp313EventScanTask8PriorityEv:
.LFB2437:
	.cfi_startproc
	movl	$180, %eax
	ret
	.cfi_endproc
.LFE2437:
	.size	_ZNK8opendnp313EventScanTask8PriorityEv, .-_ZNK8opendnp313EventScanTask8PriorityEv
	.section	.text._ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv,"axG",@progbits,_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv
	.type	_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv, @function
_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv:
.LFB2438:
	.cfi_startproc
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2438:
	.size	_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv, .-_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv
	.section	.text._ZNK8opendnp313EventScanTask11GetTaskTypeEv,"axG",@progbits,_ZNK8opendnp313EventScanTask11GetTaskTypeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp313EventScanTask11GetTaskTypeEv
	.type	_ZNK8opendnp313EventScanTask11GetTaskTypeEv, @function
_ZNK8opendnp313EventScanTask11GetTaskTypeEv:
.LFB2439:
	.cfi_startproc
	movl	$6, %eax
	ret
	.cfi_endproc
.LFE2439:
	.size	_ZNK8opendnp313EventScanTask11GetTaskTypeEv, .-_ZNK8opendnp313EventScanTask11GetTaskTypeEv
	.section	.text._ZN8opendnp313EventScanTaskD2Ev,"axG",@progbits,_ZN8opendnp313EventScanTaskD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp313EventScanTaskD2Ev
	.type	_ZN8opendnp313EventScanTaskD2Ev, @function
_ZN8opendnp313EventScanTaskD2Ev:
.LFB3920:
	.cfi_startproc
	movq	_ZTVN8opendnp312PollTaskBaseE@GOTPCREL(%rip), %rax
	addq	$16, %rax
	movq	%rax, (%rdi)
	jmp	_ZN8opendnp311IMasterTaskD2Ev@PLT
	.cfi_endproc
.LFE3920:
	.size	_ZN8opendnp313EventScanTaskD2Ev, .-_ZN8opendnp313EventScanTaskD2Ev
	.weak	_ZN8opendnp313EventScanTaskD1Ev
	.set	_ZN8opendnp313EventScanTaskD1Ev,_ZN8opendnp313EventScanTaskD2Ev
	.section	.text._ZN8opendnp313EventScanTaskD0Ev,"axG",@progbits,_ZN8opendnp313EventScanTaskD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp313EventScanTaskD0Ev
	.type	_ZN8opendnp313EventScanTaskD0Ev, @function
_ZN8opendnp313EventScanTaskD0Ev:
.LFB3922:
	.cfi_startproc
	movq	_ZTVN8opendnp312PollTaskBaseE@GOTPCREL(%rip), %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	addq	$16, %rax
	movq	%rax, (%rdi)
	call	_ZN8opendnp311IMasterTaskD2Ev@PLT
	movq	%rbp, %rdi
	movl	$120, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE3922:
	.size	_ZN8opendnp313EventScanTaskD0Ev, .-_ZN8opendnp313EventScanTaskD0Ev
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh
	.type	_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh, @function
_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh:
.LFB3224:
	.cfi_startproc
	movq	%rdi, %r8
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	%rsi, %rdi
	movzbl	%dl, %ecx
	movl	$1, %esi
	leaq	104(%r8), %rdx
	call	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh@PLT
	movl	$1, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3224:
	.size	_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh, .-_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp313EventScanTask9IsEnabledEv
	.type	_ZNK8opendnp313EventScanTask9IsEnabledEv, @function
_ZNK8opendnp313EventScanTask9IsEnabledEv:
.LFB3225:
	.cfi_startproc
	addq	$104, %rdi
	jmp	_ZNK8opendnp310ClassField13HasEventClassEv@PLT
	.cfi_endproc
.LFE3225:
	.size	_ZNK8opendnp313EventScanTask9IsEnabledEv, .-_ZNK8opendnp313EventScanTask9IsEnabledEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE:
.LFB3226:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdx, 8(%rsp)
	cmpb	$1, %sil
	je	.L15
	cmpb	$2, %sil
	je	.L16
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movq	%rax, %rdx
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	.cfi_restore_state
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movq	%rax, %rdx
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L16:
	.cfi_restore_state
	leaq	112(%rdi), %rsi
	leaq	8(%rsp), %rdi
	call	_ZNK7openpal18MonotonicTimestamp3AddERKNS_12TimeDurationE@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	movq	%rax, %rdx
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE3226:
	.size	_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE, .-_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE
	.section	.text._ZN7openpal6LoggerD2Ev,"axG",@progbits,_ZN7openpal6LoggerD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal6LoggerD2Ev
	.type	_ZN7openpal6LoggerD2Ev, @function
_ZN7openpal6LoggerD2Ev:
.LFB2044:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	24(%rdi), %rbp
	movq	%rdi, %rbx
	testq	%rbp, %rbp
	je	.L23
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L37
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L25:
	cmpl	$1, %eax
	je	.L38
.L23:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L21
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L39
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L32:
	cmpl	$1, %eax
	je	.L40
.L21:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L41
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L28:
	cmpl	$1, %eax
	jne	.L23
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L23
	.p2align 4,,10
	.p2align 3
.L40:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L42
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L35:
	cmpl	$1, %eax
	jne	.L21
	movq	0(%rbp), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L37:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L39:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L32
	.p2align 4,,10
	.p2align 3
.L41:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L28
	.p2align 4,,10
	.p2align 3
.L42:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L35
	.cfi_endproc
.LFE2044:
	.size	_ZN7openpal6LoggerD2Ev, .-_ZN7openpal6LoggerD2Ev
	.weak	_ZN7openpal6LoggerD1Ev
	.set	_ZN7openpal6LoggerD1Ev,_ZN7openpal6LoggerD2Ev
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB1:
	.text
.LHOTB1:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE
	.type	_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE, @function
_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE:
.LFB3222:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3222
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	.cfi_offset 15, -24
	movq	%rdx, %r15
	movl	$4294967295, %edx
	pushq	%r14
	.cfi_offset 14, -32
	movq	%rsi, %r14
	pushq	%r13
	.cfi_offset 13, -40
	xorl	%r13d, %r13d
	pushq	%r12
	.cfi_offset 12, -48
	xorl	%r12d, %r12d
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -56
	movq	%rdi, -112(%rbp)
	movdqu	(%r9), %xmm0
	movb	%cl, -97(%rbp)
	movq	%r8, -120(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	%r12, %rax
	movaps	%xmm0, -96(%rbp)
	orq	%rdx, %rax
	movabsq	$-1095216660481, %rdx
	andq	%rdx, %rax
	movq	%rax, %r12
	movq	8(%r9), %rax
	testq	%rax, %rax
	je	.L44
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L75
	addl	$1, 8(%rax)
.L44:
	movdqu	16(%r9), %xmm1
	movq	24(%r9), %rax
	movaps	%xmm1, -80(%rbp)
	testq	%rax, %rax
	je	.L46
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L76
	addl	$1, 8(%rax)
.L46:
	leaq	-96(%rbp), %rbx
.LEHB0:
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	pushq	%r13
	movq	-112(%rbp), %rdi
	movq	%rax, %rcx
	movq	%rbx, %r8
	pushq	%r12
	movq	%r15, %rdx
	movq	%r14, %rsi
	.cfi_escape 0x2e,0x10
	call	_ZN8opendnp312PollTaskBaseC2ERNS_18IMasterApplicationERNS_11ISOEHandlerEN7openpal18MonotonicTimestampENS5_6LoggerENS_10TaskConfigE@PLT
.LEHE0:
	movq	-72(%rbp), %r12
	popq	%rax
	popq	%rdx
	testq	%r12, %r12
	je	.L49
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L77
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L51:
	cmpl	$1, %eax
	je	.L78
.L49:
	movq	-88(%rbp), %r12
	testq	%r12, %r12
	je	.L56
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L79
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L58:
	cmpl	$1, %eax
	je	.L80
.L56:
	movq	_ZTVN8opendnp313EventScanTaskE@GOTPCREL(%rip), %rax
	movq	-112(%rbp), %rbx
	leaq	-97(%rbp), %rdi
	addq	$16, %rax
	movq	%rax, (%rbx)
.LEHB1:
	.cfi_escape 0x2e,0
	call	_ZNK8opendnp310ClassField16OnlyEventClassesEv@PLT
.LEHE1:
	movb	%al, 104(%rbx)
	movq	-120(%rbp), %rax
	movq	%rax, 112(%rbx)
	movq	-56(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L81
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L78:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L82
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L54:
	cmpl	$1, %eax
	jne	.L49
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L49
	.p2align 4,,10
	.p2align 3
.L80:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L83
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L61:
	cmpl	$1, %eax
	jne	.L56
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L77:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L79:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L75:
	lock addl	$1, 8(%rax)
	jmp	.L44
	.p2align 4,,10
	.p2align 3
.L76:
	lock addl	$1, 8(%rax)
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L83:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L61
	.p2align 4,,10
	.p2align 3
.L82:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L54
.L81:
	call	__stack_chk_fail@PLT
.L65:
	movq	%rax, %r14
	jmp	.L62
.L66:
	movq	%rax, %r12
	jmp	.L63
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA3222:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3222-.LLSDACSB3222
.LLSDACSB3222:
	.uleb128 .LEHB0-.LFB3222
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L65-.LFB3222
	.uleb128 0
	.uleb128 .LEHB1-.LFB3222
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L66-.LFB3222
	.uleb128 0
.LLSDACSE3222:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC3222
	.type	_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE.cold, @function
_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE.cold:
.LFSB3222:
.L62:
	.cfi_def_cfa 6, 16
	.cfi_offset 3, -56
	.cfi_offset 6, -16
	.cfi_offset 12, -48
	.cfi_offset 13, -40
	.cfi_offset 14, -32
	.cfi_offset 15, -24
	movq	%rbx, %rdi
	call	_ZN7openpal6LoggerD1Ev@PLT
	movq	%r14, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.L63:
	movq	_ZTVN8opendnp312PollTaskBaseE@GOTPCREL(%rip), %rax
	movq	-112(%rbp), %rcx
	addq	$16, %rax
	movq	%rcx, %rdi
	movq	%rax, (%rcx)
	call	_ZN8opendnp311IMasterTaskD2Ev@PLT
	movq	%r12, %rdi
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE3222:
	.section	.gcc_except_table
.LLSDAC3222:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC3222-.LLSDACSBC3222
.LLSDACSBC3222:
	.uleb128 .LEHB2-.LCOLDB1
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSEC3222:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE, .-_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE
	.section	.text.unlikely
	.size	_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE.cold, .-_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE.cold
.LCOLDE1:
	.text
.LHOTE1:
	.globl	_ZN8opendnp313EventScanTaskC1ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE
	.set	_ZN8opendnp313EventScanTaskC1ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE,_ZN8opendnp313EventScanTaskC2ERNS_18IMasterApplicationERNS_11ISOEHandlerENS_10ClassFieldEN7openpal12TimeDurationENS6_6LoggerE
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_EventScanTask.cpp, @function
_GLOBAL__sub_I_EventScanTask.cpp:
.LFB3954:
	.cfi_startproc
	movl	$5000, %edi
	jmp	_ZN7openpal12TimeDuration12MillisecondsEl@PLT
	.cfi_endproc
.LFE3954:
	.size	_GLOBAL__sub_I_EventScanTask.cpp, .-_GLOBAL__sub_I_EventScanTask.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_EventScanTask.cpp
	.weak	_ZTSN8opendnp313EventScanTaskE
	.section	.rodata._ZTSN8opendnp313EventScanTaskE,"aG",@progbits,_ZTSN8opendnp313EventScanTaskE,comdat
	.align 16
	.type	_ZTSN8opendnp313EventScanTaskE, @object
	.size	_ZTSN8opendnp313EventScanTaskE, 27
_ZTSN8opendnp313EventScanTaskE:
	.string	"N8opendnp313EventScanTaskE"
	.weak	_ZTIN8opendnp313EventScanTaskE
	.section	.data.rel.ro._ZTIN8opendnp313EventScanTaskE,"awG",@progbits,_ZTIN8opendnp313EventScanTaskE,comdat
	.align 8
	.type	_ZTIN8opendnp313EventScanTaskE, @object
	.size	_ZTIN8opendnp313EventScanTaskE, 24
_ZTIN8opendnp313EventScanTaskE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8opendnp313EventScanTaskE
	.quad	_ZTIN8opendnp312PollTaskBaseE
	.weak	_ZTVN8opendnp313EventScanTaskE
	.section	.data.rel.ro._ZTVN8opendnp313EventScanTaskE,"awG",@progbits,_ZTVN8opendnp313EventScanTaskE,comdat
	.align 8
	.type	_ZTVN8opendnp313EventScanTaskE, @object
	.size	_ZTVN8opendnp313EventScanTaskE, 120
_ZTVN8opendnp313EventScanTaskE:
	.quad	0
	.quad	_ZTIN8opendnp313EventScanTaskE
	.quad	_ZN8opendnp313EventScanTaskD1Ev
	.quad	_ZN8opendnp313EventScanTaskD0Ev
	.quad	_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.quad	_ZNK8opendnp312PollTaskBase4NameEv
	.quad	_ZNK8opendnp313EventScanTask8PriorityEv
	.quad	_ZNK8opendnp313EventScanTask19BlocksLowerPriorityEv
	.quad	_ZNK8opendnp313EventScanTask11IsRecurringEv
	.quad	_ZN8opendnp313EventScanTask12BuildRequestERNS_11APDURequestEh
	.quad	_ZN8opendnp312PollTaskBase10InitializeEv
	.quad	_ZN8opendnp312PollTaskBase15ProcessResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE
	.quad	_ZN8opendnp313EventScanTask14OnTaskCompleteENS_14TaskCompletionEN7openpal18MonotonicTimestampE
	.quad	_ZNK8opendnp313EventScanTask9IsEnabledEv
	.quad	_ZNK8opendnp313EventScanTask11GetTaskTypeEv
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
