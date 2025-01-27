	.file	"IMasterTask.cpp"
	.text
	.section	.text._ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE,"axG",@progbits,_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE
	.type	_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE, @function
_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE:
.LFB2419:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE2419:
	.size	_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE, .-_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE
	.section	.text._ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE,"axG",@progbits,_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE
	.type	_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE, @function
_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE:
.LFB2420:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE2420:
	.size	_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE, .-_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE
	.section	.text._ZNK8opendnp311IMasterTask10IsAuthTaskEv,"axG",@progbits,_ZNK8opendnp311IMasterTask10IsAuthTaskEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.type	_ZNK8opendnp311IMasterTask10IsAuthTaskEv, @function
_ZNK8opendnp311IMasterTask10IsAuthTaskEv:
.LFB2432:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE2432:
	.size	_ZNK8opendnp311IMasterTask10IsAuthTaskEv, .-_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.section	.text._ZN8opendnp311IMasterTask10InitializeEv,"axG",@progbits,_ZN8opendnp311IMasterTask10InitializeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IMasterTask10InitializeEv
	.type	_ZN8opendnp311IMasterTask10InitializeEv, @function
_ZN8opendnp311IMasterTask10InitializeEv:
.LFB2433:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE2433:
	.size	_ZN8opendnp311IMasterTask10InitializeEv, .-_ZN8opendnp311IMasterTask10InitializeEv
	.section	.text._ZN7openpal6LoggerD2Ev,"axG",@progbits,_ZN7openpal6LoggerD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal6LoggerD2Ev
	.type	_ZN7openpal6LoggerD2Ev, @function
_ZN7openpal6LoggerD2Ev:
.LFB2043:
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
	je	.L8
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L22
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L10:
	cmpl	$1, %eax
	je	.L23
.L8:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L6
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L24
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L17:
	cmpl	$1, %eax
	je	.L25
.L6:
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
.L23:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L26
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L13:
	cmpl	$1, %eax
	jne	.L8
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L25:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L27
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L20:
	cmpl	$1, %eax
	jne	.L6
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
.L22:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L24:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L26:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L27:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L20
	.cfi_endproc
.LFE2043:
	.size	_ZN7openpal6LoggerD2Ev, .-_ZN7openpal6LoggerD2Ev
	.weak	_ZN7openpal6LoggerD1Ev
	.set	_ZN7openpal6LoggerD1Ev,_ZN7openpal6LoggerD2Ev
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE
	.type	_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE, @function
_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE:
.LFB2435:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2435
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	_ZTVN8opendnp311IMasterTaskE@GOTPCREL(%rip), %rax
	movq	%rsi, 8(%rdi)
	addq	$16, %rax
	movq	%rax, (%rdi)
	movq	(%rcx), %rax
	movq	%rax, 16(%rdi)
	movq	8(%rcx), %rax
	movq	%rax, 24(%rdi)
	testq	%rax, %rax
	je	.L29
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L43
	addl	$1, 8(%rax)
.L29:
	movq	16(%rcx), %rax
	movq	%rax, 32(%rbx)
	movq	24(%rcx), %rax
	movq	%rax, 40(%rbx)
	testq	%rax, %rax
	je	.L31
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L44
	addl	$1, 8(%rax)
.L31:
	movb	$0, 48(%rbx)
	movq	%rdx, 56(%rbx)
	movq	%r8, 64(%rbx)
	movq	%r9, 72(%rbx)
.LEHB0:
	call	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
