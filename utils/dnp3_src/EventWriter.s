	.file	"EventWriter.cpp"
	.text
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB464:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA464
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$184, %rsp
	.cfi_def_cfa_offset 240
	movq	%fs:40, %rax
	movq	%rax, 168(%rsp)
	xorl	%eax, %eax
.LEHB0:
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %r13d
	cmpb	$1, %r13b
	je	.L2
	cmpb	$2, %r13b
	je	.L3
	movl	$1, 16(%rsp)
	movl	$5, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp310Group2Var110ReadTargetERN7openpal6RSliceERNS_6BinaryE@GOTPCREL(%rip), %xmm0
	movl	$258, %esi
	movhps	_ZN8opendnp310Group2Var111WriteTargetERKNS_6BinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
	testb	%r13b, %r13b
	je	.L115
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE0:
	testb	%al, %al
	je	.L49
	movq	0(%rbp), %rdi
	movq	32(%rsp), %rdx
	movl	16(%rsp), %eax
	movdqa	16(%rsp), %xmm5
	movdqu	(%rdi), %xmm6
	movq	%rdx, 128(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movaps	%xmm5, 112(%rsp)
	movl	%eax, 136(%rsp)
	movw	%dx, 140(%rsp)
	movq	%rdi, 160(%rsp)
	seta	142(%rsp)
	movaps	%xmm6, 144(%rsp)
	ja	.L116
.L50:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L51:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB1:
	call	*(%rax)
	testb	%al, %al
	je	.L65
	testq	%r12, %r12
	je	.L52
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L53
	cmpb	$0, 4(%r12)
	jne	.L53
	cmpw	$0, (%r12)
	jne	.L52
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	2(%rax), %r13b
	jne	.L52
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp36BinaryC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE1:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L54
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L117
.L54:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L56:
	testb	%al, %al
	je	.L57
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %ecx
	movw	%cx, (%rax)
.L57:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L115:
.LEHB2:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L118
	pxor	%xmm0, %xmm0
	xorl	%r10d, %r10d
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%r10w, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE2:
	movq	$0, 160(%rsp)
.L6:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L7:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB3:
	call	*(%rax)
	testb	%al, %al
	je	.L62
	testq	%r12, %r12
	je	.L8
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L9
	cmpb	$0, 4(%r12)
	jne	.L9
	cmpw	$0, (%r12)
	jne	.L8
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 2(%rax)
	jne	.L8
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp36BinaryC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE3:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L10
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L119
.L10:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L12:
	testb	%al, %al
	je	.L13
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L13:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L14
	.p2align 4,,10
	.p2align 3
.L3:
	movq	_ZN8opendnp310Group2Var310ReadTargetERN7openpal6RSliceERNS_6BinaryE@GOTPCREL(%rip), %xmm0
	leaq	8(%rsp), %r13
	movl	$3, 16(%rsp)
	movq	%r13, %rdi
	movhps	_ZN8opendnp310Group2Var311WriteTargetERKNS_6BinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
.LEHB4:
	call	_ZN8opendnp311Group51Var1C1Ev@PLT
	movq	32(%r12), %rax
	movq	%rbp, %rdi
	movq	%rax, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter4MarkEv@PLT
	movl	$7, %ecx
	movl	$7, %edx
	movq	%rbp, %rdi
	movl	$307, %esi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L120
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 48(%rsp)
	movw	%di, 76(%rsp)
	leaq	80(%rsp), %rdi
	movl	$0, 72(%rsp)
	movb	$0, 78(%rsp)
	movups	%xmm0, 56(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE4:
	movq	$0, 96(%rsp)
.L31:
	xorl	%ebp, %ebp
	leaq	112(%rsp), %r13
.L38:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB5:
	call	*(%rax)
	testb	%al, %al
	je	.L64
	testq	%r12, %r12
	je	.L41
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L42
	cmpb	$0, 4(%r12)
	jne	.L42
	cmpw	$0, (%r12)
	jne	.L41
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 2(%rax)
	jne	.L41
	movq	32(%r12), %rdx
	movq	8(%rsp), %rax
	cmpq	%rax, %rdx
	jl	.L41
	subq	%rax, %rdx
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movq	%rdx, %rbp
	movzwl	(%rax), %eax
	cmpq	%rax, %rdx
	jg	.L41
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp36BinaryC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE5:
	movzwl	24(%r12), %edx
	movzbl	78(%rsp), %eax
	movq	%rbp, 120(%rsp)
	movw	%dx, 136(%rsp)
	testb	%al, %al
	je	.L43
	movq	96(%rsp), %rdi
	movl	72(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L121
.L43:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L45:
	testb	%al, %al
	je	.L57
	movq	88(%rsp), %rax
	movzwl	76(%rsp), %ecx
	movw	%cx, (%rax)
	jmp	.L57
	.p2align 4,,10
	.p2align 3
.L2:
	movl	$11, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp310Group2Var210ReadTargetERN7openpal6RSliceERNS_6BinaryE@GOTPCREL(%rip), %xmm0
	movl	$514, %esi
	movl	$7, 16(%rsp)
	movhps	_ZN8opendnp310Group2Var211WriteTargetERKNS_6BinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
.LEHB6:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L122
	pxor	%xmm0, %xmm0
	xorl	%r8d, %r8d
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%r8w, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE6:
	movq	$0, 160(%rsp)
.L18:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L19:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB7:
	call	*(%rax)
	testb	%al, %al
	je	.L63
	testq	%r12, %r12
	je	.L20
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L21
	cmpb	$0, 4(%r12)
	jne	.L21
	cmpw	$0, (%r12)
	jne	.L20
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L20
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_10BinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp36BinaryC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE7:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L25
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L123
.L24:
	testb	%al, %al
	je	.L25
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L25:
	xorl	%eax, %eax
	movb	%bpl, %al
.L14:
	movq	168(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L124
	addq	$184, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L118:
	.cfi_restore_state
	movq	0(%rbp), %rdi
	movl	16(%rsp), %eax
	xorl	%r11d, %r11d
	movdqa	16(%rsp), %xmm1
	movq	32(%rsp), %rdx
	movw	%r11w, 140(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 160(%rsp)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movaps	%xmm1, 112(%rsp)
	seta	142(%rsp)
	movaps	%xmm2, 144(%rsp)
	jbe	.L6
	movl	$2, %esi
.LEHB8:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L49:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%ax, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 160(%rsp)
	jmp	.L50
	.p2align 4,,10
	.p2align 3
.L122:
	movq	0(%rbp), %rdi
	movl	16(%rsp), %eax
	xorl	%r9d, %r9d
	movdqa	16(%rsp), %xmm3
	movq	32(%rsp), %rdx
	movw	%r9w, 140(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 160(%rsp)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movaps	%xmm3, 112(%rsp)
	seta	142(%rsp)
	movaps	%xmm4, 144(%rsp)
	jbe	.L18
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L120:
	movq	0(%rbp), %rdi
	movl	$1, %esi
	movq	8(%rdi), %rax
	movb	$1, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	0(%rbp), %rsi
	movq	%r13, %rdi
	call	_ZN8opendnp311Group51Var15WriteERKS0_RN7openpal6WSliceE@PLT
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movl	$770, %esi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE8:
	testb	%al, %al
	je	.L125
	movq	0(%rbp), %rdi
	movdqa	16(%rsp), %xmm7
	xorl	%esi, %esi
	movl	16(%rsp), %eax
	movq	32(%rsp), %rdx
	movw	%si, 140(%rsp)
	movaps	%xmm7, 112(%rsp)
	movdqu	(%rdi), %xmm7
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movq	%rdi, 160(%rsp)
	seta	142(%rsp)
	movaps	%xmm7, 144(%rsp)
	ja	.L32
.L36:
	movq	%rbp, %rdi
.LEHB9:
	call	_ZN8opendnp312HeaderWriter8RollbackEv@PLT
.LEHE9:
	movdqa	112(%rsp), %xmm1
	movq	160(%rsp), %rax
	movdqa	128(%rsp), %xmm2
	cmpb	$0, 142(%rsp)
	movdqa	144(%rsp), %xmm3
	movq	%rax, 96(%rsp)
	movaps	%xmm1, 48(%rsp)
	movaps	%xmm2, 64(%rsp)
	movaps	%xmm3, 80(%rsp)
	je	.L31
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L123:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB10:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r13, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE10:
.L21:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L119:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB11:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r14, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE11:
.L9:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L117:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB12:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r14, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE12:
.L53:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L121:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB13:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	96(%rsp), %rsi
	movq	%r13, %rdi
	call	*64(%rsp)
	movq	(%rbx), %rax
	addw	$1, 76(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE13:
.L42:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L64:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L41:
	movzbl	78(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L62:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L8:
	movzbl	142(%rsp), %eax
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L65:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L52:
	movzbl	142(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L63:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L20:
	movzbl	142(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L125:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%cx, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
.LEHB14:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 160(%rsp)
.L34:
	cmpb	$0, 142(%rsp)
	je	.L36
	movq	160(%rsp), %rax
	movdqa	112(%rsp), %xmm4
	movdqa	128(%rsp), %xmm5
	movdqa	144(%rsp), %xmm6
	movq	%rax, 96(%rsp)
	movaps	%xmm4, 48(%rsp)
	movaps	%xmm5, 64(%rsp)
	movaps	%xmm6, 80(%rsp)
.L60:
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L32:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L116:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE14:
	jmp	.L50
.L124:
	call	__stack_chk_fail@PLT
.L67:
	movq	%rax, %rdi
	jmp	.L26
.L66:
	movq	%rax, %rdi
	jmp	.L15
.L69:
	movq	%rax, %rdi
	jmp	.L39
.L68:
	movq	%rax, %rdi
	jmp	.L47
.L70:
	movq	%rax, %rdi
	jmp	.L58
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA464:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE464-.LLSDACSB464
.LLSDACSB464:
	.uleb128 .LEHB0-.LFB464
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB464
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L70-.LFB464
	.uleb128 0
	.uleb128 .LEHB2-.LFB464
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB464
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L66-.LFB464
	.uleb128 0
	.uleb128 .LEHB4-.LFB464
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB464
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L68-.LFB464
	.uleb128 0
	.uleb128 .LEHB6-.LFB464
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB7-.LFB464
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L67-.LFB464
	.uleb128 0
	.uleb128 .LEHB8-.LFB464
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB464
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L69-.LFB464
	.uleb128 0
	.uleb128 .LEHB10-.LFB464
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L67-.LFB464
	.uleb128 0
	.uleb128 .LEHB11-.LFB464
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L66-.LFB464
	.uleb128 0
	.uleb128 .LEHB12-.LFB464
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L70-.LFB464
	.uleb128 0
	.uleb128 .LEHB13-.LFB464
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L68-.LFB464
	.uleb128 0
	.uleb128 .LEHB14-.LFB464
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSE464:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC464
	.type	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB464:
.L26:
	.cfi_def_cfa_offset 240
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 142(%rsp)
	je	.L27
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L27:
.LEHB15:
	call	_Unwind_Resume@PLT
.L15:
	cmpb	$0, 142(%rsp)
	je	.L16
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L16:
	call	_Unwind_Resume@PLT
.L47:
	cmpb	$0, 78(%rsp)
	je	.L48
	movq	88(%rsp), %rax
	movzwl	76(%rsp), %edx
	movw	%dx, (%rax)
.L48:
	call	_Unwind_Resume@PLT
.L39:
	cmpb	$0, 142(%rsp)
	je	.L40
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L40:
	call	_Unwind_Resume@PLT
.L58:
	cmpb	$0, 142(%rsp)
	je	.L59
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L59:
	call	_Unwind_Resume@PLT
.LEHE15:
	.cfi_endproc
.LFE464:
	.section	.gcc_except_table
.LLSDAC464:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC464-.LLSDACSBC464
.LLSDACSBC464:
	.uleb128 .LEHB15-.LCOLDB0
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
.LLSDACSEC464:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
	.align 2
.LCOLDB1:
	.text
.LHOTB1:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB465:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA465
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$184, %rsp
	.cfi_def_cfa_offset 240
	movq	%fs:40, %rax
	movq	%rax, 168(%rsp)
	xorl	%eax, %eax
.LEHB16:
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %r13d
	cmpb	$1, %r13b
	je	.L127
	cmpb	$2, %r13b
	je	.L128
	movl	$1, 16(%rsp)
	movl	$5, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp310Group4Var110ReadTargetERN7openpal6RSliceERNS_15DoubleBitBinaryE@GOTPCREL(%rip), %xmm0
	movl	$260, %esi
	movhps	_ZN8opendnp310Group4Var111WriteTargetERKNS_15DoubleBitBinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
	testb	%r13b, %r13b
	je	.L239
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE16:
	testb	%al, %al
	je	.L174
	movq	0(%rbp), %rdi
	movq	32(%rsp), %rdx
	movl	16(%rsp), %eax
	movdqa	16(%rsp), %xmm5
	movdqu	(%rdi), %xmm6
	movq	%rdx, 128(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movaps	%xmm5, 112(%rsp)
	movl	%eax, 136(%rsp)
	movw	%dx, 140(%rsp)
	movq	%rdi, 160(%rsp)
	seta	142(%rsp)
	movaps	%xmm6, 144(%rsp)
	ja	.L240
.L175:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L176:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB17:
	call	*(%rax)
	testb	%al, %al
	je	.L190
	testq	%r12, %r12
	je	.L177
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L178
	cmpb	$0, 4(%r12)
	jne	.L178
	cmpw	$4, (%r12)
	jne	.L177
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	2(%rax), %r13b
	jne	.L177
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp315DoubleBitBinaryC1ENS_9DoubleBitENS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE17:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L179
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L241
.L179:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L181:
	testb	%al, %al
	je	.L182
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %ecx
	movw	%cx, (%rax)
.L182:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L139
	.p2align 4,,10
	.p2align 3
.L239:
.LEHB18:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L242
	pxor	%xmm0, %xmm0
	xorl	%r10d, %r10d
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%r10w, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE18:
	movq	$0, 160(%rsp)
.L131:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L132:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB19:
	call	*(%rax)
	testb	%al, %al
	je	.L187
	testq	%r12, %r12
	je	.L133
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L134
	cmpb	$0, 4(%r12)
	jne	.L134
	cmpw	$4, (%r12)
	jne	.L133
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 2(%rax)
	jne	.L133
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp315DoubleBitBinaryC1ENS_9DoubleBitENS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE19:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L135
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L243
.L135:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L137:
	testb	%al, %al
	je	.L138
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L138:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L139
	.p2align 4,,10
	.p2align 3
.L128:
	movq	_ZN8opendnp310Group4Var310ReadTargetERN7openpal6RSliceERNS_15DoubleBitBinaryE@GOTPCREL(%rip), %xmm0
	leaq	8(%rsp), %r13
	movl	$3, 16(%rsp)
	movq	%r13, %rdi
	movhps	_ZN8opendnp310Group4Var311WriteTargetERKNS_15DoubleBitBinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
.LEHB20:
	call	_ZN8opendnp311Group51Var1C1Ev@PLT
	movq	32(%r12), %rax
	movq	%rbp, %rdi
	movq	%rax, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter4MarkEv@PLT
	movl	$7, %ecx
	movl	$7, %edx
	movq	%rbp, %rdi
	movl	$307, %esi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L244
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 48(%rsp)
	movw	%di, 76(%rsp)
	leaq	80(%rsp), %rdi
	movl	$0, 72(%rsp)
	movb	$0, 78(%rsp)
	movups	%xmm0, 56(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE20:
	movq	$0, 96(%rsp)
.L156:
	xorl	%ebp, %ebp
	leaq	112(%rsp), %r13
.L163:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB21:
	call	*(%rax)
	testb	%al, %al
	je	.L189
	testq	%r12, %r12
	je	.L166
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L167
	cmpb	$0, 4(%r12)
	jne	.L167
	cmpw	$4, (%r12)
	jne	.L166
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 2(%rax)
	jne	.L166
	movq	32(%r12), %rdx
	movq	8(%rsp), %rax
	cmpq	%rax, %rdx
	jl	.L166
	subq	%rax, %rdx
	movq	_ZN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	movq	%rdx, %rbp
	movzwl	(%rax), %eax
	cmpq	%rax, %rdx
	jg	.L166
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp315DoubleBitBinaryC1ENS_9DoubleBitENS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE21:
	movzwl	24(%r12), %edx
	movzbl	78(%rsp), %eax
	movq	%rbp, 120(%rsp)
	movw	%dx, 136(%rsp)
	testb	%al, %al
	je	.L168
	movq	96(%rsp), %rdi
	movl	72(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L245
.L168:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L170:
	testb	%al, %al
	je	.L182
	movq	88(%rsp), %rax
	movzwl	76(%rsp), %ecx
	movw	%cx, (%rax)
	jmp	.L182
	.p2align 4,,10
	.p2align 3
.L127:
	movl	$11, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp310Group4Var210ReadTargetERN7openpal6RSliceERNS_15DoubleBitBinaryE@GOTPCREL(%rip), %xmm0
	movl	$516, %esi
	movl	$7, 16(%rsp)
	movhps	_ZN8opendnp310Group4Var211WriteTargetERKNS_15DoubleBitBinaryERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 24(%rsp)
.LEHB22:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L246
	pxor	%xmm0, %xmm0
	xorl	%r8d, %r8d
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%r8w, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE22:
	movq	$0, 160(%rsp)
.L143:
	xorl	%ebp, %ebp
	leaq	48(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L144:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB23:
	call	*(%rax)
	testb	%al, %al
	je	.L188
	testq	%r12, %r12
	je	.L145
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L146
	cmpb	$0, 4(%r12)
	jne	.L146
	cmpw	$4, (%r12)
	jne	.L145
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L145
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_19DoubleBitBinarySpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp315DoubleBitBinaryC1ENS_9DoubleBitENS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE23:
	movzwl	24(%r12), %edx
	movzbl	142(%rsp), %eax
	movw	%dx, 72(%rsp)
	testb	%al, %al
	je	.L150
	movq	160(%rsp), %rdi
	movl	136(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L247
.L149:
	testb	%al, %al
	je	.L150
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L150:
	xorl	%eax, %eax
	movb	%bpl, %al
.L139:
	movq	168(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L248
	addq	$184, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L242:
	.cfi_restore_state
	movq	0(%rbp), %rdi
	movl	16(%rsp), %eax
	xorl	%r11d, %r11d
	movdqa	16(%rsp), %xmm1
	movq	32(%rsp), %rdx
	movw	%r11w, 140(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 160(%rsp)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movaps	%xmm1, 112(%rsp)
	seta	142(%rsp)
	movaps	%xmm2, 144(%rsp)
	jbe	.L131
	movl	$2, %esi
.LEHB24:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L174:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%ax, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 160(%rsp)
	jmp	.L175
	.p2align 4,,10
	.p2align 3
.L246:
	movq	0(%rbp), %rdi
	movl	16(%rsp), %eax
	xorl	%r9d, %r9d
	movdqa	16(%rsp), %xmm3
	movq	32(%rsp), %rdx
	movw	%r9w, 140(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 160(%rsp)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movaps	%xmm3, 112(%rsp)
	seta	142(%rsp)
	movaps	%xmm4, 144(%rsp)
	jbe	.L143
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L143
	.p2align 4,,10
	.p2align 3
.L244:
	movq	0(%rbp), %rdi
	movl	$1, %esi
	movq	8(%rdi), %rax
	movb	$1, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	0(%rbp), %rsi
	movq	%r13, %rdi
	call	_ZN8opendnp311Group51Var15WriteERKS0_RN7openpal6WSliceE@PLT
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movl	$772, %esi
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE24:
	testb	%al, %al
	je	.L249
	movq	0(%rbp), %rdi
	movdqa	16(%rsp), %xmm7
	xorl	%esi, %esi
	movl	16(%rsp), %eax
	movq	32(%rsp), %rdx
	movw	%si, 140(%rsp)
	movaps	%xmm7, 112(%rsp)
	movdqu	(%rdi), %xmm7
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 128(%rsp)
	movl	%eax, 136(%rsp)
	movq	%rdi, 160(%rsp)
	seta	142(%rsp)
	movaps	%xmm7, 144(%rsp)
	ja	.L157
.L161:
	movq	%rbp, %rdi
.LEHB25:
	call	_ZN8opendnp312HeaderWriter8RollbackEv@PLT
.LEHE25:
	movdqa	112(%rsp), %xmm1
	movq	160(%rsp), %rax
	movdqa	128(%rsp), %xmm2
	cmpb	$0, 142(%rsp)
	movdqa	144(%rsp), %xmm3
	movq	%rax, 96(%rsp)
	movaps	%xmm1, 48(%rsp)
	movaps	%xmm2, 64(%rsp)
	movaps	%xmm3, 80(%rsp)
	je	.L156
	jmp	.L185
	.p2align 4,,10
	.p2align 3
.L247:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB26:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r13, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE26:
.L146:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L144
	.p2align 4,,10
	.p2align 3
.L243:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB27:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r14, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE27:
.L134:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L132
	.p2align 4,,10
	.p2align 3
.L241:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB28:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	160(%rsp), %rsi
	movq	%r14, %rdi
	call	*128(%rsp)
	movq	(%rbx), %rax
	movzbl	2(%r12), %esi
	movq	%rbx, %rdi
	addw	$1, 140(%rsp)
	movzwl	(%r12), %edx
	movb	$1, 4(%r12)
	call	*8(%rax)
.LEHE28:
.L178:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L176
	.p2align 4,,10
	.p2align 3
.L245:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB29:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	96(%rsp), %rsi
	movq	%r13, %rdi
	call	*64(%rsp)
	movq	(%rbx), %rax
	addw	$1, 76(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE29:
.L167:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L163
	.p2align 4,,10
	.p2align 3
.L189:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L166:
	movzbl	78(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L170
	.p2align 4,,10
	.p2align 3
.L187:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L133:
	movzbl	142(%rsp), %eax
	jmp	.L137
	.p2align 4,,10
	.p2align 3
.L190:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L177:
	movzbl	142(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L181
	.p2align 4,,10
	.p2align 3
.L188:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L145:
	movzbl	142(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L149
	.p2align 4,,10
	.p2align 3
.L249:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	144(%rsp), %rdi
	movl	$0, 112(%rsp)
	movl	$0, 136(%rsp)
	movw	%cx, 140(%rsp)
	movb	$0, 142(%rsp)
	movups	%xmm0, 120(%rsp)
.LEHB30:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 160(%rsp)
.L159:
	cmpb	$0, 142(%rsp)
	je	.L161
	movq	160(%rsp), %rax
	movdqa	112(%rsp), %xmm4
	movdqa	128(%rsp), %xmm5
	movdqa	144(%rsp), %xmm6
	movq	%rax, 96(%rsp)
	movaps	%xmm4, 48(%rsp)
	movaps	%xmm5, 64(%rsp)
	movaps	%xmm6, 80(%rsp)
.L185:
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
	jmp	.L156
	.p2align 4,,10
	.p2align 3
.L157:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L159
	.p2align 4,,10
	.p2align 3
.L240:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE30:
	jmp	.L175
.L248:
	call	__stack_chk_fail@PLT
.L192:
	movq	%rax, %rdi
	jmp	.L151
.L191:
	movq	%rax, %rdi
	jmp	.L140
.L194:
	movq	%rax, %rdi
	jmp	.L164
.L193:
	movq	%rax, %rdi
	jmp	.L172
.L195:
	movq	%rax, %rdi
	jmp	.L183
	.section	.gcc_except_table
.LLSDA465:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE465-.LLSDACSB465
.LLSDACSB465:
	.uleb128 .LEHB16-.LFB465
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB17-.LFB465
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L195-.LFB465
	.uleb128 0
	.uleb128 .LEHB18-.LFB465
	.uleb128 .LEHE18-.LEHB18
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB19-.LFB465
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L191-.LFB465
	.uleb128 0
	.uleb128 .LEHB20-.LFB465
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB21-.LFB465
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L193-.LFB465
	.uleb128 0
	.uleb128 .LEHB22-.LFB465
	.uleb128 .LEHE22-.LEHB22
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB23-.LFB465
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L192-.LFB465
	.uleb128 0
	.uleb128 .LEHB24-.LFB465
	.uleb128 .LEHE24-.LEHB24
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB25-.LFB465
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L194-.LFB465
	.uleb128 0
	.uleb128 .LEHB26-.LFB465
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L192-.LFB465
	.uleb128 0
	.uleb128 .LEHB27-.LFB465
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L191-.LFB465
	.uleb128 0
	.uleb128 .LEHB28-.LFB465
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L195-.LFB465
	.uleb128 0
	.uleb128 .LEHB29-.LFB465
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L193-.LFB465
	.uleb128 0
	.uleb128 .LEHB30-.LFB465
	.uleb128 .LEHE30-.LEHB30
	.uleb128 0
	.uleb128 0
.LLSDACSE465:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC465
	.type	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB465:
.L151:
	.cfi_def_cfa_offset 240
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 142(%rsp)
	je	.L152
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L152:
.LEHB31:
	call	_Unwind_Resume@PLT
.L140:
	cmpb	$0, 142(%rsp)
	je	.L141
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L141:
	call	_Unwind_Resume@PLT
.L172:
	cmpb	$0, 78(%rsp)
	je	.L173
	movq	88(%rsp), %rax
	movzwl	76(%rsp), %edx
	movw	%dx, (%rax)
.L173:
	call	_Unwind_Resume@PLT
.L164:
	cmpb	$0, 142(%rsp)
	je	.L165
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L165:
	call	_Unwind_Resume@PLT
.L183:
	cmpb	$0, 142(%rsp)
	je	.L184
	movq	152(%rsp), %rax
	movzwl	140(%rsp), %edx
	movw	%dx, (%rax)
.L184:
	call	_Unwind_Resume@PLT
.LEHE31:
	.cfi_endproc
.LFE465:
	.section	.gcc_except_table
.LLSDAC465:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC465-.LLSDACSBC465
.LLSDACSBC465:
	.uleb128 .LEHB31-.LCOLDB1
	.uleb128 .LEHE31-.LEHB31
	.uleb128 0
	.uleb128 0
.LLSDACSEC465:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
	.align 2
.LCOLDB2:
	.text
.LHOTB2:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB466:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA466
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB32:
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	5(%rax), %r13d
	cmpb	$2, %r13b
	je	.L251
	ja	.L252
	testb	%r13b, %r13b
	je	.L375
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group22Var210ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movl	$534, %esi
	movl	$3, (%rsp)
	movhps	_ZN8opendnp311Group22Var211WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE32:
	testb	%al, %al
	je	.L269
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r10d, %r10d
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	movw	%r10w, 92(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L376
.L270:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L271:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB33:
	call	*(%rax)
	testb	%al, %al
	je	.L315
	testq	%r12, %r12
	je	.L272
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L273
	cmpb	$0, 4(%r12)
	jne	.L273
	cmpw	$2, (%r12)
	jne	.L272
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	5(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L272
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp37CounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE33:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L277
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L377
.L276:
	testb	%al, %al
	je	.L277
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L277:
	xorl	%eax, %eax
	movb	%bpl, %al
.L266:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L378
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L252:
	.cfi_restore_state
	cmpb	$3, %r13b
	jne	.L379
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group22Var610ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movl	$1558, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group22Var611WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB34:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE34:
	testb	%al, %al
	je	.L291
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm7
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm1
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm7, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm1, 96(%rsp)
	ja	.L380
.L292:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L293:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB35:
	call	*(%rax)
	testb	%al, %al
	je	.L318
	testq	%r12, %r12
	je	.L305
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L295
	cmpb	$0, 4(%r12)
	jne	.L295
	cmpw	$2, (%r12)
	jne	.L305
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$3, 5(%rax)
	jne	.L305
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp37CounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L307
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L307
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE35:
.L295:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L293
	.p2align 4,,10
	.p2align 3
.L379:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group22Var110ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movl	$278, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group22Var111WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB36:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L381
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE36:
	movq	$0, 112(%rsp)
.L303:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L304:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB37:
	call	*(%rax)
	testb	%al, %al
	je	.L318
	testq	%r12, %r12
	je	.L305
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L306
	cmpb	$0, 4(%r12)
	jne	.L306
	cmpw	$2, (%r12)
	jne	.L305
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	5(%rax), %r13b
	jne	.L305
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp37CounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L307
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L307
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE37:
.L306:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L304
	.p2align 4,,10
	.p2align 3
.L375:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group22Var110ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movl	$278, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group22Var111WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB38:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L382
	pxor	%xmm0, %xmm0
	xorl	%r11d, %r11d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r11w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE38:
	movq	$0, 112(%rsp)
.L258:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L259:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB39:
	call	*(%rax)
	testb	%al, %al
	je	.L314
	testq	%r12, %r12
	je	.L260
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L261
	cmpb	$0, 4(%r12)
	jne	.L261
	cmpw	$2, (%r12)
	jne	.L260
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 5(%rax)
	jne	.L260
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp37CounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE39:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L262
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L383
.L262:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L264:
	testb	%al, %al
	je	.L265
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L265:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L266
	.p2align 4,,10
	.p2align 3
.L251:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group22Var510ReadTargetERN7openpal6RSliceERNS_7CounterE@GOTPCREL(%rip), %xmm0
	movl	$1302, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group22Var511WriteTargetERKNS_7CounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB40:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L384
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE40:
	movq	$0, 112(%rsp)
.L281:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L282:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB41:
	call	*(%rax)
	testb	%al, %al
	je	.L318
	testq	%r12, %r12
	je	.L305
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L284
	cmpb	$0, 4(%r12)
	jne	.L284
	cmpw	$2, (%r12)
	jne	.L305
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 5(%rax)
	jne	.L305
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_11CounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp37CounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE41:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L307
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L385
	.p2align 4,,10
	.p2align 3
.L307:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L309:
	testb	%al, %al
	je	.L310
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L310:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L266
	.p2align 4,,10
	.p2align 3
.L384:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm5
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm6
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	jbe	.L281
	movl	$2, %esi
.LEHB42:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L281
	.p2align 4,,10
	.p2align 3
.L382:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%ebp, %ebp
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%bp, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	jbe	.L258
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L258
	.p2align 4,,10
	.p2align 3
.L381:
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm2
	movdqu	(%rdi), %xmm3
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm2, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm3, 96(%rsp)
	jbe	.L303
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L303
	.p2align 4,,10
	.p2align 3
.L269:
	pxor	%xmm0, %xmm0
	xorl	%r9d, %r9d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r9w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L270
	.p2align 4,,10
	.p2align 3
.L291:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE42:
	movq	$0, 112(%rsp)
	jmp	.L292
	.p2align 4,,10
	.p2align 3
.L377:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB43:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE43:
.L273:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L271
	.p2align 4,,10
	.p2align 3
.L383:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB44:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE44:
.L261:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L259
	.p2align 4,,10
	.p2align 3
.L385:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB45:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE45:
.L284:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L282
	.p2align 4,,10
	.p2align 3
.L318:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L305:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L309
	.p2align 4,,10
	.p2align 3
.L314:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L260:
	movzbl	94(%rsp), %eax
	jmp	.L264
	.p2align 4,,10
	.p2align 3
.L315:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L272:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L276
	.p2align 4,,10
	.p2align 3
.L376:
	movl	$2, %esi
.LEHB46:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L270
	.p2align 4,,10
	.p2align 3
.L380:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE46:
	jmp	.L292
.L378:
	call	__stack_chk_fail@PLT
.L320:
	movq	%rax, %rdi
	jmp	.L278
.L319:
	movq	%rax, %rdi
	jmp	.L267
.L322:
	movq	%rax, %rdi
	jmp	.L300
.L321:
	movq	%rax, %rdi
	jmp	.L289
.L323:
	movq	%rax, %rdi
	jmp	.L311
	.section	.gcc_except_table
.LLSDA466:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE466-.LLSDACSB466
.LLSDACSB466:
	.uleb128 .LEHB32-.LFB466
	.uleb128 .LEHE32-.LEHB32
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB33-.LFB466
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L320-.LFB466
	.uleb128 0
	.uleb128 .LEHB34-.LFB466
	.uleb128 .LEHE34-.LEHB34
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB35-.LFB466
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L322-.LFB466
	.uleb128 0
	.uleb128 .LEHB36-.LFB466
	.uleb128 .LEHE36-.LEHB36
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB37-.LFB466
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L323-.LFB466
	.uleb128 0
	.uleb128 .LEHB38-.LFB466
	.uleb128 .LEHE38-.LEHB38
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB39-.LFB466
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L319-.LFB466
	.uleb128 0
	.uleb128 .LEHB40-.LFB466
	.uleb128 .LEHE40-.LEHB40
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB41-.LFB466
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L321-.LFB466
	.uleb128 0
	.uleb128 .LEHB42-.LFB466
	.uleb128 .LEHE42-.LEHB42
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB43-.LFB466
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L320-.LFB466
	.uleb128 0
	.uleb128 .LEHB44-.LFB466
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L319-.LFB466
	.uleb128 0
	.uleb128 .LEHB45-.LFB466
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L321-.LFB466
	.uleb128 0
	.uleb128 .LEHB46-.LFB466
	.uleb128 .LEHE46-.LEHB46
	.uleb128 0
	.uleb128 0
.LLSDACSE466:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC466
	.type	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB466:
.L278:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L279
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L279:
.LEHB47:
	call	_Unwind_Resume@PLT
.L267:
	cmpb	$0, 94(%rsp)
	je	.L268
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L268:
	call	_Unwind_Resume@PLT
.L289:
	cmpb	$0, 94(%rsp)
	je	.L290
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L290:
	call	_Unwind_Resume@PLT
.L300:
	cmpb	$0, 94(%rsp)
	je	.L301
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L301:
	call	_Unwind_Resume@PLT
.L311:
	cmpb	$0, 94(%rsp)
	je	.L312
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L312:
	call	_Unwind_Resume@PLT
.LEHE47:
	.cfi_endproc
.LFE466:
	.section	.gcc_except_table
.LLSDAC466:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC466-.LLSDACSBC466
.LLSDACSBC466:
	.uleb128 .LEHB47-.LCOLDB2
	.uleb128 .LEHE47-.LEHB47
	.uleb128 0
	.uleb128 0
.LLSDACSEC466:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
	.align 2
.LCOLDB3:
	.text
.LHOTB3:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB467:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA467
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB48:
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	5(%rax), %r13d
	cmpb	$2, %r13b
	je	.L387
	ja	.L388
	testb	%r13b, %r13b
	je	.L511
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group23Var210ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movl	$535, %esi
	movl	$3, (%rsp)
	movhps	_ZN8opendnp311Group23Var211WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE48:
	testb	%al, %al
	je	.L405
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r10d, %r10d
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	movw	%r10w, 92(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L512
.L406:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L407:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB49:
	call	*(%rax)
	testb	%al, %al
	je	.L451
	testq	%r12, %r12
	je	.L408
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L409
	cmpb	$0, 4(%r12)
	jne	.L409
	cmpw	$3, (%r12)
	jne	.L408
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	5(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L408
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp313FrozenCounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE49:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L413
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L513
.L412:
	testb	%al, %al
	je	.L413
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L413:
	xorl	%eax, %eax
	movb	%bpl, %al
.L402:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L514
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L388:
	.cfi_restore_state
	cmpb	$3, %r13b
	jne	.L515
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group23Var610ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movl	$1559, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group23Var611WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB50:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE50:
	testb	%al, %al
	je	.L427
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm7
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm1
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm7, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm1, 96(%rsp)
	ja	.L516
.L428:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L429:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB51:
	call	*(%rax)
	testb	%al, %al
	je	.L454
	testq	%r12, %r12
	je	.L441
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L431
	cmpb	$0, 4(%r12)
	jne	.L431
	cmpw	$3, (%r12)
	jne	.L441
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$3, 5(%rax)
	jne	.L441
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp313FrozenCounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L443
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L443
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE51:
.L431:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L429
	.p2align 4,,10
	.p2align 3
.L515:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group23Var110ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movl	$279, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group23Var111WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB52:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L517
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE52:
	movq	$0, 112(%rsp)
.L439:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L440:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB53:
	call	*(%rax)
	testb	%al, %al
	je	.L454
	testq	%r12, %r12
	je	.L441
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L442
	cmpb	$0, 4(%r12)
	jne	.L442
	cmpw	$3, (%r12)
	jne	.L441
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	5(%rax), %r13b
	jne	.L441
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp313FrozenCounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L443
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L443
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE53:
.L442:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L440
	.p2align 4,,10
	.p2align 3
.L511:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group23Var110ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movl	$279, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group23Var111WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB54:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L518
	pxor	%xmm0, %xmm0
	xorl	%r11d, %r11d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r11w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE54:
	movq	$0, 112(%rsp)
.L394:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L395:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB55:
	call	*(%rax)
	testb	%al, %al
	je	.L450
	testq	%r12, %r12
	je	.L396
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L397
	cmpb	$0, 4(%r12)
	jne	.L397
	cmpw	$3, (%r12)
	jne	.L396
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 5(%rax)
	jne	.L396
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp313FrozenCounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE55:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L398
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L519
.L398:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L400:
	testb	%al, %al
	je	.L401
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L401:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L387:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group23Var510ReadTargetERN7openpal6RSliceERNS_13FrozenCounterE@GOTPCREL(%rip), %xmm0
	movl	$1303, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group23Var511WriteTargetERKNS_13FrozenCounterERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB56:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L520
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE56:
	movq	$0, 112(%rsp)
.L417:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L418:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB57:
	call	*(%rax)
	testb	%al, %al
	je	.L454
	testq	%r12, %r12
	je	.L441
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L420
	cmpb	$0, 4(%r12)
	jne	.L420
	cmpw	$3, (%r12)
	jne	.L441
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 5(%rax)
	jne	.L441
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_17FrozenCounterSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp313FrozenCounterC1EjNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE57:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L443
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L521
	.p2align 4,,10
	.p2align 3
.L443:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L445:
	testb	%al, %al
	je	.L446
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L446:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L520:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm5
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm6
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	jbe	.L417
	movl	$2, %esi
.LEHB58:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L417
	.p2align 4,,10
	.p2align 3
.L518:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%ebp, %ebp
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%bp, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	jbe	.L394
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L394
	.p2align 4,,10
	.p2align 3
.L517:
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm2
	movdqu	(%rdi), %xmm3
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm2, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm3, 96(%rsp)
	jbe	.L439
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L439
	.p2align 4,,10
	.p2align 3
.L405:
	pxor	%xmm0, %xmm0
	xorl	%r9d, %r9d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r9w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L406
	.p2align 4,,10
	.p2align 3
.L427:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE58:
	movq	$0, 112(%rsp)
	jmp	.L428
	.p2align 4,,10
	.p2align 3
.L513:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB59:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE59:
.L409:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L407
	.p2align 4,,10
	.p2align 3
.L519:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB60:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE60:
.L397:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L395
	.p2align 4,,10
	.p2align 3
.L521:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB61:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE61:
.L420:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L418
	.p2align 4,,10
	.p2align 3
.L454:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L441:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L445
	.p2align 4,,10
	.p2align 3
.L450:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L396:
	movzbl	94(%rsp), %eax
	jmp	.L400
	.p2align 4,,10
	.p2align 3
.L451:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L408:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L412
	.p2align 4,,10
	.p2align 3
.L512:
	movl	$2, %esi
.LEHB62:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L406
	.p2align 4,,10
	.p2align 3
.L516:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE62:
	jmp	.L428
.L514:
	call	__stack_chk_fail@PLT
.L456:
	movq	%rax, %rdi
	jmp	.L414
.L455:
	movq	%rax, %rdi
	jmp	.L403
.L458:
	movq	%rax, %rdi
	jmp	.L436
.L457:
	movq	%rax, %rdi
	jmp	.L425
.L459:
	movq	%rax, %rdi
	jmp	.L447
	.section	.gcc_except_table
.LLSDA467:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE467-.LLSDACSB467
.LLSDACSB467:
	.uleb128 .LEHB48-.LFB467
	.uleb128 .LEHE48-.LEHB48
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB49-.LFB467
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L456-.LFB467
	.uleb128 0
	.uleb128 .LEHB50-.LFB467
	.uleb128 .LEHE50-.LEHB50
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB51-.LFB467
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L458-.LFB467
	.uleb128 0
	.uleb128 .LEHB52-.LFB467
	.uleb128 .LEHE52-.LEHB52
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB53-.LFB467
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L459-.LFB467
	.uleb128 0
	.uleb128 .LEHB54-.LFB467
	.uleb128 .LEHE54-.LEHB54
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB55-.LFB467
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L455-.LFB467
	.uleb128 0
	.uleb128 .LEHB56-.LFB467
	.uleb128 .LEHE56-.LEHB56
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB57-.LFB467
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L457-.LFB467
	.uleb128 0
	.uleb128 .LEHB58-.LFB467
	.uleb128 .LEHE58-.LEHB58
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB59-.LFB467
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L456-.LFB467
	.uleb128 0
	.uleb128 .LEHB60-.LFB467
	.uleb128 .LEHE60-.LEHB60
	.uleb128 .L455-.LFB467
	.uleb128 0
	.uleb128 .LEHB61-.LFB467
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L457-.LFB467
	.uleb128 0
	.uleb128 .LEHB62-.LFB467
	.uleb128 .LEHE62-.LEHB62
	.uleb128 0
	.uleb128 0
.LLSDACSE467:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC467
	.type	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB467:
.L414:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L415
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L415:
.LEHB63:
	call	_Unwind_Resume@PLT
.L403:
	cmpb	$0, 94(%rsp)
	je	.L404
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L404:
	call	_Unwind_Resume@PLT
.L425:
	cmpb	$0, 94(%rsp)
	je	.L426
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L426:
	call	_Unwind_Resume@PLT
.L436:
	cmpb	$0, 94(%rsp)
	je	.L437
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L437:
	call	_Unwind_Resume@PLT
.L447:
	cmpb	$0, 94(%rsp)
	je	.L448
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L448:
	call	_Unwind_Resume@PLT
.LEHE63:
	.cfi_endproc
.LFE467:
	.section	.gcc_except_table
.LLSDAC467:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC467-.LLSDACSBC467
.LLSDACSBC467:
	.uleb128 .LEHB63-.LCOLDB3
	.uleb128 .LEHE63-.LEHB63
	.uleb128 0
	.uleb128 0
.LLSDACSEC467:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
	.align 2
.LCOLDB4:
	.text
.LHOTB4:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB468:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA468
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB64:
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %r13d
	cmpb	$7, %r13b
	ja	.L523
	leaq	.L525(%rip), %rcx
	movzbl	%r13b, %edx
	movslq	(%rcx,%rdx,4), %rax
	addq	%rcx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L525:
	.long	.L532-.L525
	.long	.L531-.L525
	.long	.L530-.L525
	.long	.L529-.L525
	.long	.L528-.L525
	.long	.L527-.L525
	.long	.L526-.L525
	.long	.L524-.L525
	.text
	.p2align 4,,10
	.p2align 3
.L526:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var710ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$1824, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group32Var711WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE64:
	testb	%al, %al
	je	.L600
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm6
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm7
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm6, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm7, 96(%rsp)
	ja	.L740
.L601:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L602:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB65:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L604
	cmpb	$0, 4(%r12)
	jne	.L604
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$6, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L616
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE65:
.L604:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L602
	.p2align 4,,10
	.p2align 3
.L524:
	movl	$19, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var810ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$2080, %esi
	movl	$15, (%rsp)
	movhps	_ZN8opendnp311Group32Var811WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB66:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE66:
	testb	%al, %al
	je	.L611
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	ja	.L741
.L612:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L613:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB67:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L615
	cmpb	$0, 4(%r12)
	jne	.L615
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$7, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L616
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE67:
.L615:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L613
	.p2align 4,,10
	.p2align 3
.L530:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var310ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$800, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group32Var311WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB68:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE68:
	testb	%al, %al
	je	.L556
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm5
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm6
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	ja	.L742
.L557:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L558:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB69:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L560
	cmpb	$0, 4(%r12)
	jne	.L560
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L616
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE69:
.L560:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L558
	.p2align 4,,10
	.p2align 3
.L529:
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var410ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$1056, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group32Var411WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB70:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE70:
	testb	%al, %al
	je	.L567
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r14d, %r14d
	movdqa	(%rsp), %xmm7
	movq	16(%rsp), %rdx
	movw	%r14w, 92(%rsp)
	movdqu	(%rdi), %xmm1
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm7, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm1, 96(%rsp)
	ja	.L743
.L568:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L569:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB71:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L571
	cmpb	$0, 4(%r12)
	jne	.L571
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$3, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L616
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE71:
.L571:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L569
	.p2align 4,,10
	.p2align 3
.L532:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var110ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$288, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group32Var111WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB72:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE72:
	testb	%al, %al
	je	.L533
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm2
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	ja	.L744
.L534:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L535:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB73:
	call	*(%rax)
	testb	%al, %al
	je	.L634
	testq	%r12, %r12
	je	.L536
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L537
	cmpb	$0, 4(%r12)
	jne	.L537
	cmpw	$1, (%r12)
	jne	.L536
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 9(%rax)
	jne	.L536
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r14, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE73:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L538
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L745
.L538:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L540:
	testb	%al, %al
	je	.L541
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L541:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L542
	.p2align 4,,10
	.p2align 3
.L531:
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var210ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$544, %esi
	movl	$3, (%rsp)
	movhps	_ZN8opendnp311Group32Var211WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB74:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE74:
	testb	%al, %al
	je	.L545
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm4
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L746
.L546:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L547:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB75:
	call	*(%rax)
	testb	%al, %al
	je	.L635
	testq	%r12, %r12
	je	.L548
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L549
	cmpb	$0, 4(%r12)
	jne	.L549
	cmpw	$1, (%r12)
	jne	.L548
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L548
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%r15d, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE75:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L553
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L747
.L552:
	testb	%al, %al
	je	.L553
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L553:
	xorl	%eax, %eax
	movb	%bpl, %al
	.p2align 4,,10
	.p2align 3
.L542:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L748
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L528:
	.cfi_restore_state
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var510ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$1312, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group32Var511WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB76:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE76:
	testb	%al, %al
	je	.L578
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%ebp, %ebp
	movdqa	(%rsp), %xmm2
	movq	16(%rsp), %rdx
	movw	%bp, 92(%rsp)
	movdqu	(%rdi), %xmm3
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm2, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm3, 96(%rsp)
	ja	.L749
.L579:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L580:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB77:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L582
	cmpb	$0, 4(%r12)
	jne	.L582
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$4, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L616
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE77:
.L582:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L580
	.p2align 4,,10
	.p2align 3
.L527:
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var610ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$1568, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group32Var611WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB78:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE78:
	testb	%al, %al
	je	.L589
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r10d, %r10d
	movdqa	(%rsp), %xmm4
	movq	16(%rsp), %rdx
	movw	%r10w, 92(%rsp)
	movdqu	(%rdi), %xmm5
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm4, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm5, 96(%rsp)
	ja	.L750
.L590:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L591:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB79:
	call	*(%rax)
	testb	%al, %al
	je	.L641
	testq	%r12, %r12
	je	.L614
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L593
	cmpb	$0, 4(%r12)
	jne	.L593
	cmpw	$1, (%r12)
	jne	.L614
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$5, 9(%rax)
	jne	.L614
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE79:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L616
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L751
	.p2align 4,,10
	.p2align 3
.L616:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L618:
	testb	%al, %al
	je	.L630
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L630:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L542
	.p2align 4,,10
	.p2align 3
.L641:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L614:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L618
	.p2align 4,,10
	.p2align 3
.L747:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB80:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE80:
.L549:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L547
	.p2align 4,,10
	.p2align 3
.L751:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB81:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE81:
.L593:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L591
	.p2align 4,,10
	.p2align 3
.L745:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB82:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE82:
.L537:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L535
.L523:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group32Var110ReadTargetERN7openpal6RSliceERNS_6AnalogE@GOTPCREL(%rip), %xmm0
	movl	$288, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group32Var111WriteTargetERKNS_6AnalogERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB83:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE83:
	testb	%al, %al
	je	.L622
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm3
	movdqu	(%rdi), %xmm4
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L752
.L623:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L624:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB84:
	call	*(%rax)
	testb	%al, %al
	je	.L642
	testq	%r12, %r12
	je	.L625
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L626
	cmpb	$0, 4(%r12)
	jne	.L626
	cmpw	$1, (%r12)
	jne	.L625
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	9(%rax), %r13b
	jne	.L625
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_10AnalogSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r14, %rdi
	call	_ZN8opendnp36AnalogC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L627
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L753
.L627:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L629:
	testb	%al, %al
	je	.L630
	movzwl	92(%rsp), %ecx
	movq	104(%rsp), %rax
	movw	%cx, (%rax)
	jmp	.L630
	.p2align 4,,10
	.p2align 3
.L753:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE84:
.L626:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L624
	.p2align 4,,10
	.p2align 3
.L642:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L625:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L629
	.p2align 4,,10
	.p2align 3
.L634:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L536:
	movzbl	94(%rsp), %eax
	jmp	.L540
	.p2align 4,,10
	.p2align 3
.L635:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L548:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L552
	.p2align 4,,10
	.p2align 3
.L567:
	pxor	%xmm0, %xmm0
	xorl	%r13d, %r13d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r13w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
.LEHB85:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L568
	.p2align 4,,10
	.p2align 3
.L533:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L534
	.p2align 4,,10
	.p2align 3
.L578:
	pxor	%xmm0, %xmm0
	xorl	%r11d, %r11d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r11w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L579
	.p2align 4,,10
	.p2align 3
.L622:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L623
	.p2align 4,,10
	.p2align 3
.L589:
	pxor	%xmm0, %xmm0
	xorl	%r9d, %r9d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r9w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L590
	.p2align 4,,10
	.p2align 3
.L611:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L612
	.p2align 4,,10
	.p2align 3
.L545:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L546
	.p2align 4,,10
	.p2align 3
.L600:
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L601
	.p2align 4,,10
	.p2align 3
.L556:
	pxor	%xmm0, %xmm0
	xorl	%r15d, %r15d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r15w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L557
	.p2align 4,,10
	.p2align 3
.L752:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L623
	.p2align 4,,10
	.p2align 3
.L750:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L590
	.p2align 4,,10
	.p2align 3
.L749:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L579
	.p2align 4,,10
	.p2align 3
.L746:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L546
	.p2align 4,,10
	.p2align 3
.L744:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L534
	.p2align 4,,10
	.p2align 3
.L743:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L568
	.p2align 4,,10
	.p2align 3
.L742:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L557
	.p2align 4,,10
	.p2align 3
.L741:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L612
	.p2align 4,,10
	.p2align 3
.L740:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE85:
	jmp	.L601
.L748:
	call	__stack_chk_fail@PLT
.L646:
	movq	%rax, %rdi
	jmp	.L576
.L644:
	movq	%rax, %rdi
	jmp	.L554
.L645:
	movq	%rax, %rdi
	jmp	.L565
.L651:
	movq	%rax, %rdi
	jmp	.L631
.L643:
	movq	%rax, %rdi
	jmp	.L543
.L647:
	movq	%rax, %rdi
	jmp	.L587
.L649:
	movq	%rax, %rdi
	jmp	.L609
.L648:
	movq	%rax, %rdi
	jmp	.L598
.L650:
	movq	%rax, %rdi
	jmp	.L620
	.section	.gcc_except_table
.LLSDA468:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE468-.LLSDACSB468
.LLSDACSB468:
	.uleb128 .LEHB64-.LFB468
	.uleb128 .LEHE64-.LEHB64
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB65-.LFB468
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L649-.LFB468
	.uleb128 0
	.uleb128 .LEHB66-.LFB468
	.uleb128 .LEHE66-.LEHB66
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB67-.LFB468
	.uleb128 .LEHE67-.LEHB67
	.uleb128 .L650-.LFB468
	.uleb128 0
	.uleb128 .LEHB68-.LFB468
	.uleb128 .LEHE68-.LEHB68
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB69-.LFB468
	.uleb128 .LEHE69-.LEHB69
	.uleb128 .L645-.LFB468
	.uleb128 0
	.uleb128 .LEHB70-.LFB468
	.uleb128 .LEHE70-.LEHB70
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB71-.LFB468
	.uleb128 .LEHE71-.LEHB71
	.uleb128 .L646-.LFB468
	.uleb128 0
	.uleb128 .LEHB72-.LFB468
	.uleb128 .LEHE72-.LEHB72
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB73-.LFB468
	.uleb128 .LEHE73-.LEHB73
	.uleb128 .L643-.LFB468
	.uleb128 0
	.uleb128 .LEHB74-.LFB468
	.uleb128 .LEHE74-.LEHB74
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB75-.LFB468
	.uleb128 .LEHE75-.LEHB75
	.uleb128 .L644-.LFB468
	.uleb128 0
	.uleb128 .LEHB76-.LFB468
	.uleb128 .LEHE76-.LEHB76
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB77-.LFB468
	.uleb128 .LEHE77-.LEHB77
	.uleb128 .L647-.LFB468
	.uleb128 0
	.uleb128 .LEHB78-.LFB468
	.uleb128 .LEHE78-.LEHB78
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB79-.LFB468
	.uleb128 .LEHE79-.LEHB79
	.uleb128 .L648-.LFB468
	.uleb128 0
	.uleb128 .LEHB80-.LFB468
	.uleb128 .LEHE80-.LEHB80
	.uleb128 .L644-.LFB468
	.uleb128 0
	.uleb128 .LEHB81-.LFB468
	.uleb128 .LEHE81-.LEHB81
	.uleb128 .L648-.LFB468
	.uleb128 0
	.uleb128 .LEHB82-.LFB468
	.uleb128 .LEHE82-.LEHB82
	.uleb128 .L643-.LFB468
	.uleb128 0
	.uleb128 .LEHB83-.LFB468
	.uleb128 .LEHE83-.LEHB83
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB84-.LFB468
	.uleb128 .LEHE84-.LEHB84
	.uleb128 .L651-.LFB468
	.uleb128 0
	.uleb128 .LEHB85-.LFB468
	.uleb128 .LEHE85-.LEHB85
	.uleb128 0
	.uleb128 0
.LLSDACSE468:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC468
	.type	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB468:
.L576:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L577
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L577:
.LEHB86:
	call	_Unwind_Resume@PLT
.L554:
	cmpb	$0, 94(%rsp)
	je	.L555
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L555:
	call	_Unwind_Resume@PLT
.L587:
	cmpb	$0, 94(%rsp)
	je	.L588
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L588:
	call	_Unwind_Resume@PLT
.L565:
	cmpb	$0, 94(%rsp)
	je	.L566
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L566:
	call	_Unwind_Resume@PLT
.L609:
	cmpb	$0, 94(%rsp)
	je	.L610
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L610:
	call	_Unwind_Resume@PLT
.L631:
	cmpb	$0, 94(%rsp)
	je	.L632
	movzwl	92(%rsp), %edx
	movq	104(%rsp), %rax
	movw	%dx, (%rax)
.L632:
	call	_Unwind_Resume@PLT
.L598:
	cmpb	$0, 94(%rsp)
	je	.L599
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L599:
	call	_Unwind_Resume@PLT
.L543:
	cmpb	$0, 94(%rsp)
	je	.L544
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L544:
	call	_Unwind_Resume@PLT
.L620:
	cmpb	$0, 94(%rsp)
	je	.L621
	movzwl	92(%rsp), %edx
	movq	104(%rsp), %rax
	movw	%dx, (%rax)
.L621:
	call	_Unwind_Resume@PLT
.LEHE86:
	.cfi_endproc
.LFE468:
	.section	.gcc_except_table
.LLSDAC468:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC468-.LLSDACSBC468
.LLSDACSBC468:
	.uleb128 .LEHB86-.LCOLDB4
	.uleb128 .LEHE86-.LEHB86
	.uleb128 0
	.uleb128 0
.LLSDACSEC468:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
	.align 2
.LCOLDB5:
	.text
.LHOTB5:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB469:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA469
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB87:
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %r13d
	testb	%r13b, %r13b
	je	.L755
	cmpb	$1, %r13b
	je	.L756
	movl	$5, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group11Var110ReadTargetERN7openpal6RSliceERNS_18BinaryOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$267, %esi
	movl	$1, (%rsp)
	movhps	_ZN8opendnp311Group11Var111WriteTargetERKNS_18BinaryOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE87:
	testb	%al, %al
	je	.L781
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm5
	movdqu	(%rdi), %xmm6
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	ja	.L828
.L782:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L783:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB88:
	call	*(%rax)
	testb	%al, %al
	je	.L795
	testq	%r12, %r12
	je	.L784
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L785
	cmpb	$0, 4(%r12)
	jne	.L785
	cmpw	$5, (%r12)
	jne	.L784
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	2(%rax), %r13b
	jne	.L784
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp318BinaryOutputStatusC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE88:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L786
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L829
.L786:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L788:
	testb	%al, %al
	je	.L789
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L789:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L767
	.p2align 4,,10
	.p2align 3
.L755:
	movl	$5, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group11Var110ReadTargetERN7openpal6RSliceERNS_18BinaryOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$267, %esi
	movl	$1, (%rsp)
	movhps	_ZN8opendnp311Group11Var111WriteTargetERKNS_18BinaryOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB89:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L830
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE89:
	movq	$0, 112(%rsp)
.L759:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L760:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB90:
	call	*(%rax)
	testb	%al, %al
	je	.L793
	testq	%r12, %r12
	je	.L761
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L762
	cmpb	$0, 4(%r12)
	jne	.L762
	cmpw	$5, (%r12)
	jne	.L761
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 2(%rax)
	jne	.L761
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp318BinaryOutputStatusC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE90:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L763
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L831
.L763:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L765:
	testb	%al, %al
	je	.L766
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L766:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L767
	.p2align 4,,10
	.p2align 3
.L756:
	movl	$11, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group11Var210ReadTargetERN7openpal6RSliceERNS_18BinaryOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$523, %esi
	movl	$7, (%rsp)
	movhps	_ZN8opendnp311Group11Var211WriteTargetERKNS_18BinaryOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB91:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L832
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE91:
	movq	$0, 112(%rsp)
.L771:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L772:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB92:
	call	*(%rax)
	testb	%al, %al
	je	.L794
	testq	%r12, %r12
	je	.L773
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L774
	cmpb	$0, 4(%r12)
	jne	.L774
	cmpw	$5, (%r12)
	jne	.L773
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	2(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L773
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_22BinaryOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movzbl	(%rax), %esi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp318BinaryOutputStatusC1EbNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE92:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L778
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L833
.L777:
	testb	%al, %al
	je	.L778
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L778:
	xorl	%eax, %eax
	movb	%bpl, %al
.L767:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L834
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L832:
	.cfi_restore_state
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	jbe	.L771
	movl	$2, %esi
.LEHB93:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L771
	.p2align 4,,10
	.p2align 3
.L830:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	jbe	.L759
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L759
	.p2align 4,,10
	.p2align 3
.L781:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE93:
	movq	$0, 112(%rsp)
	jmp	.L782
	.p2align 4,,10
	.p2align 3
.L831:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB94:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE94:
.L762:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L760
	.p2align 4,,10
	.p2align 3
.L829:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB95:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE95:
.L785:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L783
	.p2align 4,,10
	.p2align 3
.L833:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB96:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE96:
.L774:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L772
	.p2align 4,,10
	.p2align 3
.L794:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L773:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L777
	.p2align 4,,10
	.p2align 3
.L793:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L761:
	movzbl	94(%rsp), %eax
	jmp	.L765
	.p2align 4,,10
	.p2align 3
.L795:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L784:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L788
	.p2align 4,,10
	.p2align 3
.L828:
	movl	$2, %esi
.LEHB97:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE97:
	jmp	.L782
.L834:
	call	__stack_chk_fail@PLT
.L796:
	movq	%rax, %rdi
	jmp	.L768
.L797:
	movq	%rax, %rdi
	jmp	.L779
.L798:
	movq	%rax, %rdi
	jmp	.L790
	.section	.gcc_except_table
.LLSDA469:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE469-.LLSDACSB469
.LLSDACSB469:
	.uleb128 .LEHB87-.LFB469
	.uleb128 .LEHE87-.LEHB87
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB88-.LFB469
	.uleb128 .LEHE88-.LEHB88
	.uleb128 .L798-.LFB469
	.uleb128 0
	.uleb128 .LEHB89-.LFB469
	.uleb128 .LEHE89-.LEHB89
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB90-.LFB469
	.uleb128 .LEHE90-.LEHB90
	.uleb128 .L796-.LFB469
	.uleb128 0
	.uleb128 .LEHB91-.LFB469
	.uleb128 .LEHE91-.LEHB91
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB92-.LFB469
	.uleb128 .LEHE92-.LEHB92
	.uleb128 .L797-.LFB469
	.uleb128 0
	.uleb128 .LEHB93-.LFB469
	.uleb128 .LEHE93-.LEHB93
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB94-.LFB469
	.uleb128 .LEHE94-.LEHB94
	.uleb128 .L796-.LFB469
	.uleb128 0
	.uleb128 .LEHB95-.LFB469
	.uleb128 .LEHE95-.LEHB95
	.uleb128 .L798-.LFB469
	.uleb128 0
	.uleb128 .LEHB96-.LFB469
	.uleb128 .LEHE96-.LEHB96
	.uleb128 .L797-.LFB469
	.uleb128 0
	.uleb128 .LEHB97-.LFB469
	.uleb128 .LEHE97-.LEHB97
	.uleb128 0
	.uleb128 0
.LLSDACSE469:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC469
	.type	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB469:
.L768:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L769
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L769:
.LEHB98:
	call	_Unwind_Resume@PLT
.L779:
	cmpb	$0, 94(%rsp)
	je	.L780
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L780:
	call	_Unwind_Resume@PLT
.L790:
	cmpb	$0, 94(%rsp)
	je	.L791
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L791:
	call	_Unwind_Resume@PLT
.LEHE98:
	.cfi_endproc
.LFE469:
	.section	.gcc_except_table
.LLSDAC469:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC469-.LLSDACSBC469
.LLSDACSBC469:
	.uleb128 .LEHB98-.LCOLDB5
	.uleb128 .LEHE98-.LEHB98
	.uleb128 0
	.uleb128 0
.LLSDACSEC469:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
	.align 2
.LCOLDB6:
	.text
.LHOTB6:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB470:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA470
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB99:
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %r13d
	cmpb	$7, %r13b
	ja	.L836
	leaq	.L838(%rip), %rcx
	movzbl	%r13b, %edx
	movslq	(%rcx,%rdx,4), %rax
	addq	%rcx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L838:
	.long	.L845-.L838
	.long	.L844-.L838
	.long	.L843-.L838
	.long	.L842-.L838
	.long	.L841-.L838
	.long	.L840-.L838
	.long	.L839-.L838
	.long	.L837-.L838
	.text
	.p2align 4,,10
	.p2align 3
.L839:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var710ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$1834, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group42Var711WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE99:
	testb	%al, %al
	je	.L913
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm6
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm7
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm6, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm7, 96(%rsp)
	ja	.L1053
.L914:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L915:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB100:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L917
	cmpb	$0, 4(%r12)
	jne	.L917
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$6, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L929
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE100:
.L917:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L915
	.p2align 4,,10
	.p2align 3
.L837:
	movl	$19, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var810ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$2090, %esi
	movl	$15, (%rsp)
	movhps	_ZN8opendnp311Group42Var811WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB101:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE101:
	testb	%al, %al
	je	.L924
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	ja	.L1054
.L925:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L926:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB102:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L928
	cmpb	$0, 4(%r12)
	jne	.L928
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$7, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L929
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE102:
.L928:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L926
	.p2align 4,,10
	.p2align 3
.L843:
	movl	$15, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var310ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$810, %esi
	movl	$11, (%rsp)
	movhps	_ZN8opendnp311Group42Var311WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB103:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE103:
	testb	%al, %al
	je	.L869
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm5
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm6
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	ja	.L1055
.L870:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L871:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB104:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L873
	cmpb	$0, 4(%r12)
	jne	.L873
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$2, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L929
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE104:
.L873:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L871
	.p2align 4,,10
	.p2align 3
.L842:
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var410ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$1066, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group42Var411WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB105:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE105:
	testb	%al, %al
	je	.L880
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r14d, %r14d
	movdqa	(%rsp), %xmm7
	movq	16(%rsp), %rdx
	movw	%r14w, 92(%rsp)
	movdqu	(%rdi), %xmm1
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm7, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm1, 96(%rsp)
	ja	.L1056
.L881:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L882:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB106:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L884
	cmpb	$0, 4(%r12)
	jne	.L884
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$3, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L929
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE106:
.L884:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L882
	.p2align 4,,10
	.p2align 3
.L845:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var110ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$298, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group42Var111WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB107:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE107:
	testb	%al, %al
	je	.L846
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm2
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	ja	.L1057
.L847:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L848:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB108:
	call	*(%rax)
	testb	%al, %al
	je	.L947
	testq	%r12, %r12
	je	.L849
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L850
	cmpb	$0, 4(%r12)
	jne	.L850
	cmpw	$6, (%r12)
	jne	.L849
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 9(%rax)
	jne	.L849
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r14, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE108:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L851
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1058
.L851:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L853:
	testb	%al, %al
	je	.L854
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L854:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L855
	.p2align 4,,10
	.p2align 3
.L844:
	movl	$7, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var210ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$554, %esi
	movl	$3, (%rsp)
	movhps	_ZN8opendnp311Group42Var211WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB109:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE109:
	testb	%al, %al
	je	.L858
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	addl	$2, %eax
	movdqu	(%rdi), %xmm4
	movl	%eax, 88(%rsp)
	xorl	%eax, %eax
	cmpl	$1, (%rdi)
	movq	%rdx, 80(%rsp)
	movw	%ax, 92(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L1059
.L859:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L860:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB110:
	call	*(%rax)
	testb	%al, %al
	je	.L948
	testq	%r12, %r12
	je	.L861
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L862
	cmpb	$0, 4(%r12)
	jne	.L862
	cmpw	$6, (%r12)
	jne	.L861
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L861
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%r15d, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE110:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L866
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1060
.L865:
	testb	%al, %al
	je	.L866
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L866:
	xorl	%eax, %eax
	movb	%bpl, %al
	.p2align 4,,10
	.p2align 3
.L855:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L1061
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L841:
	.cfi_restore_state
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var510ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$1322, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group42Var511WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB111:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE111:
	testb	%al, %al
	je	.L891
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%ebp, %ebp
	movdqa	(%rsp), %xmm2
	movq	16(%rsp), %rdx
	movw	%bp, 92(%rsp)
	movdqu	(%rdi), %xmm3
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm2, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm3, 96(%rsp)
	ja	.L1062
.L892:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L893:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB112:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L895
	cmpb	$0, 4(%r12)
	jne	.L895
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$4, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jb	.L929
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE112:
.L895:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L893
	.p2align 4,,10
	.p2align 3
.L840:
	movl	$13, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var610ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$1578, %esi
	movl	$9, (%rsp)
	movhps	_ZN8opendnp311Group42Var611WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB113:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE113:
	testb	%al, %al
	je	.L902
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r10d, %r10d
	movdqa	(%rsp), %xmm4
	movq	16(%rsp), %rdx
	movw	%r10w, 92(%rsp)
	movdqu	(%rdi), %xmm5
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm4, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm5, 96(%rsp)
	ja	.L1063
.L903:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L904:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB114:
	call	*(%rax)
	testb	%al, %al
	je	.L954
	testq	%r12, %r12
	je	.L927
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L906
	cmpb	$0, 4(%r12)
	jne	.L906
	cmpw	$6, (%r12)
	jne	.L927
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$5, 9(%rax)
	jne	.L927
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r13, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
.LEHE114:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L929
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1064
	.p2align 4,,10
	.p2align 3
.L929:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L931:
	testb	%al, %al
	je	.L943
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L943:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L855
	.p2align 4,,10
	.p2align 3
.L954:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L927:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L931
	.p2align 4,,10
	.p2align 3
.L1060:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB115:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE115:
.L862:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L860
	.p2align 4,,10
	.p2align 3
.L1064:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB116:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE116:
.L906:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L904
	.p2align 4,,10
	.p2align 3
.L1058:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB117:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE117:
.L850:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L848
.L836:
	movl	$9, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp311Group42Var110ReadTargetERN7openpal6RSliceERNS_18AnalogOutputStatusE@GOTPCREL(%rip), %xmm0
	movl	$298, %esi
	movl	$5, (%rsp)
	movhps	_ZN8opendnp311Group42Var111WriteTargetERKNS_18AnalogOutputStatusERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB118:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE118:
	testb	%al, %al
	je	.L935
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm3
	movdqu	(%rdi), %xmm4
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	ja	.L1065
.L936:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L937:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB119:
	call	*(%rax)
	testb	%al, %al
	je	.L955
	testq	%r12, %r12
	je	.L938
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L939
	cmpb	$0, 4(%r12)
	jne	.L939
	cmpw	$6, (%r12)
	jne	.L938
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	9(%rax), %r13b
	jne	.L938
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_22AnalogOutputStatusSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rdx
	movsd	(%rax), %xmm0
	movl	%ebp, %esi
	movq	%r14, %rdi
	call	_ZN8opendnp318AnalogOutputStatusC1EdNS_5FlagsEN7openpal10UInt48TypeE@PLT
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L940
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1066
.L940:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L942:
	testb	%al, %al
	je	.L943
	movzwl	92(%rsp), %ecx
	movq	104(%rsp), %rax
	movw	%cx, (%rax)
	jmp	.L943
	.p2align 4,,10
	.p2align 3
.L1066:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE119:
.L939:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L937
	.p2align 4,,10
	.p2align 3
.L955:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L938:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L942
	.p2align 4,,10
	.p2align 3
.L947:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L849:
	movzbl	94(%rsp), %eax
	jmp	.L853
	.p2align 4,,10
	.p2align 3
.L948:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L861:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L865
	.p2align 4,,10
	.p2align 3
.L880:
	pxor	%xmm0, %xmm0
	xorl	%r13d, %r13d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r13w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
.LEHB120:
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L881
	.p2align 4,,10
	.p2align 3
.L846:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L847
	.p2align 4,,10
	.p2align 3
.L891:
	pxor	%xmm0, %xmm0
	xorl	%r11d, %r11d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r11w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L892
	.p2align 4,,10
	.p2align 3
.L935:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L936
	.p2align 4,,10
	.p2align 3
.L902:
	pxor	%xmm0, %xmm0
	xorl	%r9d, %r9d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r9w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L903
	.p2align 4,,10
	.p2align 3
.L924:
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L925
	.p2align 4,,10
	.p2align 3
.L858:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L859
	.p2align 4,,10
	.p2align 3
.L913:
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L914
	.p2align 4,,10
	.p2align 3
.L869:
	pxor	%xmm0, %xmm0
	xorl	%r15d, %r15d
	leaq	96(%rsp), %rdi
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%r15w, 92(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	$0, 112(%rsp)
	jmp	.L870
	.p2align 4,,10
	.p2align 3
.L1065:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L936
	.p2align 4,,10
	.p2align 3
.L1063:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L903
	.p2align 4,,10
	.p2align 3
.L1062:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L892
	.p2align 4,,10
	.p2align 3
.L1059:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L859
	.p2align 4,,10
	.p2align 3
.L1057:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L847
	.p2align 4,,10
	.p2align 3
.L1056:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L881
	.p2align 4,,10
	.p2align 3
.L1055:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L870
	.p2align 4,,10
	.p2align 3
.L1054:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L925
	.p2align 4,,10
	.p2align 3
.L1053:
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE120:
	jmp	.L914
.L1061:
	call	__stack_chk_fail@PLT
.L959:
	movq	%rax, %rdi
	jmp	.L889
.L957:
	movq	%rax, %rdi
	jmp	.L867
.L958:
	movq	%rax, %rdi
	jmp	.L878
.L964:
	movq	%rax, %rdi
	jmp	.L944
.L956:
	movq	%rax, %rdi
	jmp	.L856
.L960:
	movq	%rax, %rdi
	jmp	.L900
.L962:
	movq	%rax, %rdi
	jmp	.L922
.L961:
	movq	%rax, %rdi
	jmp	.L911
.L963:
	movq	%rax, %rdi
	jmp	.L933
	.section	.gcc_except_table
.LLSDA470:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE470-.LLSDACSB470
.LLSDACSB470:
	.uleb128 .LEHB99-.LFB470
	.uleb128 .LEHE99-.LEHB99
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB100-.LFB470
	.uleb128 .LEHE100-.LEHB100
	.uleb128 .L962-.LFB470
	.uleb128 0
	.uleb128 .LEHB101-.LFB470
	.uleb128 .LEHE101-.LEHB101
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB102-.LFB470
	.uleb128 .LEHE102-.LEHB102
	.uleb128 .L963-.LFB470
	.uleb128 0
	.uleb128 .LEHB103-.LFB470
	.uleb128 .LEHE103-.LEHB103
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB104-.LFB470
	.uleb128 .LEHE104-.LEHB104
	.uleb128 .L958-.LFB470
	.uleb128 0
	.uleb128 .LEHB105-.LFB470
	.uleb128 .LEHE105-.LEHB105
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB106-.LFB470
	.uleb128 .LEHE106-.LEHB106
	.uleb128 .L959-.LFB470
	.uleb128 0
	.uleb128 .LEHB107-.LFB470
	.uleb128 .LEHE107-.LEHB107
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB108-.LFB470
	.uleb128 .LEHE108-.LEHB108
	.uleb128 .L956-.LFB470
	.uleb128 0
	.uleb128 .LEHB109-.LFB470
	.uleb128 .LEHE109-.LEHB109
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB110-.LFB470
	.uleb128 .LEHE110-.LEHB110
	.uleb128 .L957-.LFB470
	.uleb128 0
	.uleb128 .LEHB111-.LFB470
	.uleb128 .LEHE111-.LEHB111
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB112-.LFB470
	.uleb128 .LEHE112-.LEHB112
	.uleb128 .L960-.LFB470
	.uleb128 0
	.uleb128 .LEHB113-.LFB470
	.uleb128 .LEHE113-.LEHB113
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB114-.LFB470
	.uleb128 .LEHE114-.LEHB114
	.uleb128 .L961-.LFB470
	.uleb128 0
	.uleb128 .LEHB115-.LFB470
	.uleb128 .LEHE115-.LEHB115
	.uleb128 .L957-.LFB470
	.uleb128 0
	.uleb128 .LEHB116-.LFB470
	.uleb128 .LEHE116-.LEHB116
	.uleb128 .L961-.LFB470
	.uleb128 0
	.uleb128 .LEHB117-.LFB470
	.uleb128 .LEHE117-.LEHB117
	.uleb128 .L956-.LFB470
	.uleb128 0
	.uleb128 .LEHB118-.LFB470
	.uleb128 .LEHE118-.LEHB118
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB119-.LFB470
	.uleb128 .LEHE119-.LEHB119
	.uleb128 .L964-.LFB470
	.uleb128 0
	.uleb128 .LEHB120-.LFB470
	.uleb128 .LEHE120-.LEHB120
	.uleb128 0
	.uleb128 0
.LLSDACSE470:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC470
	.type	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB470:
.L889:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L890
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L890:
.LEHB121:
	call	_Unwind_Resume@PLT
.L867:
	cmpb	$0, 94(%rsp)
	je	.L868
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L868:
	call	_Unwind_Resume@PLT
.L900:
	cmpb	$0, 94(%rsp)
	je	.L901
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L901:
	call	_Unwind_Resume@PLT
.L878:
	cmpb	$0, 94(%rsp)
	je	.L879
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L879:
	call	_Unwind_Resume@PLT
.L922:
	cmpb	$0, 94(%rsp)
	je	.L923
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L923:
	call	_Unwind_Resume@PLT
.L944:
	cmpb	$0, 94(%rsp)
	je	.L945
	movzwl	92(%rsp), %edx
	movq	104(%rsp), %rax
	movw	%dx, (%rax)
.L945:
	call	_Unwind_Resume@PLT
.L911:
	cmpb	$0, 94(%rsp)
	je	.L912
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L912:
	call	_Unwind_Resume@PLT
.L856:
	cmpb	$0, 94(%rsp)
	je	.L857
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L857:
	call	_Unwind_Resume@PLT
.L933:
	cmpb	$0, 94(%rsp)
	je	.L934
	movzwl	92(%rsp), %edx
	movq	104(%rsp), %rax
	movw	%dx, (%rax)
.L934:
	call	_Unwind_Resume@PLT
.LEHE121:
	.cfi_endproc
.LFE470:
	.section	.gcc_except_table
.LLSDAC470:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC470-.LLSDACSBC470
.LLSDACSBC470:
	.uleb128 .LEHB121-.LCOLDB6
	.uleb128 .LEHE121-.LEHB121
	.uleb128 0
	.uleb128 0
.LLSDACSEC470:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
	.align 2
.LCOLDB7:
	.text
.LHOTB7:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB471:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA471
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movq	%rdx, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
.LEHB122:
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %r13d
	testb	%r13b, %r13b
	je	.L1068
	cmpb	$1, %r13b
	je	.L1069
	movl	$11, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp312Group122Var110ReadTargetERN7openpal6RSliceERNS_12SecurityStatE@GOTPCREL(%rip), %xmm0
	movl	$378, %esi
	movl	$7, (%rsp)
	movhps	_ZN8opendnp312Group122Var111WriteTargetERKNS_12SecurityStatERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
.LEHE122:
	testb	%al, %al
	je	.L1094
	movq	0(%rbp), %rdi
	movq	16(%rsp), %rdx
	movl	(%rsp), %eax
	movdqa	(%rsp), %xmm5
	movdqu	(%rdi), %xmm6
	movq	%rdx, 80(%rsp)
	xorl	%edx, %edx
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movw	%dx, 92(%rsp)
	movl	%eax, 88(%rsp)
	movq	%rdi, 112(%rsp)
	movaps	%xmm5, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm6, 96(%rsp)
	ja	.L1141
.L1095:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L1096:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB123:
	call	*(%rax)
	testb	%al, %al
	je	.L1108
	testq	%r12, %r12
	je	.L1097
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L1098
	cmpb	$0, 4(%r12)
	jne	.L1098
	cmpw	$7, (%r12)
	jne	.L1097
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	9(%rax), %r13b
	jne	.L1097
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movq	(%rax), %rsi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp312SecurityStatC1ENS0_5ValueEhN7openpal10UInt48TypeE@PLT
.LEHE123:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L1099
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1142
.L1099:
	movl	$1, %edx
	.p2align 4,,10
	.p2align 3
.L1101:
	testb	%al, %al
	je	.L1102
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %ecx
	movw	%cx, (%rax)
.L1102:
	xorl	%eax, %eax
	movb	%dl, %al
	jmp	.L1080
	.p2align 4,,10
	.p2align 3
.L1068:
	movl	$11, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp312Group122Var110ReadTargetERN7openpal6RSliceERNS_12SecurityStatE@GOTPCREL(%rip), %xmm0
	movl	$378, %esi
	movl	$7, (%rsp)
	movhps	_ZN8opendnp312Group122Var111WriteTargetERKNS_12SecurityStatERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB124:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1143
	xorl	%edi, %edi
	pxor	%xmm0, %xmm0
	movl	$0, 64(%rsp)
	movw	%di, 92(%rsp)
	leaq	96(%rsp), %rdi
	movl	$0, 88(%rsp)
	movb	$0, 94(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE124:
	movq	$0, 112(%rsp)
.L1072:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L1073:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB125:
	call	*(%rax)
	testb	%al, %al
	je	.L1106
	testq	%r12, %r12
	je	.L1074
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r15
	je	.L1075
	cmpb	$0, 4(%r12)
	jne	.L1075
	cmpw	$7, (%r12)
	jne	.L1074
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	cmpb	$0, 9(%rax)
	jne	.L1074
	movq	%r12, %rdi
	movzbl	40(%r12), %ebp
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movq	(%rax), %rsi
	movl	%ebp, %edx
	movq	%r14, %rdi
	call	_ZN8opendnp312SecurityStatC1ENS0_5ValueEhN7openpal10UInt48TypeE@PLT
.LEHE125:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L1076
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1144
.L1076:
	movl	$1, %r13d
	.p2align 4,,10
	.p2align 3
.L1078:
	testb	%al, %al
	je	.L1079
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L1079:
	xorl	%eax, %eax
	movb	%r13b, %al
	jmp	.L1080
	.p2align 4,,10
	.p2align 3
.L1069:
	movl	$17, %ecx
	movl	$40, %edx
	movq	%rbp, %rdi
	movq	_ZN8opendnp312Group122Var210ReadTargetERN7openpal6RSliceERNS_12SecurityStatE@GOTPCREL(%rip), %xmm0
	movl	$634, %esi
	movl	$13, (%rsp)
	movhps	_ZN8opendnp312Group122Var211WriteTargetERKNS_12SecurityStatERN7openpal6WSliceE@GOTPCREL(%rip), %xmm0
	movups	%xmm0, 8(%rsp)
.LEHB126:
	call	_ZN8opendnp312HeaderWriter22WriteHeaderWithReserveENS_16GroupVariationIDENS_13QualifierCodeEj@PLT
	testb	%al, %al
	jne	.L1145
	pxor	%xmm0, %xmm0
	xorl	%ecx, %ecx
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%cx, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE126:
	movq	$0, 112(%rsp)
.L1084:
	xorl	%ebp, %ebp
	leaq	32(%rsp), %r13
	.p2align 4,,10
	.p2align 3
.L1085:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
.LEHB127:
	call	*(%rax)
	testb	%al, %al
	je	.L1107
	testq	%r12, %r12
	je	.L1086
	cmpb	$0, 3(%r12)
	movq	56(%r12), %r14
	je	.L1087
	cmpb	$0, 4(%r12)
	jne	.L1087
	cmpw	$7, (%r12)
	jne	.L1086
	movq	%r12, %rdi
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movzbl	9(%rax), %ebp
	cmpb	$1, %bpl
	jne	.L1086
	movq	%r12, %rdi
	movzbl	40(%r12), %r15d
	call	_ZN8opendnp39SOERecord8GetValueINS_16SecurityStatSpecEEERKNS_17ValueAndVariationIT_EEv@PLT
	movq	32(%r12), %rcx
	movq	(%rax), %rsi
	movl	%r15d, %edx
	movq	%r13, %rdi
	call	_ZN8opendnp312SecurityStatC1ENS0_5ValueEhN7openpal10UInt48TypeE@PLT
.LEHE127:
	movzwl	24(%r12), %edx
	movzbl	94(%rsp), %eax
	movw	%dx, 56(%rsp)
	testb	%al, %al
	je	.L1091
	movq	112(%rsp), %rdi
	movl	88(%rsp), %ecx
	cmpl	%ecx, (%rdi)
	jnb	.L1146
.L1090:
	testb	%al, %al
	je	.L1091
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L1091:
	xorl	%eax, %eax
	movb	%bpl, %al
.L1080:
	movq	120(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L1147
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rdx
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
.L1145:
	.cfi_restore_state
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%esi, %esi
	movdqa	(%rsp), %xmm3
	movq	16(%rsp), %rdx
	movw	%si, 92(%rsp)
	movdqu	(%rdi), %xmm4
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm3, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm4, 96(%rsp)
	jbe	.L1084
	movl	$2, %esi
.LEHB128:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1084
	.p2align 4,,10
	.p2align 3
.L1143:
	movq	0(%rbp), %rdi
	movl	(%rsp), %eax
	xorl	%r8d, %r8d
	movdqa	(%rsp), %xmm1
	movq	16(%rsp), %rdx
	movw	%r8w, 92(%rsp)
	movdqu	(%rdi), %xmm2
	addl	$2, %eax
	cmpl	$1, (%rdi)
	movq	%rdi, 112(%rsp)
	movq	%rdx, 80(%rsp)
	movl	%eax, 88(%rsp)
	movaps	%xmm1, 64(%rsp)
	seta	94(%rsp)
	movaps	%xmm2, 96(%rsp)
	jbe	.L1072
	movl	$2, %esi
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	jmp	.L1072
	.p2align 4,,10
	.p2align 3
.L1094:
	pxor	%xmm0, %xmm0
	xorl	%eax, %eax
	leaq	96(%rsp), %rdi
	movb	$0, 94(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 88(%rsp)
	movw	%ax, 92(%rsp)
	movups	%xmm0, 72(%rsp)
	call	_ZN7openpal6WSliceC1Ev@PLT
.LEHE128:
	movq	$0, 112(%rsp)
	jmp	.L1095
	.p2align 4,,10
	.p2align 3
.L1144:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB129:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE129:
.L1075:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L1073
	.p2align 4,,10
	.p2align 3
.L1142:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB130:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r14, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE130:
.L1098:
	movq	%r12, %rbp
	movq	%r15, %r12
	jmp	.L1096
	.p2align 4,,10
	.p2align 3
.L1146:
	movq	8(%rdi), %rax
	movl	$2, %esi
	movw	%dx, (%rax)
.LEHB131:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
	movq	112(%rsp), %rsi
	movq	%r13, %rdi
	call	*80(%rsp)
	movq	(%rbx), %rax
	addw	$1, 92(%rsp)
	movq	%rbx, %rdi
	movb	$1, 4(%r12)
	movzbl	2(%r12), %esi
	movzwl	(%r12), %edx
	call	*8(%rax)
.LEHE131:
.L1087:
	movq	%r12, %rbp
	movq	%r14, %r12
	jmp	.L1085
	.p2align 4,,10
	.p2align 3
.L1107:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L1086:
	movzbl	94(%rsp), %eax
	xorl	%ebp, %ebp
	jmp	.L1090
	.p2align 4,,10
	.p2align 3
.L1106:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L1074:
	movzbl	94(%rsp), %eax
	jmp	.L1078
	.p2align 4,,10
	.p2align 3
.L1108:
	movq	%rbp, %r12
	.p2align 4,,10
	.p2align 3
.L1097:
	movzbl	94(%rsp), %eax
	xorl	%edx, %edx
	jmp	.L1101
	.p2align 4,,10
	.p2align 3
.L1141:
	movl	$2, %esi
.LEHB132:
	call	_ZN7openpal6WSlice7AdvanceEj@PLT
.LEHE132:
	jmp	.L1095
.L1147:
	call	__stack_chk_fail@PLT
.L1109:
	movq	%rax, %rdi
	jmp	.L1081
.L1110:
	movq	%rax, %rdi
	jmp	.L1092
.L1111:
	movq	%rax, %rdi
	jmp	.L1103
	.section	.gcc_except_table
.LLSDA471:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE471-.LLSDACSB471
.LLSDACSB471:
	.uleb128 .LEHB122-.LFB471
	.uleb128 .LEHE122-.LEHB122
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB123-.LFB471
	.uleb128 .LEHE123-.LEHB123
	.uleb128 .L1111-.LFB471
	.uleb128 0
	.uleb128 .LEHB124-.LFB471
	.uleb128 .LEHE124-.LEHB124
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB125-.LFB471
	.uleb128 .LEHE125-.LEHB125
	.uleb128 .L1109-.LFB471
	.uleb128 0
	.uleb128 .LEHB126-.LFB471
	.uleb128 .LEHE126-.LEHB126
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB127-.LFB471
	.uleb128 .LEHE127-.LEHB127
	.uleb128 .L1110-.LFB471
	.uleb128 0
	.uleb128 .LEHB128-.LFB471
	.uleb128 .LEHE128-.LEHB128
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB129-.LFB471
	.uleb128 .LEHE129-.LEHB129
	.uleb128 .L1109-.LFB471
	.uleb128 0
	.uleb128 .LEHB130-.LFB471
	.uleb128 .LEHE130-.LEHB130
	.uleb128 .L1111-.LFB471
	.uleb128 0
	.uleb128 .LEHB131-.LFB471
	.uleb128 .LEHE131-.LEHB131
	.uleb128 .L1110-.LFB471
	.uleb128 0
	.uleb128 .LEHB132-.LFB471
	.uleb128 .LEHE132-.LEHB132
	.uleb128 0
	.uleb128 0
.LLSDACSE471:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC471
	.type	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, @function
_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold:
.LFSB471:
.L1081:
	.cfi_def_cfa_offset 192
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	cmpb	$0, 94(%rsp)
	je	.L1082
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L1082:
.LEHB133:
	call	_Unwind_Resume@PLT
.L1092:
	cmpb	$0, 94(%rsp)
	je	.L1093
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L1093:
	call	_Unwind_Resume@PLT
.L1103:
	cmpb	$0, 94(%rsp)
	je	.L1104
	movq	104(%rsp), %rax
	movzwl	92(%rsp), %edx
	movw	%dx, (%rax)
.L1104:
	call	_Unwind_Resume@PLT
.LEHE133:
	.cfi_endproc
.LFE471:
	.section	.gcc_except_table
.LLSDAC471:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC471-.LLSDACSBC471
.LLSDACSBC471:
	.uleb128 .LEHB133-.LCOLDB7
	.uleb128 .LEHE133-.LEHB133
	.uleb128 0
	.uleb128 0
.LLSDACSEC471:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.section	.text.unlikely
	.size	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold, .-_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE.cold
.LCOLDE7:
	.text
.LHOTE7:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE:
.LFB463:
	.cfi_startproc
	cmpw	$7, (%rdx)
	ja	.L1149
	movzwl	(%rdx), %eax
	leaq	.L1151(%rip), %rcx
	movslq	(%rcx,%rax,4), %rax
	addq	%rcx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L1151:
	.long	.L1158-.L1151
	.long	.L1157-.L1151
	.long	.L1156-.L1151
	.long	.L1155-.L1151
	.long	.L1154-.L1151
	.long	.L1153-.L1151
	.long	.L1152-.L1151
	.long	.L1150-.L1151
	.text
	.p2align 4,,10
	.p2align 3
.L1152:
	jmp	_ZN8opendnp311EventWriter28LoadHeaderAnalogOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1150:
	jmp	_ZN8opendnp311EventWriter22LoadHeaderSecurityStatERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1158:
	jmp	_ZN8opendnp311EventWriter16LoadHeaderBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1157:
	jmp	_ZN8opendnp311EventWriter16LoadHeaderAnalogERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1156:
	jmp	_ZN8opendnp311EventWriter17LoadHeaderCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1155:
	jmp	_ZN8opendnp311EventWriter23LoadHeaderFrozenCounterERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1154:
	jmp	_ZN8opendnp311EventWriter22LoadHeaderDoubleBinaryERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	.p2align 4,,10
	.p2align 3
.L1153:
	jmp	_ZN8opendnp311EventWriter28LoadHeaderBinaryOutputStatusERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
.L1149:
	xorl	%edx, %edx
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE463:
	.size	_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE
	.type	_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE, @function
_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE:
.LFB462:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	testq	%rdx, %rdx
	jne	.L1160
	jmp	.L1161
	.p2align 4,,10
	.p2align 3
.L1176:
	movzbl	4(%r12), %r13d
	testb	%r13b, %r13b
	jne	.L1166
	movq	%r12, %rdx
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	call	_ZN8opendnp311EventWriter10LoadHeaderERNS_12HeaderWriterERNS_14IEventRecorderEPN7openpal8ListNodeINS_9SOERecordEEE@PLT
	movq	%rdx, %r12
	testb	%al, %al
	jne	.L1159
	testq	%r12, %r12
	je	.L1161
.L1160:
	movq	(%rbx), %rax
	movq	%rbx, %rdi
	call	*(%rax)
	testb	%al, %al
	je	.L1161
	cmpb	$0, 3(%r12)
	movq	56(%r12), %rax
	jne	.L1176
.L1166:
	movq	%rax, %r12
	testq	%r12, %r12
	jne	.L1160
.L1161:
	movl	$1, %r13d
.L1159:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	%r13d, %eax
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
.LFE462:
	.size	_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE, .-_ZN8opendnp311EventWriter5WriteERNS_12HeaderWriterERNS_14IEventRecorderEN7openpal18LinkedListIteratorINS_9SOERecordEEE
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_EventWriter.cpp, @function
_GLOBAL__sub_I_EventWriter.cpp:
.LFB713:
	.cfi_startproc
	movq	_ZGVN7openpal7Bit16LEItE3MaxE@GOTPCREL(%rip), %rax
	cmpb	$0, (%rax)
	je	.L1183
	ret
.L1183:
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
.LFE713:
	.size	_GLOBAL__sub_I_EventWriter.cpp, .-_GLOBAL__sub_I_EventWriter.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_EventWriter.cpp
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
