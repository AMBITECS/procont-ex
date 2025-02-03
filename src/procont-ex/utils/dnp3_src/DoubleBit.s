	.file	"DoubleBit.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp315DoubleBitToTypeENS_9DoubleBitE
	.type	_ZN8opendnp315DoubleBitToTypeENS_9DoubleBitE, @function
_ZN8opendnp315DoubleBitToTypeENS_9DoubleBitE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp315DoubleBitToTypeENS_9DoubleBitE, .-_ZN8opendnp315DoubleBitToTypeENS_9DoubleBitE
	.p2align 4
	.globl	_ZN8opendnp317DoubleBitFromTypeEh
	.type	_ZN8opendnp317DoubleBitFromTypeEh, @function
_ZN8opendnp317DoubleBitFromTypeEh:
.LFB1:
	.cfi_startproc
	cmpb	$2, %dil
	movl	$3, %eax
	cmovbe	%edi, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp317DoubleBitFromTypeEh, .-_ZN8opendnp317DoubleBitFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"INDETERMINATE"
.LC1:
	.string	"DETERMINED_ON"
.LC2:
	.string	"DETERMINED_OFF"
.LC3:
	.string	"INTERMEDIATE"
	.text
	.p2align 4
	.globl	_ZN8opendnp317DoubleBitToStringENS_9DoubleBitE
	.type	_ZN8opendnp317DoubleBitToStringENS_9DoubleBitE, @function
_ZN8opendnp317DoubleBitToStringENS_9DoubleBitE:
.LFB2:
	.cfi_startproc
	leaq	.LC2(%rip), %rax
	cmpb	$1, %dil
	je	.L6
	leaq	.LC1(%rip), %rax
	cmpb	$2, %dil
	je	.L6
	testb	%dil, %dil
	leaq	.LC0(%rip), %rax
	leaq	.LC3(%rip), %rdx
	cmove	%rdx, %rax
.L6:
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp317DoubleBitToStringENS_9DoubleBitE, .-_ZN8opendnp317DoubleBitToStringENS_9DoubleBitE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
