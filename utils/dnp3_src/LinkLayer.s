	.file	"LinkLayer.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer14OnLowerLayerUpEv
	.type	_ZN8opendnp39LinkLayer14OnLowerLayerUpEv, @function
_ZN8opendnp39LinkLayer14OnLowerLayerUpEv:
.LFB2322:
	.cfi_startproc
	addq	$16, %rdi
	jmp	_ZN8opendnp311LinkContext14OnLowerLayerUpEv@PLT
	.cfi_endproc
.LFE2322:
	.size	_ZN8opendnp39LinkLayer14OnLowerLayerUpEv, .-_ZN8opendnp39LinkLayer14OnLowerLayerUpEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer16OnLowerLayerDownEv
	.type	_ZN8opendnp39LinkLayer16OnLowerLayerDownEv, @function
_ZN8opendnp39LinkLayer16OnLowerLayerDownEv:
.LFB2323:
	.cfi_startproc
	addq	$16, %rdi
	jmp	_ZN8opendnp311LinkContext16OnLowerLayerDownEv@PLT
	.cfi_endproc
.LFE2323:
	.size	_ZN8opendnp39LinkLayer16OnLowerLayerDownEv, .-_ZN8opendnp39LinkLayer16OnLowerLayerDownEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer16OnTransmitResultEb
	.type	_ZN8opendnp39LinkLayer16OnTransmitResultEb, @function
_ZN8opendnp39LinkLayer16OnTransmitResultEb:
.LFB2324:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	16(%rdi), %rbp
	movzbl	%sil, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext16OnTransmitResultEb@PLT
	testb	%al, %al
	jne	.L10
	movl	$1, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext20TryStartTransmissionEv@PLT
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2324:
	.size	_ZN8opendnp39LinkLayer16OnTransmitResultEb, .-_ZN8opendnp39LinkLayer16OnTransmitResultEb
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.type	_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE, @function
_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE:
.LFB2325:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	16(%rdi), %rbp
	movq	%rbp, %rdi
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	call	_ZN8opendnp311LinkContext7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE@PLT
	testb	%al, %al
	jne	.L17
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	.cfi_restore_state
	movq	%rbp, %rdi
	movb	%al, 15(%rsp)
	call	_ZN8opendnp311LinkContext20TryStartTransmissionEv@PLT
	movzbl	15(%rsp), %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2325:
	.size	_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE, .-_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE
	.type	_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE, @function
_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE:
.LFB2321:
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
	movzbl	522(%rdi), %r12d
	testb	%r12b, %r12b
	jne	.L27
.L18:
	movl	%r12d, %eax
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
.L27:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext12SetTxSegmentERNS_17ITransportSegmentE@PLT
	movl	%eax, %ebx
	testb	%al, %al
	je	.L18
	movl	%ebx, %r12d
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext20TryStartTransmissionEv@PLT
	movl	%r12d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2321:
	.size	_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE, .-_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE
	.p2align 4
	.globl	_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv
	.type	_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv, @function
_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv:
.LFB3000:
	.cfi_startproc
	addq	$8, %rdi
	jmp	_ZN8opendnp311LinkContext14OnLowerLayerUpEv@PLT
	.cfi_endproc
.LFE3000:
	.size	_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv, .-_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv
	.p2align 4
	.globl	_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv
	.type	_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv, @function
_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv:
.LFB3001:
	.cfi_startproc
	addq	$8, %rdi
	jmp	_ZN8opendnp311LinkContext16OnLowerLayerDownEv@PLT
	.cfi_endproc
.LFE3001:
	.size	_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv, .-_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv
	.p2align 4
	.globl	_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb
	.type	_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb, @function
_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb:
.LFB3003:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	8(%rdi), %rbp
	movzbl	%sil, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext16OnTransmitResultEb@PLT
	testb	%al, %al
	jne	.L36
	movl	$1, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L36:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	_ZN8opendnp311LinkContext20TryStartTransmissionEv@PLT
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3003:
	.size	_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb, .-_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb
	.p2align 4
	.globl	_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.type	_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE, @function
