	.file	"Conversions.cpp"
	.text
	.p2align 4
	.type	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_, @function
_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_:
.LFB1573:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	(%rdi), %rax
	movq	(%rax), %rbx
	movq	8(%rax), %r12
	cmpq	%rbx, %r12
	je	.L2
	movq	%rsi, %rbp
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L11:
	addq	$8, %rbx
	cmpq	%rbx, %r12
	je	.L2
.L4:
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_ZNK8opendnp36Header7WriteToERNS_12HeaderWriterE@PLT
	testb	%al, %al
	jne	.L11
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 24
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1573:
	.size	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_, .-_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4
	.type	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation, @function
_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation:
.LFB1575:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1575
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	testl	%edx, %edx
	je	.L13
	cmpl	$1, %edx
	je	.L14
	cmpl	$2, %edx
	je	.L17
	cmpl	$3, %edx
	jne	.L16
	movq	(%rdi), %rbp
	testq	%rbp, %rbp
	je	.L16
	movq	0(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L24
	movq	16(%rbp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L24:
	movl	$24, %esi
	movq	%rbp, %rdi
	call	_ZdlPvm@PLT
.L16:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
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
.L13:
	.cfi_restore_state
	leaq	_ZTIZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_(%rip), %rax
	movq	%rax, (%rdi)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
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
.L14:
	.cfi_restore_state
	movq	(%rsi), %rax
	movq	%rax, (%rdi)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
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
.L17:
	.cfi_restore_state
	movq	(%rsi), %r12
	movl	$24, %edi
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	pxor	%xmm0, %xmm0
	movq	8(%r12), %r13
	subq	(%r12), %r13
	movq	%rax, %rbp
	movups	%xmm0, (%rax)
	movq	$0, 16(%rax)
	je	.L25
	movabsq	$9223372036854775800, %rax
	cmpq	%rax, %r13
	ja	.L36
	movq	%r13, %rdi
.LEHB1:
	call	_Znwm@PLT
	movq	%rax, %rcx
.L19:
	movq	%rcx, %xmm0
	addq	%rcx, %r13
	punpcklqdq	%xmm0, %xmm0
	movq	%r13, 16(%rbp)
	movups	%xmm0, 0(%rbp)
	movq	8(%r12), %rsi
	movq	(%r12), %rdi
	cmpq	%rdi, %rsi
	je	.L21
	subq	%rdi, %rsi
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L22:
	movq	(%rdi,%rax), %rdx
	movq	%rdx, (%rcx,%rax)
	addq	$8, %rax
	cmpq	%rax, %rsi
	jne	.L22
	addq	%rsi, %rcx
.L21:
	movq	%rcx, 8(%rbp)
	movq	%rbp, (%rbx)
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L25:
	xorl	%r13d, %r13d
	xorl	%ecx, %ecx
	jmp	.L19
.L36:
	call	_ZSt17__throw_bad_allocv@PLT
.LEHE1:
.L26:
	movq	%rax, %r12
	jmp	.L23
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1575:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1575-.LLSDACSB1575
.LLSDACSB1575:
	.uleb128 .LEHB0-.LFB1575
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1575
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L26-.LFB1575
	.uleb128 0
.LLSDACSE1575:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC1575
	.type	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation.cold, @function
_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation.cold:
.LFSB1575:
.L23:
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -40
	.cfi_offset 6, -32
	.cfi_offset 12, -24
	.cfi_offset 13, -16
	movq	%rbp, %rdi
	movl	$24, %esi
	call	_ZdlPvm@PLT
	movq	%r12, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE1575:
	.section	.gcc_except_table
.LLSDAC1575:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC1575-.LLSDACSBC1575
.LLSDACSBC1575:
	.uleb128 .LEHB2-.LCOLDB0
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSEC1575:
	.section	.text.unlikely
	.text
	.size	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation, .-_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation
	.section	.text.unlikely
	.size	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation.cold, .-_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4
	.globl	_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE
	.type	_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE, @function
_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE:
.LFB1515:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1515
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
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movq	8(%rsi), %rcx
	movq	(%rsi), %rsi
	movq	%rcx, %r13
	subq	%rsi, %r13
	je	.L52
	movabsq	$9223372036854775800, %rax
	cmpq	%rax, %r13
	ja	.L62
	movq	%r13, %rdi
.LEHB3:
	call	_Znwm@PLT
.LEHE3:
	movq	8(%rbx), %rcx
	movq	(%rbx), %rsi
	movq	%rax, %rbp
	cmpq	%rcx, %rsi
	je	.L53
.L64:
	subq	%rsi, %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L41:
	movq	(%rsi,%rax), %rdx
	movq	%rdx, 0(%rbp,%rax)
	addq	$8, %rax
	cmpq	%rax, %rcx
	jne	.L41
	leaq	0(%rbp,%rcx), %rbx
.L40:
	movq	$0, 16(%r12)
	movl	$24, %edi
.LEHB4:
	call	_Znwm@PLT
.LEHE4:
	pxor	%xmm0, %xmm0
	movq	%rbx, %r15
	movq	$0, 16(%rax)
	movq	%rax, %r14
	movups	%xmm0, (%rax)
	subq	%rbp, %r15
	je	.L54
	movabsq	$9223372036854775800, %rax
	cmpq	%rax, %r15
	ja	.L63
	movq	%r15, %rdi
.LEHB5:
	call	_Znwm@PLT
	movq	%rax, %rdi
.L42:
	movq	%rdi, %xmm0
	addq	%rdi, %r15
	punpcklqdq	%xmm0, %xmm0
	movq	%r15, 16(%r14)
	movups	%xmm0, (%r14)
	cmpq	%rbx, %rbp
	je	.L44
	subq	%rbp, %rbx
	movq	%rbp, %rsi
	movq	%rbx, %rdx
	call	memcpy@PLT
	movq	%r14, (%r12)
	movq	%rax, %rdi
	leaq	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_(%rip), %rax
	addq	%rbx, %rdi
	leaq	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation(%rip), %rbx
	movq	%rax, %xmm1
	movq	%rbx, %xmm0
	movq	%rdi, 8(%r14)
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, 16(%r12)
.L45:
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZdlPvm@PLT
.L37:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rax
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
.L44:
	.cfi_restore_state
	leaq	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E9_M_invokeERKSt9_Any_dataS2_(%rip), %rax
	leaq	_ZNSt17_Function_handlerIFbRN8opendnp312HeaderWriterEEZN8asiodnp315ConvertToLambdaERKSt6vectorINS0_6HeaderESaIS6_EEEUlS2_E_E10_M_managerERSt9_Any_dataRKSD_St18_Manager_operation(%rip), %rbx
	movq	%rdi, 8(%r14)
	movq	%rbx, %xmm0
	movq	%rax, %xmm2
	movq	%r14, (%r12)
	punpcklqdq	%xmm2, %xmm0
	movups	%xmm0, 16(%r12)
	testq	%rbp, %rbp
	je	.L37
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L54:
	xorl	%edi, %edi
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L52:
	xorl	%ebp, %ebp
	cmpq	%rcx, %rsi
	jne	.L64
.L53:
	movq	%rbp, %rbx
	jmp	.L40
.L63:
	call	_ZSt17__throw_bad_allocv@PLT
.LEHE5:
.L62:
.LEHB6:
	call	_ZSt17__throw_bad_allocv@PLT
.LEHE6:
.L55:
	movq	%rax, %r14
	jmp	.L48
.L56:
	movq	%rax, %rbx
	jmp	.L47
	.section	.gcc_except_table
.LLSDA1515:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1515-.LLSDACSB1515
.LLSDACSB1515:
	.uleb128 .LEHB3-.LFB1515
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB1515
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L55-.LFB1515
	.uleb128 0
	.uleb128 .LEHB5-.LFB1515
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L56-.LFB1515
	.uleb128 0
	.uleb128 .LEHB6-.LFB1515
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE1515:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC1515
	.type	_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE.cold, @function
_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE.cold:
.LFSB1515:
.L47:
	.cfi_def_cfa_offset 64
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	%r14, %rdi
	movl	$24, %esi
	movq	%rbx, %r14
	call	_ZdlPvm@PLT
.L48:
	movq	16(%r12), %rax
	testq	%rax, %rax
	je	.L49
	movl	$3, %edx
	movq	%r12, %rsi
	movq	%r12, %rdi
	call	*%rax
.L49:
	testq	%rbp, %rbp
	je	.L51
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZdlPvm@PLT
.L51:
	movq	%r14, %rdi
.LEHB7:
	call	_Unwind_Resume@PLT
.LEHE7:
	.cfi_endproc
.LFE1515:
	.section	.gcc_except_table
.LLSDAC1515:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC1515-.LLSDACSBC1515
.LLSDACSBC1515:
	.uleb128 .LEHB7-.LCOLDB1
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
.LLSDACSEC1515:
	.section	.text.unlikely
	.text
	.size	_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE, .-_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE
	.section	.text.unlikely
	.size	_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE.cold, .-_ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EE.cold
.LCOLDE1:
	.text
.LHOTE1:
	.section	.data.rel.ro,"aw"
	.align 8
	.type	_ZTIZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_, @object
	.size	_ZTIZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_, 16
_ZTIZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_
	.section	.rodata
	.align 32
	.type	_ZTSZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_, @object
	.size	_ZTSZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_, 94
_ZTSZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_:
	.string	"*ZN8asiodnp315ConvertToLambdaERKSt6vectorIN8opendnp36HeaderESaIS2_EEEUlRNS1_12HeaderWriterEE_"
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
