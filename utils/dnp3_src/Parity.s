	.file	"Parity.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp312ParityToTypeENS_6ParityE
	.type	_ZN8opendnp312ParityToTypeENS_6ParityE, @function
_ZN8opendnp312ParityToTypeENS_6ParityE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp312ParityToTypeENS_6ParityE, .-_ZN8opendnp312ParityToTypeENS_6ParityE
	.p2align 4
	.globl	_ZN8opendnp314ParityFromTypeEh
	.type	_ZN8opendnp314ParityFromTypeEh, @function
_ZN8opendnp314ParityFromTypeEh:
.LFB1:
	.cfi_startproc
	movl	%edi, %eax
	cmpb	$1, %dil
	je	.L4
	cmpb	$2, %dil
	movl	$0, %edx
	cmovne	%edx, %eax
.L4:
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp314ParityFromTypeEh, .-_ZN8opendnp314ParityFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"None"
.LC1:
	.string	"Even"
.LC2:
	.string	"Odd"
	.text
	.p2align 4
	.globl	_ZN8opendnp314ParityToStringENS_6ParityE
	.type	_ZN8opendnp314ParityToStringENS_6ParityE, @function
_ZN8opendnp314ParityToStringENS_6ParityE:
.LFB2:
	.cfi_startproc
	leaq	.LC1(%rip), %rax
	cmpb	$1, %dil
	je	.L6
	cmpb	$2, %dil
	leaq	.LC0(%rip), %rax
	leaq	.LC2(%rip), %rdx
	cmove	%rdx, %rax
.L6:
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp314ParityToStringENS_6ParityE, .-_ZN8opendnp314ParityToStringENS_6ParityE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
