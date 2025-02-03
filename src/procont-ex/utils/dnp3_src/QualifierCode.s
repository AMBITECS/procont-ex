	.file	"QualifierCode.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp319QualifierCodeToTypeENS_13QualifierCodeE
	.type	_ZN8opendnp319QualifierCodeToTypeENS_13QualifierCodeE, @function
_ZN8opendnp319QualifierCodeToTypeENS_13QualifierCodeE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp319QualifierCodeToTypeENS_13QualifierCodeE, .-_ZN8opendnp319QualifierCodeToTypeENS_13QualifierCodeE
	.p2align 4
	.globl	_ZN8opendnp321QualifierCodeFromTypeEh
	.type	_ZN8opendnp321QualifierCodeFromTypeEh, @function
_ZN8opendnp321QualifierCodeFromTypeEh:
.LFB1:
	.cfi_startproc
	movl	%edi, %eax
	cmpb	$40, %dil
	ja	.L4
	leaq	.L7(%rip), %rcx
	movzbl	%dil, %edi
	movslq	(%rcx,%rdi,4), %rdx
	addq	%rcx, %rdx
	jmp	*%rdx
	.section	.rodata
	.align 4
	.align 4
.L7:
	.long	.L6-.L7
	.long	.L6-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L6-.L7
	.long	.L6-.L7
	.long	.L6-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L6-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L6-.L7
	.text
	.p2align 4,,10
	.p2align 3
.L5:
	movl	$-1, %eax
.L6:
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	cmpb	$91, %dil
	movl	$-1, %edx
	cmovne	%edx, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp321QualifierCodeFromTypeEh, .-_ZN8opendnp321QualifierCodeFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"unknown"
.LC1:
	.string	"8-bit start stop"
.LC2:
	.string	"all objects"
.LC3:
	.string	"8-bit count"
.LC4:
	.string	"16-bit count"
.LC5:
	.string	"8-bit count and prefix"
.LC6:
	.string	"16-bit count and prefix"
.LC7:
	.string	"16-bit start stop"
.LC8:
	.string	"16-bit free format"
	.text
	.p2align 4
	.globl	_ZN8opendnp321QualifierCodeToStringENS_13QualifierCodeE
	.type	_ZN8opendnp321QualifierCodeToStringENS_13QualifierCodeE, @function
_ZN8opendnp321QualifierCodeToStringENS_13QualifierCodeE:
.LFB2:
	.cfi_startproc
	cmpb	$40, %dil
	ja	.L10
	leaq	.L13(%rip), %rdx
	movzbl	%dil, %edi
	movslq	(%rdx,%rdi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L13:
	.long	.L20-.L13
	.long	.L18-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L17-.L13
	.long	.L16-.L13
	.long	.L15-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L14-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L11-.L13
	.long	.L12-.L13
	.text
	.p2align 4,,10
	.p2align 3
.L11:
	leaq	.LC0(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	cmpb	$91, %dil
	leaq	.LC8(%rip), %rdx
	leaq	.LC0(%rip), %rax
	cmove	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	.LC6(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L17:
	leaq	.LC2(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L16:
	leaq	.LC3(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	leaq	.LC4(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	leaq	.LC5(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L20:
	leaq	.LC1(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L18:
	leaq	.LC7(%rip), %rax
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp321QualifierCodeToStringENS_13QualifierCodeE, .-_ZN8opendnp321QualifierCodeToStringENS_13QualifierCodeE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
