	.file	"DatabaseBuffers.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE:
.LFB2401:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rsi, %rbx
	subq	$144, %rsp
	.cfi_def_cfa_offset 176
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	$0, 8(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 88(%rsp)
	movq	%rax, (%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	$0, 104(%rsp)
	movq	%rax, 16(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	$0, 120(%rsp)
	movq	%rax, 32(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	%rax, 48(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	%rax, 64(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	%rax, 80(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	%rax, 96(%rsp)
	movq	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE@GOTPCREL(%rip), %rax
	movq	%rax, 112(%rsp)
	.p2align 4,,10
	.p2align 3
.L4:
	movslq	%r12d, %rax
	salq	$4, %rax
	movq	8(%rsp,%rax), %rdi
	movq	(%rsp,%rax), %rax
	addq	%rbp, %rdi
	testb	$1, %al
	je	.L2
	movq	(%rdi), %rdx
	movq	-1(%rdx,%rax), %rax
.L2:
	movq	%rbx, %rsi
	call	*%rax
	testb	%al, %al
	je	.L1
	addl	$1, %r12d
	cmpl	$8, %r12d
	jne	.L4
.L1:
	movq	136(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L15
	addq	$144, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2401:
	.size	_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.set	.LTHUNK1,_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.p2align 4
	.globl	_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.type	_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE, @function
_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE:
.LFB3292:
	.cfi_startproc
	subq	$8, %rdi
	jmp	.LTHUNK1
	.cfi_endproc
.LFE3292:
	.size	_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE, .-_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers8UnselectEv
	.type	_ZN8opendnp315DatabaseBuffers8UnselectEv, @function
_ZN8opendnp315DatabaseBuffers8UnselectEv:
.LFB2398:
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
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movq	%rbp, %rdi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10BinarySpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L42
.L17:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L43
.L19:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L44
.L21:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L45
.L23:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L46
.L25:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L47
.L27:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L48
.L29:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19TimeAndIntervalSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %r12d
	movzwl	2(%rax), %r13d
	cmpw	%r13w, %r12w
	jbe	.L49
	addq	$8, %rsp
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
.L42:
	.cfi_restore_state
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L18:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	movb	$0, 72(%rcx,%rax)
	cmpw	%r12w, %r13w
	jnb	.L18
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10BinarySpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L17
	.p2align 4,,10
	.p2align 3
.L49:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L32:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	movb	$0, 24(%rcx,%rax,8)
	cmpw	%r12w, %r13w
	jnb	.L32
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19TimeAndIntervalSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	addq	$8, %rsp
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
.L48:
	.cfi_restore_state
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L30:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movb	$0, 80(%rcx,%rax,8)
	cmpw	%r12w, %r13w
	jnb	.L30
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L47:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L28:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	movb	$0, 72(%rcx,%rax)
	cmpw	%r12w, %r13w
	jnb	.L28
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L46:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L26:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movb	$0, 80(%rcx,%rax,8)
	cmpw	%r12w, %r13w
	jnb	.L26
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L45:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L24:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movb	$0, 80(%rcx,%rax,8)
	cmpw	%r12w, %r13w
	jnb	.L24
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L23
	.p2align 4,,10
	.p2align 3
.L44:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L22:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movb	$0, 80(%rcx,%rax,8)
	cmpw	%r12w, %r13w
	jnb	.L22
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L43:
	leaq	24(%rbx), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L20:
	movzwl	%r12w, %edx
	addl	$1, %r12d
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	movb	$0, 72(%rcx,%rax)
	cmpw	%r12w, %r13w
	jnb	.L20
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	movl	$1, (%rax)
	jmp	.L19
	.cfi_endproc
.LFE2398:
	.size	_ZN8opendnp315DatabaseBuffers8UnselectEv, .-_ZN8opendnp315DatabaseBuffers8UnselectEv
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE:
.LFB2774:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19TimeAndIntervalSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L72
.L50:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L73
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L72:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L56:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L52
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L59:
	movzwl	%dx, %ecx
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	leaq	(%rdi,%rax,8), %rax
	cmpb	$0, 24(%rax)
	jne	.L74
	cmpw	%dx, %si
	ja	.L75
	movl	$1, 12(%rsp)
.L52:
	movl	$1, %r13d
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L75:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L59
	movw	%dx, 12(%rsp)
	jmp	.L52
	.p2align 4,,10
	.p2align 3
.L74:
	testb	%r8b, %r8b
	je	.L55
	movw	%dx, 12(%rsp)
.L55:
	movzbl	48(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L56
.L57:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19TimeAndIntervalSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L50
.L73:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2774:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19TimeAndIntervalSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE:
.LFB2773:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L98
.L76:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L99
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L98:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L82:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L78
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L85:
	movzwl	%dx, %ecx
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	leaq	(%rdi,%rax,8), %rax
	cmpb	$0, 80(%rax)
	jne	.L100
	cmpw	%dx, %si
	ja	.L101
	movl	$1, 12(%rsp)
.L78:
	movl	$1, %r13d
	jmp	.L83
	.p2align 4,,10
	.p2align 3
.L101:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L85
	movw	%dx, 12(%rsp)
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L100:
	testb	%r8b, %r8b
	je	.L81
	movw	%dx, 12(%rsp)
.L81:
	movzbl	112(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L82
.L83:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L76
.L99:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2773:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22AnalogOutputStatusSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE:
.LFB2772:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L124
.L102:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L125
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L124:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L108:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L104
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L111:
	movzwl	%dx, %ecx
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	addq	%rdi, %rax
	cmpb	$0, 72(%rax)
	jne	.L126
	cmpw	%dx, %si
	ja	.L127
	movl	$1, 12(%rsp)
.L104:
	movl	$1, %r13d
	jmp	.L109
	.p2align 4,,10
	.p2align 3
.L127:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L111
	movw	%dx, 12(%rsp)
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L126:
	testb	%r8b, %r8b
	je	.L107
	movw	%dx, 12(%rsp)
.L107:
	movzbl	104(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L108
.L109:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L102
.L125:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2772:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_22BinaryOutputStatusSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE:
.LFB2771:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L150
.L128:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L151
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L150:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L134:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L130
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L137:
	movzwl	%dx, %ecx
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	leaq	(%rdi,%rax,8), %rax
	cmpb	$0, 80(%rax)
	jne	.L152
	cmpw	%dx, %si
	ja	.L153
	movl	$1, 12(%rsp)
.L130:
	movl	$1, %r13d
	jmp	.L135
	.p2align 4,,10
	.p2align 3
.L153:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L137
	movw	%dx, 12(%rsp)
	jmp	.L130
	.p2align 4,,10
	.p2align 3
.L152:
	testb	%r8b, %r8b
	je	.L133
	movw	%dx, 12(%rsp)
.L133:
	movzbl	112(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L134
.L135:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L128
.L151:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2771:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10AnalogSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE:
.LFB2770:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L176
.L154:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L177
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L176:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L160:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L156
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L163:
	movzwl	%dx, %ecx
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	leaq	(%rdi,%rax,8), %rax
	cmpb	$0, 80(%rax)
	jne	.L178
	cmpw	%dx, %si
	ja	.L179
	movl	$1, 12(%rsp)
.L156:
	movl	$1, %r13d
	jmp	.L161
	.p2align 4,,10
	.p2align 3
.L179:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L163
	movw	%dx, 12(%rsp)
	jmp	.L156
	.p2align 4,,10
	.p2align 3
.L178:
	testb	%r8b, %r8b
	je	.L159
	movw	%dx, 12(%rsp)
.L159:
	movzbl	112(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L160
.L161:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L154
.L177:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2770:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_17FrozenCounterSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE:
.LFB2769:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L202
.L180:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L203
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L202:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L186:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L182
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L189:
	movzwl	%dx, %ecx
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	leaq	(%rdi,%rax,8), %rax
	cmpb	$0, 80(%rax)
	jne	.L204
	cmpw	%dx, %si
	ja	.L205
	movl	$1, 12(%rsp)
.L182:
	movl	$1, %r13d
	jmp	.L187
	.p2align 4,,10
	.p2align 3
.L205:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L189
	movw	%dx, 12(%rsp)
	jmp	.L182
	.p2align 4,,10
	.p2align 3
.L204:
	testb	%r8b, %r8b
	je	.L185
	movw	%dx, 12(%rsp)
.L185:
	movzbl	112(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L186
.L187:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L180
.L203:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2769:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_11CounterSpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE:
.LFB2768:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L228
.L206:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L229
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L228:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L212:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L208
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L215:
	movzwl	%dx, %ecx
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	addq	%rdi, %rax
	cmpb	$0, 72(%rax)
	jne	.L230
	cmpw	%dx, %si
	ja	.L231
	movl	$1, 12(%rsp)
.L208:
	movl	$1, %r13d
	jmp	.L213
	.p2align 4,,10
	.p2align 3
.L231:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L215
	movw	%dx, 12(%rsp)
	jmp	.L208
	.p2align 4,,10
	.p2align 3
.L230:
	testb	%r8b, %r8b
	je	.L211
	movw	%dx, 12(%rsp)
.L211:
	movzbl	104(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L212
.L213:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L206
.L229:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2768:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_19DoubleBitBinarySpecEEEbRNS_12HeaderWriterE
	.section	.text._ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE
	.type	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE, @function
_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE:
.LFB2767:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	leaq	220(%rdi), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rbp, %rdi
	movq	%rsi, %rbx
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10BinarySpecEEERNS_5RangeEv@PLT
	movzwl	(%rax), %edx
	movzwl	2(%rax), %eax
	movw	%dx, 12(%rsp)
	movw	%ax, 14(%rsp)
	cmpw	%dx, %ax
	jnb	.L254
.L232:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L255
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.L254:
	.cfi_restore_state
	leaq	24(%r12), %rdi
	leaq	12(%rsp), %r12
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
.L238:
	movzwl	12(%rsp), %edx
	movzwl	14(%rsp), %esi
	cmpw	%si, %dx
	ja	.L234
	movq	24(%rsp), %rdi
	xorl	%r8d, %r8d
.L241:
	movzwl	%dx, %ecx
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	addq	%rdi, %rax
	cmpb	$0, 72(%rax)
	jne	.L256
	cmpw	%dx, %si
	ja	.L257
	movl	$1, 12(%rsp)
.L234:
	movl	$1, %r13d
	jmp	.L239
	.p2align 4,,10
	.p2align 3
.L257:
	addl	$1, %edx
	movl	$1, %r8d
	cmpw	%si, %dx
	jbe	.L241
	movw	%dx, 12(%rsp)
	jmp	.L234
	.p2align 4,,10
	.p2align 3
.L256:
	testb	%r8b, %r8b
	je	.L237
	movw	%dx, 12(%rsp)
.L237:
	movzbl	104(%rax), %edi
	call	_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rdx
	movq	%rbx, %rsi
	call	*%rax
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L238
.L239:
	movq	%rbp, %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10BinarySpecEEERNS_5RangeEv@PLT
	movl	12(%rsp), %edx
	movl	%edx, (%rax)
	jmp	.L232
.L255:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2767:
	.size	_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE, .-_ZN8opendnp315DatabaseBuffers8LoadTypeINS_10BinarySpecEEEbRNS_12HeaderWriterE
	.section	.text._ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv,"axG",@progbits,_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.type	_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv, @function
_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv:
.LFB375:
	.cfi_startproc
	addq	$220, %rdi
	jmp	_ZNK8opendnp314SelectedRanges15HasAnySelectionEv@PLT
	.cfi_endproc
.LFE375:
	.size	_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv, .-_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.p2align 4
	.weak	_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.type	_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv, @function
_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv:
.LFB3281:
	.cfi_startproc
	addq	$212, %rdi
	jmp	_ZNK8opendnp314SelectedRanges15HasAnySelectionEv@PLT
	.cfi_endproc
.LFE3281:
	.size	_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv, .-_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE
	.type	_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE, @function
_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE:
.LFB2396:
	.cfi_startproc
	movq	_ZTVN8opendnp315DatabaseBuffersE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%ecx, %ebp
	leaq	88(%rax), %rdx
	leaq	16(%rax), %rcx
	addq	$120, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rcx, %xmm0
	movq	%rax, 16(%rdi)
	movq	%rdx, %xmm1
	movq	%rdi, %rbx
	punpcklqdq	%xmm1, %xmm0
	leaq	24(%rdi), %rdi
	movups	%xmm0, -24(%rdi)
	call	_ZN8opendnp313StaticBuffersC1ERKNS_13DatabaseSizesE@PLT
	movdqa	.LC0(%rip), %xmm0
	movw	%r12w, 216(%rbx)
	movb	%bpl, 218(%rbx)
	movl	$1, 252(%rbx)
	movups	%xmm0, 220(%rbx)
	movups	%xmm0, 236(%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2396:
	.size	_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE, .-_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE
	.globl	_ZN8opendnp315DatabaseBuffersC1ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE
	.set	_ZN8opendnp315DatabaseBuffersC1ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE,_ZN8opendnp315DatabaseBuffersC2ERKNS_13DatabaseSizesENS_18StaticTypeBitFieldENS_9IndexModeE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_
	.type	_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_, @function
_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_:
.LFB2404:
	.cfi_startproc
	movl	%esi, %eax
	testb	%sil, %sil
	jne	.L262
	movzbl	(%rdi), %eax
	andl	$127, %eax
	cmpb	$1, %al
	setne	%al
.L262:
	ret
	.cfi_endproc
.LFE2404:
	.size	_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_, .-_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers7RangeOfEt
	.type	_ZN8opendnp315DatabaseBuffers7RangeOfEt, @function
_ZN8opendnp315DatabaseBuffers7RangeOfEt:
.LFB2405:
	.cfi_startproc
	movl	%edi, %edx
	movl	$1, %eax
	testw	%di, %di
	je	.L266
	leal	-1(%rdi), %edx
	xorl	%eax, %eax
.L266:
	sall	$16, %edx
	andl	$1, %eax
	orl	%edx, %eax
	ret
	.cfi_endproc
.LFE2405:
	.size	_ZN8opendnp315DatabaseBuffers7RangeOfEt, .-_ZN8opendnp315DatabaseBuffers7RangeOfEt
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.type	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, @function
_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE:
.LFB2403:
	.cfi_startproc
	cmpb	$6, %sil
	ja	.L269
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movzbl	%sil, %esi
	addq	$24, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rcx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%edx, %ebx
	leaq	.L271(%rip), %rdx
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L271:
	.long	.L277-.L271
	.long	.L276-.L271
	.long	.L275-.L271
	.long	.L274-.L271
	.long	.L273-.L271
	.long	.L272-.L271
	.long	.L270-.L271
	.text
	.p2align 4,,10
	.p2align 3
.L272:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %esi
	.p2align 4,,10
	.p2align 3
.L290:
	movzwl	%si, %edi
	addl	$1, %esi
	leaq	0(,%rdi,8), %rcx
	subq	%rdi, %rcx
	salq	$4, %rcx
	movb	%bl, 27(%r12,%rcx)
	cmpw	%si, %ax
	jnb	.L290
.L291:
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L270:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %ecx
	.p2align 4,,10
	.p2align 3
.L292:
	movzwl	%cx, %edi
	addl	$1, %ecx
	movq	%rdi, %rsi
	salq	$4, %rsi
	subq	%rdi, %rsi
	movb	%bl, 27(%r12,%rsi,8)
	cmpw	%cx, %ax
	jnb	.L292
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L277:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %esi
	.p2align 4,,10
	.p2align 3
.L279:
	movzwl	%si, %edi
	addl	$1, %esi
	leaq	0(,%rdi,8), %rcx
	subq	%rdi, %rcx
	salq	$4, %rcx
	movb	%bl, 27(%r12,%rcx)
	cmpw	%si, %ax
	jnb	.L279
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L276:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %esi
	.p2align 4,,10
	.p2align 3
.L282:
	movzwl	%si, %edi
	addl	$1, %esi
	leaq	0(,%rdi,8), %rcx
	subq	%rdi, %rcx
	salq	$4, %rcx
	movb	%bl, 27(%r12,%rcx)
	cmpw	%si, %ax
	jnb	.L282
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L275:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %ecx
	.p2align 4,,10
	.p2align 3
.L284:
	movzwl	%cx, %edi
	addl	$1, %ecx
	movq	%rdi, %rsi
	salq	$4, %rsi
	subq	%rdi, %rsi
	movb	%bl, 27(%r12,%rsi,8)
	cmpw	%cx, %ax
	jnb	.L284
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L274:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %ecx
	.p2align 4,,10
	.p2align 3
.L286:
	movzwl	%cx, %edi
	addl	$1, %ecx
	movq	%rdi, %rsi
	salq	$4, %rsi
	subq	%rdi, %rsi
	movb	%bl, 27(%r12,%rsi,8)
	cmpw	%cx, %ax
	jnb	.L286
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L273:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %ecx
	movl	%eax, %edx
	movzwl	2(%rbp), %eax
	shrl	$16, %edx
	cmpw	%dx, %ax
	cmovnb	%edx, %eax
	movzwl	0(%rbp), %edx
	cmpw	%cx, %dx
	cmovbe	%ecx, %edx
	cmpw	%dx, %ax
	jb	.L291
	movl	%edx, %ecx
	.p2align 4,,10
	.p2align 3
.L288:
	movzwl	%cx, %edi
	addl	$1, %ecx
	movq	%rdi, %rsi
	salq	$4, %rsi
	subq	%rdi, %rsi
	movb	%bl, 27(%r12,%rsi,8)
	cmpw	%cx, %ax
	jnb	.L288
	movl	%eax, %ecx
	movzwl	%dx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	sall	$16, %ecx
	popq	%r12
	.cfi_def_cfa_offset 8
	orl	%ecx, %eax
	ret
.L269:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2403:
	.size	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, .-_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.set	.LTHUNK3,_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.p2align 4
	.globl	_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.type	_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, @function
_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE:
.LFB3294:
	.cfi_startproc
	subq	$16, %rdi
	jmp	.LTHUNK3
	.cfi_endproc
.LFE3294:
	.size	_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, .-_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.type	_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE, @function
_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE:
.LFB2402:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpb	$6, %sil
	ja	.L305
	leaq	.L307(%rip), %rcx
	movzbl	%sil, %esi
	movq	%rdi, %rbp
	movl	%edx, %ebx
	movslq	(%rcx,%rsi,4), %rax
	leaq	24(%rdi), %rdi
	addq	%rcx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L307:
	.long	.L313-.L307
	.long	.L312-.L307
	.long	.L311-.L307
	.long	.L310-.L307
	.long	.L309-.L307
	.long	.L308-.L307
	.long	.L306-.L307
	.text
	.p2align 4,,10
	.p2align 3
.L308:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$5, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	.p2align 4,,10
	.p2align 3
.L314:
	movq	8(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L317
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
.L306:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$6, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L313:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L312:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$1, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L311:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$2, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L310:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$3, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L309:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	leaq	4(%rsp), %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	movl	$4, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	jmp	.L314
.L305:
	movl	$1, %eax
	jmp	.L314
.L317:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2402:
	.size	_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE, .-_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3290:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L341
.L330:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L342
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
.L341:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %ebx
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r14d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r13d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r15d
	cmovbe	%ecx, %r15d
	cmpw	%ax, %bx
	cmovnb	%ebx, %r13d
	cmpw	%r13w, %r15w
	jb	.L320
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L321
	cmpw	%ax, %bx
	jnb	.L343
.L321:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L322:
	movl	%r13d, %ebx
	testb	%r8b, %r8b
	jne	.L332
	leaq	22(%rsp), %rcx
	jmp	.L327
	.p2align 4,,10
	.p2align 3
.L344:
	movq	(%rax), %rdx
	addl	$1, %ebx
	movb	$1, 24(%rax)
	movb	%r14b, 48(%rax)
	movq	%rdx, 32(%rax)
	movl	8(%rax), %edx
	movl	%edx, 40(%rax)
	movzbl	12(%rax), %edx
	movb	%dl, 44(%rax)
	cmpw	%bx, %r15w
	jb	.L326
.L327:
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 24(%rax)
	je	.L344
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %ebx
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%bx, %r15w
	jnb	.L327
	.p2align 4,,10
	.p2align 3
.L326:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19TimeAndIntervalSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%r13w, (%rax)
	cmovbe	(%rax), %r13w
	movw	%r15w, 2(%rax)
	movw	%r13w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L330
	.p2align 4,,10
	.p2align 3
.L332:
	leaq	22(%rsp), %r14
	jmp	.L323
	.p2align 4,,10
	.p2align 3
.L328:
	movq	(%rax), %rdx
	movb	$1, 24(%rax)
	movq	%rdx, 32(%rax)
	movl	8(%rax), %edx
	movl	%edx, 40(%rax)
	movzbl	12(%rax), %edx
	movb	%dl, 44(%rax)
	movzbl	18(%rax), %edx
	movb	%dl, 48(%rax)
.L329:
	addl	$1, %ebx
	cmpw	%bx, %r15w
	jb	.L326
.L323:
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 24(%rax)
	je	.L328
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L329
	.p2align 4,,10
	.p2align 3
.L320:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L330
	.p2align 4,,10
	.p2align 3
.L343:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L322
.L342:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3290:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3289:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L368
.L357:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L369
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
.L368:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %ebx
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r14d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r13d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r15d
	cmovbe	%ecx, %r15d
	cmpw	%ax, %bx
	cmovnb	%ebx, %r13d
	cmpw	%r13w, %r15w
	jb	.L347
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L348
	cmpw	%ax, %bx
	jnb	.L370
.L348:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L349:
	movl	%r13d, %ebx
	testb	%r8b, %r8b
	jne	.L359
	leaq	22(%rsp), %rcx
	jmp	.L354
	.p2align 4,,10
	.p2align 3
.L371:
	movdqu	(%rax), %xmm0
	movq	16(%rax), %rdx
	addl	$1, %ebx
	movb	$1, 80(%rax)
	movb	%r14b, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm0, 88(%rax)
	cmpw	%bx, %r15w
	jb	.L353
.L354:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L371
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %ebx
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%bx, %r15w
	jnb	.L354
	.p2align 4,,10
	.p2align 3
.L353:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%r13w, (%rax)
	cmovbe	(%rax), %r13w
	movw	%r15w, 2(%rax)
	movw	%r13w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L357
	.p2align 4,,10
	.p2align 3
.L359:
	leaq	22(%rsp), %r14
	jmp	.L350
	.p2align 4,,10
	.p2align 3
.L355:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movq	%rdx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L356:
	addl	$1, %ebx
	cmpw	%bx, %r15w
	jb	.L353
.L350:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L355
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L356
	.p2align 4,,10
	.p2align 3
.L347:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L357
	.p2align 4,,10
	.p2align 3
.L370:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L349
.L369:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3289:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3288:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L395
.L384:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L396
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
.L395:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %ebx
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r14d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r13d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r15d
	cmovbe	%ecx, %r15d
	cmpw	%ax, %bx
	cmovnb	%ebx, %r13d
	cmpw	%r13w, %r15w
	jb	.L374
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L375
	cmpw	%ax, %bx
	jnb	.L397
.L375:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L376:
	movl	%r13d, %ebx
	testb	%r8b, %r8b
	jne	.L386
	leaq	22(%rsp), %rcx
	jmp	.L381
	.p2align 4,,10
	.p2align 3
.L398:
	movdqu	(%rax), %xmm0
	movq	16(%rax), %rdx
	addl	$1, %ebx
	movb	$1, 80(%rax)
	movb	%r14b, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm0, 88(%rax)
	cmpw	%bx, %r15w
	jb	.L380
.L381:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L398
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %ebx
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%bx, %r15w
	jnb	.L381
	.p2align 4,,10
	.p2align 3
.L380:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%r13w, (%rax)
	cmovbe	(%rax), %r13w
	movw	%r15w, 2(%rax)
	movw	%r13w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L384
	.p2align 4,,10
	.p2align 3
.L386:
	leaq	22(%rsp), %r14
	jmp	.L377
	.p2align 4,,10
	.p2align 3
.L382:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movq	%rdx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L383:
	addl	$1, %ebx
	cmpw	%bx, %r15w
	jb	.L380
.L377:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L382
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L374:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L384
	.p2align 4,,10
	.p2align 3
.L397:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L376
.L396:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3288:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3287:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L422
.L411:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L423
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
.L422:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %ebx
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r14d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r13d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r15d
	cmovbe	%ecx, %r15d
	cmpw	%ax, %bx
	cmovnb	%ebx, %r13d
	cmpw	%r13w, %r15w
	jb	.L401
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L402
	cmpw	%ax, %bx
	jnb	.L424
.L402:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L403:
	movl	%r13d, %ebx
	testb	%r8b, %r8b
	jne	.L413
	leaq	22(%rsp), %rcx
	jmp	.L408
	.p2align 4,,10
	.p2align 3
.L425:
	movdqu	(%rax), %xmm0
	movl	16(%rax), %edx
	addl	$1, %ebx
	movb	$1, 80(%rax)
	movb	%r14b, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm0, 88(%rax)
	cmpw	%bx, %r15w
	jb	.L407
.L408:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L425
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %ebx
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%bx, %r15w
	jnb	.L408
	.p2align 4,,10
	.p2align 3
.L407:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%r13w, (%rax)
	cmovbe	(%rax), %r13w
	movw	%r15w, 2(%rax)
	movw	%r13w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L411
	.p2align 4,,10
	.p2align 3
.L413:
	leaq	22(%rsp), %r14
	jmp	.L404
	.p2align 4,,10
	.p2align 3
.L409:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movl	%edx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L410:
	addl	$1, %ebx
	cmpw	%bx, %r15w
	jb	.L407
.L404:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L409
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L410
	.p2align 4,,10
	.p2align 3
.L401:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L411
	.p2align 4,,10
	.p2align 3
.L424:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L403
.L423:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3287:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3286:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L449
.L438:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L450
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
.L449:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %ebx
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r14d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r13d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r15d
	cmovbe	%ecx, %r15d
	cmpw	%ax, %bx
	cmovnb	%ebx, %r13d
	cmpw	%r13w, %r15w
	jb	.L428
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L429
	cmpw	%ax, %bx
	jnb	.L451
.L429:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L430:
	movl	%r13d, %ebx
	testb	%r8b, %r8b
	jne	.L440
	leaq	22(%rsp), %rcx
	jmp	.L435
	.p2align 4,,10
	.p2align 3
.L452:
	movdqu	(%rax), %xmm0
	movl	16(%rax), %edx
	addl	$1, %ebx
	movb	$1, 80(%rax)
	movb	%r14b, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm0, 88(%rax)
	cmpw	%bx, %r15w
	jb	.L434
.L435:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L452
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %ebx
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%bx, %r15w
	jnb	.L435
	.p2align 4,,10
	.p2align 3
.L434:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%r13w, (%rax)
	cmovbe	(%rax), %r13w
	movw	%r15w, 2(%rax)
	movw	%r13w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L438
	.p2align 4,,10
	.p2align 3
.L440:
	leaq	22(%rsp), %r14
	jmp	.L431
	.p2align 4,,10
	.p2align 3
.L436:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movl	%edx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L437:
	addl	$1, %ebx
	cmpw	%bx, %r15w
	jb	.L434
.L431:
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%rbp,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L436
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L437
	.p2align 4,,10
	.p2align 3
.L428:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L438
	.p2align 4,,10
	.p2align 3
.L451:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L430
.L450:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3286:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3285:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rcx, %r12
	movl	%esi, %ecx
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	shrl	$16, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L476
.L465:
	movq	24(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L477
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
.L476:
	.cfi_restore_state
	movq	%rdi, %rbx
	movzwl	%dx, %edi
	movl	%esi, %r15d
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r13d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %ebp
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r14d
	cmovbe	%ecx, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebp
	cmpw	%bp, %r14w
	jb	.L455
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L456
	cmpw	%ax, %r15w
	jnb	.L478
.L456:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L457:
	testb	%r8b, %r8b
	jne	.L467
	movl	%ebp, %r15d
	leaq	22(%rsp), %rcx
	jmp	.L462
	.p2align 4,,10
	.p2align 3
.L479:
	movdqu	(%rax), %xmm0
	movzbl	16(%rax), %edx
	addl	$1, %r15d
	movb	$1, 72(%rax)
	movb	%r13b, 104(%rax)
	movb	%dl, 96(%rax)
	movups	%xmm0, 80(%rax)
	cmpw	%r15w, %r14w
	jb	.L461
.L462:
	movzwl	%r15w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r12, %rax
	cmpb	$0, 72(%rax)
	je	.L479
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %r15d
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%r15w, %r14w
	jnb	.L462
	.p2align 4,,10
	.p2align 3
.L461:
	leaq	220(%rbx), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	cmpw	%r14w, 2(%rax)
	cmovnb	2(%rax), %r14w
	cmpw	%bp, (%rax)
	cmovbe	(%rax), %bp
	movw	%r14w, 2(%rax)
	movw	%bp, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L465
	.p2align 4,,10
	.p2align 3
.L467:
	movl	%ebp, %r13d
	leaq	22(%rsp), %r15
	jmp	.L458
	.p2align 4,,10
	.p2align 3
.L463:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 72(%rax)
	movb	%dl, 96(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 80(%rax)
	movb	%dl, 104(%rax)
.L464:
	addl	$1, %r13d
	cmpw	%r13w, %r14w
	jb	.L461
.L458:
	movzwl	%r13w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r12, %rax
	cmpb	$0, 72(%rax)
	je	.L463
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L464
	.p2align 4,,10
	.p2align 3
.L455:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L465
	.p2align 4,,10
	.p2align 3
.L478:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L457
.L477:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3285:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3284:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rcx, %r12
	movl	%esi, %ecx
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	shrl	$16, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L503
.L492:
	movq	24(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L504
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
.L503:
	.cfi_restore_state
	movq	%rdi, %rbx
	movzwl	%dx, %edi
	movl	%esi, %r15d
	movl	%ecx, (%rsp)
	movl	%r8d, 12(%rsp)
	movl	%r9d, %r13d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %ebp
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r14d
	cmovbe	%ecx, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebp
	cmpw	%bp, %r14w
	jb	.L482
	cmpw	%dx, %cx
	movl	12(%rsp), %r8d
	ja	.L483
	cmpw	%ax, %r15w
	jnb	.L505
.L483:
	xorl	%edi, %edi
	movl	$10, %esi
	movl	%r8d, (%rsp)
	movw	%di, 20(%rsp)
	leaq	20(%rsp), %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L484:
	testb	%r8b, %r8b
	jne	.L494
	movl	%ebp, %r15d
	leaq	22(%rsp), %rcx
	jmp	.L489
	.p2align 4,,10
	.p2align 3
.L506:
	movdqu	(%rax), %xmm0
	movzbl	16(%rax), %edx
	addl	$1, %r15d
	movb	$1, 72(%rax)
	movb	%r13b, 104(%rax)
	movb	%dl, 96(%rax)
	movups	%xmm0, 80(%rax)
	cmpw	%r15w, %r14w
	jb	.L488
.L489:
	movzwl	%r15w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r12, %rax
	cmpb	$0, 72(%rax)
	je	.L506
	xorl	%esi, %esi
	movq	%rcx, %rdi
	addl	$1, %r15d
	movq	%rcx, (%rsp)
	movw	%si, 22(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 20(%rsp)
	cmpw	%r15w, %r14w
	jnb	.L489
	.p2align 4,,10
	.p2align 3
.L488:
	leaq	220(%rbx), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	cmpw	%r14w, 2(%rax)
	cmovnb	2(%rax), %r14w
	cmpw	%bp, (%rax)
	cmovbe	(%rax), %bp
	movw	%r14w, 2(%rax)
	movw	%bp, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L492
	.p2align 4,,10
	.p2align 3
.L494:
	movl	%ebp, %r13d
	leaq	22(%rsp), %r15
	jmp	.L485
	.p2align 4,,10
	.p2align 3
.L490:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 72(%rax)
	movb	%dl, 96(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 80(%rax)
	movb	%dl, 104(%rax)
.L491:
	addl	$1, %r13d
	cmpw	%r13w, %r14w
	jb	.L488
.L485:
	movzwl	%r13w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r12, %rax
	cmpb	$0, 72(%rax)
	je	.L490
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L491
	.p2align 4,,10
	.p2align 3
.L482:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L492
	.p2align 4,,10
	.p2align 3
.L505:
	xorl	%r9d, %r9d
	movw	%r9w, 20(%rsp)
	jmp	.L484
.L504:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3284:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.type	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, @function
_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0:
.LFB3283:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rcx, %rbp
	movl	%esi, %ecx
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	shrl	$16, %ecx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpw	%cx, %si
	jbe	.L530
.L519:
	movq	24(%rsp), %rsi
	subq	%fs:40, %rsi
	jne	.L531
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
.L530:
	.cfi_restore_state
	movq	%rdi, %r12
	movzwl	%dx, %edi
	movl	%esi, %r15d
	movl	%ecx, (%rsp)
	movl	%r8d, 8(%rsp)
	movl	%r9d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	%eax, %edx
	movl	%eax, %r14d
	shrl	$16, %edx
	cmpw	%dx, %cx
	movl	%edx, %r13d
	cmovbe	%ecx, %r13d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %r14d
	cmpw	%r14w, %r13w
	jb	.L509
	cmpw	%dx, %cx
	movl	8(%rsp), %r8d
	ja	.L510
	cmpw	%ax, %r15w
	jnb	.L532
.L510:
	xorl	%esi, %esi
	leaq	20(%rsp), %rdi
	movl	%r8d, (%rsp)
	movw	%si, 20(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movl	(%rsp), %r8d
.L511:
	movl	%r14d, %r15d
	leaq	22(%rsp), %rax
	testb	%r8b, %r8b
	jne	.L521
	movq	%rax, 8(%rsp)
	jmp	.L516
	.p2align 4,,10
	.p2align 3
.L533:
	movzbl	16(%rdx), %eax
	movdqu	(%rdx), %xmm0
	movb	$1, 72(%rdx)
	leaq	80(%rdx), %rdi
	movl	%ebx, %esi
	movq	%rdx, (%rsp)
	addl	$1, %r15d
	movb	%al, 96(%rdx)
	movups	%xmm0, 80(%rdx)
	call	_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_@PLT
	movq	(%rsp), %rdx
	movb	%al, 104(%rdx)
	cmpw	%r15w, %r13w
	jb	.L515
.L516:
	movzwl	%r15w, %eax
	leaq	0(,%rax,8), %rdx
	subq	%rax, %rdx
	salq	$4, %rdx
	addq	%rbp, %rdx
	cmpb	$0, 72(%rdx)
	je	.L533
	movq	8(%rsp), %rdi
	xorl	%ecx, %ecx
	movl	$10, %esi
	addl	$1, %r15d
	movw	%cx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	cmpw	%r15w, %r13w
	jnb	.L516
	.p2align 4,,10
	.p2align 3
.L515:
	leaq	220(%r12), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10BinarySpecEEERNS_5RangeEv@PLT
	cmpw	%r13w, 2(%rax)
	cmovnb	2(%rax), %r13w
	cmpw	%r14w, (%rax)
	cmovbe	(%rax), %r14w
	movw	%r13w, 2(%rax)
	movw	%r14w, (%rax)
	movzwl	20(%rsp), %eax
	jmp	.L519
	.p2align 4,,10
	.p2align 3
.L521:
	movq	%rax, (%rsp)
	jmp	.L512
	.p2align 4,,10
	.p2align 3
.L517:
	movzbl	16(%rbx), %eax
	movdqu	(%rbx), %xmm1
	movb	$1, 72(%rbx)
	leaq	80(%rbx), %rdi
	movzbl	26(%rbx), %esi
	movb	%al, 96(%rbx)
	movups	%xmm1, 80(%rbx)
	call	_ZN8opendnp315DatabaseBuffers17CheckForPromotionINS_10BinarySpecEEENT_18static_variation_tERKNS3_6meas_tES4_@PLT
	movb	%al, 104(%rbx)
.L518:
	addl	$1, %r15d
	cmpw	%r15w, %r13w
	jb	.L515
.L512:
	movzwl	%r15w, %eax
	leaq	0(,%rax,8), %rbx
	subq	%rax, %rbx
	salq	$4, %rbx
	addq	%rbp, %rbx
	cmpb	$0, 72(%rbx)
	je	.L517
	movq	(%rsp), %rdi
	xorl	%edx, %edx
	movl	$10, %esi
	movw	%dx, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	orw	%ax, 20(%rsp)
	jmp	.L518
	.p2align 4,,10
	.p2align 3
.L509:
	xorl	%eax, %eax
	leaq	22(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 22(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	22(%rsp), %eax
	jmp	.L519
	.p2align 4,,10
	.p2align 3
.L532:
	xorl	%edi, %edi
	movw	%di, 20(%rsp)
	jmp	.L511
.L531:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3283:
	.size	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0, .-_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE
	.type	_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE, @function
_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE:
.LFB2399:
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
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpw	$15361, %si
	je	.L662
	cmpw	$5386, %si
	ja	.L545
	cmpw	$5375, %si
	ja	.L546
	cmpw	$2562, %si
	je	.L547
	jbe	.L663
	subw	$5120, %si
	cmpw	$6, %si
	ja	.L554
	leaq	.L578(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L578:
	.long	.L582-.L578
	.long	.L581-.L578
	.long	.L580-.L578
	.long	.L554-.L578
	.long	.L554-.L578
	.long	.L579-.L578
	.long	.L577-.L578
	.text
	.p2align 4,,10
	.p2align 3
.L663:
	cmpw	$768, %si
	je	.L549
	jbe	.L664
	cmpw	$770, %si
	je	.L583
	cmpw	$2560, %si
	jne	.L554
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
.L653:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L545:
	.cfi_restore_state
	cmpw	$7686, %si
	ja	.L586
	cmpw	$7679, %si
	jbe	.L554
	subw	$7681, %si
	cmpw	$5, %si
	ja	.L561
	leaq	.L563(%rip), %rdx
	movzwl	%si, %esi
	leaq	24(%rbp), %rdi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L563:
	.long	.L568-.L563
	.long	.L567-.L563
	.long	.L566-.L563
	.long	.L565-.L563
	.long	.L564-.L563
	.long	.L562-.L563
	.text
	.p2align 4,,10
	.p2align 3
.L586:
	cmpw	$10244, %si
	ja	.L588
	cmpw	$10239, %si
	jbe	.L554
	subw	$10241, %si
	cmpw	$3, %si
	ja	.L555
	leaq	.L557(%rip), %rdx
	movzwl	%si, %esi
	leaq	24(%rbp), %rdi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L557:
	.long	.L560-.L557
	.long	.L559-.L557
	.long	.L558-.L557
	.long	.L556-.L557
	.text
.L664:
	cmpw	$257, %si
	je	.L551
	cmpw	$258, %si
	jne	.L665
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$1, %r9d
	jmp	.L650
	.p2align 4,,10
	.p2align 3
.L546:
	subw	$5376, %si
	cmpw	$10, %si
	ja	.L554
	leaq	.L570(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L570:
	.long	.L576-.L570
	.long	.L575-.L570
	.long	.L574-.L570
	.long	.L554-.L570
	.long	.L554-.L570
	.long	.L573-.L570
	.long	.L572-.L570
	.long	.L554-.L570
	.long	.L554-.L570
	.long	.L571-.L570
	.long	.L569-.L570
	.text
	.p2align 4,,10
	.p2align 3
.L588:
	cmpw	$12804, %si
	jne	.L554
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	xorl	%r9d, %r9d
	popq	%rbp
	.cfi_def_cfa_offset 16
	xorl	%r8d, %r8d
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L665:
	.cfi_restore_state
	cmpw	$256, %si
	jne	.L554
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
	jmp	.L649
	.p2align 4,,10
	.p2align 3
.L662:
	movzwl	216(%rdi), %eax
	testb	$1, %al
	jne	.L666
.L536:
	testb	$2, %al
	jne	.L667
.L537:
	testb	$4, %al
	jne	.L668
.L538:
	testb	$8, %al
	jne	.L669
	testb	$16, %al
	jne	.L670
.L540:
	testb	$32, %al
	jne	.L671
.L541:
	testb	$64, %al
	jne	.L672
.L542:
	testb	$-128, %al
	jne	.L673
.L543:
	xorl	%eax, %eax
.L544:
	movq	8(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L651
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L673:
	.cfi_restore_state
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	jmp	.L543
	.p2align 4,,10
	.p2align 3
.L669:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	testb	$16, %al
	je	.L540
.L670:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	testb	$32, %al
	je	.L541
.L671:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	testb	$64, %al
	je	.L542
.L672:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	jmp	.L542
	.p2align 4,,10
	.p2align 3
.L668:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	jmp	.L538
	.p2align 4,,10
	.p2align 3
.L667:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	jmp	.L537
	.p2align 4,,10
	.p2align 3
.L666:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movl	%ebx, %edx
	movl	%eax, %esi
	movq	%r12, %rcx
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movzwl	216(%rbp), %eax
	jmp	.L536
	.p2align 4,,10
	.p2align 3
.L554:
	xorl	%eax, %eax
	leaq	6(%rsp), %rdi
	movl	$8, %esi
	movw	%ax, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	jmp	.L544
	.p2align 4,,10
	.p2align 3
.L583:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
.L652:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L551:
	.cfi_restore_state
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
.L650:
	xorl	%r8d, %r8d
.L649:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L559:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$1, %r9d
.L654:
	xorl	%r8d, %r8d
.L655:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L560:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	jmp	.L654
	.p2align 4,,10
	.p2align 3
.L558:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$2, %r9d
	jmp	.L654
	.p2align 4,,10
	.p2align 3
.L556:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$3, %r9d
	jmp	.L654
	.p2align 4,,10
	.p2align 3
.L577:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$3, %r9d
.L659:
	xorl	%r8d, %r8d
.L656:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L579:
	.cfi_restore_state
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$2, %r9d
	jmp	.L659
	.p2align 4,,10
	.p2align 3
.L580:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$1, %r9d
	jmp	.L659
	.p2align 4,,10
	.p2align 3
.L581:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	jmp	.L659
	.p2align 4,,10
	.p2align 3
.L582:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
	jmp	.L656
	.p2align 4,,10
	.p2align 3
.L565:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$3, %r9d
	.p2align 4,,10
	.p2align 3
.L657:
	xorl	%r8d, %r8d
.L658:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L566:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$2, %r9d
	jmp	.L657
	.p2align 4,,10
	.p2align 3
.L567:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$1, %r9d
	jmp	.L657
	.p2align 4,,10
	.p2align 3
.L568:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	jmp	.L657
	.p2align 4,,10
	.p2align 3
.L564:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$4, %r9d
	jmp	.L657
	.p2align 4,,10
	.p2align 3
.L562:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$5, %r9d
	jmp	.L657
	.p2align 4,,10
	.p2align 3
.L576:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
.L661:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movq	%r12, %rcx
	movl	%ebx, %edx
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	.p2align 4,,10
	.p2align 3
.L569:
	.cfi_restore_state
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$5, %r9d
	.p2align 4,,10
	.p2align 3
.L660:
	xorl	%r8d, %r8d
	jmp	.L661
	.p2align 4,,10
	.p2align 3
.L571:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$4, %r9d
	jmp	.L660
	.p2align 4,,10
	.p2align 3
.L572:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$3, %r9d
	jmp	.L660
	.p2align 4,,10
	.p2align 3
.L573:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$2, %r9d
	jmp	.L660
	.p2align 4,,10
	.p2align 3
.L574:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	movl	$1, %r9d
	jmp	.L660
	.p2align 4,,10
	.p2align 3
.L575:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	jmp	.L660
	.p2align 4,,10
	.p2align 3
.L547:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	jmp	.L653
	.p2align 4,,10
	.p2align 3
.L549:
	leaq	24(%rdi), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
	jmp	.L652
	.p2align 4,,10
	.p2align 3
.L555:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
	jmp	.L655
	.p2align 4,,10
	.p2align 3
.L561:
	leaq	24(%rbp), %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %esi
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L651
	xorl	%r9d, %r9d
	movl	$1, %r8d
	jmp	.L658
.L651:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2399:
	.size	_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE, .-_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE
	.section	.text.unlikely,"ax",@progbits
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4
	.globl	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.type	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE, @function
_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE:
.LFB3282:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpb	$6, %sil
	ja	.L685
	movl	%edx, %ebx
	movzbl	%sil, %esi
	leaq	.L677(%rip), %rdx
	movslq	(%rdx,%rsi,4), %rax
	leaq	-16(%rdi), %rbp
	addq	$8, %rdi
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L677:
	.long	.L683-.L677
	.long	.L682-.L677
	.long	.L681-.L677
	.long	.L680-.L677
	.long	.L679-.L677
	.long	.L678-.L677
	.long	.L676-.L677
	.text
	.p2align 4,,10
	.p2align 3
.L678:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$5, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	.p2align 4,,10
	.p2align 3
.L675:
	sall	$16, %eax
	orl	%edx, %eax
	movq	8(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L687
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
.L676:
	.cfi_restore_state
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$6, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
	.p2align 4,,10
	.p2align 3
.L683:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
	.p2align 4,,10
	.p2align 3
.L682:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$1, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
	.p2align 4,,10
	.p2align 3
.L681:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$2, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
	.p2align 4,,10
	.p2align 3
.L680:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$3, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
	.p2align 4,,10
	.p2align 3
.L679:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%ebx, %edx
	leaq	4(%rsp), %rcx
	movq	%rbp, %rdi
	movl	$4, %esi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	%ax, %edx
	shrl	$16, %eax
	jmp	.L675
.L687:
	call	__stack_chk_fail@PLT
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE.cold, @function
_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE.cold:
.LFSB3282:
.L685:
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	xorl	%eax, %eax
	movl	$1, %edx
	jmp	.L675
	.cfi_endproc
.LFE3282:
	.text
	.size	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE, .-_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.section	.text.unlikely
	.size	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE.cold, .-_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE.cold
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3087:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L690
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L691
	.p2align 4,,10
	.p2align 3
.L694:
	testw	%bp, %bp
	je	.L692
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L692
.L691:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	8(%r13), %rax
	cmpw	%r14w, 24(%rax)
	je	.L699
	jnb	.L694
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L692
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L691
	.p2align 4,,10
	.p2align 3
.L692:
	movl	%ebx, %eax
	sall	$16, %eax
.L690:
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
.L699:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3087:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3030:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L701
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L707
.L701:
	movl	$1, %eax
.L704:
	addq	$8, %rsp
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
.L707:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10BinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	leaq	0(,%rcx,8), %rdx
	shrl	$16, %eax
	subq	%rcx, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jb	.L708
.L703:
	movzwl	%r14w, %eax
	leaq	0(,%rax,8), %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jbe	.L705
	testw	%r14w, %r14w
	je	.L701
	leal	-1(%r14), %r15d
.L705:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L701
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L704
	.p2align 4,,10
	.p2align 3
.L708:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L701
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L703
	.cfi_endproc
.LFE3030:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3090:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L711
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L712
	.p2align 4,,10
	.p2align 3
.L715:
	testw	%bp, %bp
	je	.L713
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L713
.L712:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	8(%r13), %rax
	cmpw	%r14w, 24(%rax)
	je	.L720
	jnb	.L715
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L713
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L712
	.p2align 4,,10
	.p2align 3
.L713:
	movl	%ebx, %eax
	sall	$16, %eax
.L711:
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
.L720:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3090:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3031:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L722
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L728
.L722:
	movl	$1, %eax
.L725:
	addq	$8, %rsp
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
.L728:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19DoubleBitBinarySpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	leaq	0(,%rcx,8), %rdx
	shrl	$16, %eax
	subq	%rcx, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jb	.L729
.L724:
	movzwl	%r14w, %eax
	leaq	0(,%rax,8), %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jbe	.L726
	testw	%r14w, %r14w
	je	.L722
	leal	-1(%r14), %r15d
.L726:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L722
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L725
	.p2align 4,,10
	.p2align 3
.L729:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L722
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L724
	.cfi_endproc
.LFE3031:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3093:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L732
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L733
	.p2align 4,,10
	.p2align 3
.L736:
	testw	%bp, %bp
	je	.L734
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L734
.L733:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	8(%r13), %rax
	cmpw	%r14w, 24(%rax)
	je	.L741
	jnb	.L736
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L734
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L733
	.p2align 4,,10
	.p2align 3
.L734:
	movl	%ebx, %eax
	sall	$16, %eax
.L732:
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
.L741:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3093:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3032:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L743
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L749
.L743:
	movl	$1, %eax
.L746:
	addq	$8, %rsp
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
.L749:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22BinaryOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	leaq	0(,%rcx,8), %rdx
	shrl	$16, %eax
	subq	%rcx, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jb	.L750
.L745:
	movzwl	%r14w, %eax
	leaq	0(,%rax,8), %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	salq	$4, %rdx
	cmpw	%ax, 24(%rsi,%rdx)
	jbe	.L747
	testw	%r14w, %r14w
	je	.L743
	leal	-1(%r14), %r15d
.L747:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L743
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L746
	.p2align 4,,10
	.p2align 3
.L750:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L743
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L745
	.cfi_endproc
.LFE3032:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3096:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L753
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L754
	.p2align 4,,10
	.p2align 3
.L757:
	testw	%bp, %bp
	je	.L755
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L755
.L754:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %rax
	cmpw	%r14w, 24(%rax)
	je	.L762
	jnb	.L757
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L755
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L754
	.p2align 4,,10
	.p2align 3
.L755:
	movl	%ebx, %eax
	sall	$16, %eax
.L753:
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
.L762:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3096:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3033:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L764
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L770
.L764:
	movl	$1, %eax
.L767:
	addq	$8, %rsp
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
.L770:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_11CounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	movq	%rcx, %rdx
	shrl	$16, %eax
	salq	$4, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	subq	%rcx, %rdx
	cmpw	%ax, 24(%rsi,%rdx,8)
	jb	.L771
.L766:
	movzwl	%r14w, %eax
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	cmpw	%ax, 24(%rsi,%rdx,8)
	jbe	.L768
	testw	%r14w, %r14w
	je	.L764
	leal	-1(%r14), %r15d
.L768:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L764
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L767
	.p2align 4,,10
	.p2align 3
.L771:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L764
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L766
	.cfi_endproc
.LFE3033:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3099:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L774
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L775
	.p2align 4,,10
	.p2align 3
.L778:
	testw	%bp, %bp
	je	.L776
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L776
.L775:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %rax
	cmpw	%r14w, 24(%rax)
	je	.L783
	jnb	.L778
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L776
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L775
	.p2align 4,,10
	.p2align 3
.L776:
	movl	%ebx, %eax
	sall	$16, %eax
.L774:
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
.L783:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3099:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3034:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L785
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L791
.L785:
	movl	$1, %eax
.L788:
	addq	$8, %rsp
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
.L791:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_17FrozenCounterSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	movq	%rcx, %rdx
	shrl	$16, %eax
	salq	$4, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	subq	%rcx, %rdx
	cmpw	%ax, 24(%rsi,%rdx,8)
	jb	.L792
.L787:
	movzwl	%r14w, %eax
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	cmpw	%ax, 24(%rsi,%rdx,8)
	jbe	.L789
	testw	%r14w, %r14w
	je	.L785
	leal	-1(%r14), %r15d
.L789:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L785
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L788
	.p2align 4,,10
	.p2align 3
.L792:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L785
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L787
	.cfi_endproc
.LFE3034:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE
	.type	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE, @function
_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE:
.LFB2947:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	24(%rdi), %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	%edx, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpb	$1, 218(%rdi)
	je	.L824
	movq	%r15, %rdi
	movl	%ecx, %r13d
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	2(%rbx), %ecx
	xorl	%esi, %esi
	movq	%rdx, %r12
	movzwl	(%rbx), %edx
	xorl	%ebx, %ebx
	cmpw	%dx, %cx
	jnb	.L825
.L801:
	xorl	%eax, %eax
	movb	%sil, %al
	movb	%bl, %ah
.L800:
	movq	56(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L826
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
.L825:
	.cfi_restore_state
	movzwl	%ax, %edi
	movl	%edx, 12(%rsp)
	movl	%ecx, (%rsp)
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	12(%rsp), %edx
	movl	%eax, %esi
	shrl	$16, %esi
	movl	%ecx, %r15d
	movl	%edx, %ebx
	cmpw	%cx, %si
	cmovbe	%esi, %r15d
	cmpw	%dx, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r15w
	jb	.L802
	xorl	%edi, %edi
	movw	%di, 30(%rsp)
	cmpw	%ax, %dx
	jb	.L803
	cmpw	%si, %cx
	jbe	.L804
.L803:
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L804:
	testb	%r14b, %r14b
	jne	.L815
	movl	%ebx, %r14d
	leaq	32(%rsp), %rcx
	jmp	.L809
	.p2align 4,,10
	.p2align 3
.L827:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm0
	movb	$1, 80(%rax)
	movb	%r13b, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm0, 88(%rax)
.L807:
	addl	$1, %r14d
	cmpw	%r14w, %r15w
	jb	.L808
.L809:
	movzwl	%r14w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	(%r12,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L827
	xorl	%esi, %esi
	movq	%rcx, %rdi
	movq	%rcx, (%rsp)
	movw	%si, 32(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	32(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 30(%rsp)
	jmp	.L807
	.p2align 4,,10
	.p2align 3
.L824:
	movq	%r15, %rdi
	movl	%ecx, %r12d
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	32(%rsp), %rdi
	movq	%rbx, %rsi
	movl	%eax, 32(%rsp)
	movq	%rdx, 40(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r13d
	shrl	$16, %eax
	cmpw	%ax, %r13w
	ja	.L795
	movzwl	(%rbx), %ecx
	movzwl	2(%rbx), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L796
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L796:
	addl	$1, %eax
	movzwl	%r13w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 30(%rsp)
	cmpl	%edx, %eax
	jne	.L797
.L798:
	movq	%r15, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%r12d, %r9d
	movzbl	%r14b, %r8d
	movl	%r13d, %esi
	movq	%rdx, %rcx
	movq	%rbp, %rdi
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	orw	30(%rsp), %ax
	jmp	.L800
	.p2align 4,,10
	.p2align 3
.L797:
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	jmp	.L798
	.p2align 4,,10
	.p2align 3
.L802:
	xorl	%eax, %eax
	movl	$10, %esi
	leaq	32(%rsp), %rdi
	movw	%ax, 32(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzbl	32(%rsp), %esi
	movzbl	33(%rsp), %ebx
	jmp	.L801
	.p2align 4,,10
	.p2align 3
.L808:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%bx, (%rax)
	cmovbe	(%rax), %bx
	movw	%r15w, 2(%rax)
	movw	%bx, (%rax)
	movzbl	30(%rsp), %esi
	movzbl	31(%rsp), %ebx
	jmp	.L801
	.p2align 4,,10
	.p2align 3
.L795:
	xorl	%r8d, %r8d
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	movw	%r8w, 30(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	30(%rsp), %eax
	jmp	.L800
	.p2align 4,,10
	.p2align 3
.L815:
	movl	%ebx, %r13d
	leaq	32(%rsp), %r14
	jmp	.L805
	.p2align 4,,10
	.p2align 3
.L810:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movl	%edx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L811:
	addl	$1, %r13d
	cmpw	%r13w, %r15w
	jb	.L808
.L805:
	movzwl	%r13w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	(%r12,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L810
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 32(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	32(%rsp), %eax
	orw	%ax, 30(%rsp)
	jmp	.L811
.L826:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2947:
	.size	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE, .-_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3102:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L830
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L831
	.p2align 4,,10
	.p2align 3
.L834:
	testw	%bp, %bp
	je	.L832
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L832
.L831:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %rax
	cmpw	%r14w, 24(%rax)
	je	.L839
	jnb	.L834
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L832
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L831
	.p2align 4,,10
	.p2align 3
.L832:
	movl	%ebx, %eax
	sall	$16, %eax
.L830:
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
.L839:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3102:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3035:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L841
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L847
.L841:
	movl	$1, %eax
.L844:
	addq	$8, %rsp
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
.L847:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_10AnalogSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	movq	%rcx, %rdx
	shrl	$16, %eax
	salq	$4, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	subq	%rcx, %rdx
	cmpw	%ax, 24(%rsi,%rdx,8)
	jb	.L848
.L843:
	movzwl	%r14w, %eax
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	cmpw	%ax, 24(%rsi,%rdx,8)
	jbe	.L845
	testw	%r14w, %r14w
	je	.L841
	leal	-1(%r14), %r15d
.L845:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L841
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L844
	.p2align 4,,10
	.p2align 3
.L848:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L841
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L843
	.cfi_endproc
.LFE3035:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE,"axG",@progbits,_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE
	.type	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE, @function
_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE:
.LFB2948:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	24(%rdi), %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movl	%edx, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	cmpb	$1, 218(%rdi)
	je	.L880
	movq	%r15, %rdi
	movl	%ecx, %r13d
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	2(%rbx), %ecx
	xorl	%esi, %esi
	movq	%rdx, %r12
	movzwl	(%rbx), %edx
	xorl	%ebx, %ebx
	cmpw	%dx, %cx
	jnb	.L881
.L857:
	xorl	%eax, %eax
	movb	%sil, %al
	movb	%bl, %ah
.L856:
	movq	56(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L882
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
.L881:
	.cfi_restore_state
	movzwl	%ax, %edi
	movl	%edx, 12(%rsp)
	movl	%ecx, (%rsp)
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	(%rsp), %ecx
	movl	12(%rsp), %edx
	movl	%eax, %esi
	shrl	$16, %esi
	movl	%ecx, %r15d
	movl	%edx, %ebx
	cmpw	%cx, %si
	cmovbe	%esi, %r15d
	cmpw	%dx, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r15w
	jb	.L858
	xorl	%edi, %edi
	movw	%di, 30(%rsp)
	cmpw	%ax, %dx
	jb	.L859
	cmpw	%si, %cx
	jbe	.L860
.L859:
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L860:
	testb	%r14b, %r14b
	jne	.L871
	movl	%ebx, %r14d
	leaq	32(%rsp), %rcx
	jmp	.L865
	.p2align 4,,10
	.p2align 3
.L883:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm0
	movb	$1, 80(%rax)
	movb	%r13b, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm0, 88(%rax)
.L863:
	addl	$1, %r14d
	cmpw	%r14w, %r15w
	jb	.L864
.L865:
	movzwl	%r14w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	(%r12,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L883
	xorl	%esi, %esi
	movq	%rcx, %rdi
	movq	%rcx, (%rsp)
	movw	%si, 32(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	32(%rsp), %eax
	movq	(%rsp), %rcx
	orw	%ax, 30(%rsp)
	jmp	.L863
	.p2align 4,,10
	.p2align 3
.L880:
	movq	%r15, %rdi
	movl	%ecx, %r12d
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	32(%rsp), %rdi
	movq	%rbx, %rsi
	movl	%eax, 32(%rsp)
	movq	%rdx, 40(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r13d
	shrl	$16, %eax
	cmpw	%ax, %r13w
	ja	.L851
	movzwl	(%rbx), %ecx
	movzwl	2(%rbx), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L852
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L852:
	addl	$1, %eax
	movzwl	%r13w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 30(%rsp)
	cmpl	%edx, %eax
	jne	.L853
.L854:
	movq	%r15, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	%r12d, %r9d
	movzbl	%r14b, %r8d
	movl	%r13d, %esi
	movq	%rdx, %rcx
	movq	%rbp, %rdi
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	orw	30(%rsp), %ax
	jmp	.L856
	.p2align 4,,10
	.p2align 3
.L853:
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	jmp	.L854
	.p2align 4,,10
	.p2align 3
.L858:
	xorl	%eax, %eax
	movl	$10, %esi
	leaq	32(%rsp), %rdi
	movw	%ax, 32(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzbl	32(%rsp), %esi
	movzbl	33(%rsp), %ebx
	jmp	.L857
	.p2align 4,,10
	.p2align 3
.L864:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	cmpw	%r15w, 2(%rax)
	cmovnb	2(%rax), %r15w
	cmpw	%bx, (%rax)
	cmovbe	(%rax), %bx
	movw	%r15w, 2(%rax)
	movw	%bx, (%rax)
	movzbl	30(%rsp), %esi
	movzbl	31(%rsp), %ebx
	jmp	.L857
	.p2align 4,,10
	.p2align 3
.L851:
	xorl	%r8d, %r8d
	leaq	30(%rsp), %rdi
	movl	$10, %esi
	movw	%r8w, 30(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	30(%rsp), %eax
	jmp	.L856
	.p2align 4,,10
	.p2align 3
.L871:
	movl	%ebx, %r13d
	leaq	32(%rsp), %r14
	jmp	.L861
	.p2align 4,,10
	.p2align 3
.L866:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movq	%rdx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm1, 88(%rax)
	movb	%dl, 112(%rax)
.L867:
	addl	$1, %r13d
	cmpw	%r13w, %r15w
	jb	.L864
.L861:
	movzwl	%r13w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	(%r12,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L866
	xorl	%edx, %edx
	movl	$10, %esi
	movq	%r14, %rdi
	movw	%dx, 32(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	32(%rsp), %eax
	orw	%ax, 30(%rsp)
	jmp	.L867
.L882:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2948:
	.size	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE, .-_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3105:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L886
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L887
	.p2align 4,,10
	.p2align 3
.L890:
	testw	%bp, %bp
	je	.L888
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L888
.L887:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	movq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %rax
	cmpw	%r14w, 24(%rax)
	je	.L895
	jnb	.L890
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L888
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L887
	.p2align 4,,10
	.p2align 3
.L888:
	movl	%ebx, %eax
	sall	$16, %eax
.L886:
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
.L895:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3105:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3036:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L897
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L903
.L897:
	movl	$1, %eax
.L900:
	addq	$8, %rsp
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
.L903:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_22AnalogOutputStatusSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	movq	%rcx, %rdx
	shrl	$16, %eax
	salq	$4, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	subq	%rcx, %rdx
	cmpw	%ax, 24(%rsi,%rdx,8)
	jb	.L904
.L899:
	movzwl	%r14w, %eax
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	cmpw	%ax, 24(%rsi,%rdx,8)
	jbe	.L901
	testw	%r14w, %r14w
	je	.L897
	leal	-1(%r14), %r15d
.L901:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L897
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L900
	.p2align 4,,10
	.p2align 3
.L904:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L897
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L899
	.cfi_endproc
.LFE3036:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.section	.text._ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,"axG",@progbits,_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.type	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, @function
_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt:
.LFB3108:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	xorl	%eax, %eax
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movzwl	(%rdi), %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	testw	%bp, %bp
	je	.L907
	movq	%rdi, %r13
	movl	%esi, %r14d
	subl	$1, %ebp
	xorl	%r12d, %r12d
	jmp	.L908
	.p2align 4,,10
	.p2align 3
.L911:
	testw	%bp, %bp
	je	.L909
	leal	-1(%rbx), %ebp
	cmpw	%bp, %r12w
	ja	.L909
.L908:
	movzwl	%bp, %ebx
	movzwl	%r12w, %edx
	movl	%ebx, %eax
	subl	%edx, %eax
	movl	%eax, %ebx
	shrl	$31, %ebx
	addl	%eax, %ebx
	sarl	%ebx
	addl	%r12d, %ebx
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	movq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %rax
	cmpw	%r14w, 16(%rax)
	je	.L916
	jnb	.L911
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r12w, %ax
	jbe	.L909
	leal	1(%rbx), %r12d
	cmpw	%bp, %r12w
	jbe	.L908
	.p2align 4,,10
	.p2align 3
.L909:
	movl	%ebx, %eax
	sall	$16, %eax
.L907:
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
.L916:
	.cfi_restore_state
	sall	$16, %ebx
	movl	%ebx, %eax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	orl	$1, %eax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3108:
	.size	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt, .-_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt
	.section	.text._ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,"axG",@progbits,_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.type	_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, @function
_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_:
.LFB3037:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzwl	(%rsi), %esi
	cmpw	%si, 2(%rbx)
	jb	.L918
	cmpw	$0, (%rdi)
	movq	%rdi, %rbp
	jne	.L924
.L918:
	movl	$1, %eax
.L921:
	addq	$8, %rsp
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
.L924:
	.cfi_restore_state
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	2(%rbx), %esi
	movq	%rbp, %rdi
	shrl	$16, %eax
	movl	%eax, %r13d
	movl	%eax, %r12d
	call	_ZN8opendnp311IndexSearch19FindClosestRawIndexINS_19TimeAndIntervalSpecEEENS0_6ResultERKN7openpal9ArrayViewINS_4CellIT_EEtEEt@PLT
	movzwl	%r13w, %ecx
	movq	8(%rbp), %rsi
	leaq	0(,%rcx,8), %rdx
	shrl	$16, %eax
	subq	%rcx, %rdx
	movl	%eax, %r14d
	movl	%eax, %r15d
	movzwl	(%rbx), %eax
	cmpw	%ax, 16(%rsi,%rdx,8)
	jb	.L925
.L920:
	movzwl	%r14w, %eax
	leaq	0(,%rax,8), %rdx
	subq	%rax, %rdx
	movzwl	2(%rbx), %eax
	cmpw	%ax, 16(%rsi,%rdx,8)
	jbe	.L922
	testw	%r14w, %r14w
	je	.L918
	leal	-1(%r14), %r15d
.L922:
	cmpw	%r15w, %r12w
	movl	%r15d, %eax
	cmovnb	%r12d, %eax
	cmpw	%ax, 0(%rbp)
	jbe	.L918
	sall	$16, %r15d
	movzwl	%r12w, %eax
	orl	%r15d, %eax
	jmp	.L921
	.p2align 4,,10
	.p2align 3
.L925:
	call	_ZN7openpal8MaxValueItEET_v@PLT
	cmpw	%r13w, %ax
	jbe	.L918
	movq	8(%rbp), %rsi
	leal	1(%r13), %r12d
	jmp	.L920
	.cfi_endproc
.LFE3037:
	.size	_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_, .-_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE
	.type	_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE, @function
_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE:
.LFB2400:
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpw	$5386, %si
	ja	.L927
	cmpw	$5375, %si
	ja	.L928
	cmpw	$2562, %si
	je	.L929
	jbe	.L1430
	subw	$5120, %si
	cmpw	$6, %si
	ja	.L936
	leaq	.L960(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L960:
	.long	.L964-.L960
	.long	.L963-.L960
	.long	.L962-.L960
	.long	.L936-.L960
	.long	.L936-.L960
	.long	.L961-.L960
	.long	.L959-.L960
	.text
	.p2align 4,,10
	.p2align 3
.L927:
	cmpw	$7686, %si
	ja	.L968
	cmpw	$7679, %si
	jbe	.L936
	subw	$7681, %si
	cmpw	$5, %si
	ja	.L943
	leaq	.L945(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L945:
	.long	.L950-.L945
	.long	.L949-.L945
	.long	.L948-.L945
	.long	.L947-.L945
	.long	.L946-.L945
	.long	.L944-.L945
	.text
	.p2align 4,,10
	.p2align 3
.L1430:
	cmpw	$768, %si
	je	.L931
	jbe	.L1431
	cmpw	$770, %si
	je	.L965
	cmpw	$2560, %si
	jne	.L936
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1432
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1032
	cmpw	%ax, %r15w
	jnb	.L1033
.L1032:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1033:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1036
	.p2align 4,,10
	.p2align 3
.L1034:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm2
	movb	$1, 72(%rax)
	movb	%dl, 96(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm2, 80(%rax)
	movb	%dl, 104(%rax)
.L1035:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1433
.L1036:
	movzwl	%r12w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r13, %rax
	cmpb	$0, 72(%rax)
	je	.L1034
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1035
	.p2align 4,,10
	.p2align 3
.L928:
	subw	$5376, %si
	cmpw	$10, %si
	ja	.L936
	leaq	.L952(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L952:
	.long	.L958-.L952
	.long	.L957-.L952
	.long	.L956-.L952
	.long	.L936-.L952
	.long	.L936-.L952
	.long	.L955-.L952
	.long	.L954-.L952
	.long	.L936-.L952
	.long	.L936-.L952
	.long	.L953-.L952
	.long	.L951-.L952
	.text
	.p2align 4,,10
	.p2align 3
.L968:
	cmpw	$10244, %si
	ja	.L970
	cmpw	$10239, %si
	jbe	.L936
	subw	$10241, %si
	cmpw	$3, %si
	ja	.L937
	leaq	.L939(%rip), %rdx
	movzwl	%si, %esi
	leaq	24(%rbp), %r13
	movslq	(%rdx,%rsi,4), %rax
	movq	%r13, %rdi
	addq	%rdx, %rax
	cmpb	$1, 218(%rbp)
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L939:
	.long	.L942-.L939
	.long	.L941-.L939
	.long	.L940-.L939
	.long	.L938-.L939
	.text
.L1431:
	cmpw	$257, %si
	je	.L933
	cmpw	$258, %si
	jne	.L1434
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1435
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$1, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1426:
	xorl	%r8d, %r8d
	jmp	.L1424
	.p2align 4,,10
	.p2align 3
.L970:
	cmpw	$12804, %si
	jne	.L936
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1436
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	(%r12), %esi
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	movq	%rdx, %rcx
	movq	%rbp, %rdi
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %ecx
	movzbl	%ah, %edx
	jmp	.L1250
	.p2align 4,,10
	.p2align 3
.L1434:
	cmpw	$256, %si
	jne	.L936
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1437
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1424:
	movl	(%r12), %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %ecx
	movzbl	%ah, %edx
.L1250:
	xorl	%eax, %eax
	movb	%cl, %al
	movb	%dl, %ah
	jmp	.L980
	.p2align 4,,10
	.p2align 3
.L941:
	je	.L1438
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	jbe	.L1439
	.p2align 4,,10
	.p2align 3
.L1236:
	xorl	%eax, %eax
	movb	%dl, %al
	movb	%cl, %ah
.L980:
	movq	40(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1412
	addq	$56, %rsp
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
.L942:
	.cfi_restore_state
	je	.L1440
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %r12w
	jb	.L1236
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r11d, %r11d
	movw	%r11w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1197
	cmpw	%dx, %r12w
	jbe	.L1198
.L1197:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1198:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1201
	.p2align 4,,10
	.p2align 3
.L1199:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm5
	movb	$1, 80(%rax)
	movb	$0, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm5, 88(%rax)
.L1200:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1415
.L1201:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1199
	xorl	%r10d, %r10d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r10w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1200
	.p2align 4,,10
	.p2align 3
.L940:
	je	.L1441
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %r12w
	jb	.L1236
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1225
	cmpw	%dx, %r12w
	jbe	.L1226
.L1225:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1226:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1229
	.p2align 4,,10
	.p2align 3
.L1227:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm7
	movb	$1, 80(%rax)
	movb	$2, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm7, 88(%rax)
.L1228:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1415
.L1229:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1227
	xorl	%r11d, %r11d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r11w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1228
	.p2align 4,,10
	.p2align 3
.L938:
	je	.L1442
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %r12w
	jb	.L1236
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1239
	cmpw	%dx, %r12w
	jbe	.L1240
.L1239:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1240:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1243
	.p2align 4,,10
	.p2align 3
.L1241:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm0
	movb	$1, 80(%rax)
	movb	$3, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm0, 88(%rax)
.L1242:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1415
.L1243:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1241
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1242
	.p2align 4,,10
	.p2align 3
.L936:
	xorl	%eax, %eax
	leaq	16(%rsp), %rdi
	movl	$8, %esi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	jmp	.L980
	.p2align 4,,10
	.p2align 3
.L961:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1443
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r11d, %r11d
	movw	%r11w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1102
	cmpw	%dx, %r12w
	jbe	.L1103
.L1102:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1103:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1106
	.p2align 4,,10
	.p2align 3
.L1104:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm7
	movb	$1, 80(%rax)
	movb	$2, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm7, 88(%rax)
.L1105:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1428
.L1106:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1104
	xorl	%r10d, %r10d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r10w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1105
	.p2align 4,,10
	.p2align 3
.L964:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1444
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r11d, %r11d
	movw	%r11w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1060
	cmpw	%dx, %r12w
	jbe	.L1061
.L1060:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1061:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1064
	.p2align 4,,10
	.p2align 3
.L1062:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm4
	movb	$1, 80(%rax)
	movl	%edx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm4, 88(%rax)
	movb	%dl, 112(%rax)
.L1063:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1428
.L1064:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1062
	xorl	%r10d, %r10d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r10w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1063
	.p2align 4,,10
	.p2align 3
.L962:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1445
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1088
	cmpw	%ax, %r15w
	jnb	.L1089
.L1088:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1089:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1092
	.p2align 4,,10
	.p2align 3
.L1090:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm6
	movb	$1, 80(%rax)
	movb	$1, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm6, 88(%rax)
.L1091:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1428
.L1092:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1090
	xorl	%eax, %eax
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1091
	.p2align 4,,10
	.p2align 3
.L963:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1446
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1074
	cmpw	%dx, %r12w
	jbe	.L1075
.L1074:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1075:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1078
	.p2align 4,,10
	.p2align 3
.L1076:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm5
	movb	$1, 80(%rax)
	movb	$0, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm5, 88(%rax)
.L1077:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1428
.L1078:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1076
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1077
	.p2align 4,,10
	.p2align 3
.L959:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1447
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1116
	cmpw	%dx, %r12w
	jbe	.L1117
.L1116:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1117:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1120
	.p2align 4,,10
	.p2align 3
.L1118:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm0
	movb	$1, 80(%rax)
	movb	$3, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm0, 88(%rax)
.L1119:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1428
.L1120:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1118
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1119
	.p2align 4,,10
	.p2align 3
.L947:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1448
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %r12w
	jb	.L1236
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1167
	cmpw	%dx, %r12w
	jbe	.L1168
.L1167:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1168:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1171
	.p2align 4,,10
	.p2align 3
.L1169:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm3
	movb	$1, 80(%rax)
	movb	$3, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm3, 88(%rax)
.L1170:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1449
.L1171:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1169
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1170
	.p2align 4,,10
	.p2align 3
.L944:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$5, %ecx
.L1413:
	xorl	%edx, %edx
.L1414:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rsi
	movq	%rbp, %rdi
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
	jmp	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_10AnalogSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE@PLT
	.p2align 4,,10
	.p2align 3
.L948:
	.cfi_restore_state
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$2, %ecx
	jmp	.L1413
	.p2align 4,,10
	.p2align 3
.L949:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$1, %ecx
	jmp	.L1413
	.p2align 4,,10
	.p2align 3
.L950:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	xorl	%ecx, %ecx
	jmp	.L1413
	.p2align 4,,10
	.p2align 3
.L946:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$4, %ecx
	jmp	.L1413
	.p2align 4,,10
	.p2align 3
.L951:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1450
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %r12w
	jb	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r11d, %r11d
	movw	%r11w, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1149
	cmpw	%ax, %r15w
	jnb	.L1150
.L1149:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1150:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1153
	.p2align 4,,10
	.p2align 3
.L1151:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm2
	movb	$1, 80(%rax)
	movb	$5, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm2, 88(%rax)
.L1152:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1427
.L1153:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1151
	xorl	%r10d, %r10d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r10w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1152
	.p2align 4,,10
	.p2align 3
.L953:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$4, %ecx
	xorl	%edx, %edx
	jmp	.L1410
	.p2align 4,,10
	.p2align 3
.L954:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1451
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1134
	cmpw	%dx, %r12w
	jbe	.L1135
.L1134:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1135:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1138
	.p2align 4,,10
	.p2align 3
.L1136:
	movl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 80(%rax)
	movb	$3, 112(%rax)
	movl	%edx, 104(%rax)
	movups	%xmm1, 88(%rax)
.L1137:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1427
.L1138:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1136
	xorl	%eax, %eax
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1137
	.p2align 4,,10
	.p2align 3
.L955:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$2, %ecx
	xorl	%edx, %edx
	jmp	.L1410
	.p2align 4,,10
	.p2align 3
.L957:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	jmp	.L1410
	.p2align 4,,10
	.p2align 3
.L958:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	xorl	%ecx, %ecx
	movl	$1, %edx
.L1410:
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rsi
	movq	%rbp, %rdi
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
	jmp	_ZN8opendnp315DatabaseBuffers18SelectVirtualRangeINS_17FrozenCounterSpecEEENS_8IINFieldERKNS_5RangeEbNT_18static_variation_tE@PLT
	.p2align 4,,10
	.p2align 3
.L956:
	.cfi_restore_state
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	movl	$1, %ecx
	xorl	%edx, %edx
	jmp	.L1410
	.p2align 4,,10
	.p2align 3
.L1437:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1245
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L975
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L975:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L977
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L977:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	%r14d, %esi
	movq	%rbp, %rdi
	movq	%rdx, %rcx
	movl	$1, %r8d
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
.L1425:
	movl	%eax, %ecx
	movzbl	%ah, %eax
	orb	15(%rsp), %al
	orb	14(%rsp), %cl
	movl	%eax, %edx
	jmp	.L1250
	.p2align 4,,10
	.p2align 3
.L1436:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_19TimeAndIntervalSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1245
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1246
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1246:
	movzwl	%r14w, %ecx
	addl	$1, %eax
	subl	%ecx, %eax
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1248
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1248:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19TimeAndIntervalSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	movl	%r14d, %esi
	movq	%rdx, %rcx
	movq	%rbp, %rdi
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19TimeAndIntervalSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	jmp	.L1425
	.p2align 4,,10
	.p2align 3
.L1435:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1245
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L990
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L990:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%edi, %edi
	subl	%ecx, %eax
	movw	%di, 14(%rsp)
	cmpl	%edx, %eax
	je	.L992
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L992:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r8d, %r8d
	movl	%r14d, %esi
	movq	%rbp, %rdi
	movq	%rdx, %rcx
	movl	$1, %r9d
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	jmp	.L1425
	.p2align 4,,10
	.p2align 3
.L1432:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1025
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1025:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1027
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1027:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1423:
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22BinaryOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1231:
	xorl	%r9d, %r9d
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	movw	%r9w, 14(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzbl	14(%rsp), %edx
	movzbl	15(%rsp), %ecx
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1238:
	xorl	%esi, %esi
	leaq	16(%rsp), %rdi
	movw	%si, 16(%rsp)
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzbl	16(%rsp), %edx
	movzbl	17(%rsp), %ecx
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L931:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1452
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1004
	cmpw	%ax, %r15w
	jnb	.L1005
.L1004:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1005:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1008
	.p2align 4,,10
	.p2align 3
.L1006:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm0
	movb	$1, 72(%rax)
	movb	%dl, 96(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm0, 80(%rax)
	movb	%dl, 104(%rax)
.L1007:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1429
.L1008:
	movzwl	%r12w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r13, %rax
	cmpb	$0, 72(%rax)
	je	.L1006
	xorl	%eax, %eax
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1007
	.p2align 4,,10
	.p2align 3
.L929:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1453
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %ebx
	movzwl	2(%r12), %r15d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r15w, %bx
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r15d, %r14d
	movl	%ebx, %r12d
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r15w, %dx
	cmovbe	%edx, %r14d
	cmpw	%bx, %ax
	cmovnb	%eax, %r12d
	cmpw	%r12w, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%ax, %bx
	jb	.L1046
	cmpw	%dx, %r15w
	jbe	.L1047
.L1046:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1047:
	movl	%r12d, %ebx
	leaq	16(%rsp), %r15
	jmp	.L1050
	.p2align 4,,10
	.p2align 3
.L1048:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm3
	movb	$1, 72(%rax)
	movb	$0, 104(%rax)
	movb	%dl, 96(%rax)
	movups	%xmm3, 80(%rax)
.L1049:
	addl	$1, %ebx
	cmpw	%bx, %r14w
	jb	.L1454
.L1050:
	movzwl	%bx, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r13, %rax
	cmpb	$0, 72(%rax)
	je	.L1048
	xorl	%eax, %eax
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1049
	.p2align 4,,10
	.p2align 3
.L933:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1455
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1426
	.p2align 4,,10
	.p2align 3
.L965:
	leaq	24(%rdi), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1456
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	movl	%r12d, %r14d
	movl	%r15d, %ebx
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	shrl	$16, %edx
	cmpw	%r12w, %dx
	cmovbe	%edx, %r14d
	cmpw	%r15w, %ax
	cmovnb	%eax, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r11d, %r11d
	movw	%r11w, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1018
	cmpw	%ax, %r15w
	jnb	.L1019
.L1018:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1019:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1022
	.p2align 4,,10
	.p2align 3
.L1020:
	movzbl	16(%rax), %edx
	movdqu	(%rax), %xmm1
	movb	$1, 72(%rax)
	movb	$0, 104(%rax)
	movb	%dl, 96(%rax)
	movups	%xmm1, 80(%rax)
.L1021:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1429
.L1022:
	movzwl	%r12w, %edx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	salq	$4, %rax
	addq	%r13, %rax
	cmpb	$0, 72(%rax)
	je	.L1020
	xorl	%r10d, %r10d
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%r10w, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1021
	.p2align 4,,10
	.p2align 3
.L937:
	leaq	24(%rbp), %r13
	cmpb	$1, 218(%rbp)
	movq	%r13, %rdi
	je	.L1457
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movzwl	(%r12), %r15d
	movzwl	2(%r12), %r12d
	xorl	%ecx, %ecx
	movq	%rdx, %r13
	xorl	%edx, %edx
	cmpw	%r12w, %r15w
	ja	.L1236
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%ecx, %ecx
	movw	%cx, 14(%rsp)
	cmpw	%ax, %r15w
	jb	.L1183
	cmpw	%dx, %r12w
	jbe	.L1184
.L1183:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1184:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1187
	.p2align 4,,10
	.p2align 3
.L1185:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm4
	movb	$1, 80(%rax)
	movq	%rdx, 104(%rax)
	movzbl	26(%rax), %edx
	movups	%xmm4, 88(%rax)
	movb	%dl, 112(%rax)
.L1186:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1415
.L1187:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1185
	xorl	%eax, %eax
	movl	$10, %esi
	movq	%r15, %rdi
	movw	%ax, 16(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1186
	.p2align 4,,10
	.p2align 3
.L943:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1412
	xorl	%ecx, %ecx
	movl	$1, %edx
	jmp	.L1414
	.p2align 4,,10
	.p2align 3
.L1415:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22AnalogOutputStatusSpecEEERNS_5RangeEv@PLT
.L1418:
	cmpw	%r14w, 2(%rax)
	cmovnb	2(%rax), %r14w
	cmpw	%bx, (%rax)
	cmovbe	(%rax), %bx
	movw	%r14w, 2(%rax)
	movw	%bx, (%rax)
	movzbl	14(%rsp), %edx
	movzbl	15(%rsp), %ecx
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1428:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_11CounterSpecEEERNS_5RangeEv@PLT
	jmp	.L1418
	.p2align 4,,10
	.p2align 3
.L1245:
	xorl	%edx, %edx
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	movw	%dx, 14(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzbl	14(%rsp), %ecx
	movzbl	15(%rsp), %edx
	jmp	.L1250
	.p2align 4,,10
	.p2align 3
.L1456:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1011
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1011:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%ebx, %ebx
	subl	%ecx, %eax
	movw	%bx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1013
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1013:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1422:
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_19DoubleBitBinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1453:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22BinaryOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1039
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1039:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1041
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1041:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22BinaryOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1423
	.p2align 4,,10
	.p2align 3
.L1457:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1176
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1176:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1178
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1178:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1417:
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_22AnalogOutputStatusSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1440:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1190
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1190:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%ebx, %ebx
	subl	%ecx, %eax
	movw	%bx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1192
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1192:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1416:
	xorl	%r8d, %r8d
	jmp	.L1417
	.p2align 4,,10
	.p2align 3
.L1447:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1109
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1109:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1111
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1111:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$3, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1420:
	xorl	%r8d, %r8d
.L1421:
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_11CounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1455:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_10BinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1245
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L983
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L983:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r8d, %r8d
	subl	%ecx, %eax
	movw	%r8w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L985
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L985:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10BinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	movl	%r14d, %esi
	movq	%rdx, %rcx
	movq	%rbp, %rdi
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10BinarySpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	jmp	.L1425
	.p2align 4,,10
	.p2align 3
.L1448:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_10AnalogSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1160
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1160:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1162
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1162:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_10AnalogSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r8d, %r8d
	movl	%r14d, %esi
	movq	%rbp, %rdi
	movq	%rdx, %rcx
	movl	$3, %r9d
	movq	%rax, %rdx
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_10AnalogSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1452:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_19DoubleBitBinarySpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L997
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L997:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L999
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L999:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_19DoubleBitBinarySpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1422
	.p2align 4,,10
	.p2align 3
.L1442:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1232
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1232:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r10d, %r10d
	subl	%ecx, %eax
	movw	%r10w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1234
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1234:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$3, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1416
	.p2align 4,,10
	.p2align 3
.L1441:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1218
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1218:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1220
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1220:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$2, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1416
	.p2align 4,,10
	.p2align 3
.L1451:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1127
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1127:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1129
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1129:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$3, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
.L1419:
	xorl	%r8d, %r8d
	movl	%r14d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp315DatabaseBuffers13GenericSelectINS_17FrozenCounterSpecEEENS_8IINFieldENS_5RangeEN7openpal9ArrayViewINS_4CellIT_EEtEEbNS8_18static_variation_tE.isra.0
	movl	%eax, %edx
	movzbl	%ah, %ecx
	orb	14(%rsp), %dl
	orb	15(%rsp), %cl
	jmp	.L1236
	.p2align 4,,10
	.p2align 3
.L1450:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_17FrozenCounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1142
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1142:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%ebx, %ebx
	subl	%ecx, %eax
	movw	%bx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1144
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1144:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_17FrozenCounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$5, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1419
	.p2align 4,,10
	.p2align 3
.L1438:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_22AnalogOutputStatusSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1204
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1204:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1206
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1206:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_22AnalogOutputStatusSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$1, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1416
	.p2align 4,,10
	.p2align 3
.L1444:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1053
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1053:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%ebx, %ebx
	subl	%ecx, %eax
	movw	%bx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1055
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1055:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movl	$1, %r8d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1421
	.p2align 4,,10
	.p2align 3
.L1443:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1095
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1095:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%ebx, %ebx
	subl	%ecx, %eax
	movw	%bx, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1097
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1097:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$2, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1420
	.p2align 4,,10
	.p2align 3
.L1445:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1081
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1081:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%esi, %esi
	subl	%ecx, %eax
	movw	%si, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1083
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1083:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	movl	$1, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1420
	.p2align 4,,10
	.p2align 3
.L1446:
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	leaq	16(%rsp), %rdi
	movq	%r12, %rsi
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	call	_ZN8opendnp311IndexSearch12FindRawRangeINS_11CounterSpecEEENS_5RangeERKN7openpal9ArrayViewINS_4CellIT_EEtEERKS3_@PLT
	movl	%eax, %r14d
	shrl	$16, %eax
	cmpw	%ax, %r14w
	ja	.L1231
	movzwl	(%r12), %ecx
	movzwl	2(%r12), %esi
	xorl	%edx, %edx
	cmpw	%si, %cx
	ja	.L1067
	movzwl	%si, %edx
	addl	$1, %edx
	subl	%ecx, %edx
.L1067:
	addl	$1, %eax
	movzwl	%r14w, %ecx
	xorl	%r9d, %r9d
	subl	%ecx, %eax
	movw	%r9w, 14(%rsp)
	cmpl	%edx, %eax
	je	.L1069
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1069:
	movq	%r13, %rdi
	call	_ZN8opendnp313StaticBuffers12GetArrayViewINS_11CounterSpecEEEN7openpal9ArrayViewINS_4CellIT_EEtEEv@PLT
	xorl	%r9d, %r9d
	movq	%rdx, %rcx
	movq	%rax, %rdx
	jmp	.L1420
.L1429:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_19DoubleBitBinarySpecEEERNS_5RangeEv@PLT
	jmp	.L1418
.L1427:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_17FrozenCounterSpecEEERNS_5RangeEv@PLT
	jmp	.L1418
.L1439:
	movzwl	%ax, %edi
	call	_ZN8opendnp315DatabaseBuffers7RangeOfEt@PLT
	movl	%eax, %edx
	movl	%eax, %ebx
	shrl	$16, %edx
	cmpw	%dx, %r12w
	movl	%edx, %r14d
	cmovbe	%r12d, %r14d
	cmpw	%ax, %r15w
	cmovnb	%r15d, %ebx
	cmpw	%bx, %r14w
	jb	.L1238
	xorl	%r8d, %r8d
	movw	%r8w, 14(%rsp)
	cmpw	%dx, %r12w
	ja	.L1211
	cmpw	%ax, %r15w
	jnb	.L1212
.L1211:
	leaq	14(%rsp), %rdi
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L1212:
	movl	%ebx, %r12d
	leaq	16(%rsp), %r15
	jmp	.L1215
	.p2align 4,,10
	.p2align 3
.L1213:
	movq	16(%rax), %rdx
	movdqu	(%rax), %xmm6
	movb	$1, 80(%rax)
	movb	$1, 112(%rax)
	movq	%rdx, 104(%rax)
	movups	%xmm6, 88(%rax)
.L1214:
	addl	$1, %r12d
	cmpw	%r12w, %r14w
	jb	.L1415
.L1215:
	movzwl	%r12w, %edx
	movq	%rdx, %rax
	salq	$4, %rax
	subq	%rdx, %rax
	leaq	0(%r13,%rax,8), %rax
	cmpb	$0, 80(%rax)
	je	.L1213
	xorl	%edi, %edi
	movl	$10, %esi
	movw	%di, 16(%rsp)
	movq	%r15, %rdi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	16(%rsp), %eax
	orw	%ax, 14(%rsp)
	jmp	.L1214
.L1433:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	jmp	.L1418
.L1449:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_10AnalogSpecEEERNS_5RangeEv@PLT
	jmp	.L1418
.L1454:
	leaq	220(%rbp), %rdi
	call	_ZN8opendnp314SelectedRanges11GetRangeRefINS_22BinaryOutputStatusSpecEEERNS_5RangeEv@PLT
	cmpw	%r14w, 2(%rax)
	cmovnb	2(%rax), %r14w
	cmpw	%r12w, (%rax)
	cmovbe	(%rax), %r12w
	movw	%r14w, 2(%rax)
	movw	%r12w, (%rax)
	movzbl	14(%rsp), %edx
	movzbl	15(%rsp), %ecx
	jmp	.L1236
.L1412:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2400:
	.size	_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE, .-_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE
	.weak	_ZTSN7openpal10UncopyableE
	.section	.rodata._ZTSN7openpal10UncopyableE,"aG",@progbits,_ZTSN7openpal10UncopyableE,comdat
	.align 16
	.type	_ZTSN7openpal10UncopyableE, @object
	.size	_ZTSN7openpal10UncopyableE, 23
_ZTSN7openpal10UncopyableE:
	.string	"N7openpal10UncopyableE"
	.weak	_ZTIN7openpal10UncopyableE
	.section	.data.rel.ro._ZTIN7openpal10UncopyableE,"awG",@progbits,_ZTIN7openpal10UncopyableE,comdat
	.align 8
	.type	_ZTIN7openpal10UncopyableE, @object
	.size	_ZTIN7openpal10UncopyableE, 16
_ZTIN7openpal10UncopyableE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN7openpal10UncopyableE
	.weak	_ZTSN8opendnp315IResponseLoaderE
	.section	.rodata._ZTSN8opendnp315IResponseLoaderE,"aG",@progbits,_ZTSN8opendnp315IResponseLoaderE,comdat
	.align 16
	.type	_ZTSN8opendnp315IResponseLoaderE, @object
	.size	_ZTSN8opendnp315IResponseLoaderE, 29
_ZTSN8opendnp315IResponseLoaderE:
	.string	"N8opendnp315IResponseLoaderE"
	.weak	_ZTIN8opendnp315IResponseLoaderE
	.section	.data.rel.ro._ZTIN8opendnp315IResponseLoaderE,"awG",@progbits,_ZTIN8opendnp315IResponseLoaderE,comdat
	.align 8
	.type	_ZTIN8opendnp315IResponseLoaderE, @object
	.size	_ZTIN8opendnp315IResponseLoaderE, 16
_ZTIN8opendnp315IResponseLoaderE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp315IResponseLoaderE
	.weak	_ZTSN8opendnp315IStaticSelectorE
	.section	.rodata._ZTSN8opendnp315IStaticSelectorE,"aG",@progbits,_ZTSN8opendnp315IStaticSelectorE,comdat
	.align 16
	.type	_ZTSN8opendnp315IStaticSelectorE, @object
	.size	_ZTSN8opendnp315IStaticSelectorE, 29
_ZTSN8opendnp315IStaticSelectorE:
	.string	"N8opendnp315IStaticSelectorE"
	.weak	_ZTIN8opendnp315IStaticSelectorE
	.section	.data.rel.ro._ZTIN8opendnp315IStaticSelectorE,"awG",@progbits,_ZTIN8opendnp315IStaticSelectorE,comdat
	.align 8
	.type	_ZTIN8opendnp315IStaticSelectorE, @object
	.size	_ZTIN8opendnp315IStaticSelectorE, 16
_ZTIN8opendnp315IStaticSelectorE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp315IStaticSelectorE
	.weak	_ZTSN8opendnp314IClassAssignerE
	.section	.rodata._ZTSN8opendnp314IClassAssignerE,"aG",@progbits,_ZTSN8opendnp314IClassAssignerE,comdat
	.align 16
	.type	_ZTSN8opendnp314IClassAssignerE, @object
	.size	_ZTSN8opendnp314IClassAssignerE, 28
_ZTSN8opendnp314IClassAssignerE:
	.string	"N8opendnp314IClassAssignerE"
	.weak	_ZTIN8opendnp314IClassAssignerE
	.section	.data.rel.ro._ZTIN8opendnp314IClassAssignerE,"awG",@progbits,_ZTIN8opendnp314IClassAssignerE,comdat
	.align 8
	.type	_ZTIN8opendnp314IClassAssignerE, @object
	.size	_ZTIN8opendnp314IClassAssignerE, 16
_ZTIN8opendnp314IClassAssignerE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp314IClassAssignerE
	.weak	_ZTSN8opendnp315DatabaseBuffersE
	.section	.rodata._ZTSN8opendnp315DatabaseBuffersE,"aG",@progbits,_ZTSN8opendnp315DatabaseBuffersE,comdat
	.align 16
	.type	_ZTSN8opendnp315DatabaseBuffersE, @object
	.size	_ZTSN8opendnp315DatabaseBuffersE, 29
_ZTSN8opendnp315DatabaseBuffersE:
	.string	"N8opendnp315DatabaseBuffersE"
	.weak	_ZTIN8opendnp315DatabaseBuffersE
	.section	.data.rel.ro._ZTIN8opendnp315DatabaseBuffersE,"awG",@progbits,_ZTIN8opendnp315DatabaseBuffersE,comdat
	.align 8
	.type	_ZTIN8opendnp315DatabaseBuffersE, @object
	.size	_ZTIN8opendnp315DatabaseBuffersE, 88
_ZTIN8opendnp315DatabaseBuffersE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN8opendnp315DatabaseBuffersE
	.long	0
	.long	4
	.quad	_ZTIN8opendnp315IStaticSelectorE
	.quad	2
	.quad	_ZTIN8opendnp315IResponseLoaderE
	.quad	2050
	.quad	_ZTIN8opendnp314IClassAssignerE
	.quad	4098
	.quad	_ZTIN7openpal10UncopyableE
	.quad	0
	.weak	_ZTVN8opendnp315DatabaseBuffersE
	.section	.data.rel.ro._ZTVN8opendnp315DatabaseBuffersE,"awG",@progbits,_ZTVN8opendnp315DatabaseBuffersE,comdat
	.align 8
	.type	_ZTVN8opendnp315DatabaseBuffersE, @object
	.size	_ZTVN8opendnp315DatabaseBuffersE, 136
_ZTVN8opendnp315DatabaseBuffersE:
	.quad	0
	.quad	_ZTIN8opendnp315DatabaseBuffersE
	.quad	_ZN8opendnp315DatabaseBuffers9SelectAllENS_14GroupVariationE
	.quad	_ZN8opendnp315DatabaseBuffers11SelectRangeENS_14GroupVariationERKNS_5RangeE
	.quad	_ZN8opendnp315DatabaseBuffers8UnselectEv
	.quad	_ZN8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.quad	_ZNK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.quad	_ZN8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.quad	_ZN8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.quad	-8
	.quad	_ZTIN8opendnp315DatabaseBuffersE
	.quad	_ZThn8_NK8opendnp315DatabaseBuffers15HasAnySelectionEv
	.quad	_ZThn8_N8opendnp315DatabaseBuffers4LoadERNS_12HeaderWriterE
	.quad	-16
	.quad	_ZTIN8opendnp315DatabaseBuffersE
	.quad	_ZThn16_N8opendnp315DatabaseBuffers16AssignClassToAllENS_15AssignClassTypeENS_10PointClassE
	.quad	_ZThn16_N8opendnp315DatabaseBuffers18AssignClassToRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.value	1
	.value	0
	.value	1
	.value	0
	.value	1
	.value	0
	.value	1
	.value	0
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