_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE:
.LFB3004:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	8(%rdi), %rbp
	movq	%rbp, %rdi
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	call	_ZN8opendnp311LinkContext7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE@PLT
	testb	%al, %al
	jne	.L43
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L43:
	.cfi_restore_state
	movq	%rbp, %rdi
	movb	%al, 15(%rsp)
	call	_ZN8opendnp311LinkContext20TryStartTransmissionEv@PLT
	movzbl	15(%rsp), %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3004:
	.size	_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE, .-_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.section	.text._ZN8opendnp39LinkLayerD2Ev,"axG",@progbits,_ZN8opendnp39LinkLayerD5Ev,comdat
	.p2align 4
	.weak	_ZThn8_N8opendnp39LinkLayerD1Ev
	.type	_ZThn8_N8opendnp39LinkLayerD1Ev, @function
_ZThn8_N8opendnp39LinkLayerD1Ev:
.LFB2999:
	.cfi_startproc
	movq	_ZTVN8opendnp39LinkLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	592(%rdi), %r12
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	movq	%rdi, %rbx
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, -8(%rdi)
	testq	%r12, %r12
	je	.L46
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L81
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L48:
	cmpl	$1, %eax
	je	.L82
.L46:
	movq	576(%rbx), %r12
	testq	%r12, %r12
	je	.L53
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L83
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L55:
	cmpl	$1, %eax
	je	.L84
