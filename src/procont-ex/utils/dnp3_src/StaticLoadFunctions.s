	.file	"StaticLoadFunctions.cpp"
	.text
	.section	.text._ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB446:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA446
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	0(%rbp), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	2(%rbp), %ecx
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %r14d
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r13b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r13b
	jne	.L65
	movl	$5, %ecx
	movl	$1, %edx
	movl	$515, %esi
	movq	%rbx, %rdi
.LEHB0:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L66
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE0:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L15:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L16
.L22:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L16
	movzbl	104(%rbx), %esi
	cmpb	%sil, 104(%rdi)
	jne	.L16
	cmpw	%r14w, 24(%rdi)
	jne	.L16
	testb	%al, %al
	je	.L1
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L18
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L19
	addq	$80, %rdi
.LEHB1:
	call	*24(%rsp)
.LEHE1:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L16
	jb	.L67
	movl	$1, 0(%rbp)
.L16:
	testb	%al, %al
	jne	.L68
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L69
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L66:
	.cfi_restore_state
	movq	_ZN8opendnp310Group3Var210ReadTargetERN7openpal6RSliceERNS_15DoubleBitBinaryE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movw	%r14w, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp310Group3Var211WriteTargetERKNS_15DoubleBitBinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L70
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L1
	xorl	%eax, %eax
	jmp	.L22
.L68:
	movl	32(%rsp), %edx
	movl	%eax, %r13d
	.p2align 4,,10
	.p2align 3
.L18:
	testl	%edx, %edx
	jne	.L19
.L25:
	movl	%r13d, %eax
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L19:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L67:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L16
	movzwl	%cx, %edx
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L70:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB2:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L65:
	xorl	%edx, %edx
	movl	$3, %ecx
	movl	$515, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L3
	movq	_ZN8opendnp310Group3Var210ReadTargetERN7openpal6RSliceERNS_15DoubleBitBinaryE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movb	%r14b, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp310Group3Var211WriteTargetERKNS_15DoubleBitBinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L71
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L1
	xorl	%eax, %eax
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L3:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE2:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L5:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	%dx, 2(%rbp)
	jb	.L6
.L12:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L6
	movzbl	104(%rbx), %ecx
	cmpb	%cl, 104(%rdi)
	jne	.L6
	cmpw	%r14w, 24(%rdi)
	jne	.L6
	testb	%al, %al
	je	.L1
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L35
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L36
	addq	$80, %rdi
.LEHB3:
	call	*24(%rsp)
.LEHE3:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L72
.L6:
	testb	%al, %al
	je	.L25
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L8:
	testl	%edx, %edx
	je	.L1
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L36:
	xorl	%eax, %eax
.L9:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1
	.p2align 4,,10
	.p2align 3
.L71:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB4:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L35:
	xorl	%eax, %eax
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L72:
	jb	.L73
	movl	$1, 0(%rbp)
	jmp	.L6
.L73:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L6
	movzwl	%cx, %edx
	jmp	.L12
.L69:
	call	__stack_chk_fail@PLT
.L42:
	movq	%rax, %rdi
	jmp	.L29
.L41:
	movq	%rax, %rdi
	jmp	.L26
.L29:
	cmpb	$0, 36(%rsp)
	je	.L30
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L30
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L30:
	call	_Unwind_Resume@PLT
.LEHE4:
.L26:
	cmpb	$0, 36(%rsp)
	je	.L30
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L30
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L30
	.cfi_endproc
.LFE446:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA446:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE446-.LLSDACSB446
.LLSDACSB446:
	.uleb128 .LEHB0-.LFB446
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB446
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L42-.LFB446
	.uleb128 0
	.uleb128 .LEHB2-.LFB446
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB446
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L41-.LFB446
	.uleb128 0
	.uleb128 .LEHB4-.LFB446
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE446:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB458:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA458
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	0(%rbp), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	2(%rbp), %ecx
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %r14d
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r13b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r13b
	jne	.L137
	movl	$5, %ecx
	movl	$1, %edx
	movl	$522, %esi
	movq	%rbx, %rdi
.LEHB5:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L138
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE5:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L88:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L89
.L95:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L89
	movzbl	104(%rbx), %esi
	cmpb	%sil, 104(%rdi)
	jne	.L89
	cmpw	%r14w, 24(%rdi)
	jne	.L89
	testb	%al, %al
	je	.L74
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L91
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L92
	addq	$80, %rdi
.LEHB6:
	call	*24(%rsp)
.LEHE6:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L89
	jb	.L139
	movl	$1, 0(%rbp)
.L89:
	testb	%al, %al
	jne	.L140
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L74:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L141
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L138:
	.cfi_restore_state
	movq	_ZN8opendnp311Group10Var210ReadTargetERN7openpal6RSliceERNS_18BinaryOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movw	%r14w, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp311Group10Var211WriteTargetERKNS_18BinaryOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L142
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L74
	xorl	%eax, %eax
	jmp	.L95
.L140:
	movl	32(%rsp), %edx
	movl	%eax, %r13d
	.p2align 4,,10
	.p2align 3
.L91:
	testl	%edx, %edx
	jne	.L92
.L98:
	movl	%r13d, %eax
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L92:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L98
	.p2align 4,,10
	.p2align 3
.L139:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L89
	movzwl	%cx, %edx
	jmp	.L95
	.p2align 4,,10
	.p2align 3
.L142:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB7:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L137:
	xorl	%edx, %edx
	movl	$3, %ecx
	movl	$522, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L76
	movq	_ZN8opendnp311Group10Var210ReadTargetERN7openpal6RSliceERNS_18BinaryOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movb	%r14b, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp311Group10Var211WriteTargetERKNS_18BinaryOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L143
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L74
	xorl	%eax, %eax
	jmp	.L85
	.p2align 4,,10
	.p2align 3
.L76:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE7:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L78:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	%dx, 2(%rbp)
	jb	.L79
.L85:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L79
	movzbl	104(%rbx), %ecx
	cmpb	%cl, 104(%rdi)
	jne	.L79
	cmpw	%r14w, 24(%rdi)
	jne	.L79
	testb	%al, %al
	je	.L74
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L108
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L109
	addq	$80, %rdi
.LEHB8:
	call	*24(%rsp)
.LEHE8:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L144
.L79:
	testb	%al, %al
	je	.L98
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L81:
	testl	%edx, %edx
	je	.L74
	jmp	.L82
	.p2align 4,,10
	.p2align 3
.L109:
	xorl	%eax, %eax
.L82:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L143:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB9:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L108:
	xorl	%eax, %eax
	jmp	.L81
	.p2align 4,,10
	.p2align 3
.L144:
	jb	.L145
	movl	$1, 0(%rbp)
	jmp	.L79
.L145:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L79
	movzwl	%cx, %edx
	jmp	.L85
.L141:
	call	__stack_chk_fail@PLT
.L115:
	movq	%rax, %rdi
	jmp	.L102
.L114:
	movq	%rax, %rdi
	jmp	.L99
.L102:
	cmpb	$0, 36(%rsp)
	je	.L103
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L103
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L103:
	call	_Unwind_Resume@PLT
.LEHE9:
.L99:
	cmpb	$0, 36(%rsp)
	je	.L103
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L103
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L103
	.cfi_endproc
.LFE458:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA458:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE458-.LLSDACSB458
.LLSDACSB458:
	.uleb128 .LEHB5-.LFB458
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB458
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L115-.LFB458
	.uleb128 0
	.uleb128 .LEHB7-.LFB458
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB458
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L114-.LFB458
	.uleb128 0
	.uleb128 .LEHB9-.LFB458
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSE458:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB457:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA457
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdx, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%rbx), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%rbx), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r12b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r12b
	jne	.L209
	movl	$9, %ecx
	movl	$1, %edx
	movl	$277, %esi
	movq	%r13, %rdi
.LEHB10:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L210
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE10:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L160:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L161
.L167:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L161
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L161
	cmpw	%r14w, 24(%rdi)
	jne	.L161
	testb	%al, %al
	je	.L146
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L163
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L164
	addq	$88, %rdi
.LEHB11:
	call	*24(%rsp)
.LEHE11:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%rbx), %edx
	movb	$0, 80(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L161
	jb	.L211
	movl	$1, (%rbx)
.L161:
	testb	%al, %al
	jne	.L212
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L146:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L213
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L210:
	.cfi_restore_state
	movq	_ZN8opendnp311Group21Var110ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group21Var111WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L214
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L146
	xorl	%eax, %eax
	jmp	.L167
.L212:
	movl	32(%rsp), %edx
	movl	%eax, %r12d
	.p2align 4,,10
	.p2align 3
.L163:
	testl	%edx, %edx
	jne	.L164
.L170:
	movl	%r12d, %eax
	jmp	.L146
	.p2align 4,,10
	.p2align 3
.L164:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L170
	.p2align 4,,10
	.p2align 3
.L211:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L161
	movzwl	%cx, %edx
	jmp	.L167
	.p2align 4,,10
	.p2align 3
.L214:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB12:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L160
	.p2align 4,,10
	.p2align 3
.L209:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$277, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L148
	movq	_ZN8opendnp311Group21Var110ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movb	%r14b, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group21Var111WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L215
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L146
	xorl	%eax, %eax
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L148:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE12:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L150:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%rbx)
	jb	.L151
.L157:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L151
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L151
	cmpw	%r14w, 24(%rdi)
	jne	.L151
	testb	%al, %al
	je	.L146
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L180
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L181
	addq	$88, %rdi
.LEHB13:
	call	*24(%rsp)
