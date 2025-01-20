	.file	"ControlRelayOutputBlock.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE
	.type	_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE, @function
_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE:
.LFB3:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movd	%ecx, %xmm0
	movd	%r8d, %xmm1
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	punpckldq	%xmm1, %xmm0
	movl	%r9d, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	%esi, %edi
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movb	%sil, (%rbx)
	movq	%xmm0, 8(%rsp)
	call	_ZN8opendnp317ControlCodeToTypeENS_11ControlCodeE@PLT
	movq	8(%rsp), %xmm0
	movb	%r12b, 2(%rbx)
	movb	%bpl, 12(%rbx)
	movb	%al, 1(%rbx)
	movq	%xmm0, 4(%rbx)
	addq	$16, %rsp
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3:
	.size	_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE, .-_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE
	.globl	_ZN8opendnp323ControlRelayOutputBlockC1ENS_11ControlCodeEhjjNS_13CommandStatusE
	.set	_ZN8opendnp323ControlRelayOutputBlockC1ENS_11ControlCodeEhjjNS_13CommandStatusE,_ZN8opendnp323ControlRelayOutputBlockC2ENS_11ControlCodeEhjjNS_13CommandStatusE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE
	.type	_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE, @function
_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE:
.LFB6:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movd	%r8d, %xmm1
	movd	%ecx, %xmm0
	movl	%edx, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	punpckldq	%xmm1, %xmm0
	movl	%r9d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	movzbl	%sil, %edi
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movq	%xmm0, 8(%rsp)
	call	_ZN8opendnp319ControlCodeFromTypeEh@PLT
	movq	8(%rsp), %xmm0
	movl	%ebp, %edx
	movb	%r13b, 2(%rbx)
	movl	%eax, %r8d
	xorl	%eax, %eax
	movb	%r12b, 12(%rbx)
	movb	%r8b, %al
	movq	%xmm0, 4(%rbx)
	movb	%dl, %ah
	movw	%ax, (%rbx)
	addq	$24, %rsp
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
.LFE6:
	.size	_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE, .-_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE
	.globl	_ZN8opendnp323ControlRelayOutputBlockC1EhhjjNS_13CommandStatusE
	.set	_ZN8opendnp323ControlRelayOutputBlockC1EhhjjNS_13CommandStatusE,_ZN8opendnp323ControlRelayOutputBlockC2EhhjjNS_13CommandStatusE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
