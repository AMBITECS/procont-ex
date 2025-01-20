	.file	"LinkHeaderFields.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp316LinkHeaderFieldsC2Ev
	.type	_ZN8opendnp316LinkHeaderFieldsC2Ev, @function
_ZN8opendnp316LinkHeaderFieldsC2Ev:
.LFB1:
	.cfi_startproc
	movq	$255, (%rdi)
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp316LinkHeaderFieldsC2Ev, .-_ZN8opendnp316LinkHeaderFieldsC2Ev
	.globl	_ZN8opendnp316LinkHeaderFieldsC1Ev
	.set	_ZN8opendnp316LinkHeaderFieldsC1Ev,_ZN8opendnp316LinkHeaderFieldsC2Ev
	.align 2
	.p2align 4
	.globl	_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt
	.type	_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt, @function
_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt:
.LFB4:
	.cfi_startproc
	movl	8(%rsp), %eax
	movb	%sil, (%rdi)
	movb	%dl, 1(%rdi)
	movb	%cl, 2(%rdi)
	movb	%r8b, 3(%rdi)
	movw	%r9w, 4(%rdi)
	movw	%ax, 6(%rdi)
	ret
	.cfi_endproc
.LFE4:
	.size	_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt, .-_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt
	.globl	_ZN8opendnp316LinkHeaderFieldsC1ENS_12LinkFunctionEbbbtt
	.set	_ZN8opendnp316LinkHeaderFieldsC1ENS_12LinkFunctionEbbbtt,_ZN8opendnp316LinkHeaderFieldsC2ENS_12LinkFunctionEbbbtt
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
