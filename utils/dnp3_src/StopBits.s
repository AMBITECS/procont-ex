	.file	"StopBits.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp314StopBitsToTypeENS_8StopBitsE
	.type	_ZN8opendnp314StopBitsToTypeENS_8StopBitsE, @function
_ZN8opendnp314StopBitsToTypeENS_8StopBitsE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp314StopBitsToTypeENS_8StopBitsE, .-_ZN8opendnp314StopBitsToTypeENS_8StopBitsE
	.p2align 4
	.globl	_ZN8opendnp316StopBitsFromTypeEh
	.type	_ZN8opendnp316StopBitsFromTypeEh, @function
_ZN8opendnp316StopBitsFromTypeEh:
.LFB1:
	.cfi_startproc
	leal	-1(%rdi), %eax
	cmpb	$2, %al
	movl	$0, %eax
	cmovbe	%edi, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp316StopBitsFromTypeEh, .-_ZN8opendnp316StopBitsFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"None"
.LC1:
	.string	"Two"
.LC2:
	.string	"OnePointFive"
.LC3:
	.string	"One"
	.text
	.p2align 4
	.globl	_ZN8opendnp316StopBitsToStringENS_8StopBitsE
	.type	_ZN8opendnp316StopBitsToStringENS_8StopBitsE, @function
_ZN8opendnp316StopBitsToStringENS_8StopBitsE:
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
	.size	_ZN8opendnp316StopBitsToStringENS_8StopBitsE, .-_ZN8opendnp316StopBitsToStringENS_8StopBitsE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
