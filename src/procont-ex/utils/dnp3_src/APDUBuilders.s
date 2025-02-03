	.file	"APDUBuilders.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp35build14ReadAllObjectsERNS_11APDURequestENS_16GroupVariationIDEh
	.type	_ZN8opendnp35build14ReadAllObjectsERNS_11APDURequestENS_16GroupVariationIDEh, @function
_ZN8opendnp35build14ReadAllObjectsERNS_11APDURequestENS_16GroupVariationIDEh:
.LFB276:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movzbl	%dl, %r9d
	xorl	%r8d, %r8d
	xorl	%ecx, %ecx
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	$1, %edx
	movl	%esi, %r13d
	movl	$1, %esi
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %r12
	movq	%r12, %rdi
	call	_ZN8opendnp315AppControlFieldC1Ebbbbh@PLT
	movq	(%rsp), %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper10SetControlENS_15AppControlFieldE@PLT
	movl	$1, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper11SetFunctionENS_12FunctionCodeE@PLT
	movq	%rbp, %rsi
	movq	%r12, %rdi
	call	_ZN8opendnp311APDUWrapper9GetWriterEv@PLT
	movl	$6, %edx
	movl	%r13d, %esi
	movq	%r12, %rdi
	call	_ZN8opendnp312HeaderWriter11WriteHeaderENS_16GroupVariationIDENS_13QualifierCodeE@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L5
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE276:
	.size	_ZN8opendnp35build14ReadAllObjectsERNS_11APDURequestENS_16GroupVariationIDEh, .-_ZN8opendnp35build14ReadAllObjectsERNS_11APDURequestENS_16GroupVariationIDEh
	.p2align 4
	.globl	_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE
	.type	_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE, @function
_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE:
.LFB278:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	movq	%rsi, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	_ZNK8opendnp310ClassField9HasClass1Ev@PLT
	testb	%al, %al
	je	.L10
	movl	$6, %edx
	movl	$572, %esi
	movq	%r12, %rdi
	call	_ZN8opendnp312HeaderWriter11WriteHeaderENS_16GroupVariationIDENS_13QualifierCodeE@PLT
	testb	%al, %al
	je	.L14
.L10:
	movq	%rbp, %rdi
	call	_ZNK8opendnp310ClassField9HasClass2Ev@PLT
	testb	%al, %al
	je	.L9
	movl	$6, %edx
	movl	$828, %esi
	movq	%r12, %rdi
	call	_ZN8opendnp312HeaderWriter11WriteHeaderENS_16GroupVariationIDENS_13QualifierCodeE@PLT
	testb	%al, %al
	je	.L14
.L9:
	movq	%rbp, %rdi
	call	_ZNK8opendnp310ClassField9HasClass3Ev@PLT
	testb	%al, %al
	je	.L13
	movl	$6, %edx
	movl	$1084, %esi
	movq	%r12, %rdi
	call	_ZN8opendnp312HeaderWriter11WriteHeaderENS_16GroupVariationIDENS_13QualifierCodeE@PLT
	testb	%al, %al
	je	.L14
.L13:
	movq	%rbp, %rdi
	call	_ZNK8opendnp310ClassField9HasClass0Ev@PLT
	testb	%al, %al
	jne	.L15
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	.cfi_restore_state
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%r12, %rdi
	movl	$6, %edx
	movl	$316, %esi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp312HeaderWriter11WriteHeaderENS_16GroupVariationIDENS_13QualifierCodeE@PLT
	.cfi_endproc
.LFE278:
	.size	_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE, .-_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE
	.p2align 4
	.globl	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh
	.type	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh, @function
_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh:
.LFB277:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movzbl	%cl, %r9d
	xorl	%r8d, %r8d
	xorl	%ecx, %ecx
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdx, %r13
	movl	$1, %edx
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movl	%esi, %ebx
	movl	$1, %esi
	subq	$56, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %r12
	movq	%r12, %rdi
	call	_ZN8opendnp315AppControlFieldC1Ebbbbh@PLT
	movq	(%rsp), %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper10SetControlENS_15AppControlFieldE@PLT
	movl	%ebx, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper11SetFunctionENS_12FunctionCodeE@PLT
	movq	%rbp, %rsi
	movq	%r12, %rdi
	call	_ZN8opendnp311APDUWrapper9GetWriterEv@PLT
	movq	%r13, %rsi
	movq	%r12, %rdi
	call	_ZN8opendnp35build17WriteClassHeadersERNS_12HeaderWriterERKNS_10ClassFieldE@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L20
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L20:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE277:
	.size	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh, .-_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh
	.p2align 4
	.globl	_ZN8opendnp35build13ReadIntegrityERNS_11APDURequestERKNS_10ClassFieldEh
	.type	_ZN8opendnp35build13ReadIntegrityERNS_11APDURequestERKNS_10ClassFieldEh, @function
