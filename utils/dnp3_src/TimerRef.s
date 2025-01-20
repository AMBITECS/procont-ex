	.file	"TimerRef.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRefC2ERNS_9IExecutorE
	.type	_ZN7openpal8TimerRefC2ERNS_9IExecutorE, @function
_ZN7openpal8TimerRefC2ERNS_9IExecutorE:
.LFB940:
	.cfi_startproc
	movq	%rsi, (%rdi)
	movq	$0, 8(%rdi)
	ret
	.cfi_endproc
.LFE940:
	.size	_ZN7openpal8TimerRefC2ERNS_9IExecutorE, .-_ZN7openpal8TimerRefC2ERNS_9IExecutorE
	.globl	_ZN7openpal8TimerRefC1ERNS_9IExecutorE
	.set	_ZN7openpal8TimerRefC1ERNS_9IExecutorE,_ZN7openpal8TimerRefC2ERNS_9IExecutorE
	.align 2
	.p2align 4
	.globl	_ZNK7openpal8TimerRef8IsActiveEv
	.type	_ZNK7openpal8TimerRef8IsActiveEv, @function
_ZNK7openpal8TimerRef8IsActiveEv:
.LFB945:
	.cfi_startproc
	cmpq	$0, 8(%rdi)
	setne	%al
	ret
	.cfi_endproc
.LFE945:
	.size	_ZNK7openpal8TimerRef8IsActiveEv, .-_ZNK7openpal8TimerRef8IsActiveEv
	.align 2
	.p2align 4
	.globl	_ZNK7openpal8TimerRef9ExpiresAtEv
	.type	_ZNK7openpal8TimerRef9ExpiresAtEv, @function
_ZNK7openpal8TimerRef9ExpiresAtEv:
.LFB946:
	.cfi_startproc
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L5
	movq	(%rdi), %rax
	jmp	*24(%rax)
	.p2align 4,,10
	.p2align 3
.L5:
	jmp	_ZN7openpal18MonotonicTimestamp3MaxEv@PLT
	.cfi_endproc
.LFE946:
	.size	_ZNK7openpal8TimerRef9ExpiresAtEv, .-_ZNK7openpal8TimerRef9ExpiresAtEv
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRef6CancelEv
	.type	_ZN7openpal8TimerRef6CancelEv, @function
_ZN7openpal8TimerRef6CancelEv:
.LFB947:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L6
	movq	(%rdi), %rax
	call	*16(%rax)
	movq	$0, 8(%rbx)
	movl	$1, %eax
.L6:
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE947:
	.size	_ZN7openpal8TimerRef6CancelEv, .-_ZN7openpal8TimerRef6CancelEv
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRefD2Ev
	.type	_ZN7openpal8TimerRefD2Ev, @function
_ZN7openpal8TimerRefD2Ev:
.LFB943:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA943
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZN7openpal8TimerRef6CancelEv@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE943:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA943:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE943-.LLSDACSB943
.LLSDACSB943:
.LLSDACSE943:
	.text
	.size	_ZN7openpal8TimerRefD2Ev, .-_ZN7openpal8TimerRefD2Ev
	.globl	_ZN7openpal8TimerRefD1Ev
	.set	_ZN7openpal8TimerRefD1Ev,_ZN7openpal8TimerRefD2Ev
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRef11StartActionERKNS_12TimeDurationERKSt8functionIFvvEE
	.type	_ZN7openpal8TimerRef11StartActionERKNS_12TimeDurationERKSt8functionIFvvEE, @function
_ZN7openpal8TimerRef11StartActionERKNS_12TimeDurationERKSt8functionIFvvEE:
.LFB948:
	.cfi_startproc
	cmpq	$0, 8(%rdi)
	je	.L22
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L22:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	(%rdi), %rdi
	movq	(%rdi), %rax
	call	*24(%rax)
	movq	%rax, 8(%rbx)
	movl	$1, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE948:
	.size	_ZN7openpal8TimerRef11StartActionERKNS_12TimeDurationERKSt8functionIFvvEE, .-_ZN7openpal8TimerRef11StartActionERKNS_12TimeDurationERKSt8functionIFvvEE
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRef11StartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE
	.type	_ZN7openpal8TimerRef11StartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE, @function
_ZN7openpal8TimerRef11StartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE:
.LFB949:
	.cfi_startproc
	cmpq	$0, 8(%rdi)
	je	.L31
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L31:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	(%rdi), %rdi
	movq	(%rdi), %rax
	call	*32(%rax)
	movq	%rax, 8(%rbx)
	movl	$1, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE949:
	.size	_ZN7openpal8TimerRef11StartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE, .-_ZN7openpal8TimerRef11StartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRef13RestartActionERKNS_12TimeDurationERKSt8functionIFvvEE
	.type	_ZN7openpal8TimerRef13RestartActionERKNS_12TimeDurationERKSt8functionIFvvEE, @function
_ZN7openpal8TimerRef13RestartActionERKNS_12TimeDurationERKSt8functionIFvvEE:
.LFB950:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L33
	movq	(%rdi), %rax
	call	*16(%rax)
.L33:
	movq	(%rbx), %rdi
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*24(%rax)
	movq	%rax, 8(%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE950:
	.size	_ZN7openpal8TimerRef13RestartActionERKNS_12TimeDurationERKSt8functionIFvvEE, .-_ZN7openpal8TimerRef13RestartActionERKNS_12TimeDurationERKSt8functionIFvvEE
	.align 2
	.p2align 4
	.globl	_ZN7openpal8TimerRef13RestartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE
	.type	_ZN7openpal8TimerRef13RestartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE, @function
_ZN7openpal8TimerRef13RestartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE:
.LFB951:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L39
	movq	(%rdi), %rax
	call	*16(%rax)
.L39:
	movq	(%rbx), %rdi
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*32(%rax)
	movq	%rax, 8(%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE951:
	.size	_ZN7openpal8TimerRef13RestartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE, .-_ZN7openpal8TimerRef13RestartActionERKNS_18MonotonicTimestampERKSt8functionIFvvEE
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