.L53:
	leaq	496(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	leaq	480(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	movq	472(%rbx), %r12
	testq	%r12, %r12
	je	.L60
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L85
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L62:
	cmpl	$1, %eax
	je	.L86
.L60:
	movq	408(%rbx), %r12
	testq	%r12, %r12
	je	.L67
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L87
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L69:
	cmpl	$1, %eax
	je	.L88
.L67:
	movq	392(%rbx), %r12
	testq	%r12, %r12
	je	.L44
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L89
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L76:
	cmpl	$1, %eax
	je	.L90
.L44:
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
.L82:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L91
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L51:
	cmpl	$1, %eax
	jne	.L46
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L84:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L92
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L58:
	cmpl	$1, %eax
	jne	.L53
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L86:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L93
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L65:
	cmpl	$1, %eax
	jne	.L60
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L90:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L94
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L79:
	cmpl	$1, %eax
	jne	.L44
	movq	(%r12), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L88:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L95
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L72:
	cmpl	$1, %eax
	jne	.L67
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L67
	.p2align 4,,10
	.p2align 3
.L85:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L62
	.p2align 4,,10
	.p2align 3
.L83:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L89:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L81:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L87:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L69
	.p2align 4,,10
	.p2align 3
.L95:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L72
	.p2align 4,,10
	.p2align 3
.L91:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L93:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L65
	.p2align 4,,10
	.p2align 3
.L92:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L94:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L79
	.cfi_endproc
.LFE2999:
	.size	_ZThn8_N8opendnp39LinkLayerD1Ev, .-_ZThn8_N8opendnp39LinkLayerD1Ev
	.section	.text._ZN8opendnp39LinkLayerD0Ev,"axG",@progbits,_ZN8opendnp39LinkLayerD5Ev,comdat
	.p2align 4
	.weak	_ZThn8_N8opendnp39LinkLayerD0Ev
	.type	_ZThn8_N8opendnp39LinkLayerD0Ev, @function
_ZThn8_N8opendnp39LinkLayerD0Ev:
.LFB3002:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	-8(%rdi), %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movq	_ZTVN8opendnp39LinkLayerE@GOTPCREL(%rip), %rax
	movq	592(%rdi), %r12
	leaq	88(%rax), %rdx
	addq	$16, %rax
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, -8(%rdi)
	testq	%r12, %r12
	je	.L98
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L133
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L100:
	cmpl	$1, %eax
	je	.L134
.L98:
	movq	576(%rbx), %r12
	testq	%r12, %r12
	je	.L105
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L135
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L107:
	cmpl	$1, %eax
	je	.L136
.L105:
	leaq	496(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	leaq	480(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	movq	472(%rbx), %r12
	testq	%r12, %r12
	je	.L112
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L137
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L114:
	cmpl	$1, %eax
	je	.L138
.L112:
	movq	408(%rbx), %r12
	testq	%r12, %r12
	je	.L119
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L139
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L121:
	cmpl	$1, %eax
	je	.L140
.L119:
	movq	392(%rbx), %r12
	testq	%r12, %r12
	je	.L126
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L141
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L128:
	cmpl	$1, %eax
	je	.L142
.L126:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$616, %esi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L134:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L143
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L103:
	cmpl	$1, %eax
	jne	.L98
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L98
	.p2align 4,,10
	.p2align 3
.L136:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L144
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L110:
	cmpl	$1, %eax
	jne	.L105
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L105
	.p2align 4,,10
	.p2align 3
.L138:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L145
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L117:
	cmpl	$1, %eax
	jne	.L112
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L142:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L146
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L131:
	cmpl	$1, %eax
	jne	.L126
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L126
	.p2align 4,,10
	.p2align 3
.L140:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L147
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L124:
	cmpl	$1, %eax
	jne	.L119
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L119
	.p2align 4,,10
	.p2align 3
.L137:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L114
	.p2align 4,,10
	.p2align 3
.L135:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L107
	.p2align 4,,10
	.p2align 3
.L141:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L128
	.p2align 4,,10
	.p2align 3
.L133:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L100
	.p2align 4,,10
	.p2align 3
.L139:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L121
	.p2align 4,,10
	.p2align 3
.L147:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L124
	.p2align 4,,10
	.p2align 3
.L143:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L103
	.p2align 4,,10
	.p2align 3
.L145:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L117
	.p2align 4,,10
	.p2align 3
.L144:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L110
	.p2align 4,,10
	.p2align 3
.L146:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L131
	.cfi_endproc
.LFE3002:
	.size	_ZThn8_N8opendnp39LinkLayerD0Ev, .-_ZThn8_N8opendnp39LinkLayerD0Ev
	.align 2
	.p2align 4
	.weak	_ZN8opendnp39LinkLayerD0Ev
	.type	_ZN8opendnp39LinkLayerD0Ev, @function
_ZN8opendnp39LinkLayerD0Ev:
.LFB2966:
	.cfi_startproc
	movq	_ZTVN8opendnp39LinkLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	600(%rdi), %r12
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, (%rdi)
	testq	%r12, %r12
	je	.L150
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L185
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L152:
	cmpl	$1, %eax
	je	.L186
.L150:
	movq	584(%rbp), %r12
	testq	%r12, %r12
	je	.L157
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L187
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L159:
	cmpl	$1, %eax
	je	.L188
.L157:
	leaq	504(%rbp), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	leaq	488(%rbp), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	movq	480(%rbp), %r12
	testq	%r12, %r12
	je	.L164
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L189
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L166:
	cmpl	$1, %eax
	je	.L190
.L164:
	movq	416(%rbp), %r12
	testq	%r12, %r12
	je	.L171
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L191
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L173:
	cmpl	$1, %eax
	je	.L192
.L171:
	movq	400(%rbp), %r12
	testq	%r12, %r12
	je	.L178
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L193
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L180:
	cmpl	$1, %eax
	je	.L194
.L178:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	movl	$616, %esi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L186:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L195
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L155:
	cmpl	$1, %eax
	jne	.L150
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L188:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L196
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L162:
	cmpl	$1, %eax
	jne	.L157
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L190:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L197
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L169:
	cmpl	$1, %eax
	jne	.L164
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L164
	.p2align 4,,10
	.p2align 3
.L194:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L198
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L183:
	cmpl	$1, %eax
	jne	.L178
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L178
	.p2align 4,,10
	.p2align 3
.L192:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L199
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L176:
	cmpl	$1, %eax
	jne	.L171
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L171
	.p2align 4,,10
	.p2align 3
.L189:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L166
	.p2align 4,,10
	.p2align 3
.L187:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L193:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L180
	.p2align 4,,10
	.p2align 3
.L185:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L191:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L173
	.p2align 4,,10
	.p2align 3
.L199:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L176
	.p2align 4,,10
	.p2align 3
.L195:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L155
	.p2align 4,,10
	.p2align 3
.L197:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L169
	.p2align 4,,10
	.p2align 3
.L196:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L162
	.p2align 4,,10
	.p2align 3
.L198:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L183
	.cfi_endproc
.LFE2966:
	.size	_ZN8opendnp39LinkLayerD0Ev, .-_ZN8opendnp39LinkLayerD0Ev
	.section	.text._ZN8opendnp39LinkLayerD2Ev,"axG",@progbits,_ZN8opendnp39LinkLayerD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp39LinkLayerD2Ev
	.type	_ZN8opendnp39LinkLayerD2Ev, @function
_ZN8opendnp39LinkLayerD2Ev:
.LFB2964:
	.cfi_startproc
	movq	_ZTVN8opendnp39LinkLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	600(%rdi), %r12
	movq	%rax, %xmm0
	movq	%rdx, %xmm1
	movq	%rdi, %rbx
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, (%rdi)
	testq	%r12, %r12
	je	.L202
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L237
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L204:
	cmpl	$1, %eax
	je	.L238
.L202:
	movq	584(%rbx), %r12
	testq	%r12, %r12
	je	.L209
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L239
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L211:
	cmpl	$1, %eax
	je	.L240
.L209:
	leaq	504(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	leaq	488(%rbx), %rdi
	call	_ZN7openpal8TimerRefD1Ev@PLT
	movq	480(%rbx), %r12
	testq	%r12, %r12
	je	.L216
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L241
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L218:
	cmpl	$1, %eax
	je	.L242
.L216:
	movq	416(%rbx), %r12
	testq	%r12, %r12
	je	.L223
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L243
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L225:
	cmpl	$1, %eax
	je	.L244
.L223:
	movq	400(%rbx), %r12
	testq	%r12, %r12
	je	.L200
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L245
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L232:
	cmpl	$1, %eax
	je	.L246
.L200:
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
.L238:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L247
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L207:
	cmpl	$1, %eax
	jne	.L202
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L202
	.p2align 4,,10
	.p2align 3
.L240:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L248
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L214:
	cmpl	$1, %eax
	jne	.L209
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L209
	.p2align 4,,10
	.p2align 3
.L242:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L249
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L221:
	cmpl	$1, %eax
	jne	.L216
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L216
	.p2align 4,,10
	.p2align 3
.L246:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L250
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L235:
	cmpl	$1, %eax
	jne	.L200
	movq	(%r12), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L244:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L251
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L228:
	cmpl	$1, %eax
	jne	.L223
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L223
	.p2align 4,,10
	.p2align 3
.L241:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L218
	.p2align 4,,10
	.p2align 3
.L239:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L211
	.p2align 4,,10
	.p2align 3
.L245:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L232
	.p2align 4,,10
	.p2align 3
.L237:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L204
	.p2align 4,,10
	.p2align 3
.L243:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L225
	.p2align 4,,10
	.p2align 3
.L251:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L228
	.p2align 4,,10
	.p2align 3
.L247:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L207
	.p2align 4,,10
	.p2align 3
.L249:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L221
	.p2align 4,,10
	.p2align 3
.L248:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L214
	.p2align 4,,10
	.p2align 3
.L250:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L235
	.cfi_endproc
.LFE2964:
	.size	_ZN8opendnp39LinkLayerD2Ev, .-_ZN8opendnp39LinkLayerD2Ev
	.weak	_ZN8opendnp39LinkLayerD1Ev
	.set	_ZN8opendnp39LinkLayerD1Ev,_ZN8opendnp39LinkLayerD2Ev
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE
	.type	_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE, @function
_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE:
.LFB2317:
	.cfi_startproc
	subq	$16, %rsp
	.cfi_def_cfa_offset 24
	movq	_ZTVN8opendnp39LinkLayerE@GOTPCREL(%rip), %rax
	leaq	88(%rax), %r10
	addq	$16, %rax
	movq	%r10, %xmm1
	movq	%rax, %xmm0
	leaq	16(%rdi), %r10
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, (%rdi)
	pushq	%r9
	.cfi_def_cfa_offset 32
	leaq	8(%rdi), %r9
	movq	%r10, %rdi
	call	_ZN8opendnp311LinkContextC1ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERNS_12ILinkSessionERKNS_10LinkConfigE@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2317:
	.size	_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE, .-_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE
	.globl	_ZN8opendnp39LinkLayerC1ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE
	.set	_ZN8opendnp39LinkLayerC1ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE,_ZN8opendnp39LinkLayerC2ERKN7openpal6LoggerERKSt10shared_ptrINS1_9IExecutorEERKS5_INS_11IUpperLayerEERKS5_INS_13ILinkListenerEERKNS_10LinkConfigE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39LinkLayer13GetStatisticsEv
	.type	_ZNK8opendnp39LinkLayer13GetStatisticsEv, @function
_ZNK8opendnp39LinkLayer13GetStatisticsEv:
.LFB2319:
	.cfi_startproc
	leaq	536(%rdi), %rax
	ret
	.cfi_endproc
.LFE2319:
	.size	_ZNK8opendnp39LinkLayer13GetStatisticsEv, .-_ZNK8opendnp39LinkLayer13GetStatisticsEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39LinkLayer9SetRouterERNS_7ILinkTxE
	.type	_ZN8opendnp39LinkLayer9SetRouterERNS_7ILinkTxE, @function
_ZN8opendnp39LinkLayer9SetRouterERNS_7ILinkTxE:
.LFB2320:
	.cfi_startproc
	movq	%rsi, 552(%rdi)
	ret
	.cfi_endproc
.LFE2320:
	.size	_ZN8opendnp39LinkLayer9SetRouterERNS_7ILinkTxE, .-_ZN8opendnp39LinkLayer9SetRouterERNS_7ILinkTxE
	.weak	_ZTSN8opendnp310ILinkLayerE
	.section	.rodata._ZTSN8opendnp310ILinkLayerE,"aG",@progbits,_ZTSN8opendnp310ILinkLayerE,comdat
	.align 16
	.type	_ZTSN8opendnp310ILinkLayerE, @object
	.size	_ZTSN8opendnp310ILinkLayerE, 24
_ZTSN8opendnp310ILinkLayerE:
	.string	"N8opendnp310ILinkLayerE"
	.weak	_ZTIN8opendnp310ILinkLayerE
	.section	.data.rel.ro._ZTIN8opendnp310ILinkLayerE,"awG",@progbits,_ZTIN8opendnp310ILinkLayerE,comdat
	.align 8
	.type	_ZTIN8opendnp310ILinkLayerE, @object
	.size	_ZTIN8opendnp310ILinkLayerE, 16
_ZTIN8opendnp310ILinkLayerE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp310ILinkLayerE
	.weak	_ZTSN8opendnp310IFrameSinkE
	.section	.rodata._ZTSN8opendnp310IFrameSinkE,"aG",@progbits,_ZTSN8opendnp310IFrameSinkE,comdat
	.align 16
	.type	_ZTSN8opendnp310IFrameSinkE, @object
	.size	_ZTSN8opendnp310IFrameSinkE, 24
_ZTSN8opendnp310IFrameSinkE:
	.string	"N8opendnp310IFrameSinkE"
	.weak	_ZTIN8opendnp310IFrameSinkE
	.section	.data.rel.ro._ZTIN8opendnp310IFrameSinkE,"awG",@progbits,_ZTIN8opendnp310IFrameSinkE,comdat
	.align 8
	.type	_ZTIN8opendnp310IFrameSinkE, @object
	.size	_ZTIN8opendnp310IFrameSinkE, 16
_ZTIN8opendnp310IFrameSinkE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp310IFrameSinkE
	.weak	_ZTSN8opendnp312ILinkSessionE
	.section	.rodata._ZTSN8opendnp312ILinkSessionE,"aG",@progbits,_ZTSN8opendnp312ILinkSessionE,comdat
	.align 16
	.type	_ZTSN8opendnp312ILinkSessionE, @object
	.size	_ZTSN8opendnp312ILinkSessionE, 26
_ZTSN8opendnp312ILinkSessionE:
	.string	"N8opendnp312ILinkSessionE"
	.weak	_ZTIN8opendnp312ILinkSessionE
	.section	.data.rel.ro._ZTIN8opendnp312ILinkSessionE,"awG",@progbits,_ZTIN8opendnp312ILinkSessionE,comdat
	.align 8
	.type	_ZTIN8opendnp312ILinkSessionE, @object
	.size	_ZTIN8opendnp312ILinkSessionE, 24
_ZTIN8opendnp312ILinkSessionE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8opendnp312ILinkSessionE
	.quad	_ZTIN8opendnp310IFrameSinkE
	.weak	_ZTSN8opendnp39LinkLayerE
	.section	.rodata._ZTSN8opendnp39LinkLayerE,"aG",@progbits,_ZTSN8opendnp39LinkLayerE,comdat
	.align 16
	.type	_ZTSN8opendnp39LinkLayerE, @object
	.size	_ZTSN8opendnp39LinkLayerE, 22
_ZTSN8opendnp39LinkLayerE:
	.string	"N8opendnp39LinkLayerE"
	.weak	_ZTIN8opendnp39LinkLayerE
	.section	.data.rel.ro._ZTIN8opendnp39LinkLayerE,"awG",@progbits,_ZTIN8opendnp39LinkLayerE,comdat
	.align 8
	.type	_ZTIN8opendnp39LinkLayerE, @object
	.size	_ZTIN8opendnp39LinkLayerE, 56
_ZTIN8opendnp39LinkLayerE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN8opendnp39LinkLayerE
	.long	0
	.long	2
	.quad	_ZTIN8opendnp310ILinkLayerE
	.quad	2
	.quad	_ZTIN8opendnp312ILinkSessionE
	.quad	2050
	.weak	_ZTVN8opendnp39LinkLayerE
	.section	.data.rel.ro._ZTVN8opendnp39LinkLayerE,"awG",@progbits,_ZTVN8opendnp39LinkLayerE,comdat
	.align 8
	.type	_ZTVN8opendnp39LinkLayerE, @object
	.size	_ZTVN8opendnp39LinkLayerE, 136
_ZTVN8opendnp39LinkLayerE:
	.quad	0
	.quad	_ZTIN8opendnp39LinkLayerE
	.quad	_ZN8opendnp39LinkLayerD1Ev
	.quad	_ZN8opendnp39LinkLayerD0Ev
	.quad	_ZN8opendnp39LinkLayer4SendERNS_17ITransportSegmentE
	.quad	_ZN8opendnp39LinkLayer14OnLowerLayerUpEv
	.quad	_ZN8opendnp39LinkLayer16OnLowerLayerDownEv
	.quad	_ZN8opendnp39LinkLayer16OnTransmitResultEb
	.quad	_ZN8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.quad	-8
	.quad	_ZTIN8opendnp39LinkLayerE
	.quad	_ZThn8_N8opendnp39LinkLayerD1Ev
	.quad	_ZThn8_N8opendnp39LinkLayerD0Ev
	.quad	_ZThn8_N8opendnp39LinkLayer7OnFrameERKNS_16LinkHeaderFieldsERKN7openpal6RSliceE
	.quad	_ZThn8_N8opendnp39LinkLayer16OnTransmitResultEb
	.quad	_ZThn8_N8opendnp39LinkLayer14OnLowerLayerUpEv
	.quad	_ZThn8_N8opendnp39LinkLayer16OnLowerLayerDownEv
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
