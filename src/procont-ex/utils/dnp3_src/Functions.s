	.file	"Functions.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39Functions15IsNoAckFuncCodeENS_12FunctionCodeE
	.type	_ZN8opendnp39Functions15IsNoAckFuncCodeENS_12FunctionCodeE, @function
_ZN8opendnp39Functions15IsNoAckFuncCodeENS_12FunctionCodeE:
.LFB6:
	.cfi_startproc
	cmpb	$12, %dil
	ja	.L3
	movl	%edi, %ecx
	movl	$1, %eax
	salq	%cl, %rax
	testl	$5440, %eax
	setne	%al
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE6:
	.size	_ZN8opendnp39Functions15IsNoAckFuncCodeENS_12FunctionCodeE, .-_ZN8opendnp39Functions15IsNoAckFuncCodeENS_12FunctionCodeE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
