	.file	"EventBuffer.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer15HasAnySelectionEv
	.type	_ZNK8opendnp311EventBuffer15HasAnySelectionEv, @function
_ZNK8opendnp311EventBuffer15HasAnySelectionEv:
.LFB422:
	.cfi_startproc
	movl	208(%rdi), %eax
	cmpl	%eax, 160(%rdi)
	seta	%al
	ret
	.cfi_endproc
.LFE422:
	.size	_ZNK8opendnp311EventBuffer15HasAnySelectionEv, .-_ZNK8opendnp311EventBuffer15HasAnySelectionEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.type	_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv, @function
_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv:
.LFB424:
	.cfi_startproc
	jmp	_ZNK8opendnp311EventBuffer15HasAnySelectionEv@PLT
	.cfi_endproc
.LFE424:
	.size	_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv, .-_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.section	.text._ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev,"axG",@progbits,_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev
	.type	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev, @function
_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev:
.LFB464:
	.cfi_startproc
	movq	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE@GOTPCREL(%rip), %rax
	addq	$16, %rax
	movq	%rax, (%rdi)
	movq	16(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L4
	jmp	_ZdaPv@PLT
	.p2align 4,,10
	.p2align 3
.L4:
	ret
	.cfi_endproc
.LFE464:
	.size	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev, .-_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev
	.weak	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED1Ev
	.set	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED1Ev,_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED2Ev
	.section	.text._ZN8opendnp311EventBufferD2Ev,"axG",@progbits,_ZN8opendnp311EventBufferD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBufferD2Ev
	.type	_ZN8opendnp311EventBufferD2Ev, @function
_ZN8opendnp311EventBufferD2Ev:
.LFB521:
	.cfi_startproc
	movq	_ZTVN8opendnp311EventBufferE@GOTPCREL(%rip), %rax
	leaq	160(%rax), %rdx
	leaq	16(%rax), %rcx
	movq	%rdx, %xmm1
	movq	%rcx, %xmm0
	leaq	224(%rax), %rdx
	addq	$192, %rax
	punpcklqdq	%xmm1, %xmm0
	movq	%rdx, %xmm2
	movups	%xmm0, (%rdi)
	movq	%rax, %xmm0
	movq	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE@GOTPCREL(%rip), %rax
	punpcklqdq	%xmm2, %xmm0
	addq	$16, %rax
	movups	%xmm0, 16(%rdi)
	movq	%rax, 88(%rdi)
	movq	104(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L6
	jmp	_ZdaPv@PLT
	.p2align 4,,10
	.p2align 3
.L6:
	ret
	.cfi_endproc
.LFE521:
	.size	_ZN8opendnp311EventBufferD2Ev, .-_ZN8opendnp311EventBufferD2Ev
	.weak	_ZN8opendnp311EventBufferD1Ev
	.set	_ZN8opendnp311EventBufferD1Ev,_ZN8opendnp311EventBufferD2Ev
	.section	.text._ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev,"axG",@progbits,_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev
	.type	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev, @function
_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev:
.LFB466:
	.cfi_startproc
	movq	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE@GOTPCREL(%rip), %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	addq	$16, %rax
	movq	%rax, (%rdi)
	movq	16(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L9
	call	_ZdaPv@PLT
.L9:
	movq	%rbp, %rdi
	movl	$24, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE466:
	.size	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev, .-_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev
	.section	.text._ZN8opendnp311EventBufferD0Ev,"axG",@progbits,_ZN8opendnp311EventBufferD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBufferD0Ev
	.type	_ZN8opendnp311EventBufferD0Ev, @function
_ZN8opendnp311EventBufferD0Ev:
.LFB523:
	.cfi_startproc
	movq	_ZTVN8opendnp311EventBufferE@GOTPCREL(%rip), %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	leaq	160(%rax), %rdx
	leaq	16(%rax), %rcx
	movq	%rdx, %xmm1
	movq	%rcx, %xmm0
	leaq	224(%rax), %rdx
	addq	$192, %rax
	punpcklqdq	%xmm1, %xmm0
	movq	%rdx, %xmm2
	movups	%xmm0, (%rdi)
	movq	%rax, %xmm0
	movq	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE@GOTPCREL(%rip), %rax
	punpcklqdq	%xmm2, %xmm0
	addq	$16, %rax
	movups	%xmm0, 16(%rdi)
	movq	%rax, 88(%rdi)
	movq	104(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L15
	call	_ZdaPv@PLT
.L15:
	movq	%rbp, %rdi
	movl	$256, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE523:
	.size	_ZN8opendnp311EventBufferD0Ev, .-_ZN8opendnp311EventBufferD0Ev
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer8UnselectEv
	.type	_ZN8opendnp311EventBuffer8UnselectEv, @function
_ZN8opendnp311EventBuffer8UnselectEv:
.LFB417:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	160(%rdi), %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movq	64(%rdi), %rbx
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L22:
	cmpb	$0, 4(%rbx)
	jne	.L30
.L23:
	movl	160(%r12), %eax
	testl	%eax, %eax
	je	.L20
.L24:
	movq	%rbp, %rbx
.L25:
	testq	%rbx, %rbx
	je	.L20
	cmpb	$0, 3(%rbx)
	movq	56(%rbx), %rbp
	je	.L22
	movzbl	2(%rbx), %esi
	movzwl	(%rbx), %edx
	movq	%r13, %rdi
	call	_ZN8opendnp310EventCount9DecrementENS_10EventClassENS_9EventTypeE@PLT
	cmpb	$0, 4(%rbx)
	movb	$0, 3(%rbx)
	je	.L23
.L30:
	movzwl	(%rbx), %edx
	movzbl	2(%rbx), %esi
	leaq	208(%r12), %rdi
	call	_ZN8opendnp310EventCount9DecrementENS_10EventClassENS_9EventTypeE@PLT
	movl	160(%r12), %edx
	movb	$0, 4(%rbx)
	testl	%edx, %edx
	jne	.L24
.L20:
	addq	$8, %rsp
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
	.cfi_endproc
.LFE417:
	.size	_ZN8opendnp311EventBuffer8UnselectEv, .-_ZN8opendnp311EventBuffer8UnselectEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.type	_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE, @function
_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE:
.LFB425:
	.cfi_startproc
	addq	$208, %rdi
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.cfi_endproc
.LFE425:
	.size	_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE, .-_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.type	_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE, @function
_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE:
.LFB423:
	.cfi_startproc
	movq	%rsi, %r8
	movq	64(%rdi), %rdx
	leaq	24(%rdi), %rsi
	movq	%r8, %rdi
	jmp	_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE@PLT
	.cfi_endproc
.LFE423:
	.size	_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE, .-_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.p2align 4
	.globl	_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv
	.type	_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv, @function
_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv:
.LFB529:
	.cfi_startproc
	movl	192(%rdi), %eax
	cmpl	%eax, 144(%rdi)
	seta	%al
	ret
	.cfi_endproc
.LFE529:
	.size	_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv, .-_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv
	.p2align 4
	.globl	_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.type	_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv, @function
_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv:
.LFB530:
	.cfi_startproc
	subq	$24, %rdi
	jmp	_ZNK8opendnp311EventBuffer15HasAnySelectionEv@PLT
	.cfi_endproc
.LFE530:
	.size	_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv, .-_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.p2align 4
	.globl	_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.type	_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE, @function
_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE:
.LFB531:
	.cfi_startproc
	addq	$184, %rdi
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.cfi_endproc
.LFE531:
	.size	_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE, .-_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.p2align 4
	.globl	_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.type	_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE, @function
_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE:
.LFB533:
	.cfi_startproc
	movq	%rsi, %r8
	movq	48(%rdi), %rdx
	leaq	8(%rdi), %rsi
	movq	%r8, %rdi
	jmp	_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE@PLT
	.cfi_endproc
.LFE533:
	.size	_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE, .-_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB3:
	.text
.LHOTB3:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE
	.type	_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE, @function
_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE:
.LFB415:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA415
	movq	_ZTVN8opendnp311EventBufferE@GOTPCREL(%rip), %rax
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	leaq	160(%rax), %rdx
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	movq	%rsi, %rdi
	leaq	16(%rax), %rsi
	movq	%rdx, %xmm6
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	leaq	224(%rax), %rdx
	movq	%rsi, %xmm0
	addq	$192, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	punpcklqdq	%xmm6, %xmm0
	movq	%rdx, %xmm6
	movb	$0, 32(%r12)
	movups	%xmm0, (%r12)
	movq	%rax, %xmm0
	punpcklqdq	%xmm6, %xmm0
	movdqu	(%rdi), %xmm6
	movups	%xmm0, 16(%r12)
	movups	%xmm6, 34(%r12)
.LEHB0:
	call	_ZNK8opendnp317EventBufferConfig11TotalEventsEv@PLT
	movq	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE@GOTPCREL(%rip), %r14
	pxor	%xmm0, %xmm0
	movl	$0, 56(%r12)
	movl	%eax, %ebx
	movl	%eax, 96(%r12)
	leaq	16(%r14), %rdx
	movq	%rbx, %rdi
	movups	%xmm0, 64(%r12)
	movq	$0, 80(%r12)
	salq	$6, %rdi
	movq	%rdx, 88(%r12)
	call	_Znam@PLT
.LEHE0:
	movq	%rax, %r13
	testq	%rbx, %rbx
	je	.L38
	leaq	-1(%rbx), %rbp
	movq	%rax, %rbx
	.p2align 4,,10
	.p2align 3
.L39:
	movq	%rbx, %rdi
.LEHB1:
	call	_ZN8opendnp39SOERecordC1Ev@PLT
.LEHE1:
	pxor	%xmm7, %xmm7
	addq	$64, %rbx
	movups	%xmm7, -16(%rbx)
	subq	$1, %rbp
	jnb	.L39
.L38:
	movl	96(%r12), %edx
	movq	%r13, 104(%r12)
	testl	%edx, %edx
	je	.L41
	movq	%r13, 80(%r12)
	cmpl	$1, %edx
	je	.L41
	leal	-2(%rdx), %eax
	leal	-1(%rdx), %esi
	cmpl	$9, %eax
	jbe	.L48
	movl	%esi, %ecx
	movq	%r13, %xmm5
	pcmpeqd	%xmm7, %xmm7
	movq	%r13, %rax
	shrl	$2, %ecx
	movdqa	.LC0(%rip), %xmm6
	punpcklqdq	%xmm5, %xmm5
	movdqa	.LC1(%rip), %xmm8
	salq	$8, %rcx
	movdqa	.LC2(%rip), %xmm4
	addq	%r13, %rcx
	.p2align 4,,10
	.p2align 3
.L44:
	movdqa	%xmm6, %xmm0
	addq	$256, %rax
	paddd	%xmm8, %xmm6
	movdqa	%xmm0, %xmm3
	movdqa	%xmm0, %xmm2
	punpckldq	%xmm0, %xmm3
	punpckhdq	%xmm0, %xmm2
	paddd	%xmm7, %xmm0
	pmuludq	%xmm4, %xmm3
	pmuludq	%xmm4, %xmm2
	movdqa	%xmm0, %xmm1
	punpckldq	%xmm0, %xmm1
	punpckhdq	%xmm0, %xmm0
	pmuludq	%xmm4, %xmm1
	pmuludq	%xmm4, %xmm0
	paddq	%xmm5, %xmm3
	paddq	%xmm5, %xmm2
	movq	%xmm3, -200(%rax)
	paddq	%xmm5, %xmm1
	paddq	%xmm5, %xmm0
	movq	%xmm2, -72(%rax)
	movhps	%xmm3, -136(%rax)
	movhps	%xmm2, -8(%rax)
	movq	%xmm1, -144(%rax)
	movhps	%xmm1, -80(%rax)
	movq	%xmm0, -16(%rax)
	movhps	%xmm0, 48(%rax)
	cmpq	%rcx, %rax
	jne	.L44
	movl	%esi, %ecx
	andl	$-4, %ecx
	leal	1(%rcx), %eax
	cmpl	%ecx, %esi
	je	.L41
.L43:
	movl	%eax, %esi
	leal	-1(%rax), %ecx
	salq	$6, %rsi
	salq	$6, %rcx
	addq	%r13, %rcx
	addq	%r13, %rsi
	movq	%rsi, 56(%rcx)
	movq	%rcx, 48(%rsi)
	leal	1(%rax), %ecx
	cmpl	%ecx, %edx
	jbe	.L41
	salq	$6, %rcx
	addq	%r13, %rcx
	movq	%rcx, 56(%rsi)
	movq	%rsi, 48(%rcx)
	leal	2(%rax), %esi
	cmpl	%esi, %edx
	jbe	.L41
	salq	$6, %rsi
	addq	%r13, %rsi
	movq	%rsi, 56(%rcx)
	movq	%rcx, 48(%rsi)
	leal	3(%rax), %ecx
	cmpl	%ecx, %edx
	jbe	.L41
	salq	$6, %rcx
	addq	%r13, %rcx
	movq	%rcx, 56(%rsi)
	movq	%rsi, 48(%rcx)
	leal	4(%rax), %esi
	cmpl	%esi, %edx
	jbe	.L41
	salq	$6, %rsi
	addq	%r13, %rsi
	movq	%rsi, 56(%rcx)
	movq	%rcx, 48(%rsi)
	leal	5(%rax), %ecx
	cmpl	%ecx, %edx
	jbe	.L41
	salq	$6, %rcx
	addq	%r13, %rcx
	movq	%rcx, 56(%rsi)
	movq	%rsi, 48(%rcx)
	leal	6(%rax), %esi
	cmpl	%esi, %edx
	jbe	.L41
	salq	$6, %rsi
	addq	%r13, %rsi
	movq	%rsi, 56(%rcx)
	movq	%rcx, 48(%rsi)
	leal	7(%rax), %ecx
	cmpl	%ecx, %edx
	jbe	.L41
	salq	$6, %rcx
	addq	%r13, %rcx
	movq	%rcx, 56(%rsi)
	movq	%rsi, 48(%rcx)
	leal	8(%rax), %esi
	cmpl	%esi, %edx
	jbe	.L41
	salq	$6, %rsi
	addl	$9, %eax
	addq	%r13, %rsi
	movq	%rsi, 56(%rcx)
	movq	%rcx, 48(%rsi)
	cmpl	%eax, %edx
	jbe	.L41
	salq	$6, %rax
	addq	%rax, %r13
	movq	%r13, 56(%rsi)
	movq	%rsi, 48(%r13)
	.p2align 4,,10
	.p2align 3
.L41:
	leaq	112(%r12), %rdi
.LEHB2:
	call	_ZN8opendnp310EventCountC1Ev@PLT
	leaq	160(%r12), %rdi
	call	_ZN8opendnp310EventCountC1Ev@PLT
	leaq	208(%r12), %rdi
	call	_ZN8opendnp310EventCountC1Ev@PLT
.LEHE2:
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
.L48:
	.cfi_restore_state
	movl	$1, %eax
	jmp	.L43
.L50:
	movq	%rax, %rbp
	jmp	.L42
.L49:
	movq	%rax, %rbp
	jmp	.L46
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA415:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE415-.LLSDACSB415
.LLSDACSB415:
	.uleb128 .LEHB0-.LFB415
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB415
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L50-.LFB415
	.uleb128 0
	.uleb128 .LEHB2-.LFB415
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L49-.LFB415
	.uleb128 0
.LLSDACSE415:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC415
	.type	_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE.cold, @function
_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE.cold:
.LFSB415:
.L42:
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	.cfi_offset 6, -40
	.cfi_offset 12, -32
	.cfi_offset 13, -24
	.cfi_offset 14, -16
	movq	%r13, %rdi
	call	_ZdaPv@PLT
	movq	%rbp, %rdi
.LEHB3:
	call	_Unwind_Resume@PLT
.L46:
	movq	104(%r12), %rdi
	leaq	16(%r14), %rax
	movq	%rax, 88(%r12)
	testq	%rdi, %rdi
	je	.L47
	call	_ZdaPv@PLT
.L47:
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE3:
	.cfi_endproc
.LFE415:
	.section	.gcc_except_table
.LLSDAC415:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC415-.LLSDACSBC415
.LLSDACSBC415:
	.uleb128 .LEHB3-.LCOLDB3
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSEC415:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE, .-_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE.cold, .-_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE.cold
.LCOLDE3:
	.text
.LHOTE3:
	.globl	_ZN8opendnp311EventBufferC1ERKNS_17EventBufferConfigE
	.set	_ZN8opendnp311EventBufferC1ERKNS_17EventBufferConfigE,_ZN8opendnp311EventBufferC2ERKNS_17EventBufferConfigE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer19UnwrittenClassFieldEv
	.type	_ZNK8opendnp311EventBuffer19UnwrittenClassFieldEv, @function
_ZNK8opendnp311EventBuffer19UnwrittenClassFieldEv:
.LFB426:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$2, %esi
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
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	leaq	112(%rdi), %rbx
	addq	$208, %rbp
	movq	%rbx, %rdi
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r14d
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	movq	%rbx, %rdi
	movl	$1, %esi
	movl	%eax, %r15d
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	%eax, %r12d
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	xorl	%esi, %esi
	movq	%rbp, %rdi
	movl	%eax, %ebx
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10EventClassE@PLT
	xorl	%r8d, %r8d
	cmpl	%r15d, %r14d
	leaq	7(%rsp), %rdi
	setne	%r8b
	xorl	%ecx, %ecx
	cmpl	%r12d, %r13d
	setne	%cl
	xorl	%edx, %edx
	cmpl	%eax, %ebx
	setne	%dl
	xorl	%esi, %esi
	call	_ZN8opendnp310ClassFieldC1Ebbbb@PLT
	movzbl	7(%rsp), %eax
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L67
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
.L67:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE426:
	.size	_ZNK8opendnp311EventBuffer19UnwrittenClassFieldEv, .-_ZNK8opendnp311EventBuffer19UnwrittenClassFieldEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj
	.type	_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj, @function
_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj:
.LFB428:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	addq	$112, %rdi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r14
	addq	$160, %r15
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movl	%edx, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movzbl	(%rsi), %esi
	movq	-48(%rdi), %rbx
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10ClassFieldE@PLT
	movzbl	(%r14), %esi
	movq	%r15, %rdi
	movl	%eax, %r12d
	call	_ZNK8opendnp310EventCount10NumOfClassENS_10ClassFieldE@PLT
	subl	%eax, %r12d
	testq	%rbx, %rbx
	je	.L76
	cmpl	%ebp, %r12d
	cmova	%ebp, %r12d
	xorl	%r13d, %r13d
	testl	%r12d, %r12d
	jne	.L70
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L71:
	testq	%rbx, %rbx
	je	.L76
.L86:
	cmpl	%r12d, %r13d
	jnb	.L76
.L70:
	movq	%rbx, %rbp
	movq	%r14, %rdi
	movq	56(%rbx), %rbx
	movzbl	2(%rbp), %esi
	call	_ZNK8opendnp310ClassField12HasEventTypeENS_10EventClassE@PLT
	testb	%al, %al
	je	.L71
	movq	%rbp, %rdi
	addl	$1, %r13d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%rbp), %esi
	movzwl	0(%rbp), %edx
	movq	%r15, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	testq	%rbx, %rbx
	jne	.L86
.L76:
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
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
	.cfi_endproc
.LFE428:
	.size	_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj, .-_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj
	.type	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj, @function
_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj:
.LFB421:
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
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$16, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpw	$8200, %si
	ja	.L88
	cmpw	$8191, %si
	ja	.L89
	cmpw	$2818, %si
	je	.L90
	jbe	.L617
	cmpw	$5638, %si
	jbe	.L618
	subw	$5888, %si
	cmpw	$6, %si
	ja	.L98
	leaq	.L120(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L120:
	.long	.L124-.L120
	.long	.L123-.L120
	.long	.L122-.L120
	.long	.L98-.L120
	.long	.L98-.L120
	.long	.L121-.L120
	.long	.L119-.L120
	.text
	.p2align 4,,10
	.p2align 3
.L88:
	cmpw	$10760, %si
	ja	.L141
	cmpw	$10751, %si
	jbe	.L98
	subw	$10753, %si
	cmpw	$7, %si
	ja	.L99
	movzwl	%si, %esi
	leaq	.L101(%rip), %rdx
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movslq	(%rdx,%rsi,4), %rax
	movl	$6, %esi
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L101:
	.long	.L108-.L101
	.long	.L107-.L101
	.long	.L106-.L101
	.long	.L105-.L101
	.long	.L104-.L101
	.long	.L103-.L101
	.long	.L102-.L101
	.long	.L100-.L101
	.text
	.p2align 4,,10
	.p2align 3
.L618:
	cmpw	$5631, %si
	ja	.L619
.L98:
	xorl	%eax, %eax
	leaq	6(%rsp), %rdi
	movl	$8, %esi
	movw	%ax, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L152:
	movq	8(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L620
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
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
.L619:
	.cfi_restore_state
	subw	$5632, %si
	cmpw	$6, %si
	ja	.L98
	leaq	.L126(%rip), %rdx
	movzwl	%si, %esi
	movslq	(%rdx,%rsi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L126:
	.long	.L130-.L126
	.long	.L129-.L126
	.long	.L128-.L126
	.long	.L98-.L126
	.long	.L98-.L126
	.long	.L127-.L126
	.long	.L125-.L126
	.text
	.p2align 4,,10
	.p2align 3
.L141:
	cmpw	$31232, %si
	je	.L143
	jbe	.L621
	cmpw	$31233, %si
	je	.L148
	cmpw	$31234, %si
	jne	.L98
	movq	64(%rdi), %rbx
	movl	$7, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r14
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$7, %esi
	movq	%r14, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	%eax, %r8d
	movl	%r13d, %eax
	subl	%r8d, %eax
	testq	%rbx, %rbx
	je	.L150
	cmpl	%eax, %r12d
	cmova	%eax, %r12d
	xorl	%r13d, %r13d
	testl	%r12d, %r12d
	jne	.L234
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L622:
	cmpl	%r12d, %r13d
	jnb	.L150
.L234:
	movq	%rbx, %rbp
	movq	56(%rbx), %rbx
	cmpw	$7, 0(%rbp)
	jne	.L235
	movl	$1, %esi
	movq	%rbp, %rdi
	addl	$1, %r13d
	call	_ZN8opendnp39SOERecord6SelectENS_26EventSecurityStatVariationE@PLT
	movzbl	2(%rbp), %esi
	movzwl	0(%rbp), %edx
	movq	%r14, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L235:
	testq	%rbx, %rbx
	jne	.L622
	.p2align 4,,10
	.p2align 3
.L150:
	xorl	%eax, %eax
	jmp	.L152
.L621:
	cmpw	$15363, %si
	je	.L145
	cmpw	$15364, %si
	jne	.L623
	leaq	6(%rsp), %r13
	movl	$8, %esi
.L575:
	movq	%r13, %rdi
	call	_ZN8opendnp310ClassFieldC1ENS_10PointClassE@PLT
	movl	%r12d, %edx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj@PLT
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L617:
	cmpw	$1025, %si
	je	.L92
	jbe	.L624
	cmpw	$2816, %si
	je	.L133
	jbe	.L625
	cmpw	$2817, %si
	jne	.L98
	movq	64(%rdi), %rbx
	movl	$5, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$5, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L170
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L626:
	cmpl	%r14d, %r13d
	jbe	.L150
.L170:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$5, (%r12)
	jne	.L171
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventBinaryOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L171:
	testq	%rbx, %rbx
	jne	.L626
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L89:
	subw	$8193, %si
	cmpw	$7, %si
	ja	.L109
	movzwl	%si, %esi
	leaq	.L111(%rip), %rdx
	movq	64(%rdi), %rbx
	leaq	112(%rdi), %rdi
	movslq	(%rdx,%rsi,4), %rax
	movl	$1, %esi
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L111:
	.long	.L118-.L111
	.long	.L117-.L111
	.long	.L116-.L111
	.long	.L115-.L111
	.long	.L114-.L111
	.long	.L113-.L111
	.long	.L112-.L111
	.long	.L110-.L111
	.text
.L623:
	cmpw	$15362, %si
	jne	.L98
	leaq	6(%rsp), %r13
	movl	$2, %esi
	jmp	.L575
	.p2align 4,,10
	.p2align 3
.L625:
	cmpw	$1026, %si
	je	.L135
	cmpw	$1027, %si
	jne	.L98
	movq	64(%rdi), %rbx
	movl	$4, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$4, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L166
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L627:
	cmpl	%r14d, %r13d
	jbe	.L150
.L166:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$4, (%r12)
	jne	.L167
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_26EventDoubleBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L167:
	testq	%rbx, %rbx
	jne	.L627
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L624:
	cmpw	$514, %si
	je	.L94
	jbe	.L628
	cmpw	$515, %si
	je	.L131
	cmpw	$1024, %si
	jne	.L98
	movq	64(%rdi), %rbx
	movl	$4, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$4, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L160
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L629:
	cmpl	%r14d, %r13d
	jbe	.L150
.L160:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$4, (%r12)
	jne	.L161
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L161:
	testq	%rbx, %rbx
	jne	.L629
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L628:
	cmpw	$512, %si
	je	.L96
	cmpw	$513, %si
	jne	.L98
	movq	64(%rdi), %rbx
	xorl	%esi, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r14
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	xorl	%esi, %esi
	movq	%r14, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%ebp, %ebp
	testl	%r13d, %r13d
	jne	.L154
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L630:
	cmpl	%ebp, %r13d
	jbe	.L150
.L154:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$0, (%r12)
	jne	.L155
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %ebp
	call	_ZN8opendnp39SOERecord6SelectENS_20EventBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%r14, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L155:
	testq	%rbx, %rbx
	jne	.L630
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L119:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$3, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$3, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L192
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L631:
	cmpl	%r14d, %r13d
	jbe	.L150
.L192:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$3, (%r12)
	jne	.L193
	movl	$3, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_27EventFrozenCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L193:
	testq	%rbx, %rbx
	jne	.L631
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L121:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$3, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$3, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L190
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L632:
	cmpl	%r14d, %r13d
	jbe	.L150
.L190:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$3, (%r12)
	jne	.L191
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_27EventFrozenCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L191:
	testq	%rbx, %rbx
	jne	.L632
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L122:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$3, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$3, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L188
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L633:
	cmpl	%r14d, %r13d
	jbe	.L150
.L188:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$3, (%r12)
	jne	.L189
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_27EventFrozenCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L189:
	testq	%rbx, %rbx
	jne	.L633
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L123:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$3, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$3, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L186
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L634:
	cmpl	%r14d, %r13d
	jbe	.L150
.L186:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$3, (%r12)
	jne	.L187
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_27EventFrozenCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L187:
	testq	%rbx, %rbx
	jne	.L634
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L124:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$3, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$3, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L184
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L635:
	cmpl	%r14d, %r13d
	jbe	.L150
.L184:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$3, (%r12)
	jne	.L185
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L185:
	testq	%rbx, %rbx
	jne	.L635
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L125:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$2, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L182
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L636:
	cmpl	%r14d, %r13d
	jbe	.L150
.L182:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$2, (%r12)
	jne	.L183
	movl	$3, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_21EventCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L183:
	testq	%rbx, %rbx
	jne	.L636
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L127:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$2, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L180
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L637:
	cmpl	%r14d, %r13d
	jbe	.L150
.L180:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$2, (%r12)
	jne	.L181
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_21EventCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L181:
	testq	%rbx, %rbx
	jne	.L637
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L128:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$2, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L178
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L638:
	cmpl	%r14d, %r13d
	jbe	.L150
.L178:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$2, (%r12)
	jne	.L179
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_21EventCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L179:
	testq	%rbx, %rbx
	jne	.L638
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L129:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$2, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L176
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L639:
	cmpl	%r14d, %r13d
	jbe	.L150
.L176:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$2, (%r12)
	jne	.L177
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_21EventCounterVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L177:
	testq	%rbx, %rbx
	jne	.L639
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L130:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$2, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$2, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L174
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L640:
	cmpl	%r14d, %r13d
	jbe	.L150
.L174:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$2, (%r12)
	jne	.L175
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L175:
	testq	%rbx, %rbx
	jne	.L640
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L105:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L220
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L641:
	cmpl	%r13d, %r14d
	jnb	.L150
.L220:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L221
	movl	$3, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L221:
	testq	%rbx, %rbx
	jne	.L641
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L106:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L218
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L642:
	cmpl	%r13d, %r14d
	jnb	.L150
.L218:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L219
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L219:
	testq	%rbx, %rbx
	jne	.L642
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L107:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L216
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L643:
	cmpl	%r13d, %r14d
	jnb	.L150
.L216:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L217
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L217:
	testq	%rbx, %rbx
	jne	.L643
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L108:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L214
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L644:
	cmpl	%r13d, %r14d
	jnb	.L150
.L214:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L215
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L215:
	testq	%rbx, %rbx
	jne	.L644
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L103:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L224
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L645:
	cmpl	%r13d, %r14d
	jnb	.L150
.L224:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L225
	movl	$5, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L225:
	testq	%rbx, %rbx
	jne	.L645
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L104:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L222
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L646:
	cmpl	%r13d, %r14d
	jnb	.L150
.L222:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L223
	movl	$4, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L223:
	testq	%rbx, %rbx
	jne	.L646
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L110:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L210
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L647:
	cmpl	%r13d, %r14d
	jnb	.L150
.L210:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L211
	movl	$7, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L211:
	testq	%rbx, %rbx
	jne	.L647
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L102:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L226
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L648:
	cmpl	%r13d, %r14d
	jnb	.L150
.L226:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L227
	movl	$6, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L227:
	testq	%rbx, %rbx
	jne	.L648
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L100:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L228
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L649:
	cmpl	%r13d, %r14d
	jnb	.L150
.L228:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L229
	movl	$7, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventAnalogOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L229:
	testq	%rbx, %rbx
	jne	.L649
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L113:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L206
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L650:
	cmpl	%r13d, %r14d
	jnb	.L150
.L206:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L207
	movl	$5, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L207:
	testq	%rbx, %rbx
	jne	.L650
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L114:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L204
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L651:
	cmpl	%r13d, %r14d
	jnb	.L150
.L204:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L205
	movl	$4, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L205:
	testq	%rbx, %rbx
	jne	.L651
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L115:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L202
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L652:
	cmpl	%r13d, %r14d
	jnb	.L150
.L202:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L203
	movl	$3, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L203:
	testq	%rbx, %rbx
	jne	.L652
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L116:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L200
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L653:
	cmpl	%r13d, %r14d
	jnb	.L150
.L200:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L201
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L201:
	testq	%rbx, %rbx
	jne	.L653
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L117:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L198
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L654:
	cmpl	%r13d, %r14d
	jnb	.L150
.L198:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L199
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L199:
	testq	%rbx, %rbx
	jne	.L654
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L118:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L196
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L655:
	cmpl	%r14d, %r13d
	jbe	.L150
.L196:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L197
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L197:
	testq	%rbx, %rbx
	jne	.L655
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L112:
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	addq	$160, %rbp
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L208
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L656:
	cmpl	%r13d, %r14d
	jnb	.L150
.L208:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L209
	movl	$6, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_20EventAnalogVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L209:
	testq	%rbx, %rbx
	jne	.L656
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L96:
	movq	64(%rdi), %rbx
	xorl	%esi, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r14
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	xorl	%esi, %esi
	movq	%r14, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%ebp, %ebp
	testl	%r13d, %r13d
	jne	.L151
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L657:
	cmpl	%ebp, %r13d
	jbe	.L150
.L151:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$0, (%r12)
	jne	.L153
	movq	%r12, %rdi
	addl	$1, %ebp
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%r14, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L153:
	testq	%rbx, %rbx
	jne	.L657
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L145:
	leaq	6(%rsp), %r13
	movl	$4, %esi
	jmp	.L575
	.p2align 4,,10
	.p2align 3
.L99:
	movq	64(%rbp), %rbx
	leaq	112(%rbp), %rdi
	movl	$6, %esi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$6, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L212
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L658:
	cmpl	%r13d, %r14d
	jnb	.L150
.L212:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$6, (%r12)
	jne	.L213
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L213:
	testq	%rbx, %rbx
	jne	.L658
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L94:
	movq	64(%rdi), %rbx
	xorl	%esi, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r14
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	xorl	%esi, %esi
	movq	%r14, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%ebp, %ebp
	testl	%r13d, %r13d
	jne	.L156
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L659:
	cmpl	%ebp, %r13d
	jbe	.L150
.L156:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$0, (%r12)
	jne	.L157
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %ebp
	call	_ZN8opendnp39SOERecord6SelectENS_20EventBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%r14, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L157:
	testq	%rbx, %rbx
	jne	.L659
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L135:
	movq	64(%rdi), %rbx
	movl	$4, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$4, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L164
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L660:
	cmpl	%r14d, %r13d
	jbe	.L150
.L164:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$4, (%r12)
	jne	.L165
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_26EventDoubleBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L165:
	testq	%rbx, %rbx
	jne	.L660
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L92:
	movq	64(%rdi), %rbx
	movl	$4, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$4, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L162
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L661:
	cmpl	%r14d, %r13d
	jbe	.L150
.L162:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$4, (%r12)
	jne	.L163
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_26EventDoubleBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L163:
	testq	%rbx, %rbx
	jne	.L661
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L109:
	movq	64(%rdi), %rbx
	movl	$1, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$1, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L194
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L662:
	cmpl	%r14d, %r13d
	jbe	.L150
.L194:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$1, (%r12)
	jne	.L195
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L195:
	testq	%rbx, %rbx
	jne	.L662
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L133:
	movq	64(%rdi), %rbx
	movl	$5, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$5, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L168
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L663:
	cmpl	%r14d, %r13d
	jbe	.L150
.L168:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$5, (%r12)
	jne	.L169
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L169:
	testq	%rbx, %rbx
	jne	.L663
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L131:
	movq	64(%rdi), %rbx
	xorl	%esi, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r14
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	xorl	%esi, %esi
	movq	%r14, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%ebp, %ebp
	testl	%r13d, %r13d
	jne	.L158
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L664:
	cmpl	%ebp, %r13d
	jbe	.L150
.L158:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$0, (%r12)
	jne	.L159
	movl	$2, %esi
	movq	%r12, %rdi
	addl	$1, %ebp
	call	_ZN8opendnp39SOERecord6SelectENS_20EventBinaryVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%r14, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L159:
	testq	%rbx, %rbx
	jne	.L664
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L148:
	movq	64(%rdi), %rbx
	movl	$7, %esi
	leaq	112(%rdi), %rdi
	leaq	160(%rbp), %r13
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$7, %esi
	movq	%r13, %rdi
	movl	%eax, %r14d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	%eax, %r8d
	movl	%r14d, %eax
	subl	%r8d, %eax
	testq	%rbx, %rbx
	je	.L150
	cmpl	%eax, %r12d
	cmovbe	%r12d, %eax
	xorl	%r14d, %r14d
	movl	%eax, %ebp
	testl	%eax, %eax
	jne	.L232
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L665:
	cmpl	%ebp, %r14d
	jnb	.L150
.L232:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$7, (%r12)
	jne	.L233
	xorl	%esi, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_26EventSecurityStatVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%r13, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L233:
	testq	%rbx, %rbx
	jne	.L665
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L143:
	movq	64(%rdi), %rbx
	movl	$7, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$7, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L230
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L666:
	cmpl	%r13d, %r14d
	jnb	.L150
.L230:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$7, (%r12)
	jne	.L231
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord13SelectDefaultEv@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L231:
	testq	%rbx, %rbx
	jne	.L666
	xorl	%eax, %eax
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L90:
	movq	64(%rdi), %rbx
	movl	$5, %esi
	leaq	112(%rdi), %rdi
	addq	$160, %rbp
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	movl	$5, %esi
	movq	%rbp, %rdi
	movl	%eax, %r13d
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	subl	%eax, %r13d
	testq	%rbx, %rbx
	je	.L150
	cmpl	%r13d, %r12d
	cmovbe	%r12d, %r13d
	xorl	%r14d, %r14d
	testl	%r13d, %r13d
	jne	.L172
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L667:
	cmpl	%r14d, %r13d
	jbe	.L150
.L172:
	movq	%rbx, %r12
	movq	56(%rbx), %rbx
	cmpw	$5, (%r12)
	jne	.L173
	movl	$1, %esi
	movq	%r12, %rdi
	addl	$1, %r14d
	call	_ZN8opendnp39SOERecord6SelectENS_32EventBinaryOutputStatusVariationE@PLT
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	movq	%rbp, %rdi
	call	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
.L173:
	testq	%rbx, %rbx
	jne	.L667
	xorl	%eax, %eax
	jmp	.L152
.L620:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE421:
	.size	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj, .-_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.type	_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE, @function
_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE:
.LFB419:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%esi, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZN7openpal8MaxValueIjEET_v@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movl	%ebx, %esi
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	movl	%eax, %edx
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj@PLT
	.cfi_endproc
.LFE419:
	.size	_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE, .-_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.type	_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt, @function
_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt:
.LFB420:
	.cfi_startproc
	movzwl	%dx, %edx
	jmp	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj@PLT
	.cfi_endproc
.LFE420:
	.size	_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt, .-_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.p2align 4
	.globl	_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.type	_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt, @function
_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt:
.LFB532:
	.cfi_startproc
	movzwl	%dx, %edx
	subq	$8, %rdi
	jmp	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj@PLT
	.cfi_endproc
.LFE532:
	.size	_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt, .-_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.p2align 4
	.globl	_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.type	_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE, @function
_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE:
.LFB534:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZN7openpal8MaxValueIjEET_v@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	leaq	-8(%rbx), %rdi
	movl	%ebp, %esi
	popq	%rbx
	.cfi_def_cfa_offset 16
	movl	%eax, %edx
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311EventBuffer14SelectMaxCountENS_14GroupVariationEj@PLT
	.cfi_endproc
.LFE534:
	.size	_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE, .-_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE
	.type	_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE, @function
_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE:
.LFB429:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	addq	$112, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movzbl	2(%rsi), %esi
	movzwl	(%rbx), %edx
	call	_ZN8opendnp310EventCount9DecrementENS_10EventClassENS_9EventTypeE@PLT
	cmpb	$0, 3(%rbx)
	jne	.L678
	cmpb	$0, 4(%rbx)
	jne	.L679
.L674:
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
.L678:
	.cfi_restore_state
	movzbl	2(%rbx), %esi
	movzwl	(%rbx), %edx
	leaq	160(%rbp), %rdi
	call	_ZN8opendnp310EventCount9DecrementENS_10EventClassENS_9EventTypeE@PLT
	cmpb	$0, 4(%rbx)
	je	.L674
.L679:
	movzbl	2(%rbx), %esi
	movzwl	(%rbx), %edx
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	leaq	208(%rbp), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9DecrementENS_10EventClassENS_9EventTypeE@PLT
	.cfi_endproc
.LFE429:
	.size	_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE, .-_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE
	.type	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE, @function
_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE:
.LFB430:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	64(%rdi), %rbp
	jmp	.L683
	.p2align 4,,10
	.p2align 3
.L700:
	movq	56(%rbp), %rax
	cmpw	0(%rbp), %si
	je	.L682
	movq	%rax, %rbp
.L683:
	testq	%rbp, %rbp
	jne	.L700
	xorl	%eax, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L682:
	.cfi_restore_state
	movq	48(%rbp), %rdx
	testq	%rdx, %rdx
	je	.L701
	testq	%rax, %rax
	je	.L702
.L685:
	movq	%rax, 56(%rdx)
.L688:
	testq	%rax, %rax
	je	.L686
	movq	%rdx, 48(%rax)
.L686:
	movq	80(%rdi), %rax
	movq	%rax, 56(%rbp)
	testq	%rax, %rax
	je	.L687
	movq	%rbp, 48(%rax)
.L687:
	movq	$0, 48(%rbp)
	movq	%rbp, %rsi
	subl	$1, 56(%rdi)
	movq	%rbp, 80(%rdi)
	call	_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE@PLT
	movq	%rbp, %rdi
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movl	$1, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L701:
	.cfi_restore_state
	testq	%rax, %rax
	je	.L703
.L684:
	movq	%rax, 64(%rdi)
	jmp	.L688
	.p2align 4,,10
	.p2align 3
.L702:
	movq	%rdx, 72(%rdi)
	jmp	.L685
.L703:
	movq	$0, 72(%rdi)
	jmp	.L684
	.cfi_endproc
.LFE430:
	.size	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE, .-_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE:
.LFB387:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$6, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L718
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L717
	addq	$72, %rsp
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
.L718:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$6, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L706
	cmpq	$0, 80(%rbx)
	je	.L706
.L707:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_18AnalogOutputStatusEtNS_10EventClassENS_32EventAnalogOutputStatusVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L708
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L709
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L711:
	movq	%rdi, 72(%rbx)
.L708:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L717
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$6, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L709:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L711
	.p2align 4,,10
	.p2align 3
.L706:
	movb	$1, 32(%rbx)
	movl	$6, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L707
.L717:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE387:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE:
.LFB386:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$5, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L733
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L732
	addq	$72, %rsp
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
.L733:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$5, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L721
	cmpq	$0, 80(%rbx)
	je	.L721
.L722:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_18BinaryOutputStatusEtNS_10EventClassENS_32EventBinaryOutputStatusVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L723
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L724
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L726:
	movq	%rdi, 72(%rbx)
.L723:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L732
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$5, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L724:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L726
	.p2align 4,,10
	.p2align 3
.L721:
	movb	$1, 32(%rbx)
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L722
.L732:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE386:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE:
.LFB385:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$3, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L748
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L747
	addq	$72, %rsp
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
.L748:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$3, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L736
	cmpq	$0, 80(%rbx)
	je	.L736
.L737:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_13FrozenCounterEtNS_10EventClassENS_27EventFrozenCounterVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L738
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L739
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L741:
	movq	%rdi, 72(%rbx)
.L738:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L747
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$3, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L739:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L741
	.p2align 4,,10
	.p2align 3
.L736:
	movb	$1, 32(%rbx)
	movl	$3, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L737
.L747:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE385:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE:
.LFB384:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$2, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L763
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L762
	addq	$72, %rsp
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
.L763:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$2, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L751
	cmpq	$0, 80(%rbx)
	je	.L751
.L752:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_7CounterEtNS_10EventClassENS_21EventCounterVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L753
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L754
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L756:
	movq	%rdi, 72(%rbx)
.L753:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L762
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$2, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L754:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L756
	.p2align 4,,10
	.p2align 3
.L751:
	movb	$1, 32(%rbx)
	movl	$2, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L752
.L762:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE384:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE:
.LFB383:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$1, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L778
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L777
	addq	$72, %rsp
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
.L778:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$1, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L766
	cmpq	$0, 80(%rbx)
	je	.L766
.L767:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_6AnalogEtNS_10EventClassENS_20EventAnalogVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L768
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L769
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L771:
	movq	%rdi, 72(%rbx)
.L768:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L777
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$1, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L769:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L771
	.p2align 4,,10
	.p2align 3
.L766:
	movb	$1, 32(%rbx)
	movl	$1, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L767
.L777:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE383:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE:
.LFB382:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	movl	$4, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L793
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L792
	addq	$72, %rsp
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
.L793:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	movl	$4, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L781
	cmpq	$0, 80(%rbx)
	je	.L781
.L782:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_15DoubleBitBinaryEtNS_10EventClassENS_26EventDoubleBinaryVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L783
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L784
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L786:
	movq	%rdi, 72(%rbx)
.L783:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L792
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$4, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L784:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L786
	.p2align 4,,10
	.p2align 3
.L781:
	movb	$1, 32(%rbx)
	movl	$4, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L782
.L792:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE382:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE
	.section	.text._ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE,"axG",@progbits,_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE
	.type	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE, @function
_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE:
.LFB381:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rsi, %r12
	xorl	%esi, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	addq	$34, %rdi
	subq	$72, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebp
	testw	%bp, %bp
	jne	.L808
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L807
	addq	$72, %rsp
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
.L808:
	.cfi_restore_state
	leaq	112(%rbx), %r13
	xorl	%esi, %esi
	movq	%r13, %rdi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%ebp, %eax
	jnb	.L796
	cmpq	$0, 80(%rbx)
	je	.L796
.L797:
	movzbl	2(%r12), %ecx
	movzwl	(%r12), %edx
	movq	%rsp, %rdi
	leaq	8(%r12), %rsi
	movzbl	32(%r12), %r8d
	call	_ZN8opendnp39SOERecordC1ERKNS_6BinaryEtNS_10EventClassENS_20EventBinaryVariationE@PLT
	movq	80(%rbx), %rdi
	movq	72(%rbx), %rax
	testq	%rdi, %rdi
	je	.L798
	movdqu	(%rsp), %xmm1
	movq	56(%rdi), %rdx
	movq	%rdx, 80(%rbx)
	movups	%xmm1, (%rdi)
	movdqu	16(%rsp), %xmm2
	movups	%xmm2, 16(%rdi)
	movq	32(%rsp), %rdx
	movq	%rdx, 32(%rdi)
	movzbl	40(%rsp), %edx
	movb	%dl, 40(%rdi)
	addl	$1, 56(%rbx)
	testq	%rax, %rax
	je	.L799
	movq	%rdi, 56(%rax)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
.L801:
	movq	%rdi, 72(%rbx)
.L798:
	call	_ZN8opendnp39SOERecord5ResetEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L807
	movzbl	2(%r12), %esi
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	xorl	%edx, %edx
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp310EventCount9IncrementENS_10EventClassENS_9EventTypeE@PLT
	.p2align 4,,10
	.p2align 3
.L799:
	.cfi_restore_state
	pxor	%xmm0, %xmm0
	movups	%xmm0, 48(%rdi)
	movq	%rdi, 64(%rbx)
	jmp	.L801
	.p2align 4,,10
	.p2align 3
.L796:
	movb	$1, 32(%rbx)
	xorl	%esi, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp311EventBuffer23RemoveOldestEventOfTypeENS_9EventTypeE@PLT
	jmp	.L797
.L807:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE381:
	.size	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE, .-_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer16SelectAllByClassERKNS_10ClassFieldE
	.type	_ZN8opendnp311EventBuffer16SelectAllByClassERKNS_10ClassFieldE, @function
_ZN8opendnp311EventBuffer16SelectAllByClassERKNS_10ClassFieldE:
.LFB432:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZN7openpal8MaxValueIjEET_v@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	%eax, %edx
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311EventBuffer13SelectByClassERKNS_10ClassFieldEj@PLT
	.cfi_endproc
.LFE432:
	.size	_ZN8opendnp311EventBuffer16SelectAllByClassERKNS_10ClassFieldE, .-_ZN8opendnp311EventBuffer16SelectAllByClassERKNS_10ClassFieldE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer12ClearWrittenEv
	.type	_ZN8opendnp311EventBuffer12ClearWrittenEv, @function
_ZN8opendnp311EventBuffer12ClearWrittenEv:
.LFB433:
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
	movq	64(%rdi), %rbx
	testq	%rbx, %rbx
	je	.L811
	movq	56(%rbx), %rbp
	movq	%rdi, %r12
	jmp	.L813
	.p2align 4,,10
	.p2align 3
.L842:
	testq	%rbp, %rbp
	je	.L811
	movq	56(%rbp), %rax
.L822:
	movq	%rbp, %rbx
	movq	%rax, %rbp
.L813:
	cmpb	$0, 4(%rbx)
	je	.L842
	movq	%rbx, %rsi
	movq	%r12, %rdi
	call	_ZN8opendnp311EventBuffer16RemoveFromCountsERKNS_9SOERecordE@PLT
	testq	%rbp, %rbp
	je	.L824
	movq	56(%rbp), %rax
.L816:
	movq	48(%rbx), %rcx
	movq	56(%rbx), %rdx
	testq	%rcx, %rcx
	je	.L843
	testq	%rdx, %rdx
	je	.L844
.L819:
	movq	%rdx, 56(%rcx)
.L823:
	testq	%rdx, %rdx
	je	.L820
	movq	%rcx, 48(%rdx)
.L820:
	movq	80(%r12), %rdx
	movq	%rdx, 56(%rbx)
	testq	%rdx, %rdx
	je	.L821
	movq	%rbx, 48(%rdx)
.L821:
	movq	$0, 48(%rbx)
	subl	$1, 56(%r12)
	movq	%rbx, 80(%r12)
	testq	%rbp, %rbp
	jne	.L822
.L811:
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
.L843:
	.cfi_restore_state
	testq	%rdx, %rdx
	je	.L845
.L818:
	movq	%rdx, 64(%r12)
	jmp	.L823
	.p2align 4,,10
	.p2align 3
.L844:
	movq	%rcx, 72(%r12)
	jmp	.L819
	.p2align 4,,10
	.p2align 3
.L824:
	xorl	%eax, %eax
	jmp	.L816
	.p2align 4,,10
	.p2align 3
.L845:
	movq	$0, 72(%r12)
	jmp	.L818
	.cfi_endproc
.LFE433:
	.size	_ZN8opendnp311EventBuffer12ClearWrittenEv, .-_ZN8opendnp311EventBuffer12ClearWrittenEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE
	.type	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE, @function
_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE:
.LFB435:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	addq	$34, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	_ZNK8opendnp317EventBufferConfig19GetMaxEventsForTypeENS_9EventTypeE@PLT
	movzwl	%ax, %ebx
	xorl	%eax, %eax
	testw	%bx, %bx
	jne	.L852
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
.L852:
	.cfi_restore_state
	leaq	112(%rbp), %rdi
	movl	%r12d, %esi
	call	_ZNK8opendnp310EventCount9NumOfTypeENS_9EventTypeE@PLT
	cmpl	%eax, %ebx
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	setbe	%al
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE435:
	.size	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE, .-_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv
	.type	_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv, @function
_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv:
.LFB436:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%esi, %esi
	movq	%rdi, %rbp
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	je	.L858
.L855:
	movl	$1, %eax
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L858:
	.cfi_restore_state
	movl	$4, %esi
	movq	%rbp, %rdi
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	jne	.L855
	movl	$5, %esi
	movq	%rbp, %rdi
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	jne	.L855
	movl	$2, %esi
	movq	%rbp, %rdi
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	jne	.L855
	movl	$3, %esi
	movq	%rbp, %rdi
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	jne	.L855
	movl	$1, %esi
	movq	%rbp, %rdi
	call	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	testb	%al, %al
	jne	.L855
	movq	%rbp, %rdi
	movl	$6, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZNK8opendnp311EventBuffer15IsTypeOverflownENS_9EventTypeE@PLT
	.cfi_endproc
.LFE436:
	.size	_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv, .-_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv
	.type	_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv, @function
_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv:
.LFB437:
	.cfi_startproc
	cmpq	$0, 80(%rdi)
	je	.L862
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZNK8opendnp311EventBuffer18IsAnyTypeOverflownEv@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	xorl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L862:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE437:
	.size	_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv, .-_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventBuffer11IsOverflownEv
	.type	_ZN8opendnp311EventBuffer11IsOverflownEv, @function
_ZN8opendnp311EventBuffer11IsOverflownEv:
.LFB427:
	.cfi_startproc
	movzbl	32(%rdi), %eax
	testb	%al, %al
	jne	.L877
	ret
	.p2align 4,,10
	.p2align 3
.L877:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	call	_ZNK8opendnp311EventBuffer29HasEnoughSpaceToClearOverflowEv@PLT
	testb	%al, %al
	je	.L878
	movb	$0, 32(%rbx)
	xorl	%eax, %eax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L878:
	.cfi_restore_state
	movzbl	32(%rbx), %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE427:
	.size	_ZN8opendnp311EventBuffer11IsOverflownEv, .-_ZN8opendnp311EventBuffer11IsOverflownEv
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_EventBuffer.cpp, @function
_GLOBAL__sub_I_EventBuffer.cpp:
.LFB525:
	.cfi_startproc
	movq	_ZGVN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	cmpb	$0, (%rax)
	je	.L885
	ret
.L885:
	pushq	%rdx
	.cfi_def_cfa_offset 16
	movb	$1, (%rax)
	call	_ZN7openpal8MaxValueItEET_v@PLT
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rdx
	movw	%ax, (%rdx)
	popq	%rcx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE525:
	.size	_GLOBAL__sub_I_EventBuffer.cpp, .-_GLOBAL__sub_I_EventBuffer.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_EventBuffer.cpp
	.weak	_ZTSN7openpal7HasSizeIjEE
	.section	.rodata._ZTSN7openpal7HasSizeIjEE,"aG",@progbits,_ZTSN7openpal7HasSizeIjEE,comdat
	.align 16
	.type	_ZTSN7openpal7HasSizeIjEE, @object
	.size	_ZTSN7openpal7HasSizeIjEE, 22
_ZTSN7openpal7HasSizeIjEE:
	.string	"N7openpal7HasSizeIjEE"
	.weak	_ZTIN7openpal7HasSizeIjEE
	.section	.data.rel.ro._ZTIN7openpal7HasSizeIjEE,"awG",@progbits,_ZTIN7openpal7HasSizeIjEE,comdat
	.align 8
	.type	_ZTIN7openpal7HasSizeIjEE, @object
	.size	_ZTIN7openpal7HasSizeIjEE, 16
_ZTIN7openpal7HasSizeIjEE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN7openpal7HasSizeIjEE
	.weak	_ZGVN7openpal7Bit16LEItE3MaxE
	.section	.bss._ZGVN7openpal7Bit16LEItE3MaxE,"awG",@nobits,_ZGVN7openpal7Bit16LEItE3MaxE,comdat
	.align 8
	.type	_ZGVN7openpal7Bit16LEItE3MaxE, @gnu_unique_object
	.size	_ZGVN7openpal7Bit16LEItE3MaxE, 8
_ZGVN7openpal7Bit16LEItE3MaxE:
	.zero	8
	.weak	_ZN7openpal7Bit16LEItE3MaxE
	.section	.bss._ZN7openpal7Bit16LEItE3MaxE,"awG",@nobits,_ZN7openpal7Bit16LEItE3MaxE,comdat
	.align 2
	.type	_ZN7openpal7Bit16LEItE3MaxE, @gnu_unique_object
	.size	_ZN7openpal7Bit16LEItE3MaxE, 2
_ZN7openpal7Bit16LEItE3MaxE:
	.zero	2
	.weak	_ZTSN8opendnp314IEventReceiverE
	.section	.rodata._ZTSN8opendnp314IEventReceiverE,"aG",@progbits,_ZTSN8opendnp314IEventReceiverE,comdat
	.align 16
	.type	_ZTSN8opendnp314IEventReceiverE, @object
	.size	_ZTSN8opendnp314IEventReceiverE, 28
_ZTSN8opendnp314IEventReceiverE:
	.string	"N8opendnp314IEventReceiverE"
	.weak	_ZTIN8opendnp314IEventReceiverE
	.section	.data.rel.ro._ZTIN8opendnp314IEventReceiverE,"awG",@progbits,_ZTIN8opendnp314IEventReceiverE,comdat
	.align 8
	.type	_ZTIN8opendnp314IEventReceiverE, @object
	.size	_ZTIN8opendnp314IEventReceiverE, 16
_ZTIN8opendnp314IEventReceiverE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp314IEventReceiverE
	.weak	_ZTSN8opendnp314IEventSelectorE
	.section	.rodata._ZTSN8opendnp314IEventSelectorE,"aG",@progbits,_ZTSN8opendnp314IEventSelectorE,comdat
	.align 16
	.type	_ZTSN8opendnp314IEventSelectorE, @object
	.size	_ZTSN8opendnp314IEventSelectorE, 28
_ZTSN8opendnp314IEventSelectorE:
	.string	"N8opendnp314IEventSelectorE"
	.weak	_ZTIN8opendnp314IEventSelectorE
	.section	.data.rel.ro._ZTIN8opendnp314IEventSelectorE,"awG",@progbits,_ZTIN8opendnp314IEventSelectorE,comdat
	.align 8
	.type	_ZTIN8opendnp314IEventSelectorE, @object
	.size	_ZTIN8opendnp314IEventSelectorE, 16
_ZTIN8opendnp314IEventSelectorE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp314IEventSelectorE
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
	.weak	_ZTSN8opendnp314IEventRecorderE
	.section	.rodata._ZTSN8opendnp314IEventRecorderE,"aG",@progbits,_ZTSN8opendnp314IEventRecorderE,comdat
	.align 16
	.type	_ZTSN8opendnp314IEventRecorderE, @object
	.size	_ZTSN8opendnp314IEventRecorderE, 28
_ZTSN8opendnp314IEventRecorderE:
	.string	"N8opendnp314IEventRecorderE"
	.weak	_ZTIN8opendnp314IEventRecorderE
	.section	.data.rel.ro._ZTIN8opendnp314IEventRecorderE,"awG",@progbits,_ZTIN8opendnp314IEventRecorderE,comdat
	.align 8
	.type	_ZTIN8opendnp314IEventRecorderE, @object
	.size	_ZTIN8opendnp314IEventRecorderE, 16
_ZTIN8opendnp314IEventRecorderE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp314IEventRecorderE
	.weak	_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE
	.section	.rodata._ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,"aG",@progbits,_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,comdat
	.align 32
	.type	_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, @object
	.size	_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, 56
_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE:
	.string	"N7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE"
	.weak	_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE
	.section	.data.rel.ro._ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,"awG",@progbits,_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,comdat
	.align 8
	.type	_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, @object
	.size	_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, 40
_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE
	.long	0
	.long	1
	.quad	_ZTIN7openpal7HasSizeIjEE
	.quad	2050
	.weak	_ZTSN8opendnp311EventBufferE
	.section	.rodata._ZTSN8opendnp311EventBufferE,"aG",@progbits,_ZTSN8opendnp311EventBufferE,comdat
	.align 16
	.type	_ZTSN8opendnp311EventBufferE, @object
	.size	_ZTSN8opendnp311EventBufferE, 25
_ZTSN8opendnp311EventBufferE:
	.string	"N8opendnp311EventBufferE"
	.weak	_ZTIN8opendnp311EventBufferE
	.section	.data.rel.ro._ZTIN8opendnp311EventBufferE,"awG",@progbits,_ZTIN8opendnp311EventBufferE,comdat
	.align 8
	.type	_ZTIN8opendnp311EventBufferE, @object
	.size	_ZTIN8opendnp311EventBufferE, 88
_ZTIN8opendnp311EventBufferE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN8opendnp311EventBufferE
	.long	0
	.long	4
	.quad	_ZTIN8opendnp314IEventReceiverE
	.quad	2
	.quad	_ZTIN8opendnp314IEventSelectorE
	.quad	2050
	.quad	_ZTIN8opendnp315IResponseLoaderE
	.quad	4098
	.quad	_ZTIN8opendnp314IEventRecorderE
	.quad	6144
	.weak	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE
	.section	.data.rel.ro._ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,"awG",@progbits,_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE,comdat
	.align 8
	.type	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, @object
	.size	_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE, 32
_ZTVN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE:
	.quad	0
	.quad	_ZTIN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjEE
	.quad	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED1Ev
	.quad	_ZN7openpal5ArrayINS_8ListNodeIN8opendnp39SOERecordEEEjED0Ev
	.weak	_ZTVN8opendnp311EventBufferE
	.section	.data.rel.ro._ZTVN8opendnp311EventBufferE,"awG",@progbits,_ZTVN8opendnp311EventBufferE,comdat
	.align 8
	.type	_ZTVN8opendnp311EventBufferE, @object
	.size	_ZTVN8opendnp311EventBufferE, 240
_ZTVN8opendnp311EventBufferE:
	.quad	0
	.quad	_ZTIN8opendnp311EventBufferE
	.quad	_ZN8opendnp311EventBufferD1Ev
	.quad	_ZN8opendnp311EventBufferD0Ev
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10BinarySpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_19DoubleBitBinarySpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_10AnalogSpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_11CounterSpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_17FrozenCounterSpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22BinaryOutputStatusSpecEEE
	.quad	_ZN8opendnp311EventBuffer6UpdateERKNS_5EventINS_22AnalogOutputStatusSpecEEE
	.quad	_ZN8opendnp311EventBuffer8UnselectEv
	.quad	_ZN8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.quad	_ZN8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.quad	_ZNK8opendnp311EventBuffer15HasAnySelectionEv
	.quad	_ZN8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.quad	_ZNK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.quad	_ZN8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.quad	-8
	.quad	_ZTIN8opendnp311EventBufferE
	.quad	_ZThn8_N8opendnp311EventBuffer9SelectAllENS_14GroupVariationE
	.quad	_ZThn8_N8opendnp311EventBuffer11SelectCountENS_14GroupVariationEt
	.quad	-16
	.quad	_ZTIN8opendnp311EventBufferE
	.quad	_ZThn16_NK8opendnp311EventBuffer15HasAnySelectionEv
	.quad	_ZThn16_N8opendnp311EventBuffer4LoadERNS_12HeaderWriterE
	.quad	-24
	.quad	_ZTIN8opendnp311EventBufferE
	.quad	_ZThn24_NK8opendnp311EventBuffer22HasMoreUnwrittenEventsEv
	.quad	_ZThn24_N8opendnp311EventBuffer13RecordWrittenENS_10EventClassENS_9EventTypeE
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1
	.long	2
	.long	3
	.long	4
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.align 16
.LC2:
	.long	64
	.long	64
	.long	64
	.long	64
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