_ZN8opendnp35build13ReadIntegrityERNS_11APDURequestERKNS_10ClassFieldEh:
.LFB275:
	.cfi_startproc
	movzbl	%dl, %ecx
	movq	%rsi, %rdx
	movl	$1, %esi
	jmp	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh@PLT
	.cfi_endproc
.LFE275:
	.size	_ZN8opendnp35build13ReadIntegrityERNS_11APDURequestERKNS_10ClassFieldEh, .-_ZN8opendnp35build13ReadIntegrityERNS_11APDURequestERKNS_10ClassFieldEh
	.p2align 4
	.globl	_ZN8opendnp35build18DisableUnsolicitedERNS_11APDURequestEh
	.type	_ZN8opendnp35build18DisableUnsolicitedERNS_11APDURequestEh, @function
_ZN8opendnp35build18DisableUnsolicitedERNS_11APDURequestEh:
.LFB279:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%esi, %ebx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp310ClassField15AllEventClassesEv@PLT
	movzbl	%bl, %ecx
	leaq	7(%rsp), %rdx
	movq	%rbp, %rdi
	movl	$21, %esi
	movb	%al, 7(%rsp)
	call	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh@PLT
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L25
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L25:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE279:
	.size	_ZN8opendnp35build18DisableUnsolicitedERNS_11APDURequestEh, .-_ZN8opendnp35build18DisableUnsolicitedERNS_11APDURequestEh
	.p2align 4
	.globl	_ZN8opendnp35build17EnableUnsolicitedERNS_11APDURequestERKNS_10ClassFieldEh
	.type	_ZN8opendnp35build17EnableUnsolicitedERNS_11APDURequestERKNS_10ClassFieldEh, @function
_ZN8opendnp35build17EnableUnsolicitedERNS_11APDURequestERKNS_10ClassFieldEh:
.LFB280:
	.cfi_startproc
	movzbl	%dl, %ecx
	movq	%rsi, %rdx
	movl	$20, %esi
	jmp	_ZN8opendnp35build12ClassRequestERNS_11APDURequestENS_12FunctionCodeERKNS_10ClassFieldEh@PLT
	.cfi_endproc
.LFE280:
	.size	_ZN8opendnp35build17EnableUnsolicitedERNS_11APDURequestERKNS_10ClassFieldEh, .-_ZN8opendnp35build17EnableUnsolicitedERNS_11APDURequestERKNS_10ClassFieldEh
	.p2align 4
	.globl	_ZN8opendnp35build15ClearRestartIINERNS_11APDURequestEh
	.type	_ZN8opendnp35build15ClearRestartIINERNS_11APDURequestEh, @function
_ZN8opendnp35build15ClearRestartIINERNS_11APDURequestEh:
.LFB281:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA281
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%esi, %ebx
	movl	$2, %esi
	subq	$112, %rsp
	.cfi_def_cfa_offset 144
	movq	%fs:40, %rax
	movq	%rax, 104(%rsp)
	xorl	%eax, %eax
	leaq	32(%rsp), %r12
.LEHB0:
	call	_ZN8opendnp311APDUWrapper11SetFunctionENS_12FunctionCodeE@PLT
	xorl	%ecx, %ecx
	xorl	%r8d, %r8d
	movl	$1, %edx
	movzbl	%bl, %r9d
	leaq	64(%rsp), %rdi
	movl	$1, %esi
	call	_ZN8opendnp315AppControlFieldC1Ebbbbh@PLT
	movq	64(%rsp), %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper10SetControlENS_15AppControlFieldE@PLT
	movq	%rbp, %rsi
	movq	%r12, %rdi
	call	_ZN8opendnp311APDUWrapper9GetWriterEv@PLT
	xorl	%edx, %edx
	movl	$3, %ecx
	movq	%r12, %rdi
	movl	$336, %esi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L28
	movq	32(%rsp), %rax
	movb	$7, 16(%rsp)
	movq	$7, 64(%rsp)
	movdqu	(%rax), %xmm0
	cmpl	$1, (%rax)
	movq	%rax, 96(%rsp)
	seta	72(%rsp)
	movups	%xmm0, 80(%rsp)
	ja	.L50
