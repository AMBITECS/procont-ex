	.file	"GroupVariationRecord.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE
	.type	_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE, @function
_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE:
.LFB127:
	.cfi_startproc
	xorl	%eax, %eax
	movw	%cx, (%rdi)
	movb	%sil, %al
	movl	%r8d, 4(%rdi)
	movb	%dl, %ah
	movw	%ax, 8(%rdi)
	ret
	.cfi_endproc
.LFE127:
	.size	_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE, .-_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE
	.globl	_ZN8opendnp320GroupVariationRecordC1EhhNS_14GroupVariationENS_18GroupVariationTypeE
	.set	_ZN8opendnp320GroupVariationRecordC1EhhNS_14GroupVariationENS_18GroupVariationTypeE,_ZN8opendnp320GroupVariationRecordC2EhhNS_14GroupVariationENS_18GroupVariationTypeE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj
	.type	_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj, @function
_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj:
.LFB130:
	.cfi_startproc
	movq	(%rsi), %rax
	movb	%dl, 10(%rdi)
	movl	%ecx, 12(%rdi)
	movq	%rax, (%rdi)
	movzwl	8(%rsi), %eax
	movw	%ax, 8(%rdi)
	ret
	.cfi_endproc
.LFE130:
	.size	_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj, .-_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj
	.globl	_ZN8opendnp312HeaderRecordC1ERKNS_20GroupVariationRecordEhj
	.set	_ZN8opendnp312HeaderRecordC1ERKNS_20GroupVariationRecordEhj,_ZN8opendnp312HeaderRecordC2ERKNS_20GroupVariationRecordEhj
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp312HeaderRecord16GetQualifierCodeEv
	.type	_ZNK8opendnp312HeaderRecord16GetQualifierCodeEv, @function
_ZNK8opendnp312HeaderRecord16GetQualifierCodeEv:
.LFB132:
	.cfi_startproc
	movzbl	10(%rdi), %edi
	jmp	_ZN8opendnp321QualifierCodeFromTypeEh@PLT
	.cfi_endproc
.LFE132:
	.size	_ZNK8opendnp312HeaderRecord16GetQualifierCodeEv, .-_ZNK8opendnp312HeaderRecord16GetQualifierCodeEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh
	.type	_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh, @function
_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh:
.LFB134:
	.cfi_startproc
	sall	$8, %edi
	movzbl	%sil, %eax
	orl	%edi, %eax
	ret
	.cfi_endproc
.LFE134:
	.size	_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh, .-_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh
	.align 2
	.p2align 4
	.globl	_ZN8opendnp320GroupVariationRecord7GetTypeEhh
	.type	_ZN8opendnp320GroupVariationRecord7GetTypeEhh, @function
_ZN8opendnp320GroupVariationRecord7GetTypeEhh:
.LFB136:
	.cfi_startproc
	cmpb	$122, %dil
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
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L7-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L8-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L12-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L11-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L7-.L9
	.long	.L13-.L9
	.long	.L8-.L9
	.text
	.p2align 4,,10
	.p2align 3
.L7:
	movl	$2, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L8:
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L13:
	xorl	%eax, %eax
	ret
.L12:
	xorl	%eax, %eax
	cmpb	$4, %sil
	setne	%al
	addl	%eax, %eax
	ret
.L11:
	xorl	%eax, %eax
	cmpb	$1, %sil
	setne	%al
	ret
	.cfi_endproc
.LFE136:
	.size	_ZN8opendnp320GroupVariationRecord7GetTypeEhh, .-_ZN8opendnp320GroupVariationRecord7GetTypeEhh
	.align 2
	.p2align 4
	.globl	_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh
	.type	_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh, @function
_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh:
.LFB135:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movzbl	%dil, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movzbl	%sil, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movl	%r12d, %esi
	movl	%edi, %ebp
	movl	%r13d, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	_ZN8opendnp320GroupVariationRecord7GetTypeEhh@PLT
	movl	%r13d, %edi
	movl	%r12d, %esi
	movl	%eax, %ebx
	call	_ZN8opendnp320GroupVariationRecord11GetGroupVarEhh@PLT
	movzwl	%ax, %edi
	call	_ZN8opendnp322GroupVariationFromTypeEt@PLT
	cmpw	$-1, %ax
	jne	.L16
	leal	-110(%rbp), %edx
	sall	$8, %ebp
	cmpb	$4, %dl
	cmovb	%ebp, %eax
.L16:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	salq	$32, %rbx
	movzwl	%ax, %eax
	orq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE135:
	.size	_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh, .-_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh
	.align 2
	.p2align 4
	.globl	_ZN8opendnp320GroupVariationRecord9GetRecordEhh
	.type	_ZN8opendnp320GroupVariationRecord9GetRecordEhh, @function
_ZN8opendnp320GroupVariationRecord9GetRecordEhh:
.LFB133:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movzbl	%sil, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movzbl	%dil, %ebp
	movl	%r12d, %esi
	movl	%ebp, %edi
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp320GroupVariationRecord14GetEnumAndTypeEhh@PLT
	movl	%r12d, %edx
	leaq	16(%rsp), %rdi
	movl	%ebp, %esi
	movq	%rax, %r8
	movq	%rax, %rcx
	shrq	$32, %r8
	call	_ZN8opendnp320GroupVariationRecordC1EhhNS_14GroupVariationENS_18GroupVariationTypeE@PLT
	movq	16(%rsp), %rax
	movl	24(%rsp), %edx
	movq	40(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L21
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L21:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE133:
	.size	_ZN8opendnp320GroupVariationRecord9GetRecordEhh, .-_ZN8opendnp320GroupVariationRecord9GetRecordEhh
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
