	.file	"AssignClassHandler.cpp"
	.text
	.section	.text._ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE,"axG",@progbits,_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE
	.type	_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE, @function
_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE:
.LFB334:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE334:
	.size	_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE, .-_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE
	.section	.text._ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt,"axG",@progbits,_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt
	.type	_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt, @function
_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt:
.LFB1882:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE1882:
	.size	_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt, .-_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt
	.section	.text._ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE,"axG",@progbits,_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE
	.type	_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE, @function
_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE:
.LFB2469:
	.cfi_startproc
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE2469:
	.size	_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE, .-_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE
	.text
	.p2align 4
	.type	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E10_M_managerERSt9_Any_dataRKSA_St18_Manager_operation, @function
_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E10_M_managerERSt9_Any_dataRKSA_St18_Manager_operation:
.LFB2944:
	.cfi_startproc
	testl	%edx, %edx
	je	.L6
	cmpl	$1, %edx
	je	.L7
	cmpl	$2, %edx
	je	.L11
.L9:
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	_ZTIZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_(%rip), %rax
	movq	%rax, (%rdi)
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%rsi, (%rdi)
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	movdqu	(%rsi), %xmm0
	movups	%xmm0, (%rdi)
	jmp	.L9
	.cfi_endproc
.LFE2944:
	.size	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E10_M_managerERSt9_Any_dataRKSA_St18_Manager_operation, .-_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E10_M_managerERSt9_Any_dataRKSA_St18_Manager_operation
	.p2align 4
	.type	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E9_M_invokeERKSt9_Any_data, @function
_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E9_M_invokeERKSt9_Any_data:
.LFB2943:
	.cfi_startproc
	movq	(%rdi), %r9
	movq	(%r9), %rax
	movq	72(%rax), %rax
	cmpq	_ZN8opendnp322IOutstationApplication21RecordClassAssignmentENS_15AssignClassTypeENS_10PointClassEtt@GOTPCREL(%rip), %rax
	jne	.L14
	ret
	.p2align 4,,10
	.p2align 3
.L14:
	movzwl	8(%rdi), %ecx
	movzbl	12(%rdi), %edx
	movzbl	13(%rdi), %esi
	movzwl	10(%rdi), %r8d
	movq	%r9, %rdi
	jmp	*%rax
	.cfi_endproc
.LFE2943:
	.size	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E9_M_invokeERKSt9_Any_data, .-_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E9_M_invokeERKSt9_Any_data
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE
	.type	_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE, @function
_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE:
.LFB2471:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %xmm0
	movq	%rdx, %xmm1
	movq	%rcx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	punpcklqdq	%xmm1, %xmm0
	movq	%rdi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movaps	%xmm0, (%rsp)
	call	_ZN8opendnp312IAPDUHandlerC2Ev@PLT
	movq	_ZTVN8opendnp318AssignClassHandlerE@GOTPCREL(%rip), %rax
	movq	%rbp, 48(%rbx)
	movdqa	(%rsp), %xmm0
	movl	$-1, 20(%rbx)
	addq	$16, %rax
	movb	$1, 24(%rbx)
	movq	%rax, (%rbx)
	movups	%xmm0, 32(%rbx)
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2471:
	.size	_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE, .-_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE
	.globl	_ZN8opendnp318AssignClassHandlerC1ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE
	.set	_ZN8opendnp318AssignClassHandlerC1ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE,_ZN8opendnp318AssignClassHandlerC2ERN7openpal9IExecutorERNS_22IOutstationApplicationERNS_14IClassAssignerE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv
	.type	_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv, @function
_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv:
.LFB2475:
	.cfi_startproc
	movl	12(%rdi), %eax
	xorl	%r8d, %r8d
	testl	%eax, %eax
	jle	.L17
	subl	$1, %eax
	cmpl	20(%rdi), %eax
	je	.L21
.L17:
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	movl	$1, %r8d
	movl	$-1, 20(%rdi)
	movl	%r8d, %eax
	ret
	.cfi_endproc
.LFE2475:
	.size	_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv, .-_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.type	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, @function
