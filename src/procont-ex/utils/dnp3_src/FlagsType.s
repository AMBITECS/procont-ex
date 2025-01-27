	.file	"FlagsType.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp315FlagsTypeToTypeENS_9FlagsTypeE
	.type	_ZN8opendnp315FlagsTypeToTypeENS_9FlagsTypeE, @function
_ZN8opendnp315FlagsTypeToTypeENS_9FlagsTypeE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp315FlagsTypeToTypeENS_9FlagsTypeE, .-_ZN8opendnp315FlagsTypeToTypeENS_9FlagsTypeE
	.p2align 4
	.globl	_ZN8opendnp317FlagsTypeFromTypeEh
	.type	_ZN8opendnp317FlagsTypeFromTypeEh, @function
_ZN8opendnp317FlagsTypeFromTypeEh:
.LFB1:
	.cfi_startproc
	leal	-1(%rdi), %eax
	cmpb	$5, %al
	movl	$0, %eax
	cmovbe	%edi, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp317FlagsTypeFromTypeEh, .-_ZN8opendnp317FlagsTypeFromTypeEh
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"BinaryInput"
.LC1:
	.string	"DoubleBinaryInput"
.LC2:
	.string	"FrozenCounter"
.LC3:
	.string	"AnalogInput"
.LC4:
	.string	"BinaryOutputStatus"
.LC5:
	.string	"AnalogOutputStatus"
.LC6:
	.string	"Counter"
	.text
	.p2align 4
	.globl	_ZN8opendnp317FlagsTypeToStringENS_9FlagsTypeE
	.type	_ZN8opendnp317FlagsTypeToStringENS_9FlagsTypeE, @function
_ZN8opendnp317FlagsTypeToStringENS_9FlagsTypeE:
.LFB2:
	.cfi_startproc
	cmpb	$6, %dil
	ja	.L7
	leaq	.L9(%rip), %rdx
	movzbl	%dil, %edi
	movslq	(%rdx,%rdi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L9:
	.long	.L7-.L9
	.long	.L15-.L9
	.long	.L13-.L9
	.long	.L12-.L9
	.long	.L11-.L9
	.long	.L10-.L9
	.long	.L8-.L9
	.text
	.p2align 4,,10
	.p2align 3
.L13:
	leaq	.LC6(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	leaq	.LC1(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	leaq	.LC5(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	.LC2(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	leaq	.LC3(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	leaq	.LC4(%rip), %rax
	ret
.L7:
	leaq	.LC0(%rip), %rax
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp317FlagsTypeToStringENS_9FlagsTypeE, .-_ZN8opendnp317FlagsTypeToStringENS_9FlagsTypeE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
