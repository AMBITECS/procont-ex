	.file	"DeferredRequest.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DeferredRequestC2Ej
	.type	_ZN8opendnp315DeferredRequestC2Ej, @function
_ZN8opendnp315DeferredRequestC2Ej:
.LFB156:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$-256, %eax
	movl	%esi, %ebp
	xorl	%r9d, %r9d
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	$1, %esi
	movq	%rdi, %rbx
	xorl	%r8d, %r8d
	leaq	2(%rdi), %rdi
	xorl	%ecx, %ecx
	movl	$1, %edx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movw	%ax, -2(%rdi)
	call	_ZN8opendnp315AppControlFieldC1Ebbbbh@PLT
	leaq	8(%rbx), %rdi
	call	_ZN7openpal6RSliceC1Ev@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	leaq	24(%rbx), %rdi
	movl	%ebp, %esi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN7openpal6BufferC1Ej@PLT
	.cfi_endproc
.LFE156:
	.size	_ZN8opendnp315DeferredRequestC2Ej, .-_ZN8opendnp315DeferredRequestC2Ej
	.globl	_ZN8opendnp315DeferredRequestC1Ej
	.set	_ZN8opendnp315DeferredRequestC1Ej,_ZN8opendnp315DeferredRequestC2Ej
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DeferredRequest5ResetEv
	.type	_ZN8opendnp315DeferredRequest5ResetEv, @function
_ZN8opendnp315DeferredRequest5ResetEv:
.LFB158:
	.cfi_startproc
	movb	$0, (%rdi)
	ret
	.cfi_endproc
.LFE158:
	.size	_ZN8opendnp315DeferredRequest5ResetEv, .-_ZN8opendnp315DeferredRequest5ResetEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp315DeferredRequest5IsSetEv
	.type	_ZNK8opendnp315DeferredRequest5IsSetEv, @function
_ZNK8opendnp315DeferredRequest5IsSetEv:
.LFB159:
	.cfi_startproc
	movzbl	(%rdi), %eax
	ret
	.cfi_endproc
.LFE159:
	.size	_ZNK8opendnp315DeferredRequest5IsSetEv, .-_ZNK8opendnp315DeferredRequest5IsSetEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp315DeferredRequest11GetFunctionEv
	.type	_ZNK8opendnp315DeferredRequest11GetFunctionEv, @function
_ZNK8opendnp315DeferredRequest11GetFunctionEv:
.LFB160:
	.cfi_startproc
	movzbl	1(%rdi), %eax
	ret
	.cfi_endproc
.LFE160:
	.size	_ZNK8opendnp315DeferredRequest11GetFunctionEv, .-_ZNK8opendnp315DeferredRequest11GetFunctionEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp315DeferredRequest3SetENS_10APDUHeaderEN7openpal6RSliceE
	.type	_ZN8opendnp315DeferredRequest3SetENS_10APDUHeaderEN7openpal6RSliceE, @function
_ZN8opendnp315DeferredRequest3SetENS_10APDUHeaderEN7openpal6RSliceE:
.LFB161:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	%esi, %eax
	shrq	$32, %rsi
	movq	%rdi, %rbx
	addq	$24, %rdi
	subq	$64, %rsp
	.cfi_def_cfa_offset 80
	movq	%rdx, (%rsp)
	movq	%rcx, 8(%rsp)
	movq	%fs:40, %rcx
	movq	%rcx, 56(%rsp)
	xorl	%ecx, %ecx
	movl	%eax, -23(%rdi)
	movw	%si, -19(%rdi)
	movb	$1, -24(%rdi)
	call	_ZN7openpal6Buffer9GetWSliceEv@PLT
	leaq	32(%rsp), %rsi
	movq	%rsp, %rdi
	movl	%eax, 32(%rsp)
	movq	%rdx, 40(%rsp)
	call	_ZNK7openpal6RSlice6CopyToERNS_6WSliceE@PLT
	movl	%eax, 8(%rbx)
	movq	%rdx, 16(%rbx)
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L10
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L10:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE161:
	.size	_ZN8opendnp315DeferredRequest3SetENS_10APDUHeaderEN7openpal6RSliceE, .-_ZN8opendnp315DeferredRequest3SetENS_10APDUHeaderEN7openpal6RSliceE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