_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE:
.LFB2478:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2478
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movzwl	(%rcx), %eax
	movzwl	2(%rcx), %ecx
	cmpw	%cx, %ax
	ja	.L22
	movq	40(%rdi), %r8
	testq	%r8, %r8
	je	.L22
	movq	32(%rdi), %rdi
	sall	$16, %ecx
	movq	%rsp, %rbp
	orl	%ecx, %eax
	movq	(%rdi), %r9
	movl	%eax, 8(%rsp)
	xorl	%eax, %eax
	movb	%dl, %al
	movl	%esi, %edx
	leaq	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E10_M_managerERSt9_Any_dataRKSA_St18_Manager_operation(%rip), %rsi
	movq	%r8, (%rsp)
	movb	%dl, %ah
	movq	%rsi, %xmm0
	movq	%rbp, %rsi
	movw	%ax, 12(%rsp)
	leaq	_ZNSt17_Function_handlerIFvvEZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS1_15AssignClassTypeENS1_10PointClassERKNS1_5RangeEEUlvE_E9_M_invokeERKSt9_Any_data(%rip), %rax
	movq	%rax, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movaps	%xmm0, 16(%rsp)
.LEHB0:
	call	*40(%r9)
.LEHE0:
	movq	16(%rsp), %rax
	testq	%rax, %rax
	je	.L22
	movl	$3, %edx
	movq	%rbp, %rsi
	movq	%rbp, %rdi
	call	*%rax
.L22:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L39
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L39:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
.L28:
	movq	%rax, %r12
	jmp	.L25
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2478:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2478-.LLSDACSB2478
.LLSDACSB2478:
	.uleb128 .LEHB0-.LFB2478
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L28-.LFB2478
	.uleb128 0
.LLSDACSE2478:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC2478
	.type	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE.cold, @function
_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE.cold:
.LFSB2478:
.L25:
	.cfi_def_cfa_offset 80
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	16(%rsp), %rax
	testq	%rax, %rax
	je	.L26
	movl	$3, %edx
	movq	%rbp, %rsi
	movq	%rbp, %rdi
	call	*%rax
.L26:
	movq	%r12, %rdi
.LEHB1:
	call	_Unwind_Resume@PLT
.LEHE1:
	.cfi_endproc
.LFE2478:
	.section	.gcc_except_table
.LLSDAC2478:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC2478-.LLSDACSBC2478
.LLSDACSBC2478:
	.uleb128 .LEHB1-.LCOLDB0
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSEC2478:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, .-_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.section	.text.unlikely
	.size	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE.cold, .-_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE.cold
.LCOLDE0:
	.text
.LHOTE0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.type	_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, @function
_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE:
.LFB2476:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	%edx, %r13d
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rcx, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movq	48(%rdi), %rdi
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	(%rdi), %rax
	call	*8(%rax)
	leaq	4(%rsp), %rcx
	movl	%r13d, %edx
	movl	%r12d, %esi
	movq	%rbp, %rdi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	4(%rsp), %eax
	cmpw	%ax, (%rbx)
	je	.L45
