	.file	"LinkStatus.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"UNDEFINED"
.LC1:
	.string	"UNRESET"
.LC2:
	.string	"RESET"
	.text
	.p2align 4
	.globl	_ZN8opendnp318LinkStatusToStringENS_10LinkStatusE
	.type	_ZN8opendnp318LinkStatusToStringENS_10LinkStatusE, @function
_ZN8opendnp318LinkStatusToStringENS_10LinkStatusE:
.LFB0:
	.cfi_startproc
	leaq	.LC1(%rip), %rax
	testb	%dil, %dil
	je	.L1
	cmpb	$1, %dil
	leaq	.LC0(%rip), %rax
	leaq	.LC2(%rip), %rdx
	cmove	%rdx, %rax
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp318LinkStatusToStringENS_10LinkStatusE, .-_ZN8opendnp318LinkStatusToStringENS_10LinkStatusE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
