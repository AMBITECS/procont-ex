	.file	"LinkHeader.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeaderC2Ev
	.type	_ZN8opendnp310LinkHeaderC2Ev, @function
_ZN8opendnp310LinkHeaderC2Ev:
.LFB75:
	.cfi_startproc
	movb	$5, (%rdi)
	movl	$0, 2(%rdi)
	movb	$0, 6(%rdi)
	ret
	.cfi_endproc
.LFE75:
	.size	_ZN8opendnp310LinkHeaderC2Ev, .-_ZN8opendnp310LinkHeaderC2Ev
	.globl	_ZN8opendnp310LinkHeaderC1Ev
	.set	_ZN8opendnp310LinkHeaderC1Ev,_ZN8opendnp310LinkHeaderC2Ev
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeader9ChangeFCBEb
	.type	_ZN8opendnp310LinkHeader9ChangeFCBEb, @function
_ZN8opendnp310LinkHeader9ChangeFCBEb:
.LFB81:
	.cfi_startproc
	movzbl	6(%rdi), %eax
	movl	%eax, %edx
	andl	$-33, %eax
	orl	$32, %edx
	testb	%sil, %sil
	cmovne	%edx, %eax
	movb	%al, 6(%rdi)
	ret
	.cfi_endproc
.LFE81:
	.size	_ZN8opendnp310LinkHeader9ChangeFCBEb, .-_ZN8opendnp310LinkHeader9ChangeFCBEb
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE
	.type	_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE, @function
_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE:
.LFB82:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edi, %r12d
	movl	%ecx, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	%esi, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%edx, %ebx
	call	_ZN8opendnp318LinkFunctionToTypeENS_12LinkFunctionE@PLT
	movl	%eax, %edx
	orl	$-128, %edx
	testb	%r12b, %r12b
	cmovne	%edx, %eax
	movl	%eax, %edx
	orl	$32, %edx
	testb	%bpl, %bpl
	cmovne	%edx, %eax
	movl	%eax, %edx
	orl	$16, %edx
	testb	%bl, %bl
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	cmovne	%edx, %eax
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE82:
	.size	_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE, .-_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE
	.type	_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE, @function
_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE:
.LFB80:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movb	%sil, (%rdi)
	movzbl	16(%rsp), %esi
	movw	%dx, 2(%rdi)
	movzbl	%r9b, %edx
	movw	%cx, 4(%rdi)
	movzbl	24(%rsp), %ecx
	movzbl	%r8b, %edi
	call	_ZN8opendnp310LinkHeader11ControlByteEbbbNS_12LinkFunctionE@PLT
	movb	%al, 6(%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE80:
	.size	_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE, .-_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE
	.type	_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE, @function
_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE:
.LFB78:
	.cfi_startproc
	movzbl	8(%rsp), %eax
	movzwl	%cx, %ecx
	movzwl	%dx, %edx
	movzbl	%sil, %esi
	movzbl	%r9b, %r9d
	movzbl	%r8b, %r8d
	movl	%eax, 8(%rsp)
	jmp	_ZN8opendnp310LinkHeader3SetEhttbbbNS_12LinkFunctionE@PLT
	.cfi_endproc
.LFE78:
	.size	_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE, .-_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE
	.globl	_ZN8opendnp310LinkHeaderC1EhttbbbNS_12LinkFunctionE
	.set	_ZN8opendnp310LinkHeaderC1EhttbbbNS_12LinkFunctionE,_ZN8opendnp310LinkHeaderC2EhttbbbNS_12LinkFunctionE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp310LinkHeader4ReadEPKh
	.type	_ZN8opendnp310LinkHeader4ReadEPKh, @function
_ZN8opendnp310LinkHeader4ReadEPKh:
.LFB83:
	.cfi_startproc
	movzbl	2(%rsi), %eax
	movb	%al, (%rdi)
	movzwl	4(%rsi), %eax
	movw	%ax, 4(%rdi)
	movzwl	6(%rsi), %eax
	movw	%ax, 2(%rdi)
	movzbl	3(%rsi), %eax
	movb	%al, 6(%rdi)
	ret
	.cfi_endproc
.LFE83:
	.size	_ZN8opendnp310LinkHeader4ReadEPKh, .-_ZN8opendnp310LinkHeader4ReadEPKh
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp310LinkHeader5WriteEPh
	.type	_ZNK8opendnp310LinkHeader5WriteEPh, @function
_ZNK8opendnp310LinkHeader5WriteEPh:
.LFB84:
	.cfi_startproc
	movq	%rdi, %rax
	movl	$25605, %edx
	movq	%rsi, %rdi
	movw	%dx, (%rsi)
	movzbl	(%rax), %edx
	movb	%dl, 2(%rsi)
	movzwl	4(%rax), %edx
	movw	%dx, 4(%rsi)
	movzwl	2(%rax), %edx
	movw	%dx, 6(%rsi)
	movzbl	6(%rax), %eax
	movb	%al, 3(%rsi)
	movl	$8, %esi
	jmp	_ZN8opendnp33CRC6AddCrcEPhj@PLT
	.cfi_endproc
.LFE84:
	.size	_ZNK8opendnp310LinkHeader5WriteEPh, .-_ZNK8opendnp310LinkHeader5WriteEPh
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
