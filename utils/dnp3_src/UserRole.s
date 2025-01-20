	.file	"UserRole.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp314UserRoleToTypeENS_8UserRoleE
	.type	_ZN8opendnp314UserRoleToTypeENS_8UserRoleE, @function
_ZN8opendnp314UserRoleToTypeENS_8UserRoleE:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp314UserRoleToTypeENS_8UserRoleE, .-_ZN8opendnp314UserRoleToTypeENS_8UserRoleE
	.p2align 4
	.globl	_ZN8opendnp316UserRoleFromTypeEt
	.type	_ZN8opendnp316UserRoleFromTypeEt, @function
_ZN8opendnp316UserRoleFromTypeEt:
.LFB1:
	.cfi_startproc
	movl	%edi, %eax
	cmpw	$6, %di
	ja	.L4
	leaq	.L7(%rip), %rcx
	movzwl	%di, %edi
	movslq	(%rcx,%rdi,4), %rdx
	addq	%rcx, %rdx
	jmp	*%rdx
	.section	.rodata
	.align 4
	.align 4
.L7:
	.long	.L13-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.long	.L5-.L7
	.text
	.p2align 4,,10
	.p2align 3
.L13:
	xorl	%eax, %eax
.L5:
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	cmpw	$-32768, %di
	movl	$32767, %edx
	cmovne	%edx, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	_ZN8opendnp316UserRoleFromTypeEt, .-_ZN8opendnp316UserRoleFromTypeEt
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"UNDEFINED"
.LC1:
	.string	"VIEWER"
.LC2:
	.string	"ENGINEER"
.LC3:
	.string	"INSTALLER"
.LC4:
	.string	"SECADM"
.LC5:
	.string	"SECAUD"
.LC6:
	.string	"RBACMNT"
.LC7:
	.string	"OPERATOR"
.LC8:
	.string	"SINGLE_USER"
	.text
	.p2align 4
	.globl	_ZN8opendnp316UserRoleToStringENS_8UserRoleE
	.type	_ZN8opendnp316UserRoleToStringENS_8UserRoleE, @function
_ZN8opendnp316UserRoleToStringENS_8UserRoleE:
.LFB2:
	.cfi_startproc
	cmpw	$6, %di
	ja	.L16
	leaq	.L19(%rip), %rdx
	movzwl	%di, %edi
	movslq	(%rdx,%rdi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L19:
	.long	.L25-.L19
	.long	.L24-.L19
	.long	.L23-.L19
	.long	.L22-.L19
	.long	.L21-.L19
	.long	.L20-.L19
	.long	.L18-.L19
	.text
	.p2align 4,,10
	.p2align 3
.L16:
	cmpw	$-32768, %di
	leaq	.LC8(%rip), %rdx
	leaq	.LC0(%rip), %rax
	cmove	%rdx, %rax
	ret
	.p2align 4,,10
	.p2align 3
.L24:
	leaq	.LC7(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L23:
	leaq	.LC2(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L22:
	leaq	.LC3(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	leaq	.LC4(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L20:
	leaq	.LC5(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L18:
	leaq	.LC6(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L25:
	leaq	.LC1(%rip), %rax
	ret
	.cfi_endproc
.LFE2:
	.size	_ZN8opendnp316UserRoleToStringENS_8UserRoleE, .-_ZN8opendnp316UserRoleToStringENS_8UserRoleE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