.LEHE0:
	movq	%rax, 80(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L43:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L44:
	lock addl	$1, 8(%rax)
	jmp	.L31
.L34:
	movq	%rax, %rbp
	jmp	.L33
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2435:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2435-.LLSDACSB2435
.LLSDACSB2435:
	.uleb128 .LEHB0-.LFB2435
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L34-.LFB2435
	.uleb128 0
.LLSDACSE2435:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC2435
	.type	_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE.cold, @function
_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE.cold:
.LFSB2435:
.L33:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	leaq	16(%rbx), %rdi
	call	_ZN7openpal6LoggerD1Ev@PLT
	movq	%rbp, %rdi
.LEHB1:
	call	_Unwind_Resume@PLT
.LEHE1:
	.cfi_endproc
.LFE2435:
	.section	.gcc_except_table
.LLSDAC2435:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC2435-.LLSDACSBC2435
.LLSDACSBC2435:
	.uleb128 .LEHB1-.LCOLDB0
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSEC2435:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE, .-_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE
	.section	.text.unlikely
	.size	_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE.cold, .-_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE.cold
.LCOLDE0:
	.text
.LHOTE0:
	.globl	_ZN8opendnp311IMasterTaskC1ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE
	.set	_ZN8opendnp311IMasterTaskC1ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE,_ZN8opendnp311IMasterTaskC2ERNS_18IMasterApplicationEN7openpal18MonotonicTimestampENS3_6LoggerENS_10TaskConfigE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTaskD2Ev
	.type	_ZN8opendnp311IMasterTaskD2Ev, @function
_ZN8opendnp311IMasterTaskD2Ev:
.LFB2438:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2438
	movq	_ZTVN8opendnp311IMasterTaskE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rax, (%rdi)
	movq	72(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L46
	movq	(%rdi), %rax
	call	*16(%rax)
.L46:
	movq	40(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L48
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L65
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L50:
	cmpl	$1, %eax
	je	.L66
.L48:
	movq	24(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L45
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L67
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L57:
	cmpl	$1, %eax
	je	.L68
.L45:
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
.L66:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L69
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L53:
	cmpl	$1, %eax
	jne	.L48
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L68:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L70
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L60:
	cmpl	$1, %eax
	jne	.L45
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
.L65:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L67:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L69:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L70:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L60
	.cfi_endproc
.LFE2438:
	.section	.gcc_except_table
.LLSDA2438:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2438-.LLSDACSB2438
.LLSDACSB2438:
.LLSDACSE2438:
	.text
	.size	_ZN8opendnp311IMasterTaskD2Ev, .-_ZN8opendnp311IMasterTaskD2Ev
	.globl	_ZN8opendnp311IMasterTaskD1Ev
	.set	_ZN8opendnp311IMasterTaskD1Ev,_ZN8opendnp311IMasterTaskD2Ev
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTaskD0Ev
	.type	_ZN8opendnp311IMasterTaskD0Ev, @function
_ZN8opendnp311IMasterTaskD0Ev:
.LFB2440:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	call	_ZN8opendnp311IMasterTaskD1Ev@PLT
	movq	%rbp, %rdi
	movl	$88, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE2440:
	.size	_ZN8opendnp311IMasterTaskD0Ev, .-_ZN8opendnp311IMasterTaskD0Ev
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311IMasterTask14ExpirationTimeEv
	.type	_ZNK8opendnp311IMasterTask14ExpirationTimeEv, @function
_ZNK8opendnp311IMasterTask14ExpirationTimeEv:
.LFB2441:
	.cfi_startproc
	cmpb	$0, 48(%rdi)
	jne	.L82
	movq	(%rdi), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	call	*88(%rax)
	testb	%al, %al
	je	.L85
	movq	56(%rbx), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L85:
	.cfi_restore_state
	popq	%rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 8
	jmp	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	.p2align 4,,10
	.p2align 3
.L82:
	jmp	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	.cfi_endproc
.LFE2441:
	.size	_ZNK8opendnp311IMasterTask14ExpirationTimeEv, .-_ZNK8opendnp311IMasterTask14ExpirationTimeEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask24ConfigureStartExpirationEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask24ConfigureStartExpirationEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask24ConfigureStartExpirationEN7openpal18MonotonicTimestampE:
.LFB2442:
	.cfi_startproc
	movq	%rsi, 80(%rdi)
	ret
	.cfi_endproc
.LFE2442:
	.size	_ZN8opendnp311IMasterTask24ConfigureStartExpirationEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask24ConfigureStartExpirationEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv
	.type	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv, @function
_ZNK8opendnp311IMasterTask19StartExpirationTimeEv:
.LFB2443:
	.cfi_startproc
	movq	80(%rdi), %rax
	ret
	.cfi_endproc
.LFE2443:
	.size	_ZNK8opendnp311IMasterTask19StartExpirationTimeEv, .-_ZNK8opendnp311IMasterTask19StartExpirationTimeEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE
	.type	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE, @function
_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE:
.LFB2452:
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
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	movq	72(%rdi), %rdi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L89
	movq	(%rdi), %rax
	call	*8(%rax)
.L89:
	movq	8(%rbx), %r13
	movq	%rbx, %rdi
	movq	0(%r13), %rax
	movq	64(%rax), %r12
	movq	(%rbx), %rax
	call	*96(%rax)
	movl	64(%rbx), %ecx
	movzbl	68(%rbx), %edx
	movl	%ebp, %ebx
	movl	%eax, %r8d
	xorl	%eax, %eax
	cmpq	_ZN8opendnp318IMasterApplication14OnTaskCompleteERKNS_8TaskInfoE@GOTPCREL(%rip), %r12
	movb	%r8b, %al
	movl	%ecx, 16(%rsp)
	movb	%bl, %ah
	movb	%dl, 20(%rsp)
	movw	%ax, 12(%rsp)
	jne	.L96
.L88:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L97
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L96:
	.cfi_restore_state
	leaq	12(%rsp), %rsi
	movq	%r13, %rdi
	call	*%r12
	jmp	.L88
.L97:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2452:
	.size	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE, .-_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask10OnResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceENS4_18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask10OnResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceENS4_18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask10OnResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceENS4_18MonotonicTimestampE:
.LFB2444:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rcx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	call	*72(%rax)
	movl	%eax, %r12d
	cmpb	$1, %al
	je	.L99
	cmpb	$2, %al
	je	.L100
	testb	%al, %al
	je	.L103
	movl	%r12d, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L99:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%r13, %rdx
	movq	%rbp, %rdi
	movl	$5, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$5, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	call	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	movl	%r12d, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L103:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%r13, %rdx
	movq	%rbp, %rdi
	movl	$1, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$1, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	call	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	movl	%r12d, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L100:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%r13, %rdx
	movq	%rbp, %rdi
	xorl	%esi, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	xorl	%esi, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	call	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	movl	%r12d, %eax
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2444:
	.size	_ZN8opendnp311IMasterTask10OnResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceENS4_18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask10OnResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceENS4_18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask17OnResponseTimeoutEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask17OnResponseTimeoutEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask17OnResponseTimeoutEN7openpal18MonotonicTimestampE:
.LFB2445:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$2, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$2, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2445:
	.size	_ZN8opendnp311IMasterTask17OnResponseTimeoutEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask17OnResponseTimeoutEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask17OnLowerLayerCloseEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask17OnLowerLayerCloseEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask17OnLowerLayerCloseEN7openpal18MonotonicTimestampE:
.LFB2446:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$-1, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$-1, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2446:
	.size	_ZN8opendnp311IMasterTask17OnLowerLayerCloseEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask17OnLowerLayerCloseEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE:
.LFB2447:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$3, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$3, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2447:
	.size	_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask14OnStartTimeoutEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask8OnNoUserEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask8OnNoUserEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask8OnNoUserEN7openpal18MonotonicTimestampE:
.LFB2448:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$4, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$4, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2448:
	.size	_ZN8opendnp311IMasterTask8OnNoUserEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask8OnNoUserEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask15OnInternalErrorEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask15OnInternalErrorEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask15OnInternalErrorEN7openpal18MonotonicTimestampE:
.LFB2449:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$5, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$5, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2449:
	.size	_ZN8opendnp311IMasterTask15OnInternalErrorEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask15OnInternalErrorEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask23OnAuthenticationFailureEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask23OnAuthenticationFailureEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask23OnAuthenticationFailureEN7openpal18MonotonicTimestampE:
.LFB2450:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$6, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$6, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2450:
	.size	_ZN8opendnp311IMasterTask23OnAuthenticationFailureEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask23OnAuthenticationFailureEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask22OnAuthorizationFailureEN7openpal18MonotonicTimestampE
	.type	_ZN8opendnp311IMasterTask22OnAuthorizationFailureEN7openpal18MonotonicTimestampE, @function
_ZN8opendnp311IMasterTask22OnAuthorizationFailureEN7openpal18MonotonicTimestampE:
.LFB2451:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	(%rdi), %rax
	movq	%rdi, %rbp
	movq	%rsi, %rdx
	movl	$7, %esi
	call	*80(%rax)
	movq	%rbp, %rdi
	movl	$7, %esi
	movl	%eax, 48(%rbp)
	movq	%rdx, 56(%rbp)
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask12NotifyResultENS_14TaskCompletionE@PLT
	.cfi_endproc
.LFE2451:
	.size	_ZN8opendnp311IMasterTask22OnAuthorizationFailureEN7openpal18MonotonicTimestampE, .-_ZN8opendnp311IMasterTask22OnAuthorizationFailureEN7openpal18MonotonicTimestampE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask7OnStartEv
	.type	_ZN8opendnp311IMasterTask7OnStartEv, @function
_ZN8opendnp311IMasterTask7OnStartEv:
.LFB2453:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	72(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L119
	movq	(%rdi), %rax
	call	*(%rax)
.L119:
	movq	8(%rbp), %r12
	movq	%rbp, %rdi
	movq	(%r12), %rax
	movq	56(%rax), %rbx
	movq	0(%rbp), %rax
	call	*96(%rax)
	cmpq	_ZN8opendnp318IMasterApplication11OnTaskStartENS_14MasterTaskTypeENS_6TaskIdE@GOTPCREL(%rip), %rbx
	jne	.L126
.L120:
	movq	0(%rbp), %rax
	movq	64(%rax), %rax
	cmpq	_ZN8opendnp311IMasterTask10InitializeEv@GOTPCREL(%rip), %rax
	jne	.L127
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
.L126:
	.cfi_restore_state
	movq	64(%rbp), %rdx
	movl	%eax, %esi
	movq	%r12, %rdi
	call	*%rbx
	jmp	.L120
	.p2align 4,,10
	.p2align 3
.L127:
	popq	%rbx
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	*%rax
	.cfi_endproc
.LFE2453:
	.size	_ZN8opendnp311IMasterTask7OnStartEv, .-_ZN8opendnp311IMasterTask7OnStartEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask6DemandEv
	.type	_ZN8opendnp311IMasterTask6DemandEv, @function
_ZN8opendnp311IMasterTask6DemandEv:
.LFB2454:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%esi, %esi
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_ZN7openpal18MonotonicTimestampC1El@PLT
	movq	(%rsp), %rax
	movb	$0, 48(%rbx)
	movq	%rax, 56(%rbx)
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L131
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L131:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2454:
	.size	_ZN8opendnp311IMasterTask6DemandEv, .-_ZN8opendnp311IMasterTask6DemandEv
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Ignoring unexpected response FIR/FIN not set"
	.align 8
.LC2:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/master/IMasterTask.cpp(164)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE
	.type	_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE, @function
_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE:
.LFB2455:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpb	$0, 1(%rsi)
	je	.L133
	movzbl	2(%rsi), %eax
	testb	%al, %al
	je	.L133
.L132:
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L140
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L133:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$4, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L132
	leaq	.LC1(%rip), %rcx
	leaq	.LC2(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L132
.L140:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2455:
	.size	_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE, .-_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"Task was explicitly rejected via response with error IIN bit(s): %s"
	.align 8
.LC4:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/master/IMasterTask.cpp(179)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE
	.type	_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE, @function
_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE:
.LFB2457:
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
	subq	$152, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	movl	$1, %eax
	testb	$7, 7(%rsi)
	jne	.L150
.L141:
	movq	136(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L151
	addq	$152, %rsp
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
.L150:
	.cfi_restore_state
	leaq	16(%rdi), %r12
	leaq	12(%rsp), %r13
	movq	%rdi, %rbp
	movl	$4, 12(%rsp)
	movq	%r13, %rsi
	movq	%r12, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L141
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	leaq	16(%rsp), %r14
	call	*24(%rax)
	movl	$120, %ecx
	movl	$1, %edx
	movq	%r14, %rdi
	movq	%rax, %r9
	leaq	.LC3(%rip), %r8
	movl	$120, %esi
	xorl	%eax, %eax
	call	__snprintf_chk@PLT
	movq	%r14, %rcx
	movq	%r13, %rsi
	movq	%r12, %rdi
	leaq	.LC4(%rip), %rdx
	movl	$4, 12(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L141
.L151:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2457:
	.size	_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE, .-_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"Received unexpected response object headers for task: %s"
	.align 8
.LC6:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/master/IMasterTask.cpp(196)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE
	.type	_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE, @function
_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE:
.LFB2458:
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
	subq	$152, %rsp
	.cfi_def_cfa_offset 192
	movl	(%rsi), %edx
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	movl	$1, %eax
	testl	%edx, %edx
	jne	.L160
.L152:
	movq	136(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L161
	addq	$152, %rsp
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
.L160:
	.cfi_restore_state
	leaq	16(%rdi), %r12
	leaq	12(%rsp), %r13
	movq	%rdi, %rbp
	movl	$4, 12(%rsp)
	movq	%r13, %rsi
	movq	%r12, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L152
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	leaq	16(%rsp), %r14
	call	*24(%rax)
	movl	$120, %ecx
	movl	$1, %edx
	movq	%r14, %rdi
	movq	%rax, %r9
	leaq	.LC5(%rip), %r8
	movl	$120, %esi
	xorl	%eax, %eax
	call	__snprintf_chk@PLT
	movq	%r14, %rcx
	movq	%r13, %rsi
	movq	%r12, %rdi
	leaq	.LC6(%rip), %rdx
	movl	$4, 12(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L152
.L161:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2458:
	.size	_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE, .-_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311IMasterTask20ValidateNullResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE
	.type	_ZN8opendnp311IMasterTask20ValidateNullResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE, @function
_ZN8opendnp311IMasterTask20ValidateNullResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE:
.LFB2456:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	call	_ZN8opendnp311IMasterTask22ValidateSingleResponseERKNS_18APDUResponseHeaderE@PLT
	testb	%al, %al
	jne	.L170
.L164:
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L170:
	.cfi_restore_state
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311IMasterTask17ValidateNoObjectsERKN7openpal6RSliceE@PLT
	testb	%al, %al
	je	.L164
	movq	%r12, %rsi
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311IMasterTask27ValidateInternalIndicationsERKNS_18APDUResponseHeaderE@PLT
	.cfi_endproc
.LFE2456:
	.size	_ZN8opendnp311IMasterTask20ValidateNullResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE, .-_ZN8opendnp311IMasterTask20ValidateNullResponseERKNS_18APDUResponseHeaderERKN7openpal6RSliceE
	.weak	_ZTSN8opendnp311IMasterTaskE
	.section	.rodata._ZTSN8opendnp311IMasterTaskE,"aG",@progbits,_ZTSN8opendnp311IMasterTaskE,comdat
	.align 16
	.type	_ZTSN8opendnp311IMasterTaskE, @object
	.size	_ZTSN8opendnp311IMasterTaskE, 25
_ZTSN8opendnp311IMasterTaskE:
	.string	"N8opendnp311IMasterTaskE"
	.weak	_ZTIN8opendnp311IMasterTaskE
	.section	.data.rel.ro._ZTIN8opendnp311IMasterTaskE,"awG",@progbits,_ZTIN8opendnp311IMasterTaskE,comdat
	.align 8
	.type	_ZTIN8opendnp311IMasterTaskE, @object
	.size	_ZTIN8opendnp311IMasterTaskE, 16
_ZTIN8opendnp311IMasterTaskE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp311IMasterTaskE
	.weak	_ZTVN8opendnp311IMasterTaskE
	.section	.data.rel.ro._ZTVN8opendnp311IMasterTaskE,"awG",@progbits,_ZTVN8opendnp311IMasterTaskE,comdat
	.align 8
	.type	_ZTVN8opendnp311IMasterTaskE, @object
	.size	_ZTVN8opendnp311IMasterTaskE, 120
_ZTVN8opendnp311IMasterTaskE:
	.quad	0
	.quad	_ZTIN8opendnp311IMasterTaskE
	.quad	0
	.quad	0
	.quad	_ZNK8opendnp311IMasterTask10IsAuthTaskEv
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	_ZN8opendnp311IMasterTask10InitializeEv
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
	.quad	__cxa_pure_virtual
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