.LEHE13:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%rbx), %edx
	movb	$0, 80(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L216
.L151:
	testb	%al, %al
	je	.L170
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L153:
	testl	%edx, %edx
	je	.L146
	jmp	.L154
	.p2align 4,,10
	.p2align 3
.L181:
	xorl	%eax, %eax
.L154:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L146
	.p2align 4,,10
	.p2align 3
.L215:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB14:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L180:
	xorl	%eax, %eax
	jmp	.L153
	.p2align 4,,10
	.p2align 3
.L216:
	jb	.L217
	movl	$1, (%rbx)
	jmp	.L151
.L217:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L151
	movzwl	%cx, %edx
	jmp	.L157
.L213:
	call	__stack_chk_fail@PLT
.L187:
	movq	%rax, %rdi
	jmp	.L174
.L186:
	movq	%rax, %rdi
	jmp	.L171
.L174:
	cmpb	$0, 36(%rsp)
	je	.L175
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L175
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L175:
	call	_Unwind_Resume@PLT
.LEHE14:
.L171:
	cmpb	$0, 36(%rsp)
	je	.L175
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L175
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L175
	.cfi_endproc
.LFE457:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA457:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE457-.LLSDACSB457
.LLSDACSB457:
	.uleb128 .LEHB10-.LFB457
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB457
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L187-.LFB457
	.uleb128 0
	.uleb128 .LEHB12-.LFB457
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB13-.LFB457
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L186-.LFB457
	.uleb128 0
	.uleb128 .LEHB14-.LFB457
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSE457:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB463:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA463
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdx, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%rbx), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	2(%rbx), %ecx
	movzwl	16(%rdx,%rax,8), %r14d
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	16(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r12b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r12b
	jne	.L281
	movl	$15, %ecx
	movl	$1, %edx
	movl	$1074, %esi
	movq	%r13, %rdi
.LEHB15:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L282
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE15:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L232:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	16(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L233
.L239:
	leaq	0(,%rdx,8), %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 24(%rdi)
	je	.L233
	movzbl	48(%r13), %esi
	cmpb	%sil, 48(%rdi)
	jne	.L233
	cmpw	%r14w, 16(%rdi)
	jne	.L233
	testb	%al, %al
	je	.L218
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L235
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L236
	addq	$32, %rdi
.LEHB16:
	call	*24(%rsp)
.LEHE16:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbx), %edx
	movb	$0, 24(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L233
	jb	.L283
	movl	$1, (%rbx)
.L233:
	testb	%al, %al
	jne	.L284
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L218:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L285
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L282:
	.cfi_restore_state
	movq	_ZN8opendnp311Group50Var410ReadTargetERN7openpal6RSliceERNS_15TimeAndIntervalE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$11, 8(%rsp)
	movhps	_ZN8opendnp311Group50Var411WriteTargetERKNS_15TimeAndIntervalERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L286
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	16(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L218
	xorl	%eax, %eax
	jmp	.L239
.L284:
	movl	32(%rsp), %edx
	movl	%eax, %r12d
	.p2align 4,,10
	.p2align 3
.L235:
	testl	%edx, %edx
	jne	.L236
.L242:
	movl	%r12d, %eax
	jmp	.L218
	.p2align 4,,10
	.p2align 3
.L236:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L242
	.p2align 4,,10
	.p2align 3
.L283:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L233
	movzwl	%cx, %edx
	jmp	.L239
	.p2align 4,,10
	.p2align 3
.L286:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB17:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L232
	.p2align 4,,10
	.p2align 3
.L281:
	xorl	%edx, %edx
	movl	$13, %ecx
	movl	$1074, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L220
	movq	_ZN8opendnp311Group50Var410ReadTargetERN7openpal6RSliceERNS_15TimeAndIntervalE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movb	%r14b, (%rsp)
	movl	$11, 8(%rsp)
	movhps	_ZN8opendnp311Group50Var411WriteTargetERKNS_15TimeAndIntervalERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L287
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	16(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L218
	xorl	%eax, %eax
	jmp	.L229
	.p2align 4,,10
	.p2align 3
.L220:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE17:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L222:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	16(%r13), %r14d
	cmpw	%dx, 2(%rbx)
	jb	.L223
.L229:
	leaq	0(,%rdx,8), %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 24(%rdi)
	je	.L223
	movzbl	48(%r13), %esi
	cmpb	%sil, 48(%rdi)
	jne	.L223
	cmpw	%r14w, 16(%rdi)
	jne	.L223
	testb	%al, %al
	je	.L218
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L252
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L253
	addq	$32, %rdi
.LEHB18:
	call	*24(%rsp)
.LEHE18:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbx), %edx
	movb	$0, 24(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L288
.L223:
	testb	%al, %al
	je	.L242
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L225:
	testl	%edx, %edx
	je	.L218
	jmp	.L226
	.p2align 4,,10
	.p2align 3
.L253:
	xorl	%eax, %eax
.L226:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L218
	.p2align 4,,10
	.p2align 3
.L287:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB19:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L222
	.p2align 4,,10
	.p2align 3
.L252:
	xorl	%eax, %eax
	jmp	.L225
	.p2align 4,,10
	.p2align 3
.L288:
	jb	.L289
	movl	$1, (%rbx)
	jmp	.L223
.L289:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L223
	movzwl	%cx, %edx
	jmp	.L229
.L285:
	call	__stack_chk_fail@PLT
.L259:
	movq	%rax, %rdi
	jmp	.L246
.L258:
	movq	%rax, %rdi
	jmp	.L243
.L246:
	cmpb	$0, 36(%rsp)
	je	.L247
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L247
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L247:
	call	_Unwind_Resume@PLT
.LEHE19:
.L243:
	cmpb	$0, 36(%rsp)
	je	.L247
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L247
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L247
	.cfi_endproc
.LFE463:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA463:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE463-.LLSDACSB463
.LLSDACSB463:
	.uleb128 .LEHB15-.LFB463
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB16-.LFB463
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L259-.LFB463
	.uleb128 0
	.uleb128 .LEHB17-.LFB463
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB463
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L258-.LFB463
	.uleb128 0
	.uleb128 .LEHB19-.LFB463
	.uleb128 .LEHE19-.LEHB19
	.uleb128 0
	.uleb128 0
.LLSDACSE463:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB445:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA445
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rsi, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	0(%rbp), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	2(%rbp), %ecx
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %r14d
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r13b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r13b
	jne	.L353
	movl	$5, %ecx
	movl	$1, %edx
	movl	$513, %esi
	movq	%rbx, %rdi
.LEHB20:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L354
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE20:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L304:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L305
.L311:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L305
	movzbl	104(%rbx), %esi
	cmpb	%sil, 104(%rdi)
	jne	.L305
	cmpw	%r14w, 24(%rdi)
	jne	.L305
	testb	%al, %al
	je	.L290
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L307
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L308
	addq	$80, %rdi
.LEHB21:
	call	*24(%rsp)
.LEHE21:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L305
	jb	.L355
	movl	$1, 0(%rbp)
.L305:
	testb	%al, %al
	jne	.L356
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L290:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L357
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L354:
	.cfi_restore_state
	movq	_ZN8opendnp310Group1Var210ReadTargetERN7openpal6RSliceERNS_6BinaryE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movw	%r14w, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp310Group1Var211WriteTargetERKNS_6BinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L358
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L290
	xorl	%eax, %eax
	jmp	.L311
.L356:
	movl	32(%rsp), %edx
	movl	%eax, %r13d
	.p2align 4,,10
	.p2align 3
.L307:
	testl	%edx, %edx
	jne	.L308
.L314:
	movl	%r13d, %eax
	jmp	.L290
	.p2align 4,,10
	.p2align 3
.L308:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L314
	.p2align 4,,10
	.p2align 3
.L355:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L305
	movzwl	%cx, %edx
	jmp	.L311
	.p2align 4,,10
	.p2align 3
.L358:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB22:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L304
	.p2align 4,,10
	.p2align 3
.L353:
	xorl	%edx, %edx
	movl	$3, %ecx
	movl	$513, %esi
	movq	%rbx, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L292
	movq	_ZN8opendnp310Group1Var210ReadTargetERN7openpal6RSliceERNS_6BinaryE@GOTPCREL(%rip), %xmm0
	movq	(%rbx), %rdx
	movb	%r14b, (%rsp)
	movl	$1, 8(%rsp)
	movhps	_ZN8opendnp310Group1Var211WriteTargetERKNS_6BinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L359
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	2(%rbp), %dx
	ja	.L290
	xorl	%eax, %eax
	jmp	.L301
	.p2align 4,,10
	.p2align 3
.L292:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE22:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L294:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	leaq	0(,%rdx,8), %rbx
	subq	%rdx, %rbx
	salq	$4, %rbx
	addq	%rsi, %rbx
	movzwl	24(%rbx), %r14d
	cmpw	%dx, 2(%rbp)
	jb	.L295
.L301:
	leaq	0(,%rdx,8), %rdi
	subq	%rdx, %rdi
	salq	$4, %rdi
	addq	%rsi, %rdi
	cmpb	$0, 72(%rdi)
	je	.L295
	movzbl	104(%rbx), %ecx
	cmpb	%cl, 104(%rdi)
	jne	.L295
	cmpw	%r14w, 24(%rdi)
	jne	.L295
	testb	%al, %al
	je	.L290
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L324
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L325
	addq	$80, %rdi
.LEHB23:
	call	*24(%rsp)
.LEHE23:
	movzwl	0(%rbp), %edx
	movq	8(%r12), %rsi
	addl	$1, 32(%rsp)
	leaq	0(,%rdx,8), %rax
	movq	%rdx, %rcx
	subq	%rdx, %rax
	movzwl	2(%rbp), %edx
	salq	$4, %rax
	movb	$0, 72(%rsi,%rax)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L360
.L295:
	testb	%al, %al
	je	.L314
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L297:
	testl	%edx, %edx
	je	.L290
	jmp	.L298
	.p2align 4,,10
	.p2align 3
.L325:
	xorl	%eax, %eax
.L298:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L290
	.p2align 4,,10
	.p2align 3
.L359:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB24:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L294
	.p2align 4,,10
	.p2align 3
.L324:
	xorl	%eax, %eax
	jmp	.L297
	.p2align 4,,10
	.p2align 3
.L360:
	jb	.L361
	movl	$1, 0(%rbp)
	jmp	.L295
.L361:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, 0(%rbp)
	cmpw	%cx, %dx
	jb	.L295
	movzwl	%cx, %edx
	jmp	.L301
.L357:
	call	__stack_chk_fail@PLT
.L331:
	movq	%rax, %rdi
	jmp	.L318
.L330:
	movq	%rax, %rdi
	jmp	.L315
.L318:
	cmpb	$0, 36(%rsp)
	je	.L319
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L319
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L319:
	call	_Unwind_Resume@PLT
.LEHE24:
.L315:
	cmpb	$0, 36(%rsp)
	je	.L319
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L319
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L319
	.cfi_endproc
.LFE445:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA445:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE445-.LLSDACSB445
.LLSDACSB445:
	.uleb128 .LEHB20-.LFB445
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB21-.LFB445
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L331-.LFB445
	.uleb128 0
	.uleb128 .LEHB22-.LFB445
	.uleb128 .LEHE22-.LEHB22
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB23-.LFB445
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L330-.LFB445
	.uleb128 0
	.uleb128 .LEHB24-.LFB445
	.uleb128 .LEHE24-.LEHB24
	.uleb128 0
	.uleb128 0
.LLSDACSE445:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB464:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA464
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdx, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%rdx), %edx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	movq	8(%rdi), %rax
	leaq	(%rdx,%rdx,8), %rdx
	movzwl	24(%rax,%rdx,8), %r14d
	movzwl	2(%rbx), %edx
	leaq	(%rdx,%rdx,8), %rdx
	movzwl	24(%rax,%rdx,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%r12b
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %r12b
	jne	.L425
	movl	$11, %ecx
	movl	$1, %edx
	movl	$377, %esi
	movq	%r13, %rdi
.LEHB25:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L426
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE25:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L376:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	(%rdx,%rdx,8), %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L377
.L383:
	leaq	(%rdx,%rdx,8), %rdx
	leaq	(%rsi,%rdx,8), %rdi
	cmpb	$0, 32(%rdi)
	je	.L377
	movzbl	64(%r13), %ecx
	cmpb	%cl, 64(%rdi)
	jne	.L377
	cmpw	%r14w, 24(%rdi)
	jne	.L377
	testb	%al, %al
	je	.L362
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L379
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L380
	addq	$40, %rdi
.LEHB26:
	call	*24(%rsp)
.LEHE26:
	movzwl	(%rbx), %eax
	movq	8(%rbp), %rsi
	movzwl	2(%rbx), %edx
	addl	$1, 32(%rsp)
	movq	%rax, %rcx
	leaq	(%rax,%rax,8), %rax
	movb	$0, 32(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	ja	.L377
	jb	.L427
	movl	$1, (%rbx)
.L377:
	testb	%al, %al
	jne	.L428
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L362:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L429
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L426:
	.cfi_restore_state
	movq	_ZN8opendnp312Group121Var110ReadTargetERN7openpal6RSliceERNS_12SecurityStatE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$7, 8(%rsp)
	movhps	_ZN8opendnp312Group121Var111WriteTargetERKNS_12SecurityStatERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L430
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	(%rdx,%rdx,8), %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L362
	xorl	%eax, %eax
	jmp	.L383
.L428:
	movl	32(%rsp), %edx
	movl	%eax, %r12d
	.p2align 4,,10
	.p2align 3
.L379:
	testl	%edx, %edx
	jne	.L380
.L386:
	movl	%r12d, %eax
	jmp	.L362
	.p2align 4,,10
	.p2align 3
.L380:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	jmp	.L386
	.p2align 4,,10
	.p2align 3
.L427:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L377
	movzwl	%cx, %edx
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L430:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB27:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L376
	.p2align 4,,10
	.p2align 3
.L425:
	xorl	%edx, %edx
	movl	$9, %ecx
	movl	$377, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	je	.L364
	movq	_ZN8opendnp312Group121Var110ReadTargetERN7openpal6RSliceERNS_12SecurityStatE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movb	%r14b, (%rsp)
	movl	$7, 8(%rsp)
	movhps	_ZN8opendnp312Group121Var111WriteTargetERKNS_12SecurityStatERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm2
	cmpl	$1, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L431
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	(%rdx,%rdx,8), %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rbx), %dx
	ja	.L362
	xorl	%eax, %eax
	jmp	.L373
	.p2align 4,,10
	.p2align 3
.L364:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE27:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L366:
	movzwl	(%rbx), %edx
	movq	8(%rbp), %rsi
	leaq	(%rdx,%rdx,8), %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%rbx)
	jb	.L367
.L373:
	leaq	(%rdx,%rdx,8), %rdx
	leaq	(%rsi,%rdx,8), %rdi
	cmpb	$0, 32(%rdi)
	je	.L367
	movzbl	64(%r13), %ecx
	cmpb	%cl, 64(%rdi)
	jne	.L367
	cmpw	%r14w, 24(%rdi)
	jne	.L367
	testb	%al, %al
	je	.L362
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L396
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L397
	addq	$40, %rdi
.LEHB28:
	call	*24(%rsp)
.LEHE28:
	movzwl	(%rbx), %eax
	movq	8(%rbp), %rsi
	movzwl	2(%rbx), %edx
	addl	$1, 32(%rsp)
	movq	%rax, %rcx
	leaq	(%rax,%rax,8), %rax
	movb	$0, 32(%rsi,%rax,8)
	movzbl	36(%rsp), %eax
	cmpw	%dx, %cx
	jbe	.L432
.L367:
	testb	%al, %al
	je	.L386
	movl	32(%rsp), %edx
	.p2align 4,,10
	.p2align 3
.L369:
	testl	%edx, %edx
	je	.L362
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L397:
	xorl	%eax, %eax
.L370:
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L362
	.p2align 4,,10
	.p2align 3
.L431:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB29:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L366
	.p2align 4,,10
	.p2align 3
.L396:
	xorl	%eax, %eax
	jmp	.L369
	.p2align 4,,10
	.p2align 3
.L432:
	jb	.L433
	movl	$1, (%rbx)
	jmp	.L367
.L433:
	addl	$1, %ecx
	addl	$1, %r14d
	movw	%cx, (%rbx)
	cmpw	%cx, %dx
	jb	.L367
	movzwl	%cx, %edx
	jmp	.L373
.L429:
	call	__stack_chk_fail@PLT
.L403:
	movq	%rax, %rdi
	jmp	.L390
.L402:
	movq	%rax, %rdi
	jmp	.L387
.L390:
	cmpb	$0, 36(%rsp)
	je	.L391
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L391
	movzwl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
.L391:
	call	_Unwind_Resume@PLT
.LEHE29:
.L387:
	cmpb	$0, 36(%rsp)
	je	.L391
	movl	32(%rsp), %eax
	testl	%eax, %eax
	je	.L391
	movzbl	(%rsp), %edx
	leal	-1(%rax,%rdx), %edx
	movq	48(%rsp), %rax
	movb	%dl, (%rax)
	jmp	.L391
	.cfi_endproc
.LFE464:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA464:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE464-.LLSDACSB464
.LLSDACSB464:
	.uleb128 .LEHB25-.LFB464
	.uleb128 .LEHE25-.LEHB25
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB26-.LFB464
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L403-.LFB464
	.uleb128 0
	.uleb128 .LEHB27-.LFB464
	.uleb128 .LEHE27-.LEHB27
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB28-.LFB464
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L402-.LFB464
	.uleb128 0
	.uleb128 .LEHB29-.LFB464
	.uleb128 .LEHE29-.LEHB29
	.uleb128 0
	.uleb128 0
.LLSDACSE464:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB444:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA444
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movzwl	0(%rbp), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	movzwl	2(%rbp), %ecx
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %r15d
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	movzwl	24(%rdx,%rax), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r15w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L498
	movl	$5, %ecx
	movl	$1, %edx
	movl	$257, %esi
	movq	%r14, %rdi
.LEHB30:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	movl	%eax, %r13d
	testb	%al, %al
	jne	.L499
	call	_ZN7openpal6WSlice5EmptyEv@PLT
	movq	$0, 32(%rsp)
	movq	%rdx, 24(%rsp)
	xorl	%edx, %edx
	cmpl	$3, %eax
	movl	%eax, 16(%rsp)
	movdqu	16(%rsp), %xmm1
	movw	%dx, 14(%rsp)
	leaq	16(%rsp), %rdx
	movq	%rdx, 64(%rsp)
	seta	40(%rsp)
	movups	%xmm1, 48(%rsp)
	ja	.L500
.L453:
	movzwl	0(%rbp), %ecx
	movq	8(%r12), %r9
	leaq	0(,%rcx,8), %rdi
	subq	%rcx, %rdi
	salq	$4, %rdi
	addq	%r9, %rdi
	movzwl	24(%rdi), %esi
	cmpw	2(%rbp), %cx
	ja	.L455
	movl	$1, %r8d
	.p2align 4,,10
	.p2align 3
.L462:
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	addq	%r9, %rax
	cmpb	$0, 72(%rax)
	je	.L455
	movzbl	104(%rdi), %edx
	cmpb	%dl, 104(%rax)
	jne	.L455
	cmpw	%si, 24(%rax)
	jne	.L455
	testb	%r13b, %r13b
	je	.L434
	movzwl	34(%rsp), %edx
	movl	%edx, %ecx
	cmpl	36(%rsp), %edx
	jb	.L501
.L457:
	testw	%cx, %cx
	jne	.L502
.L463:
	movl	%ebx, %r13d
	.p2align 4,,10
	.p2align 3
.L434:
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L503
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%r13d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L499:
	.cfi_restore_state
	movq	(%r14), %rax
	xorl	%ecx, %ecx
	xorl	%r13d, %r13d
	movw	%r15w, 16(%rsp)
	movw	%r15w, 32(%rsp)
	leaq	16(%rsp), %rsi
	movdqu	(%rax), %xmm0
	cmpl	$3, (%rax)
	movw	%cx, 34(%rsp)
	movl	$0, 36(%rsp)
	movq	%rax, 64(%rsp)
	seta	40(%rsp)
	movups	%xmm0, 48(%rsp)
	jbe	.L453
.L497:
	leaq	48(%rsp), %rdi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	64(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE30:
	movq	64(%rsp), %rax
	movzbl	40(%rsp), %r13d
	movl	(%rax), %eax
	sall	$3, %eax
	movl	%eax, 36(%rsp)
	jmp	.L453
	.p2align 4,,10
	.p2align 3
.L501:
	movzbl	96(%rax), %r9d
	movl	%edx, %eax
	shrw	$3, %ax
	andw	$7, %cx
	jne	.L458
	movq	64(%rsp), %r10
	movzwl	%ax, %edx
	movq	8(%r10), %r10
	movb	$0, (%r10,%rdx)
.L458:
	testb	%r9b, %r9b
	je	.L459
	movq	64(%rsp), %rdx
	movzwl	%ax, %eax
	movzwl	%cx, %ecx
	addq	8(%rdx), %rax
	movl	%r8d, %edx
	sall	%cl, %edx
	orb	%dl, (%rax)
.L459:
	movzwl	0(%rbp), %eax
	movq	8(%r12), %r9
	addw	$1, 34(%rsp)
	leaq	0(,%rax,8), %rcx
	movq	%rax, %rdx
	subq	%rax, %rcx
	movzwl	2(%rbp), %eax
	salq	$4, %rcx
	movb	$0, 72(%r9,%rcx)
	cmpw	%ax, %dx
	jbe	.L504
.L460:
	movzbl	40(%rsp), %r13d
.L455:
	testb	%r13b, %r13b
	jne	.L505
	movl	$1, %r13d
	jmp	.L434
	.p2align 4,,10
	.p2align 3
.L504:
	jb	.L506
	movl	$1, 0(%rbp)
	jmp	.L460
	.p2align 4,,10
	.p2align 3
.L506:
	addl	$1, %edx
	movzbl	40(%rsp), %r13d
	addl	$1, %esi
	movw	%dx, 0(%rbp)
	cmpw	%dx, %ax
	jb	.L455
	movzwl	%dx, %ecx
	jmp	.L462
	.p2align 4,,10
	.p2align 3
.L500:
	leaq	14(%rsp), %rsi
	jmp	.L497
	.p2align 4,,10
	.p2align 3
.L502:
	movzwl	32(%rsp), %eax
	leaq	16(%rsp), %rsi
	leaq	48(%rsp), %rdi
	leal	-1(%rcx,%rax), %ecx
	movw	%cx, 16(%rsp)
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movzwl	34(%rsp), %eax
	movq	64(%rsp), %rdi
	movl	%eax, %esi
	andl	$7, %eax
	shrw	$3, %si
	cmpw	$1, %ax
	sbbw	$-1, %si
	movzwl	%si, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L463
	.p2align 4,,10
	.p2align 3
.L498:
	movl	$3, %ecx
	xorl	%edx, %edx
	movl	$257, %esi
	movq	%r14, %rdi
.LEHB31:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE31:
	movl	%eax, %r13d
	testb	%al, %al
	je	.L436
	movq	(%r14), %rax
	movb	%r15b, 16(%rsp)
	xorl	%r13d, %r13d
	leaq	16(%rsp), %rsi
	movb	%r15b, 32(%rsp)
	movb	$0, 33(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	movl	$0, 36(%rsp)
	movq	%rax, 64(%rsp)
	seta	40(%rsp)
	movups	%xmm2, 48(%rsp)
	ja	.L496
.L438:
	movzwl	0(%rbp), %ecx
	movq	8(%r12), %r9
	leaq	0(,%rcx,8), %rdi
	subq	%rcx, %rdi
	salq	$4, %rdi
	addq	%r9, %rdi
	movzwl	24(%rdi), %esi
	cmpw	2(%rbp), %cx
	ja	.L440
	movl	$1, %r8d
	.p2align 4,,10
	.p2align 3
.L447:
	leaq	0(,%rcx,8), %rax
	subq	%rcx, %rax
	salq	$4, %rax
	addq	%r9, %rax
	cmpb	$0, 72(%rax)
	je	.L440
	movzbl	104(%rdi), %ecx
	cmpb	%cl, 104(%rax)
	jne	.L440
	cmpw	24(%rax), %si
	jne	.L440
	testb	%r13b, %r13b
	je	.L434
	movzbl	33(%rsp), %edx
	movl	%edx, %ecx
	cmpl	36(%rsp), %edx
	jnb	.L467
	movzbl	96(%rax), %edx
	movl	%ecx, %eax
	shrb	$3, %al
	andl	$7, %ecx
	jne	.L443
	movq	64(%rsp), %r10
	movzbl	%al, %r9d
	movq	8(%r10), %r10
	movb	$0, (%r10,%r9)
.L443:
	testb	%dl, %dl
	je	.L444
	movq	64(%rsp), %rdx
	movzbl	%al, %eax
	addq	8(%rdx), %rax
	movl	%r8d, %edx
	sall	%cl, %edx
	orb	%dl, (%rax)
.L444:
	movzwl	0(%rbp), %eax
	movq	8(%r12), %r9
	addb	$1, 33(%rsp)
	leaq	0(,%rax,8), %rcx
	movq	%rax, %rdx
	subq	%rax, %rcx
	movzwl	2(%rbp), %eax
	salq	$4, %rcx
	movb	$0, 72(%r9,%rcx)
	cmpw	%ax, %dx
	jbe	.L507
.L445:
	movzbl	40(%rsp), %r13d
.L440:
	movzbl	33(%rsp), %ecx
	testb	%r13b, %r13b
	je	.L463
	jmp	.L442
	.p2align 4,,10
	.p2align 3
.L507:
	jb	.L508
	movl	$1, 0(%rbp)
	jmp	.L445
	.p2align 4,,10
	.p2align 3
.L508:
	addl	$1, %edx
	movzbl	40(%rsp), %r13d
	addl	$1, %esi
	movw	%dx, 0(%rbp)
	cmpw	%dx, %ax
	jb	.L440
	movzwl	%dx, %ecx
	jmp	.L447
	.p2align 4,,10
	.p2align 3
.L467:
	xorl	%r13d, %r13d
.L442:
	testb	%cl, %cl
	je	.L434
	movzbl	32(%rsp), %eax
	leaq	16(%rsp), %rsi
	leaq	48(%rsp), %rdi
	leal	-1(%rcx,%rax), %ecx
	movb	%cl, 16(%rsp)
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movzbl	33(%rsp), %edx
	movq	64(%rsp), %rdi
	movl	%edx, %eax
	andl	$7, %edx
	shrb	$3, %al
	cmpb	$1, %dl
	sbbb	$-1, %al
	movzbl	%al, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L434
.L436:
.LEHB32:
	call	_ZN7openpal6WSlice5EmptyEv@PLT
	movb	$0, 14(%rsp)
	movq	%rdx, 24(%rsp)
	cmpl	$1, %eax
	leaq	16(%rsp), %rdx
	movl	%eax, 16(%rsp)
	movdqu	16(%rsp), %xmm3
	movq	$0, 32(%rsp)
	movq	%rdx, 64(%rsp)
	seta	40(%rsp)
	movups	%xmm3, 48(%rsp)
	jbe	.L438
	leaq	14(%rsp), %rsi
.L496:
	leaq	48(%rsp), %rdi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	64(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE32:
	movq	64(%rsp), %rax
	movzbl	40(%rsp), %r13d
	movl	(%rax), %eax
	sall	$3, %eax
	movl	%eax, 36(%rsp)
	jmp	.L438
.L503:
	call	__stack_chk_fail@PLT
.L505:
	movzwl	34(%rsp), %ecx
	movl	%r13d, %ebx
	jmp	.L457
	.cfi_endproc
.LFE444:
	.section	.gcc_except_table._ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA444:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE444-.LLSDACSB444
.LLSDACSB444:
	.uleb128 .LEHB30-.LFB444
	.uleb128 .LEHE30-.LEHB30
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB31-.LFB444
	.uleb128 .LEHE31-.LEHB31
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB32-.LFB444
	.uleb128 .LEHE32-.LEHB32
	.uleb128 0
	.uleb128 0
.LLSDACSE444:
	.section	.text._ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.text
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE, @function
_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE:
.LFB393:
	.cfi_startproc
	testb	%dil, %dil
	je	.L511
	movq	_ZN8opendnp319WriteWithSerializerINS_10BinarySpecENS_10Group1Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L511:
	movq	_ZN8opendnp319WriteSingleBitfieldINS_10BinarySpecENS_10Group1Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE393:
	.size	_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE, .-_ZN8opendnp315GetStaticWriterENS_21StaticBinaryVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE, @function
_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE:
.LFB394:
	.cfi_startproc
	movq	_ZN8opendnp319WriteWithSerializerINS_19DoubleBitBinarySpecENS_10Group3Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE394:
	.size	_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE, .-_ZN8opendnp315GetStaticWriterENS_27StaticDoubleBinaryVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE, @function
_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE:
.LFB395:
	.cfi_startproc
	cmpb	$5, %dil
	ja	.L521
	leaq	.L516(%rip), %rdx
	movzbl	%dil, %edi
	movslq	(%rdx,%rdi,4), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L516:
	.long	.L521-.L516
	.long	.L520-.L516
	.long	.L519-.L516
	.long	.L518-.L516
	.long	.L517-.L516
	.long	.L515-.L516
	.text
	.p2align 4,,10
	.p2align 3
.L520:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L515:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L519:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L518:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L517:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
.L521:
	movq	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE395:
	.size	_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE, .-_ZN8opendnp315GetStaticWriterENS_21StaticAnalogVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE, @function
_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE:
.LFB396:
	.cfi_startproc
	cmpb	$2, %dil
	je	.L524
	cmpb	$3, %dil
	je	.L525
	cmpb	$1, %dil
	je	.L527
	movq	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L525:
	movq	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L527:
	movq	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L524:
	movq	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE396:
	.size	_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE, .-_ZN8opendnp315GetStaticWriterENS_22StaticCounterVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE, @function
_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE:
.LFB397:
	.cfi_startproc
	movq	_ZN8opendnp319WriteWithSerializerINS_17FrozenCounterSpecENS_11Group21Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE397:
	.size	_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE, .-_ZN8opendnp315GetStaticWriterENS_28StaticFrozenCounterVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE, @function
_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE:
.LFB398:
	.cfi_startproc
	movq	_ZN8opendnp319WriteWithSerializerINS_22BinaryOutputStatusSpecENS_11Group10Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE398:
	.size	_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE, .-_ZN8opendnp315GetStaticWriterENS_33StaticBinaryOutputStatusVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE, @function
_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE:
.LFB399:
	.cfi_startproc
	cmpb	$2, %dil
	je	.L532
	cmpb	$3, %dil
	je	.L533
	cmpb	$1, %dil
	je	.L535
	movq	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L533:
	movq	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L535:
	movq	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.p2align 4,,10
	.p2align 3
.L532:
	movq	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE399:
	.size	_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE, .-_ZN8opendnp315GetStaticWriterENS_33StaticAnalogOutputStatusVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE, @function
_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE:
.LFB400:
	.cfi_startproc
	movq	_ZN8opendnp319WriteWithSerializerINS_19TimeAndIntervalSpecENS_11Group50Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE400:
	.size	_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE, .-_ZN8opendnp315GetStaticWriterENS_30StaticTimeAndIntervalVariationE
	.p2align 4
	.globl	_ZN8opendnp315GetStaticWriterENS_27StaticSecurityStatVariationE
	.type	_ZN8opendnp315GetStaticWriterENS_27StaticSecurityStatVariationE, @function
_ZN8opendnp315GetStaticWriterENS_27StaticSecurityStatVariationE:
.LFB401:
	.cfi_startproc
	movq	_ZN8opendnp319WriteWithSerializerINS_16SecurityStatSpecENS_12Group121Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE@GOTPCREL(%rip), %rax
	ret
	.cfi_endproc
.LFE401:
	.size	_ZN8opendnp315GetStaticWriterENS_27StaticSecurityStatVariationE, .-_ZN8opendnp315GetStaticWriterENS_27StaticSecurityStatVariationE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev:
.LFB527:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L538
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L538
	movzbl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movb	%al, (%rdx)
.L538:
	ret
	.cfi_endproc
.LFE527:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED2Ev
	.section	.text._ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,"axG",@progbits,_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.type	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, @function
_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE:
.LFB529:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movzwl	(%rdx), %eax
	movq	%rsi, %rbx
	movq	8(%rdi), %rsi
	movq	%rax, %rcx
	salq	$4, %rcx
	subq	%rax, %rcx
	leaq	(%rsi,%rcx,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rdx), %ax
	ja	.L544
	movq	%rdi, %r12
.L547:
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	leaq	(%rsi,%rdx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L544
	movzbl	112(%r13), %eax
	cmpb	%al, 112(%rdi)
	jne	.L544
	cmpw	%r14w, 24(%rdi)
	jne	.L544
	movzbl	36(%rbx), %eax
	testb	%al, %al
	je	.L543
	movq	56(%rbx), %rsi
	movl	8(%rbx), %eax
	cmpl	%eax, (%rsi)
	jb	.L549
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%eax, 32(%rbx)
	jbe	.L555
.L549:
	xorl	%eax, %eax
.L543:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L555:
	.cfi_restore_state
	addq	$88, %rdi
	call	*24(%rbx)
	movzwl	0(%rbp), %ecx
	movq	8(%r12), %rsi
	addl	$1, 32(%rbx)
	movq	%rcx, %rax
	movq	%rcx, %rdx
	salq	$4, %rax
	subq	%rcx, %rax
	movb	$0, 80(%rsi,%rax,8)
	movzwl	2(%rbp), %eax
	cmpw	%ax, %cx
	ja	.L544
	jb	.L556
	movl	$1, 0(%rbp)
.L544:
	movl	$1, %eax
	jmp	.L543
	.p2align 4,,10
	.p2align 3
.L556:
	addl	$1, %edx
	addl	$1, %r14d
	movw	%dx, 0(%rbp)
	cmpw	%dx, %ax
	jb	.L544
	movzwl	%dx, %eax
	jmp	.L547
	.cfi_endproc
.LFE529:
	.size	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, .-_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev:
.LFB532:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L557
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L557
	movzwl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movw	%ax, (%rdx)
.L557:
	ret
	.cfi_endproc
.LFE532:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED2Ev
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB452:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA452
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L602
	movl	$13, %ecx
	movl	$1, %edx
	movl	$1566, %esi
	movq	%r13, %rdi
.LEHB33:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L603
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE33:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L569:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L570
.L576:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L570
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L570
	cmpw	24(%rdi), %r14w
	jne	.L570
	testb	%al, %al
	je	.L562
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L572
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L573
	addq	$88, %rdi
.LEHB34:
	call	*24(%rsp)
.LEHE34:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L574
	jb	.L604
	movl	$1, (%r12)
.L574:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L570:
	testb	%al, %al
	jne	.L605
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L562:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L606
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L603:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var610ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$9, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var611WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L607
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L562
	xorl	%eax, %eax
	jmp	.L576
.L605:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L572:
	testl	%edx, %edx
	jne	.L573
	movl	%ebx, %eax
	jmp	.L562
	.p2align 4,,10
	.p2align 3
.L573:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L562
	.p2align 4,,10
	.p2align 3
.L604:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L570
	movzwl	%cx, %edx
	jmp	.L576
	.p2align 4,,10
	.p2align 3
.L607:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB35:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L569
	.p2align 4,,10
	.p2align 3
.L602:
	xorl	%edx, %edx
	movl	$11, %ecx
	movl	$1566, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE35:
	testb	%al, %al
	je	.L564
	movq	_ZN8opendnp311Group30Var610ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$9, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var611WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L608
.L565:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB36:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE36:
	cmpb	$0, 36(%rsp)
	je	.L562
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L562
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L562
	.p2align 4,,10
	.p2align 3
.L564:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB37:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L565
	.p2align 4,,10
	.p2align 3
.L608:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L565
.L606:
	call	__stack_chk_fail@PLT
.L588:
	movq	%rax, %rbp
	jmp	.L582
.L587:
	movq	%rax, %rbp
	jmp	.L581
.L582:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L581:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE37:
	.cfi_endproc
.LFE452:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA452:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE452-.LLSDACSB452
.LLSDACSB452:
	.uleb128 .LEHB33-.LFB452
	.uleb128 .LEHE33-.LEHB33
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB34-.LFB452
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L588-.LFB452
	.uleb128 0
	.uleb128 .LEHB35-.LFB452
	.uleb128 .LEHE35-.LEHB35
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB36-.LFB452
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L587-.LFB452
	.uleb128 0
	.uleb128 .LEHB37-.LFB452
	.uleb128 .LEHE37-.LEHB37
	.uleb128 0
	.uleb128 0
.LLSDACSE452:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB451:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA451
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L649
	movl	$9, %ecx
	movl	$1, %edx
	movl	$1310, %esi
	movq	%r13, %rdi
.LEHB38:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L650
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE38:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L616:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L617
.L623:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L617
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L617
	cmpw	24(%rdi), %r14w
	jne	.L617
	testb	%al, %al
	je	.L609
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L619
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L620
	addq	$88, %rdi
.LEHB39:
	call	*24(%rsp)
.LEHE39:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L621
	jb	.L651
	movl	$1, (%r12)
.L621:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L617:
	testb	%al, %al
	jne	.L652
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L609:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L653
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L650:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var510ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var511WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L654
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L609
	xorl	%eax, %eax
	jmp	.L623
.L652:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L619:
	testl	%edx, %edx
	jne	.L620
	movl	%ebx, %eax
	jmp	.L609
	.p2align 4,,10
	.p2align 3
.L620:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L609
	.p2align 4,,10
	.p2align 3
.L651:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L617
	movzwl	%cx, %edx
	jmp	.L623
	.p2align 4,,10
	.p2align 3
.L654:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB40:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L616
	.p2align 4,,10
	.p2align 3
.L649:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$1310, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE40:
	testb	%al, %al
	je	.L611
	movq	_ZN8opendnp311Group30Var510ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var511WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L655
.L612:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB41:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE41:
	cmpb	$0, 36(%rsp)
	je	.L609
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L609
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L609
	.p2align 4,,10
	.p2align 3
.L611:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB42:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L612
	.p2align 4,,10
	.p2align 3
.L655:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L612
.L653:
	call	__stack_chk_fail@PLT
.L635:
	movq	%rax, %rbp
	jmp	.L629
.L634:
	movq	%rax, %rbp
	jmp	.L628
.L629:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L628:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE42:
	.cfi_endproc
.LFE451:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA451:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE451-.LLSDACSB451
.LLSDACSB451:
	.uleb128 .LEHB38-.LFB451
	.uleb128 .LEHE38-.LEHB38
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB39-.LFB451
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L635-.LFB451
	.uleb128 0
	.uleb128 .LEHB40-.LFB451
	.uleb128 .LEHE40-.LEHB40
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB41-.LFB451
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L634-.LFB451
	.uleb128 0
	.uleb128 .LEHB42-.LFB451
	.uleb128 .LEHE42-.LEHB42
	.uleb128 0
	.uleb128 0
.LLSDACSE451:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB450:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA450
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L696
	movl	$6, %ecx
	movl	$1, %edx
	movl	$1054, %esi
	movq	%r13, %rdi
.LEHB43:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L697
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE43:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L663:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L664
.L670:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L664
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L664
	cmpw	24(%rdi), %r14w
	jne	.L664
	testb	%al, %al
	je	.L656
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L666
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L667
	addq	$88, %rdi
.LEHB44:
	call	*24(%rsp)
.LEHE44:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L668
	jb	.L698
	movl	$1, (%r12)
.L668:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L664:
	testb	%al, %al
	jne	.L699
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L656:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L700
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L697:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var410ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$2, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var411WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L701
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L656
	xorl	%eax, %eax
	jmp	.L670
.L699:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L666:
	testl	%edx, %edx
	jne	.L667
	movl	%ebx, %eax
	jmp	.L656
	.p2align 4,,10
	.p2align 3
.L667:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L656
	.p2align 4,,10
	.p2align 3
.L698:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L664
	movzwl	%cx, %edx
	jmp	.L670
	.p2align 4,,10
	.p2align 3
.L701:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB45:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L663
	.p2align 4,,10
	.p2align 3
.L696:
	xorl	%edx, %edx
	movl	$4, %ecx
	movl	$1054, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE45:
	testb	%al, %al
	je	.L658
	movq	_ZN8opendnp311Group30Var410ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$2, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var411WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L702
.L659:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB46:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE46:
	cmpb	$0, 36(%rsp)
	je	.L656
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L656
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L656
	.p2align 4,,10
	.p2align 3
.L658:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB47:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L659
	.p2align 4,,10
	.p2align 3
.L702:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L659
.L700:
	call	__stack_chk_fail@PLT
.L682:
	movq	%rax, %rbp
	jmp	.L676
.L681:
	movq	%rax, %rbp
	jmp	.L675
.L676:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L675:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE47:
	.cfi_endproc
.LFE450:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA450:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE450-.LLSDACSB450
.LLSDACSB450:
	.uleb128 .LEHB43-.LFB450
	.uleb128 .LEHE43-.LEHB43
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB44-.LFB450
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L682-.LFB450
	.uleb128 0
	.uleb128 .LEHB45-.LFB450
	.uleb128 .LEHE45-.LEHB45
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB46-.LFB450
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L681-.LFB450
	.uleb128 0
	.uleb128 .LEHB47-.LFB450
	.uleb128 .LEHE47-.LEHB47
	.uleb128 0
	.uleb128 0
.LLSDACSE450:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB449:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA449
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L743
	movl	$8, %ecx
	movl	$1, %edx
	movl	$798, %esi
	movq	%r13, %rdi
.LEHB48:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L744
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE48:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L710:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L711
.L717:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L711
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L711
	cmpw	24(%rdi), %r14w
	jne	.L711
	testb	%al, %al
	je	.L703
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L713
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L714
	addq	$88, %rdi
.LEHB49:
	call	*24(%rsp)
.LEHE49:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L715
	jb	.L745
	movl	$1, (%r12)
.L715:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L711:
	testb	%al, %al
	jne	.L746
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L703:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L747
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L744:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var310ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$4, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var311WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L748
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L703
	xorl	%eax, %eax
	jmp	.L717
.L746:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L713:
	testl	%edx, %edx
	jne	.L714
	movl	%ebx, %eax
	jmp	.L703
	.p2align 4,,10
	.p2align 3
.L714:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L703
	.p2align 4,,10
	.p2align 3
.L745:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L711
	movzwl	%cx, %edx
	jmp	.L717
	.p2align 4,,10
	.p2align 3
.L748:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB50:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L710
	.p2align 4,,10
	.p2align 3
.L743:
	xorl	%edx, %edx
	movl	$6, %ecx
	movl	$798, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE50:
	testb	%al, %al
	je	.L705
	movq	_ZN8opendnp311Group30Var310ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$4, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var311WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L749
.L706:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB51:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE51:
	cmpb	$0, 36(%rsp)
	je	.L703
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L703
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L703
	.p2align 4,,10
	.p2align 3
.L705:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB52:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L706
	.p2align 4,,10
	.p2align 3
.L749:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L706
.L747:
	call	__stack_chk_fail@PLT
.L729:
	movq	%rax, %rbp
	jmp	.L723
.L728:
	movq	%rax, %rbp
	jmp	.L722
.L723:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L722:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE52:
	.cfi_endproc
.LFE449:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA449:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE449-.LLSDACSB449
.LLSDACSB449:
	.uleb128 .LEHB48-.LFB449
	.uleb128 .LEHE48-.LEHB48
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB49-.LFB449
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L729-.LFB449
	.uleb128 0
	.uleb128 .LEHB50-.LFB449
	.uleb128 .LEHE50-.LEHB50
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB51-.LFB449
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L728-.LFB449
	.uleb128 0
	.uleb128 .LEHB52-.LFB449
	.uleb128 .LEHE52-.LEHB52
	.uleb128 0
	.uleb128 0
.LLSDACSE449:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB448:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA448
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L790
	movl	$7, %ecx
	movl	$1, %edx
	movl	$542, %esi
	movq	%r13, %rdi
.LEHB53:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L791
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE53:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L757:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L758
.L764:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L758
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L758
	cmpw	24(%rdi), %r14w
	jne	.L758
	testb	%al, %al
	je	.L750
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L760
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L761
	addq	$88, %rdi
.LEHB54:
	call	*24(%rsp)
.LEHE54:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L762
	jb	.L792
	movl	$1, (%r12)
.L762:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L758:
	testb	%al, %al
	jne	.L793
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L750:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L794
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L791:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var210ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var211WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L795
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L750
	xorl	%eax, %eax
	jmp	.L764
.L793:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L760:
	testl	%edx, %edx
	jne	.L761
	movl	%ebx, %eax
	jmp	.L750
	.p2align 4,,10
	.p2align 3
.L761:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L750
	.p2align 4,,10
	.p2align 3
.L792:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L758
	movzwl	%cx, %edx
	jmp	.L764
	.p2align 4,,10
	.p2align 3
.L795:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB55:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L757
	.p2align 4,,10
	.p2align 3
.L790:
	xorl	%edx, %edx
	movl	$5, %ecx
	movl	$542, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE55:
	testb	%al, %al
	je	.L752
	movq	_ZN8opendnp311Group30Var210ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var211WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L796
.L753:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB56:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE56:
	cmpb	$0, 36(%rsp)
	je	.L750
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L750
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L750
	.p2align 4,,10
	.p2align 3
.L752:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB57:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L753
	.p2align 4,,10
	.p2align 3
.L796:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L753
.L794:
	call	__stack_chk_fail@PLT
.L776:
	movq	%rax, %rbp
	jmp	.L770
.L775:
	movq	%rax, %rbp
	jmp	.L769
.L770:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L769:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE57:
	.cfi_endproc
.LFE448:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA448:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE448-.LLSDACSB448
.LLSDACSB448:
	.uleb128 .LEHB53-.LFB448
	.uleb128 .LEHE53-.LEHB53
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB54-.LFB448
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L776-.LFB448
	.uleb128 0
	.uleb128 .LEHB55-.LFB448
	.uleb128 .LEHE55-.LEHB55
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB56-.LFB448
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L775-.LFB448
	.uleb128 0
	.uleb128 .LEHB57-.LFB448
	.uleb128 .LEHE57-.LEHB57
	.uleb128 0
	.uleb128 0
.LLSDACSE448:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB447:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA447
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L837
	movl	$9, %ecx
	movl	$1, %edx
	movl	$286, %esi
	movq	%r13, %rdi
.LEHB58:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L838
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE58:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L804:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L805
.L811:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L805
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L805
	cmpw	24(%rdi), %r14w
	jne	.L805
	testb	%al, %al
	je	.L797
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L807
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L808
	addq	$88, %rdi
.LEHB59:
	call	*24(%rsp)
.LEHE59:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L809
	jb	.L839
	movl	$1, (%r12)
.L809:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L805:
	testb	%al, %al
	jne	.L840
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L797:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L841
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L838:
	.cfi_restore_state
	movq	_ZN8opendnp311Group30Var110ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var111WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L842
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L797
	xorl	%eax, %eax
	jmp	.L811
.L840:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L807:
	testl	%edx, %edx
	jne	.L808
	movl	%ebx, %eax
	jmp	.L797
	.p2align 4,,10
	.p2align 3
.L808:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L797
	.p2align 4,,10
	.p2align 3
.L839:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L805
	movzwl	%cx, %edx
	jmp	.L811
	.p2align 4,,10
	.p2align 3
.L842:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB60:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L804
	.p2align 4,,10
	.p2align 3
.L837:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$286, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE60:
	testb	%al, %al
	je	.L799
	movq	_ZN8opendnp311Group30Var110ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group30Var111WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L843
.L800:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB61:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_10AnalogSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE61:
	cmpb	$0, 36(%rsp)
	je	.L797
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L797
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L797
	.p2align 4,,10
	.p2align 3
.L799:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB62:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L800
	.p2align 4,,10
	.p2align 3
.L843:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L800
.L841:
	call	__stack_chk_fail@PLT
.L823:
	movq	%rax, %rbp
	jmp	.L817
.L822:
	movq	%rax, %rbp
	jmp	.L816
.L817:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L816:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_6AnalogEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE62:
	.cfi_endproc
.LFE447:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA447:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE447-.LLSDACSB447
.LLSDACSB447:
	.uleb128 .LEHB58-.LFB447
	.uleb128 .LEHE58-.LEHB58
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB59-.LFB447
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L823-.LFB447
	.uleb128 0
	.uleb128 .LEHB60-.LFB447
	.uleb128 .LEHE60-.LEHB60
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB61-.LFB447
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L822-.LFB447
	.uleb128 0
	.uleb128 .LEHB62-.LFB447
	.uleb128 .LEHE62-.LEHB62
	.uleb128 0
	.uleb128 0
.LLSDACSE447:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_10AnalogSpecENS_11Group30Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev:
.LFB538:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L844
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L844
	movzbl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movb	%al, (%rdx)
.L844:
	ret
	.cfi_endproc
.LFE538:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED2Ev
	.section	.text._ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,"axG",@progbits,_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.type	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, @function
_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE:
.LFB540:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movzwl	(%rdx), %eax
	movq	%rsi, %rbx
	movq	8(%rdi), %rsi
	movq	%rax, %rcx
	salq	$4, %rcx
	subq	%rax, %rcx
	leaq	(%rsi,%rcx,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rdx), %ax
	ja	.L850
	movq	%rdi, %r12
.L853:
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	leaq	(%rsi,%rdx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L850
	movzbl	112(%r13), %eax
	cmpb	%al, 112(%rdi)
	jne	.L850
	cmpw	%r14w, 24(%rdi)
	jne	.L850
	movzbl	36(%rbx), %eax
	testb	%al, %al
	je	.L849
	movq	56(%rbx), %rsi
	movl	8(%rbx), %eax
	cmpl	%eax, (%rsi)
	jb	.L855
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%eax, 32(%rbx)
	jbe	.L861
.L855:
	xorl	%eax, %eax
.L849:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L861:
	.cfi_restore_state
	addq	$88, %rdi
	call	*24(%rbx)
	movzwl	0(%rbp), %ecx
	movq	8(%r12), %rsi
	addl	$1, 32(%rbx)
	movq	%rcx, %rax
	movq	%rcx, %rdx
	salq	$4, %rax
	subq	%rcx, %rax
	movb	$0, 80(%rsi,%rax,8)
	movzwl	2(%rbp), %eax
	cmpw	%ax, %cx
	ja	.L850
	jb	.L862
	movl	$1, 0(%rbp)
.L850:
	movl	$1, %eax
	jmp	.L849
	.p2align 4,,10
	.p2align 3
.L862:
	addl	$1, %edx
	addl	$1, %r14d
	movw	%dx, 0(%rbp)
	cmpw	%dx, %ax
	jb	.L850
	movzwl	%dx, %eax
	jmp	.L853
	.cfi_endproc
.LFE540:
	.size	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, .-_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev:
.LFB543:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L863
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L863
	movzwl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movw	%ax, (%rdx)
.L863:
	ret
	.cfi_endproc
.LFE543:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED2Ev
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB456:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA456
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L908
	movl	$6, %ecx
	movl	$1, %edx
	movl	$1556, %esi
	movq	%r13, %rdi
.LEHB63:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L909
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE63:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L875:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L876
.L882:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L876
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L876
	cmpw	24(%rdi), %r14w
	jne	.L876
	testb	%al, %al
	je	.L868
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L878
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L879
	addq	$88, %rdi
.LEHB64:
	call	*24(%rsp)
.LEHE64:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L880
	jb	.L910
	movl	$1, (%r12)
.L880:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L876:
	testb	%al, %al
	jne	.L911
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L868:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L912
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L909:
	.cfi_restore_state
	movq	_ZN8opendnp311Group20Var610ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$2, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var611WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L913
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L868
	xorl	%eax, %eax
	jmp	.L882
.L911:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L878:
	testl	%edx, %edx
	jne	.L879
	movl	%ebx, %eax
	jmp	.L868
	.p2align 4,,10
	.p2align 3
.L879:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L868
	.p2align 4,,10
	.p2align 3
.L910:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L876
	movzwl	%cx, %edx
	jmp	.L882
	.p2align 4,,10
	.p2align 3
.L913:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB65:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L875
	.p2align 4,,10
	.p2align 3
.L908:
	xorl	%edx, %edx
	movl	$4, %ecx
	movl	$1556, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE65:
	testb	%al, %al
	je	.L870
	movq	_ZN8opendnp311Group20Var610ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$2, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var611WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L914
.L871:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB66:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE66:
	cmpb	$0, 36(%rsp)
	je	.L868
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L868
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L868
	.p2align 4,,10
	.p2align 3
.L870:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB67:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L871
	.p2align 4,,10
	.p2align 3
.L914:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L871
.L912:
	call	__stack_chk_fail@PLT
.L894:
	movq	%rax, %rbp
	jmp	.L888
.L893:
	movq	%rax, %rbp
	jmp	.L887
.L888:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L887:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE67:
	.cfi_endproc
.LFE456:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA456:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE456-.LLSDACSB456
.LLSDACSB456:
	.uleb128 .LEHB63-.LFB456
	.uleb128 .LEHE63-.LEHB63
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB64-.LFB456
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L894-.LFB456
	.uleb128 0
	.uleb128 .LEHB65-.LFB456
	.uleb128 .LEHE65-.LEHB65
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB66-.LFB456
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L893-.LFB456
	.uleb128 0
	.uleb128 .LEHB67-.LFB456
	.uleb128 .LEHE67-.LEHB67
	.uleb128 0
	.uleb128 0
.LLSDACSE456:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var6EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB455:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA455
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L955
	movl	$8, %ecx
	movl	$1, %edx
	movl	$1300, %esi
	movq	%r13, %rdi
.LEHB68:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L956
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE68:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L922:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L923
.L929:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L923
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L923
	cmpw	24(%rdi), %r14w
	jne	.L923
	testb	%al, %al
	je	.L915
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L925
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L926
	addq	$88, %rdi
.LEHB69:
	call	*24(%rsp)
.LEHE69:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L927
	jb	.L957
	movl	$1, (%r12)
.L927:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L923:
	testb	%al, %al
	jne	.L958
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L915:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L959
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L956:
	.cfi_restore_state
	movq	_ZN8opendnp311Group20Var510ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$4, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var511WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L960
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L915
	xorl	%eax, %eax
	jmp	.L929
.L958:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L925:
	testl	%edx, %edx
	jne	.L926
	movl	%ebx, %eax
	jmp	.L915
	.p2align 4,,10
	.p2align 3
.L926:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L915
	.p2align 4,,10
	.p2align 3
.L957:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L923
	movzwl	%cx, %edx
	jmp	.L929
	.p2align 4,,10
	.p2align 3
.L960:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB70:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L922
	.p2align 4,,10
	.p2align 3
.L955:
	xorl	%edx, %edx
	movl	$6, %ecx
	movl	$1300, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE70:
	testb	%al, %al
	je	.L917
	movq	_ZN8opendnp311Group20Var510ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$4, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var511WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L961
.L918:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB71:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE71:
	cmpb	$0, 36(%rsp)
	je	.L915
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L915
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L915
	.p2align 4,,10
	.p2align 3
.L917:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB72:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L918
	.p2align 4,,10
	.p2align 3
.L961:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L918
.L959:
	call	__stack_chk_fail@PLT
.L941:
	movq	%rax, %rbp
	jmp	.L935
.L940:
	movq	%rax, %rbp
	jmp	.L934
.L935:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L934:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE72:
	.cfi_endproc
.LFE455:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA455:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE455-.LLSDACSB455
.LLSDACSB455:
	.uleb128 .LEHB68-.LFB455
	.uleb128 .LEHE68-.LEHB68
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB69-.LFB455
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L941-.LFB455
	.uleb128 0
	.uleb128 .LEHB70-.LFB455
	.uleb128 .LEHE70-.LEHB70
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB71-.LFB455
	.uleb128 .LEHE71-.LEHB71
	.uleb128 .L940-.LFB455
	.uleb128 0
	.uleb128 .LEHB72-.LFB455
	.uleb128 .LEHE72-.LEHB72
	.uleb128 0
	.uleb128 0
.LLSDACSE455:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var5EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB454:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA454
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1002
	movl	$7, %ecx
	movl	$1, %edx
	movl	$532, %esi
	movq	%r13, %rdi
.LEHB73:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1003
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE73:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L969:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L970
.L976:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L970
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L970
	cmpw	24(%rdi), %r14w
	jne	.L970
	testb	%al, %al
	je	.L962
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L972
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L973
	addq	$88, %rdi
.LEHB74:
	call	*24(%rsp)
.LEHE74:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L974
	jb	.L1004
	movl	$1, (%r12)
.L974:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L970:
	testb	%al, %al
	jne	.L1005
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L962:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1006
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1003:
	.cfi_restore_state
	movq	_ZN8opendnp311Group20Var210ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var211WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1007
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L962
	xorl	%eax, %eax
	jmp	.L976
.L1005:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L972:
	testl	%edx, %edx
	jne	.L973
	movl	%ebx, %eax
	jmp	.L962
	.p2align 4,,10
	.p2align 3
.L973:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L962
	.p2align 4,,10
	.p2align 3
.L1004:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L970
	movzwl	%cx, %edx
	jmp	.L976
	.p2align 4,,10
	.p2align 3
.L1007:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB75:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L969
	.p2align 4,,10
	.p2align 3
.L1002:
	xorl	%edx, %edx
	movl	$5, %ecx
	movl	$532, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE75:
	testb	%al, %al
	je	.L964
	movq	_ZN8opendnp311Group20Var210ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var211WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1008
.L965:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB76:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE76:
	cmpb	$0, 36(%rsp)
	je	.L962
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L962
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L962
	.p2align 4,,10
	.p2align 3
.L964:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB77:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L965
	.p2align 4,,10
	.p2align 3
.L1008:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L965
.L1006:
	call	__stack_chk_fail@PLT
.L988:
	movq	%rax, %rbp
	jmp	.L982
.L987:
	movq	%rax, %rbp
	jmp	.L981
.L982:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L981:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE77:
	.cfi_endproc
.LFE454:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA454:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE454-.LLSDACSB454
.LLSDACSB454:
	.uleb128 .LEHB73-.LFB454
	.uleb128 .LEHE73-.LEHB73
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB74-.LFB454
	.uleb128 .LEHE74-.LEHB74
	.uleb128 .L988-.LFB454
	.uleb128 0
	.uleb128 .LEHB75-.LFB454
	.uleb128 .LEHE75-.LEHB75
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB76-.LFB454
	.uleb128 .LEHE76-.LEHB76
	.uleb128 .L987-.LFB454
	.uleb128 0
	.uleb128 .LEHB77-.LFB454
	.uleb128 .LEHE77-.LEHB77
	.uleb128 0
	.uleb128 0
.LLSDACSE454:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB453:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA453
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1049
	movl	$9, %ecx
	movl	$1, %edx
	movl	$276, %esi
	movq	%r13, %rdi
.LEHB78:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1050
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE78:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L1016:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L1017
.L1023:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1017
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L1017
	cmpw	24(%rdi), %r14w
	jne	.L1017
	testb	%al, %al
	je	.L1009
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L1019
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L1020
	addq	$88, %rdi
.LEHB79:
	call	*24(%rsp)
.LEHE79:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L1021
	jb	.L1051
	movl	$1, (%r12)
.L1021:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L1017:
	testb	%al, %al
	jne	.L1052
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1009:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1053
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1050:
	.cfi_restore_state
	movq	_ZN8opendnp311Group20Var110ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var111WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1054
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L1009
	xorl	%eax, %eax
	jmp	.L1023
.L1052:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L1019:
	testl	%edx, %edx
	jne	.L1020
	movl	%ebx, %eax
	jmp	.L1009
	.p2align 4,,10
	.p2align 3
.L1020:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L1009
	.p2align 4,,10
	.p2align 3
.L1051:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L1017
	movzwl	%cx, %edx
	jmp	.L1023
	.p2align 4,,10
	.p2align 3
.L1054:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB80:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L1016
	.p2align 4,,10
	.p2align 3
.L1049:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$276, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE80:
	testb	%al, %al
	je	.L1011
	movq	_ZN8opendnp311Group20Var110ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group20Var111WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1055
.L1012:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB81:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_11CounterSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE81:
	cmpb	$0, 36(%rsp)
	je	.L1009
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L1009
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1009
	.p2align 4,,10
	.p2align 3
.L1011:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB82:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L1012
	.p2align 4,,10
	.p2align 3
.L1055:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1012
.L1053:
	call	__stack_chk_fail@PLT
.L1035:
	movq	%rax, %rbp
	jmp	.L1029
.L1034:
	movq	%rax, %rbp
	jmp	.L1028
.L1029:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L1028:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_7CounterEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE82:
	.cfi_endproc
.LFE453:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA453:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE453-.LLSDACSB453
.LLSDACSB453:
	.uleb128 .LEHB78-.LFB453
	.uleb128 .LEHE78-.LEHB78
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB79-.LFB453
	.uleb128 .LEHE79-.LEHB79
	.uleb128 .L1035-.LFB453
	.uleb128 0
	.uleb128 .LEHB80-.LFB453
	.uleb128 .LEHE80-.LEHB80
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB81-.LFB453
	.uleb128 .LEHE81-.LEHB81
	.uleb128 .L1034-.LFB453
	.uleb128 0
	.uleb128 .LEHB82-.LFB453
	.uleb128 .LEHE82-.LEHB82
	.uleb128 0
	.uleb128 0
.LLSDACSE453:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_11CounterSpecENS_11Group20Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev:
.LFB571:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L1056
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L1056
	movzbl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movb	%al, (%rdx)
.L1056:
	ret
	.cfi_endproc
.LFE571:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED2Ev
	.section	.text._ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,"axG",@progbits,_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.type	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, @function
_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE:
.LFB573:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movzwl	(%rdx), %eax
	movq	%rsi, %rbx
	movq	8(%rdi), %rsi
	movq	%rax, %rcx
	salq	$4, %rcx
	subq	%rax, %rcx
	leaq	(%rsi,%rcx,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%rdx), %ax
	ja	.L1062
	movq	%rdi, %r12
.L1065:
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	leaq	(%rsi,%rdx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1062
	movzbl	112(%r13), %eax
	cmpb	%al, 112(%rdi)
	jne	.L1062
	cmpw	%r14w, 24(%rdi)
	jne	.L1062
	movzbl	36(%rbx), %eax
	testb	%al, %al
	je	.L1061
	movq	56(%rbx), %rsi
	movl	8(%rbx), %eax
	cmpl	%eax, (%rsi)
	jb	.L1067
	movq	_ZN7openpal11UInt8Simple3MaxE@GOTPCREL(%rip), %rax
	movzbl	(%rax), %eax
	cmpl	%eax, 32(%rbx)
	jbe	.L1073
.L1067:
	xorl	%eax, %eax
.L1061:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1073:
	.cfi_restore_state
	addq	$88, %rdi
	call	*24(%rbx)
	movzwl	0(%rbp), %ecx
	movq	8(%r12), %rsi
	addl	$1, 32(%rbx)
	movq	%rcx, %rax
	movq	%rcx, %rdx
	salq	$4, %rax
	subq	%rcx, %rax
	movb	$0, 80(%rsi,%rax,8)
	movzwl	2(%rbp), %eax
	cmpw	%ax, %cx
	ja	.L1062
	jb	.L1074
	movl	$1, 0(%rbp)
.L1062:
	movl	$1, %eax
	jmp	.L1061
	.p2align 4,,10
	.p2align 3
.L1074:
	addl	$1, %edx
	addl	$1, %r14d
	movw	%dx, 0(%rbp)
	cmpw	%dx, %ax
	jb	.L1062
	movzwl	%dx, %eax
	jmp	.L1065
	.cfi_endproc
.LFE573:
	.size	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE, .-_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE
	.section	.text._ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev,"axG",@progbits,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev
	.type	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev, @function
_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev:
.LFB576:
	.cfi_startproc
	cmpb	$0, 36(%rdi)
	je	.L1075
	movl	32(%rdi), %eax
	testl	%eax, %eax
	je	.L1075
	movzwl	(%rdi), %ecx
	movq	48(%rdi), %rdx
	leal	-1(%rax,%rcx), %eax
	movw	%ax, (%rdx)
.L1075:
	ret
	.cfi_endproc
.LFE576:
	.size	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev, .-_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev
	.weak	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev
	.set	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev,_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED2Ev
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB462:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA462
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1120
	movl	$13, %ecx
	movl	$1, %edx
	movl	$1064, %esi
	movq	%r13, %rdi
.LEHB83:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1121
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE83:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L1087:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L1088
.L1094:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1088
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L1088
	cmpw	24(%rdi), %r14w
	jne	.L1088
	testb	%al, %al
	je	.L1080
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L1090
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L1091
	addq	$88, %rdi
.LEHB84:
	call	*24(%rsp)
.LEHE84:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L1092
	jb	.L1122
	movl	$1, (%r12)
.L1092:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L1088:
	testb	%al, %al
	jne	.L1123
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1080:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1124
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1121:
	.cfi_restore_state
	movq	_ZN8opendnp311Group40Var410ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$9, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var411WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1125
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L1080
	xorl	%eax, %eax
	jmp	.L1094
.L1123:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L1090:
	testl	%edx, %edx
	jne	.L1091
	movl	%ebx, %eax
	jmp	.L1080
	.p2align 4,,10
	.p2align 3
.L1091:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L1080
	.p2align 4,,10
	.p2align 3
.L1122:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L1088
	movzwl	%cx, %edx
	jmp	.L1094
	.p2align 4,,10
	.p2align 3
.L1125:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB85:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L1087
	.p2align 4,,10
	.p2align 3
.L1120:
	xorl	%edx, %edx
	movl	$11, %ecx
	movl	$1064, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE85:
	testb	%al, %al
	je	.L1082
	movq	_ZN8opendnp311Group40Var410ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$9, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var411WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1126
.L1083:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB86:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE86:
	cmpb	$0, 36(%rsp)
	je	.L1080
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L1080
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1080
	.p2align 4,,10
	.p2align 3
.L1082:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB87:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L1083
	.p2align 4,,10
	.p2align 3
.L1126:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1083
.L1124:
	call	__stack_chk_fail@PLT
.L1106:
	movq	%rax, %rbp
	jmp	.L1100
.L1105:
	movq	%rax, %rbp
	jmp	.L1099
.L1100:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L1099:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE87:
	.cfi_endproc
.LFE462:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA462:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE462-.LLSDACSB462
.LLSDACSB462:
	.uleb128 .LEHB83-.LFB462
	.uleb128 .LEHE83-.LEHB83
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB84-.LFB462
	.uleb128 .LEHE84-.LEHB84
	.uleb128 .L1106-.LFB462
	.uleb128 0
	.uleb128 .LEHB85-.LFB462
	.uleb128 .LEHE85-.LEHB85
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB86-.LFB462
	.uleb128 .LEHE86-.LEHB86
	.uleb128 .L1105-.LFB462
	.uleb128 0
	.uleb128 .LEHB87-.LFB462
	.uleb128 .LEHE87-.LEHB87
	.uleb128 0
	.uleb128 0
.LLSDACSE462:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var4EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB461:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA461
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1167
	movl	$9, %ecx
	movl	$1, %edx
	movl	$808, %esi
	movq	%r13, %rdi
.LEHB88:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1168
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE88:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L1134:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L1135
.L1141:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1135
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L1135
	cmpw	24(%rdi), %r14w
	jne	.L1135
	testb	%al, %al
	je	.L1127
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L1137
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L1138
	addq	$88, %rdi
.LEHB89:
	call	*24(%rsp)
.LEHE89:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L1139
	jb	.L1169
	movl	$1, (%r12)
.L1139:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L1135:
	testb	%al, %al
	jne	.L1170
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1127:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1171
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1168:
	.cfi_restore_state
	movq	_ZN8opendnp311Group40Var310ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var311WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1172
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L1127
	xorl	%eax, %eax
	jmp	.L1141
.L1170:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L1137:
	testl	%edx, %edx
	jne	.L1138
	movl	%ebx, %eax
	jmp	.L1127
	.p2align 4,,10
	.p2align 3
.L1138:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L1127
	.p2align 4,,10
	.p2align 3
.L1169:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L1135
	movzwl	%cx, %edx
	jmp	.L1141
	.p2align 4,,10
	.p2align 3
.L1172:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB90:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L1134
	.p2align 4,,10
	.p2align 3
.L1167:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$808, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE90:
	testb	%al, %al
	je	.L1129
	movq	_ZN8opendnp311Group40Var310ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var311WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1173
.L1130:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB91:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE91:
	cmpb	$0, 36(%rsp)
	je	.L1127
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L1127
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1127
	.p2align 4,,10
	.p2align 3
.L1129:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB92:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L1130
	.p2align 4,,10
	.p2align 3
.L1173:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1130
.L1171:
	call	__stack_chk_fail@PLT
.L1153:
	movq	%rax, %rbp
	jmp	.L1147
.L1152:
	movq	%rax, %rbp
	jmp	.L1146
.L1147:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L1146:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE92:
	.cfi_endproc
.LFE461:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA461:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE461-.LLSDACSB461
.LLSDACSB461:
	.uleb128 .LEHB88-.LFB461
	.uleb128 .LEHE88-.LEHB88
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB89-.LFB461
	.uleb128 .LEHE89-.LEHB89
	.uleb128 .L1153-.LFB461
	.uleb128 0
	.uleb128 .LEHB90-.LFB461
	.uleb128 .LEHE90-.LEHB90
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB91-.LFB461
	.uleb128 .LEHE91-.LEHB91
	.uleb128 .L1152-.LFB461
	.uleb128 0
	.uleb128 .LEHB92-.LFB461
	.uleb128 .LEHE92-.LEHB92
	.uleb128 0
	.uleb128 0
.LLSDACSE461:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var3EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB460:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA460
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1214
	movl	$7, %ecx
	movl	$1, %edx
	movl	$552, %esi
	movq	%r13, %rdi
.LEHB93:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1215
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE93:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L1181:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L1182
.L1188:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1182
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L1182
	cmpw	24(%rdi), %r14w
	jne	.L1182
	testb	%al, %al
	je	.L1174
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L1184
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L1185
	addq	$88, %rdi
.LEHB94:
	call	*24(%rsp)
.LEHE94:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L1186
	jb	.L1216
	movl	$1, (%r12)
.L1186:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L1182:
	testb	%al, %al
	jne	.L1217
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1174:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1218
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1215:
	.cfi_restore_state
	movq	_ZN8opendnp311Group40Var210ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var211WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1219
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L1174
	xorl	%eax, %eax
	jmp	.L1188
.L1217:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L1184:
	testl	%edx, %edx
	jne	.L1185
	movl	%ebx, %eax
	jmp	.L1174
	.p2align 4,,10
	.p2align 3
.L1185:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L1174
	.p2align 4,,10
	.p2align 3
.L1216:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L1182
	movzwl	%cx, %edx
	jmp	.L1188
	.p2align 4,,10
	.p2align 3
.L1219:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB95:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L1181
	.p2align 4,,10
	.p2align 3
.L1214:
	xorl	%edx, %edx
	movl	$5, %ecx
	movl	$552, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE95:
	testb	%al, %al
	je	.L1176
	movq	_ZN8opendnp311Group40Var210ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$3, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var211WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1220
.L1177:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB96:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE96:
	cmpb	$0, 36(%rsp)
	je	.L1174
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L1174
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1174
	.p2align 4,,10
	.p2align 3
.L1176:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB97:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L1177
	.p2align 4,,10
	.p2align 3
.L1220:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1177
.L1218:
	call	__stack_chk_fail@PLT
.L1200:
	movq	%rax, %rbp
	jmp	.L1194
.L1199:
	movq	%rax, %rbp
	jmp	.L1193
.L1194:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L1193:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE97:
	.cfi_endproc
.LFE460:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA460:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE460-.LLSDACSB460
.LLSDACSB460:
	.uleb128 .LEHB93-.LFB460
	.uleb128 .LEHE93-.LEHB93
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB94-.LFB460
	.uleb128 .LEHE94-.LEHB94
	.uleb128 .L1200-.LFB460
	.uleb128 0
	.uleb128 .LEHB95-.LFB460
	.uleb128 .LEHE95-.LEHB95
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB96-.LFB460
	.uleb128 .LEHE96-.LEHB96
	.uleb128 .L1199-.LFB460
	.uleb128 0
	.uleb128 .LEHB97-.LFB460
	.uleb128 .LEHE97-.LEHB97
	.uleb128 0
	.uleb128 0
.LLSDACSE460:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var2EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.p2align 4
	.weak	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.type	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, @function
_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE:
.LFB459:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA459
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movzwl	(%r12), %ecx
	movq	8(%rdi), %rdx
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	2(%r12), %ecx
	movzwl	24(%rdx,%rax,8), %r14d
	movq	%rcx, %rax
	salq	$4, %rax
	subq	%rcx, %rax
	movzwl	24(%rdx,%rax,8), %eax
	movl	$255, %edx
	cmpw	$255, %ax
	cmovbe	%eax, %edx
	cmpw	%dx, %r14w
	setbe	%bl
	cmpw	$255, %ax
	setbe	%al
	andb	%al, %bl
	jne	.L1261
	movl	$9, %ecx
	movl	$1, %edx
	movl	$296, %esi
	movq	%r13, %rdi
.LEHB98:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1262
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, 36(%rsp)
	movw	%ax, (%rsp)
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE98:
	movzbl	36(%rsp), %eax
	movq	$0, 56(%rsp)
.L1228:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	%dx, 2(%r12)
	jb	.L1229
.L1235:
	movq	%rdx, %rcx
	salq	$4, %rcx
	subq	%rdx, %rcx
	leaq	(%rsi,%rcx,8), %rdi
	cmpb	$0, 80(%rdi)
	je	.L1229
	movzbl	112(%r13), %esi
	cmpb	%sil, 112(%rdi)
	jne	.L1229
	cmpw	24(%rdi), %r14w
	jne	.L1229
	testb	%al, %al
	je	.L1221
	movq	56(%rsp), %rsi
	movl	32(%rsp), %edx
	movl	8(%rsp), %eax
	cmpl	%eax, (%rsi)
	jb	.L1231
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movzwl	(%rax), %eax
	cmpl	%edx, %eax
	jb	.L1232
	addq	$88, %rdi
.LEHB99:
	call	*24(%rsp)
.LEHE99:
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	addl	$1, 32(%rsp)
	movq	%rdx, %rax
	movq	%rdx, %rcx
	salq	$4, %rax
	subq	%rdx, %rax
	movzwl	2(%r12), %edx
	movb	$0, 80(%rsi,%rax,8)
	cmpw	%dx, %cx
	ja	.L1233
	jb	.L1263
	movl	$1, (%r12)
.L1233:
	movzbl	36(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L1229:
	testb	%al, %al
	jne	.L1264
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L1221:
	movq	72(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L1265
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1262:
	.cfi_restore_state
	movq	_ZN8opendnp311Group40Var110ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rdx
	movw	%r14w, (%rsp)
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var111WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rdx), %xmm1
	cmpl	$3, (%rdx)
	seta	36(%rsp)
	movq	%rdx, 56(%rsp)
	movups	%xmm1, 40(%rsp)
	ja	.L1266
	movzwl	(%r12), %edx
	movq	8(%rbp), %rsi
	movq	%rdx, %rdi
	salq	$4, %rdi
	subq	%rdx, %rdi
	leaq	(%rsi,%rdi,8), %r13
	movzwl	24(%r13), %r14d
	cmpw	2(%r12), %dx
	ja	.L1221
	xorl	%eax, %eax
	jmp	.L1235
.L1264:
	movl	32(%rsp), %edx
	movl	%eax, %ebx
	.p2align 4,,10
	.p2align 3
.L1231:
	testl	%edx, %edx
	jne	.L1232
	movl	%ebx, %eax
	jmp	.L1221
	.p2align 4,,10
	.p2align 3
.L1232:
	movzwl	(%rsp), %eax
	leal	-1(%rdx,%rax), %edx
	movq	48(%rsp), %rax
	movw	%dx, (%rax)
	movl	%ebx, %eax
	jmp	.L1221
	.p2align 4,,10
	.p2align 3
.L1263:
	addl	$1, %ecx
	movzbl	36(%rsp), %eax
	addl	$1, %r14d
	movw	%cx, (%r12)
	cmpw	%cx, %dx
	jb	.L1229
	movzwl	%cx, %edx
	jmp	.L1235
	.p2align 4,,10
	.p2align 3
.L1266:
	movq	%rsp, %rsi
	leaq	40(%rsp), %rdi
.LEHB100:
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKt@PLT
	movq	56(%rsp), %rdi
	movl	$4, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movzbl	36(%rsp), %eax
	jmp	.L1228
	.p2align 4,,10
	.p2align 3
.L1261:
	xorl	%edx, %edx
	movl	$7, %ecx
	movl	$296, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE100:
	testb	%al, %al
	je	.L1223
	movq	_ZN8opendnp311Group40Var110ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movq	0(%r13), %rax
	movb	%r14b, (%rsp)
	movq	%rsp, %r13
	movl	$5, 8(%rsp)
	movhps	_ZN8opendnp311Group40Var111WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movl	$0, 32(%rsp)
	movaps	%xmm0, 16(%rsp)
	movdqu	(%rax), %xmm2
	cmpl	$1, (%rax)
	seta	36(%rsp)
	movq	%rax, 56(%rsp)
	movups	%xmm2, 40(%rsp)
	ja	.L1267
.L1224:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
.LEHB101:
	call	_ZN8opendnp321LoadWithRangeIteratorINS_22AnalogOutputStatusSpecEN7openpal11UInt8SimpleEEEbRNS2_9ArrayViewINS_4CellIT_EEtEERNS_18RangeWriteIteratorIT0_NS6_6meas_tEEERNS_5RangeE@PLT
.LEHE101:
	cmpb	$0, 36(%rsp)
	je	.L1221
	movl	32(%rsp), %edx
	testl	%edx, %edx
	je	.L1221
	movzbl	(%rsp), %ecx
	leal	-1(%rdx,%rcx), %ecx
	movq	48(%rsp), %rdx
	movb	%cl, (%rdx)
	jmp	.L1221
	.p2align 4,,10
	.p2align 3
.L1223:
	pxor	%xmm0, %xmm0
	leaq	40(%rsp), %rdi
	movb	$0, (%rsp)
	movq	%rsp, %r13
	movl	$0, 8(%rsp)
	movl	$0, 32(%rsp)
	movb	$0, 36(%rsp)
	movaps	%xmm0, 16(%rsp)
.LEHB102:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 56(%rsp)
	jmp	.L1224
	.p2align 4,,10
	.p2align 3
.L1267:
	leaq	40(%rsp), %rdi
	movq	%r13, %rsi
	call	_ZN7openpal6Format5WriteERNS_6WSliceERKh@PLT
	movq	56(%rsp), %rdi
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1224
.L1265:
	call	__stack_chk_fail@PLT
.L1247:
	movq	%rax, %rbp
	jmp	.L1241
.L1246:
	movq	%rax, %rbp
	jmp	.L1240
.L1241:
	movq	%rsp, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal7Bit16LEItEENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L1240:
	movq	%r13, %rdi
	call	_ZN8opendnp318RangeWriteIteratorIN7openpal11UInt8SimpleENS_18AnalogOutputStatusEED1Ev@PLT
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE102:
	.cfi_endproc
.LFE459:
	.section	.gcc_except_table._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"aG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
.LLSDA459:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE459-.LLSDACSB459
.LLSDACSB459:
	.uleb128 .LEHB98-.LFB459
	.uleb128 .LEHE98-.LEHB98
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB99-.LFB459
	.uleb128 .LEHE99-.LEHB99
	.uleb128 .L1247-.LFB459
	.uleb128 0
	.uleb128 .LEHB100-.LFB459
	.uleb128 .LEHE100-.LEHB100
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB101-.LFB459
	.uleb128 .LEHE101-.LEHB101
	.uleb128 .L1246-.LFB459
	.uleb128 0
	.uleb128 .LEHB102-.LFB459
	.uleb128 .LEHE102-.LEHB102
	.uleb128 0
	.uleb128 0
.LLSDACSE459:
	.section	.text._ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,"axG",@progbits,_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE,comdat
	.size	_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE, .-_ZN8opendnp319WriteWithSerializerINS_22AnalogOutputStatusSpecENS_11Group40Var1EEEbRN7openpal9ArrayViewINS_4CellIT_EEtEERNS_12HeaderWriterERNS_5RangeE
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_StaticLoadFunctions.cpp, @function
_GLOBAL__sub_I_StaticLoadFunctions.cpp:
.LFB812:
	.cfi_startproc
	movq	_ZGVN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	cmpb	$0, (%rax)
	je	.L1274
	ret
.L1274:
	pushq	%rdx
	.cfi_def_cfa_offset 16
	movb	$1, (%rax)
	call	_ZN7openpal8MaxValueItEET_v@PLT
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rdx
	movw	%ax, (%rdx)
	popq	%rcx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE812:
	.size	_GLOBAL__sub_I_StaticLoadFunctions.cpp, .-_GLOBAL__sub_I_StaticLoadFunctions.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_StaticLoadFunctions.cpp
	.weak	_ZGVN7openpal7Bit16LEItE3MaxE
	.section	.bss._ZGVN7openpal7Bit16LEItE3MaxE,"awG",@nobits,_ZGVN7openpal7Bit16LEItE3MaxE,comdat
	.align 8
	.type	_ZGVN7openpal7Bit16LEItE3MaxE, @gnu_unique_object
	.size	_ZGVN7openpal7Bit16LEItE3MaxE, 8
_ZGVN7openpal7Bit16LEItE3MaxE:
	.zero	8
	.weak	_ZN7openpal7Bit16LEItE3MaxE
	.section	.bss._ZN7openpal7Bit16LEItE3MaxE,"awG",@nobits,_ZN7openpal7Bit16LEItE3MaxE,comdat
	.align 2
	.type	_ZN7openpal7Bit16LEItE3MaxE, @gnu_unique_object
	.size	_ZN7openpal7Bit16LEItE3MaxE, 2
_ZN7openpal7Bit16LEItE3MaxE:
	.zero	2
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
