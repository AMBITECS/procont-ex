	.file	"IINHelpers.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp318IINFromParseResultENS_11ParseResultE
	.type	_ZN8opendnp318IINFromParseResultENS_11ParseResultE, @function
_ZN8opendnp318IINFromParseResultENS_11ParseResultE:
.LFB27:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%dil, %dil
	je	.L5
	xorl	%eax, %eax
	cmpb	$6, %dil
	leaq	6(%rsp), %rdi
	movw	%ax, 6(%rsp)
	jne	.L7
	movl	$9, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
.L5:
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L10
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
	movl	$10, %esi
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	jmp	.L5
.L10:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE27:
	.size	_ZN8opendnp318IINFromParseResultENS_11ParseResultE, .-_ZN8opendnp318IINFromParseResultENS_11ParseResultE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