.L27:
	movq	104(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L51
	addq	$112, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L28:
	.cfi_restore_state
	call	_ZN7openpal6WSlice5EmptyEv@PLT
	leaq	16(%rsp), %rbp
	movb	$0, 15(%rsp)
	movl	%eax, 16(%rsp)
	cmpl	$1, %eax
	movq	%rdx, 24(%rsp)
	movdqu	16(%rsp), %xmm1
	movq	$0, 64(%rsp)
	movq	%rbp, 96(%rsp)
	seta	72(%rsp)
	movups	%xmm1, 80(%rsp)
	jbe	.L27
	leaq	15(%rsp), %rsi
	leaq	80(%rsp), %r12
.L49:
	movq	%r12, %rdi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	96(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE0:
	movq	96(%rsp), %rcx
	movl	(%rcx), %eax
	sall	$3, %eax
	movl	%eax, 68(%rsp)
	movzbl	72(%rsp), %eax
	testb	%al, %al
	je	.L27
	movzbl	65(%rsp), %edx
	movl	%edx, %eax
	cmpl	68(%rsp), %edx
	jnb	.L35
	testb	$7, %al
	jne	.L36
	movq	8(%rcx), %rdx
	shrb	$3, %al
	movzbl	%al, %eax
	movb	$0, (%rdx,%rax)
	movzbl	65(%rsp), %eax
	addl	$1, %eax
	cmpb	$0, 72(%rsp)
	movb	%al, 65(%rsp)
	je	.L27
	.p2align 4,,10
	.p2align 3
.L35:
	testb	%al, %al
	je	.L27
	movzbl	64(%rsp), %edx
	movq	%rbp, %rsi
	movq	%r12, %rdi
	leal	-1(%rax,%rdx), %eax
	movb	%al, 16(%rsp)
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movzbl	65(%rsp), %eax
	movq	96(%rsp), %rdi
	movl	%eax, %esi
	andl	$7, %eax
	shrb	$3, %sil
	cmpb	$1, %al
	sbbb	$-1, %sil
	movzbl	%sil, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L50:
	leaq	16(%rsp), %rbp
	leaq	80(%rsp), %r12
	movq	%rbp, %rsi
	jmp	.L49
	.p2align 4,,10
	.p2align 3
.L36:
	addl	$1, %eax
	movb	%al, 65(%rsp)
	jmp	.L35
.L51:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE281:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA281:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE281-.LLSDACSB281
.LLSDACSB281:
	.uleb128 .LEHB0-.LFB281
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
.LLSDACSE281:
	.text
	.size	_ZN8opendnp35build15ClearRestartIINERNS_11APDURequestEh, .-_ZN8opendnp35build15ClearRestartIINERNS_11APDURequestEh
	.p2align 4
	.globl	_ZN8opendnp35build12MeasureDelayERNS_11APDURequestEh
	.type	_ZN8opendnp35build12MeasureDelayERNS_11APDURequestEh, @function
_ZN8opendnp35build12MeasureDelayERNS_11APDURequestEh:
.LFB282:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movl	%esi, %ebx
	movl	$23, %esi
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
.LFE282:
	.size	_ZN8opendnp35build12MeasureDelayERNS_11APDURequestEh, .-_ZN8opendnp35build12MeasureDelayERNS_11APDURequestEh
	.p2align 4
	.globl	_ZN8opendnp35build15NullUnsolicitedERNS_12APDUResponseEhRKNS_8IINFieldE
	.type	_ZN8opendnp35build15NullUnsolicitedERNS_12APDUResponseEhRKNS_8IINFieldE, @function
_ZN8opendnp35build15NullUnsolicitedERNS_12APDUResponseEhRKNS_8IINFieldE:
.LFB283:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movzbl	%sil, %r9d
	movl	$1, %ecx
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	$1, %r8d
	movq	%rdi, %rbp
	movl	$1, %edx
	movl	$1, %esi
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	3(%rsp), %rdi
	call	_ZN8opendnp315AppControlFieldC1Ebbbbh@PLT
	movzbl	4(%rsp), %eax
	movzbl	3(%rsp), %esi
	movq	%rbp, %rdi
	salq	$8, %rax
	orq	%rax, %rsi
	movzbl	5(%rsp), %eax
	salq	$16, %rax
	orq	%rsi, %rax
	movzbl	6(%rsp), %esi
	salq	$24, %rsi
	orq	%rsi, %rax
	movzbl	7(%rsp), %esi
	salq	$32, %rsi
	orq	%rax, %rsi
	call	_ZN8opendnp311APDUWrapper10SetControlENS_15AppControlFieldE@PLT
	movl	$-126, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311APDUWrapper11SetFunctionENS_12FunctionCodeE@PLT
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L58
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rsi
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp312APDUResponse6SetIINERKNS_8IINFieldE@PLT
.L58:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE283:
	.size	_ZN8opendnp35build15NullUnsolicitedERNS_12APDUResponseEhRKNS_8IINFieldE, .-_ZN8opendnp35build15NullUnsolicitedERNS_12APDUResponseEhRKNS_8IINFieldE
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
