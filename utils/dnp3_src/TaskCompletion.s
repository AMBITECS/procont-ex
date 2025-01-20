	.file	"TaskCompletion.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"FAILURE_NO_COMMS"
.LC1:
	.string	"SUCCESS"
.LC2:
	.string	"FAILURE_RESPONSE_TIMEOUT"
.LC3:
	.string	"FAILURE_START_TIMEOUT"
.LC4:
	.string	"FAILURE_NO_USER"
.LC5:
	.string	"FAILURE_INTERNAL_ERROR"
.LC6:
	.string	"FAILURE_BAD_AUTHENTICATION"
.LC7:
	.string	"FAILURE_NOT_AUTHORIZED"
.LC8:
	.string	"FAILURE_BAD_RESPONSE"
	.text
	.p2align 4
	.globl	_ZN8opendnp322TaskCompletionToStringENS_14TaskCompletionE
	.type	_ZN8opendnp322TaskCompletionToStringENS_14TaskCompletionE, @function
_ZN8opendnp322TaskCompletionToStringENS_14TaskCompletionE:
.LFB0:
	.cfi_startproc
	cmpb	$7, %dil
	ja	.L2
	leaq	.L4(%rip), %rdx
	movzbl	%dil, %edi
	movslq	(%rdx,%rdi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L12-.L4
	.long	.L10-.L4
	.long	.L9-.L4
	.long	.L8-.L4
	.long	.L7-.L4
	.long	.L6-.L4
	.long	.L5-.L4
	.long	.L3-.L4
	.text
	.p2align 4,,10
	.p2align 3
.L10:
	leaq	.LC8(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	.LC1(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	leaq	.LC7(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	.LC5(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L5:
	leaq	.LC6(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	leaq	.LC2(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	leaq	.LC3(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	leaq	.LC4(%rip), %rax
	ret
.L2:
	leaq	.LC0(%rip), %rax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp322TaskCompletionToStringENS_14TaskCompletionE, .-_ZN8opendnp322TaskCompletionToStringENS_14TaskCompletionE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
