	.file	"UserOperation.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp319UserOperationToTypeENS_13UserOperationE
	.type	_ZN8opendnp319UserOperationToTypeENS_13UserOperationE, @function
_ZN8opendnp319UserOperationToTypeENS_13UserOperationE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp319UserOperationToTypeENS_13UserOperationE, .-_ZN8opendnp319UserOperationToTypeENS_13UserOperationE
	.p2align 4
	.globl	_ZN8opendnp321UserOperationFromTypeEh
	.type	_ZN8opendnp321UserOperationFromTypeEh, @function
_ZN8opendnp321UserOperationFromTypeEh:
.LFB1:
	.cfi_startproc
	leal	-1(%rdi), %eax
	cmpb	$2, %al
	movl	$-1, %eax
	cmovbe	%edi, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp321UserOperationFromTypeEh, .-_ZN8opendnp321UserOperationFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"OP_UNDEFINED"
.LC1:
	.string	"OP_CHANGE"
.LC2:
	.string	"OP_DELETE"
.LC3:
	.string	"OP_ADD"
	.text
	.p2align 4
	.globl	_ZN8opendnp321UserOperationToStringENS_13UserOperationE
	.type	_ZN8opendnp321UserOperationToStringENS_13UserOperationE, @function
_ZN8opendnp321UserOperationToStringENS_13UserOperationE:
.LFB2:
	.cfi_startproc
	leaq	.LC2(%rip), %rax
	cmpb	$2, %dil
	je	.L6
	leaq	.LC1(%rip), %rax
	cmpb	$3, %dil
	je	.L6
	cmpb	$1, %dil
	leaq	.LC0(%rip), %rax
	leaq	.LC3(%rip), %rdx
	cmove	%rdx, %rax
.L6:
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp321UserOperationToStringENS_13UserOperationE, .-_ZN8opendnp321UserOperationToStringENS_13UserOperationE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
