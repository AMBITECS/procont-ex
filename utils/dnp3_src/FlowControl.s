	.file	"FlowControl.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp317FlowControlToTypeENS_11FlowControlE
	.type	_ZN8opendnp317FlowControlToTypeENS_11FlowControlE, @function
_ZN8opendnp317FlowControlToTypeENS_11FlowControlE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp317FlowControlToTypeENS_11FlowControlE, .-_ZN8opendnp317FlowControlToTypeENS_11FlowControlE
	.p2align 4
	.globl	_ZN8opendnp319FlowControlFromTypeEh
	.type	_ZN8opendnp319FlowControlFromTypeEh, @function
_ZN8opendnp319FlowControlFromTypeEh:
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
	.size	_ZN8opendnp319FlowControlFromTypeEh, .-_ZN8opendnp319FlowControlFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"None"
.LC1:
	.string	"Hardware"
.LC2:
	.string	"XONXOFF"
	.text
	.p2align 4
	.globl	_ZN8opendnp319FlowControlToStringENS_11FlowControlE
	.type	_ZN8opendnp319FlowControlToStringENS_11FlowControlE, @function
_ZN8opendnp319FlowControlToStringENS_11FlowControlE:
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
	.size	_ZN8opendnp319FlowControlToStringENS_11FlowControlE, .-_ZN8opendnp319FlowControlToStringENS_11FlowControlE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