.L41:
	xorl	%eax, %eax
	leaq	2(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 2(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
.L42:
	movzwl	2(%rsp), %eax
	movq	8(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L46
	addq	$24, %rsp
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
	.p2align 4,,10
	.p2align 3
.L45:
	.cfi_restore_state
	movzwl	6(%rsp), %eax
	cmpw	%ax, 2(%rbx)
	jne	.L41
	xorl	%edx, %edx
	movw	%dx, 2(%rsp)
	jmp	.L42
.L46:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2476:
	.size	_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE, .-_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE
	.type	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE, @function
_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE:
.LFB2474:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv@PLT
	testb	%al, %al
	je	.L48
	movzwl	(%rbx), %eax
	cmpw	$5120, %ax
	je	.L49
	ja	.L50
	cmpw	$768, %ax
	je	.L51
	cmpw	$2560, %ax
	jne	.L70
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$5, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L50:
	cmpw	$7680, %ax
	je	.L55
	cmpw	$10240, %ax
	jne	.L71
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$6, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L71:
	cmpw	$5376, %ax
	jne	.L54
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$3, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L70:
	cmpw	$256, %ax
	jne	.L54
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	xorl	%esi, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L48:
	xorl	%eax, %eax
	leaq	6(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
.L65:
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L69
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L51:
	.cfi_restore_state
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$1, %esi
.L68:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp318AssignClassHandler18ProcessAssignRangeENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	.p2align 4,,10
	.p2align 3
.L55:
	.cfi_restore_state
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$4, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L49:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L69
	movzbl	24(%rbp), %edx
	leaq	16(%rbx), %rcx
	movl	$2, %esi
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L54:
	xorl	%edx, %edx
	leaq	6(%rsp), %rdi
	movl	$8, %esi
	movw	%dx, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	jmp	.L65
.L69:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2474:
	.size	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE, .-_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE
	.type	_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE, @function
_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE:
.LFB2477:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edx, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movl	%esi, %ebx
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	48(%rdi), %rdi
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	(%rdi), %rax
	call	*(%rax)
	leaq	4(%rsp), %rcx
	movl	%r12d, %edx
	movl	%ebx, %esi
	movq	%rbp, %rdi
	movl	%eax, 4(%rsp)
	call	_ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeE@PLT
	movzwl	6(%rsp), %eax
	cmpw	%ax, 4(%rsp)
	ja	.L73
	xorl	%eax, %eax
.L74:
	movq	8(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L77
	addq	$16, %rsp
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
.L73:
	.cfi_restore_state
	xorl	%eax, %eax
	leaq	2(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 2(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	2(%rsp), %eax
	jmp	.L74
.L77:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2477:
	.size	_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE, .-_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE
	.type	_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE, @function
_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE:
.LFB2483:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	movl	12(%rdi), %eax
	movl	%eax, 20(%rdi)
	cmpw	$15363, %si
	je	.L79
	ja	.L80
	cmpw	$15361, %si
	je	.L81
	cmpw	$15362, %si
	jne	.L83
	movb	$2, 24(%rdi)
	xorl	%eax, %eax
.L85:
	movq	8(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L88
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L80:
	.cfi_restore_state
	cmpw	$15364, %si
	jne	.L83
	movb	$8, 24(%rdi)
	xorl	%eax, %eax
	jmp	.L85
	.p2align 4,,10
	.p2align 3
.L79:
	movb	$4, 24(%rdi)
	xorl	%eax, %eax
	jmp	.L85
	.p2align 4,,10
	.p2align 3
.L83:
	movl	$-1, 20(%rdi)
	xorl	%eax, %eax
	leaq	6(%rsp), %rdi
	movl	$10, %esi
	movw	%ax, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	jmp	.L85
	.p2align 4,,10
	.p2align 3
.L81:
	movb	$1, 24(%rdi)
	xorl	%eax, %eax
	jmp	.L85
.L88:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2483:
	.size	_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE, .-_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE
	.type	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE, @function
_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE:
.LFB2473:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZN8opendnp318AssignClassHandler21IsExpectingAssignmentEv@PLT
	testb	%al, %al
	je	.L90
	movzwl	(%rbx), %eax
	cmpw	$5120, %ax
	je	.L91
	ja	.L92
	cmpw	$768, %ax
	je	.L93
	cmpw	$2560, %ax
	jne	.L113
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$5, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L92:
	cmpw	$7680, %ax
	je	.L97
	cmpw	$10240, %ax
	jne	.L114
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$6, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L114:
	cmpw	$5376, %ax
	jne	.L96
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$3, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L113:
	cmpw	$256, %ax
	jne	.L96
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	xorl	%esi, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L90:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzwl	(%rbx), %esi
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp318AssignClassHandler11RecordClassENS_14GroupVariationE@PLT
	.p2align 4,,10
	.p2align 3
.L93:
	.cfi_restore_state
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$1, %esi
.L112:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN8opendnp318AssignClassHandler16ProcessAssignAllENS_15AssignClassTypeENS_10PointClassE@PLT
	.p2align 4,,10
	.p2align 3
.L97:
	.cfi_restore_state
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$4, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L91:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L110
	movzbl	24(%rbp), %edx
	movl	$2, %esi
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L96:
	xorl	%eax, %eax
	leaq	6(%rsp), %rdi
	movl	$8, %esi
	movw	%ax, 6(%rsp)
	call	_ZN8opendnp38IINField6SetBitENS_6IINBitE@PLT
	movzwl	6(%rsp), %eax
	movq	8(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L110
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L110:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2473:
	.size	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE, .-_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE
	.weak	_ZTSN8opendnp318AssignClassHandlerE
	.section	.rodata._ZTSN8opendnp318AssignClassHandlerE,"aG",@progbits,_ZTSN8opendnp318AssignClassHandlerE,comdat
	.align 32
	.type	_ZTSN8opendnp318AssignClassHandlerE, @object
	.size	_ZTSN8opendnp318AssignClassHandlerE, 32
_ZTSN8opendnp318AssignClassHandlerE:
	.string	"N8opendnp318AssignClassHandlerE"
	.weak	_ZTIN8opendnp318AssignClassHandlerE
	.section	.data.rel.ro._ZTIN8opendnp318AssignClassHandlerE,"awG",@progbits,_ZTIN8opendnp318AssignClassHandlerE,comdat
	.align 8
	.type	_ZTIN8opendnp318AssignClassHandlerE, @object
	.size	_ZTIN8opendnp318AssignClassHandlerE, 24
_ZTIN8opendnp318AssignClassHandlerE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8opendnp318AssignClassHandlerE
	.quad	_ZTIN8opendnp312IAPDUHandlerE
	.section	.data.rel.ro,"aw"
	.align 8
	.type	_ZTIZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_, @object
	.size	_ZTIZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_, 16
_ZTIZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_
	.section	.rodata
	.align 32
	.type	_ZTSZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_, @object
	.size	_ZTSZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_, 120
_ZTSZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_:
	.string	"*ZN8opendnp318AssignClassHandler29NotifyApplicationOfAssignmentENS_15AssignClassTypeENS_10PointClassERKNS_5RangeEEUlvE_"
	.weak	_ZTVN8opendnp318AssignClassHandlerE
	.section	.data.rel.ro._ZTVN8opendnp318AssignClassHandlerE,"awG",@progbits,_ZTVN8opendnp318AssignClassHandlerE,comdat
	.align 8
	.type	_ZTVN8opendnp318AssignClassHandlerE, @object
	.size	_ZTVN8opendnp318AssignClassHandlerE, 448
_ZTVN8opendnp318AssignClassHandlerE:
	.quad	0
	.quad	_ZTIN8opendnp318AssignClassHandlerE
	.quad	_ZN8opendnp318AssignClassHandler9IsAllowedEjNS_14GroupVariationENS_13QualifierCodeE
	.quad	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_16AllObjectsHeaderE
	.quad	_ZN8opendnp318AssignClassHandler13ProcessHeaderERKNS_11RangeHeaderE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var1ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var2ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var5ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var6ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var8ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var7ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_12Group120Var9ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var10ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var11ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var12ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var13ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var14ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_16FreeFormatHeaderERKNS_13Group120Var15ERKN7openpal6RSliceE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_11Group50Var1EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_11Group51Var1EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_11Group51Var2EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_11Group52Var1EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_11Group52Var2EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_12Group120Var3EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11CountHeaderERKNS_11ICollectionINS_12Group120Var4EEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_8IINValueEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_6BinaryEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_15DoubleBitBinaryEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_18BinaryOutputStatusEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_7CounterEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_13FrozenCounterEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_6AnalogEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_18AnalogOutputStatusEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_11OctetStringEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_15TimeAndIntervalEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_11RangeHeaderERKNS_11ICollectionINS_7IndexedINS_12Group121Var1EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_6BinaryEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_18BinaryOutputStatusEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_15DoubleBitBinaryEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_7CounterEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_13FrozenCounterEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_6AnalogEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_18AnalogOutputStatusEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_11OctetStringEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_15TimeAndIntervalEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_18BinaryCommandEventEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_18AnalogCommandEventEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_12Group122Var1EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_12Group122Var2EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_23ControlRelayOutputBlockEEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_17AnalogOutputInt16EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_17AnalogOutputInt32EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_19AnalogOutputFloat32EEEEE
	.quad	_ZN8opendnp312IAPDUHandler13ProcessHeaderERKNS_12PrefixHeaderERKNS_11ICollectionINS_7IndexedINS_20AnalogOutputDouble64EEEEE
	.quad	_ZN8opendnp312IAPDUHandler14OnHeaderResultERKNS_12HeaderRecordERKNS_8IINFieldE
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
