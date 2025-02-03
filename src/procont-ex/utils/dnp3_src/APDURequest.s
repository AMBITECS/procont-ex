	.file	"APDURequest.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE
	.type	_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE, @function
_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE:
.LFB246:
	.cfi_startproc
	jmp	_ZN8opendnp311APDUWrapperC2ERKN7openpal6WSliceE@PLT
	.cfi_endproc
.LFE246:
	.size	_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE, .-_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE
	.globl	_ZN8opendnp311APDURequestC1ERKN7openpal6WSliceE
	.set	_ZN8opendnp311APDURequestC1ERKN7openpal6WSliceE,_ZN8opendnp311APDURequestC2ERKN7openpal6WSliceE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311APDURequest15ConfigureHeaderENS_12FunctionCodeEh
	.type	_ZN8opendnp311APDURequest15ConfigureHeaderENS_12FunctionCodeEh, @function
_ZN8opendnp311APDURequest15ConfigureHeaderENS_12FunctionCodeEh:
.LFB248:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movl	$32, %esi
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%edx, %ebx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	call	_ZN8opendnp311APDUWrapper11SetFunctionENS_12FunctionCodeE@PLT
	movzbl	%bl, %edi
	call	_ZN8opendnp315AppControlField7RequestEh@PLT
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	movabsq	$1099511627775, %rsi
	popq	%rbx
	.cfi_def_cfa_offset 16
	andq	%rax, %rsi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp311APDUWrapper10SetControlENS_15AppControlFieldE@PLT
	.cfi_endproc
.LFE248:
	.size	_ZN8opendnp311APDURequest15ConfigureHeaderENS_12FunctionCodeEh, .-_ZN8opendnp311APDURequest15ConfigureHeaderENS_12FunctionCodeEh
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
