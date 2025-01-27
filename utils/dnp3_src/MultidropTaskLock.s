	.file	"MultidropTaskLock.cpp"
	.text
	.align 2
	.p2align 4
	.type	_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0, @function
_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0:
.LFB1498:
	.cfi_startproc
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
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, 16(%rsp)
	testq	%rdi, %rdi
	je	.L1
.L19:
	movq	16(%rsp), %rax
	movq	24(%rax), %r14
	testq	%r14, %r14
	je	.L3
.L18:
	movq	24(%r14), %r15
	testq	%r15, %r15
	je	.L4
.L17:
	movq	24(%r15), %rax
	movq	%rax, 8(%rsp)
	testq	%rax, %rax
	je	.L5
.L16:
	movq	8(%rsp), %rax
	movq	24(%rax), %rbp
	testq	%rbp, %rbp
	je	.L6
.L15:
	movq	24(%rbp), %r13
	testq	%r13, %r13
	je	.L7
.L14:
	movq	24(%r13), %r12
	testq	%r12, %r12
	je	.L8
.L13:
	movq	24(%r12), %r9
	testq	%r9, %r9
	je	.L9
.L12:
	movq	24(%r9), %rbx
	testq	%rbx, %rbx
	je	.L10
.L11:
	movq	24(%rbx), %rdi
	movq	%r9, 24(%rsp)
	call	_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	%rbx, %rdi
	movq	16(%rbx), %rbx
	movl	$40, %esi
	call	_ZdlPvm@PLT
	movq	24(%rsp), %r9
	testq	%rbx, %rbx
	jne	.L11
.L10:
	movq	16(%r9), %rbx
	movl	$40, %esi
	movq	%r9, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L9
	movq	%rbx, %r9
	jmp	.L12
.L7:
	movq	16(%rbp), %r12
	movl	$40, %esi
	movq	%rbp, %rdi
	call	_ZdlPvm@PLT
	testq	%r12, %r12
	je	.L6
	movq	%r12, %rbp
	jmp	.L15
	.p2align 4,,10
	.p2align 3
.L8:
	movq	16(%r13), %r12
	movl	$40, %esi
	movq	%r13, %rdi
	call	_ZdlPvm@PLT
	testq	%r12, %r12
	je	.L7
	movq	%r12, %r13
	jmp	.L14
.L6:
	movq	8(%rsp), %rdi
	movl	$40, %esi
	movq	16(%rdi), %rbp
	call	_ZdlPvm@PLT
	testq	%rbp, %rbp
	je	.L5
	movq	%rbp, 8(%rsp)
	jmp	.L16
	.p2align 4,,10
	.p2align 3
.L9:
	movq	16(%r12), %rax
	movl	$40, %esi
	movq	%r12, %rdi
	movq	%rax, 24(%rsp)
	call	_ZdlPvm@PLT
	movq	24(%rsp), %rax
	testq	%rax, %rax
	je	.L8
	movq	%rax, %r12
	jmp	.L13
.L5:
	movq	16(%r15), %rbx
	movl	$40, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L4
	movq	%rbx, %r15
	jmp	.L17
.L4:
	movq	16(%r14), %rbx
	movl	$40, %esi
	movq	%r14, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L3
	movq	%rbx, %r14
	jmp	.L18
.L3:
	movq	16(%rsp), %rdi
	movl	$40, %esi
	movq	16(%rdi), %rbx
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L1
	movq	%rbx, 16(%rsp)
	jmp	.L19
.L1:
	addq	$40, %rsp
	.cfi_def_cfa_offset 56
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
	.cfi_endproc
.LFE1498:
	.size	_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0, .-_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	.align 2
	.p2align 4
	.globl	_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE
	.type	_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE, @function
_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE:
.LFB1197:
	.cfi_startproc
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
	xorl	%r12d, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	cmpq	%rsi, 144(%rdi)
	je	.L110
.L58:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%r12d, %eax
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
.L110:
	.cfi_restore_state
	movzbl	8(%rdi), %r12d
	movq	%rdi, %r14
	movq	$0, 144(%rdi)
	testb	%r12b, %r12b
	je	.L83
	movq	80(%rdi), %rax
	cmpq	112(%rdi), %rax
	je	.L58
	movq	(%rax), %rdx
	movq	96(%rdi), %rcx
	movq	%rdx, 144(%rdi)
	leaq	-8(%rcx), %rdx
	cmpq	%rdx, %rax
	je	.L60
	addq	$8, %rax
	movq	%rax, 80(%rdi)
.L61:
	movq	32(%r14), %r8
	leaq	24(%r14), %rbp
	testq	%r8, %r8
	je	.L84
	movq	144(%r14), %rdx
	movq	%rbp, %rcx
	movq	%r8, %rax
	jmp	.L63
	.p2align 4,,10
	.p2align 3
.L112:
	movq	24(%rax), %rax
	testq	%rax, %rax
	je	.L111
.L63:
	cmpq	%rdx, 32(%rax)
	jb	.L112
	movq	16(%rax), %rbx
	jbe	.L113
	movq	%rax, %rcx
	movq	%rbx, %rax
	testq	%rax, %rax
	jne	.L63
.L111:
	cmpq	%rcx, %rbp
	sete	%al
.L62:
	cmpq	%rcx, 40(%r14)
	jne	.L80
	testb	%al, %al
	je	.L80
.L76:
	movq	%r8, %rdi
	call	_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	$0, 32(%r14)
	movq	%rbp, 40(%r14)
	movq	%rbp, 48(%r14)
	movq	$0, 56(%r14)
.L80:
	movq	144(%r14), %rdi
	movq	(%rdi), %rax
	call	*(%rax)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L83:
	movl	$1, %r12d
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L113:
	movq	24(%rax), %r15
	testq	%r15, %r15
	jne	.L67
	jmp	.L86
	.p2align 4,,10
	.p2align 3
.L114:
	testq	%rsi, %rsi
	je	.L66
	movq	%r15, %rcx
.L70:
	movq	%rsi, %r15
.L67:
	movq	16(%r15), %rsi
	movq	24(%r15), %rdi
	cmpq	%rdx, 32(%r15)
	ja	.L114
	testq	%rdi, %rdi
	je	.L86
	movq	%rdi, %rsi
	jmp	.L70
	.p2align 4,,10
	.p2align 3
.L86:
	movq	%rcx, %r15
.L66:
	testq	%rbx, %rbx
	jne	.L72
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L115:
	testq	%rcx, %rcx
	je	.L71
	movq	%rbx, %rax
.L75:
	movq	%rcx, %rbx
.L72:
	movq	16(%rbx), %rcx
	movq	24(%rbx), %rsi
	cmpq	%rdx, 32(%rbx)
	jnb	.L115
	testq	%rsi, %rsi
	je	.L88
	movq	%rsi, %rcx
	jmp	.L75
	.p2align 4,,10
	.p2align 3
.L88:
	movq	%rax, %rbx
.L71:
	cmpq	%rbx, 40(%r14)
	jne	.L109
	cmpq	%r15, %rbp
	jne	.L109
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L81:
	movq	%rbx, %rdi
	movq	%rbx, %r13
	call	_ZSt18_Rb_tree_incrementPKSt18_Rb_tree_node_base@PLT
	movq	%rbp, %rsi
	movq	%r13, %rdi
	movq	%rax, %rbx
	call	_ZSt28_Rb_tree_rebalance_for_erasePSt18_Rb_tree_node_baseRS_@PLT
	movl	$40, %esi
	movq	%rax, %rdi
	call	_ZdlPvm@PLT
	subq	$1, 56(%r14)
.L109:
	cmpq	%r15, %rbx
	jne	.L81
	movq	144(%r14), %rdi
	movq	(%rdi), %rax
	call	*(%rax)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L60:
	movq	88(%rdi), %rdi
	movl	$512, %esi
	call	_ZdlPvm@PLT
	movq	104(%r14), %rdx
	movq	8(%rdx), %rax
	addq	$8, %rdx
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	addq	$512, %rax
	punpcklqdq	%xmm0, %xmm0
	movups	%xmm0, 80(%r14)
	movq	%rax, %xmm0
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, 96(%r14)
	jmp	.L61
.L84:
	movl	%r12d, %eax
	movq	%rbp, %rcx
	jmp	.L62
	.cfi_endproc
.LFE1197:
	.size	_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE, .-_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp317MultidropTaskLockC2Ev
	.type	_ZN8opendnp317MultidropTaskLockC2Ev, @function
_ZN8opendnp317MultidropTaskLockC2Ev:
.LFB1194:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1194
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pxor	%xmm0, %xmm0
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	_ZTVN8opendnp317MultidropTaskLockE@GOTPCREL(%rip), %rax
	movb	$0, 8(%rdi)
	movl	$0, 24(%rdi)
	addq	$16, %rax
	movq	$0, 32(%rdi)
	movq	%rax, (%rdi)
	leaq	24(%rdi), %rax
	movq	%rax, 40(%rdi)
	movq	%rax, 48(%rdi)
	movq	$0, 56(%rdi)
	movq	$0, 64(%rdi)
	movq	$8, 72(%rdi)
	movups	%xmm0, 80(%rdi)
	movups	%xmm0, 96(%rdi)
	movups	%xmm0, 112(%rdi)
	movups	%xmm0, 128(%rdi)
	movl	$64, %edi
.LEHB0:
	call	_Znwm@PLT
.LEHE0:
	movq	72(%rbx), %rdx
	movq	%rax, 64(%rbx)
	movl	$512, %edi
	leaq	-4(,%rdx,4), %rbp
	andq	$-8, %rbp
	addq	%rax, %rbp
.LEHB1:
	call	_Znwm@PLT
.LEHE1:
	leaq	512(%rax), %rdx
	movq	%rax, 0(%rbp)
	movq	%rbp, 104(%rbx)
	movq	%rbp, 136(%rbx)
	movq	%rax, 88(%rbx)
	movq	%rdx, 96(%rbx)
	movq	%rax, 120(%rbx)
	movq	%rdx, 128(%rbx)
	movq	%rax, 80(%rbx)
	movq	%rax, 112(%rbx)
	movq	$0, 144(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L121:
	.cfi_restore_state
	movq	%rax, %rbp
	jmp	.L120
.L123:
	movq	%rax, %rdi
	jmp	.L117
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
	.align 4
.LLSDA1194:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT1194-.LLSDATTD1194
.LLSDATTD1194:
	.byte	0x1
	.uleb128 .LLSDACSE1194-.LLSDACSB1194
.LLSDACSB1194:
	.uleb128 .LEHB0-.LFB1194
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L121-.LFB1194
	.uleb128 0
	.uleb128 .LEHB1-.LFB1194
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L123-.LFB1194
	.uleb128 0x1
.LLSDACSE1194:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT1194:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC1194
	.type	_ZN8opendnp317MultidropTaskLockC2Ev.cold, @function
_ZN8opendnp317MultidropTaskLockC2Ev.cold:
.LFSB1194:
	nop
.L122:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -24
	.cfi_offset 6, -16
	movq	%rax, %rbp
	call	__cxa_end_catch@PLT
.L120:
	movq	32(%rbx), %rdi
	call	_ZNSt8_Rb_treeIPN8opendnp317IScheduleCallbackES2_St9_IdentityIS2_ESt4lessIS2_ESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E.isra.0
	movq	%rbp, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
.L117:
	call	__cxa_begin_catch@PLT
.LEHB3:
	call	__cxa_rethrow@PLT
.LEHE3:
.L124:
	movq	%rax, %rbp
	call	__cxa_end_catch@PLT
	movq	%rbp, %rdi
	call	__cxa_begin_catch@PLT
	movq	72(%rbx), %rax
	movq	64(%rbx), %rdi
	leaq	0(,%rax,8), %rsi
	call	_ZdlPvm@PLT
	movq	$0, 64(%rbx)
	movq	$0, 72(%rbx)
.LEHB4:
	call	__cxa_rethrow@PLT
.LEHE4:
	.cfi_endproc
.LFE1194:
	.section	.gcc_except_table
	.align 4
.LLSDAC1194:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATTC1194-.LLSDATTDC1194
.LLSDATTDC1194:
	.byte	0x1
	.uleb128 .LLSDACSEC1194-.LLSDACSBC1194
.LLSDACSBC1194:
	.uleb128 .LEHB2-.LCOLDB0
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LCOLDB0
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L124-.LCOLDB0
	.uleb128 0x1
	.uleb128 .LEHB4-.LCOLDB0
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L122-.LCOLDB0
	.uleb128 0
.LLSDACSEC1194:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATTC1194:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp317MultidropTaskLockC2Ev, .-_ZN8opendnp317MultidropTaskLockC2Ev
	.section	.text.unlikely
	.size	_ZN8opendnp317MultidropTaskLockC2Ev.cold, .-_ZN8opendnp317MultidropTaskLockC2Ev.cold
.LCOLDE0:
	.text
.LHOTE0:
	.globl	_ZN8opendnp317MultidropTaskLockC1Ev
	.set	_ZN8opendnp317MultidropTaskLockC1Ev,_ZN8opendnp317MultidropTaskLockC2Ev
	.section	.rodata._ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"cannot create std::deque larger than max_size()"
	.section	.text._ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_,"axG",@progbits,_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_
	.type	_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_, @function
_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_:
.LFB1391:
	.cfi_startproc
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
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movq	72(%rdi), %r13
	movq	40(%rdi), %rsi
	movq	48(%rbx), %rdx
	subq	56(%rbx), %rdx
	movq	%r13, %r12
	movq	%rdx, %rcx
	subq	%rsi, %r12
	sarq	$3, %rcx
	movq	%r12, %rdi
	sarq	$3, %rdi
	leaq	-1(%rdi), %rax
	salq	$6, %rax
	leaq	(%rcx,%rax), %rdx
	movq	32(%rbx), %rax
	subq	16(%rbx), %rax
	movabsq	$1152921504606846975, %rcx
	sarq	$3, %rax
	addq	%rdx, %rax
	cmpq	%rcx, %rax
	je	.L136
	movq	(%rbx), %r8
	movq	8(%rbx), %rdx
	movq	%r13, %rax
	subq	%r8, %rax
	movq	%rdx, %r9
	sarq	$3, %rax
	subq	%rax, %r9
	cmpq	$1, %r9
	jbe	.L137
.L129:
	movl	$512, %edi
	call	_Znwm@PLT
	movq	0(%rbp), %rdx
	movq	%rax, 8(%r13)
	movq	48(%rbx), %rax
	movq	%rdx, (%rax)
	movq	72(%rbx), %rdx
	movq	8(%rdx), %rax
	addq	$8, %rdx
	movq	%rdx, %xmm1
	movq	%rax, %xmm0
	addq	$512, %rax
	punpcklqdq	%xmm0, %xmm0
	movups	%xmm0, 48(%rbx)
	movq	%rax, %xmm0
	punpcklqdq	%xmm1, %xmm0
	movups	%xmm0, 64(%rbx)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
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
.L137:
	.cfi_restore_state
	leaq	2(%rdi), %r14
	leaq	(%r14,%r14), %rax
	cmpq	%rax, %rdx
	ja	.L138
	testq	%rdx, %rdx
	movl	$1, %eax
	cmovne	%rdx, %rax
	leaq	2(%rdx,%rax), %r13
	cmpq	%rcx, %r13
	ja	.L139
	leaq	0(,%r13,8), %rdi
	call	_Znwm@PLT
	movq	40(%rbx), %rsi
	movq	%rax, %r15
	movq	%r13, %rax
	subq	%r14, %rax
	shrq	%rax
	leaq	(%r15,%rax,8), %r14
	movq	72(%rbx), %rax
	leaq	8(%rax), %rdx
	cmpq	%rsi, %rdx
	je	.L134
	subq	%rsi, %rdx
	movq	%r14, %rdi
	call	memmove@PLT
.L134:
	movq	8(%rbx), %rax
	movq	(%rbx), %rdi
	leaq	0(,%rax,8), %rsi
	call	_ZdlPvm@PLT
	movq	%r15, (%rbx)
	movq	%r13, 8(%rbx)
.L132:
	movq	(%r14), %rax
	movq	(%r14), %xmm0
	leaq	(%r14,%r12), %r13
	movq	%r14, 40(%rbx)
	movq	%r13, 72(%rbx)
	addq	$512, %rax
	movq	%rax, %xmm2
	punpcklqdq	%xmm2, %xmm0
	movups	%xmm0, 24(%rbx)
	movq	0(%r13), %rax
	movq	%rax, 56(%rbx)
	addq	$512, %rax
	movq	%rax, 64(%rbx)
	jmp	.L129
	.p2align 4,,10
	.p2align 3
.L138:
	subq	%r14, %rdx
	addq	$8, %r13
	shrq	%rdx
	leaq	(%r8,%rdx,8), %r14
	movq	%r13, %rdx
	subq	%rsi, %rdx
	cmpq	%r14, %rsi
	jbe	.L131
	cmpq	%r13, %rsi
	je	.L132
	movq	%r14, %rdi
	call	memmove@PLT
	jmp	.L132
	.p2align 4,,10
	.p2align 3
.L131:
	cmpq	%r13, %rsi
	je	.L132
	leaq	8(%r12), %rdi
	subq	%rdx, %rdi
	addq	%r14, %rdi
	call	memmove@PLT
	jmp	.L132
.L136:
	leaq	.LC1(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
.L139:
	call	_ZSt17__throw_bad_allocv@PLT
	.cfi_endproc
.LFE1391:
	.size	_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_, .-_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE
	.type	_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE, @function
_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE:
.LFB1198:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	leaq	24(%rdi), %r13
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
	movq	%rsi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 64
	movq	32(%rdi), %r12
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testq	%r12, %r12
	je	.L141
	movq	%r13, %rsi
	movq	%r12, %rax
	.p2align 4,,10
	.p2align 3
.L145:
	movq	16(%rax), %rdx
	movq	24(%rax), %rcx
	cmpq	%rbx, 32(%rax)
	jnb	.L142
.L172:
	testq	%rcx, %rcx
	je	.L143
	movq	%rcx, %rax
	movq	16(%rax), %rdx
	movq	24(%rax), %rcx
	cmpq	%rbx, 32(%rax)
	jb	.L172
.L142:
	movq	%rax, %rsi
	testq	%rdx, %rdx
	je	.L143
	movq	%rdx, %rax
	jmp	.L145
	.p2align 4,,10
	.p2align 3
.L143:
	cmpq	%rsi, %r13
	je	.L168
	xorl	%eax, %eax
	cmpq	%rbx, 32(%rsi)
	jbe	.L140
	.p2align 4,,10
	.p2align 3
.L168:
	movq	32(%r12), %rax
	movq	16(%r12), %rdx
	movq	24(%r12), %rcx
	cmpq	%rax, %rbx
	jb	.L147
	testq	%rcx, %rcx
	je	.L148
	movq	%rcx, %r12
	jmp	.L168
	.p2align 4,,10
	.p2align 3
.L148:
	cmpq	%rax, %rbx
	jbe	.L158
.L157:
	cmpq	%r12, %r13
	jne	.L173
.L164:
	movl	$1, %r14d
.L153:
	movl	$40, %edi
	call	_Znwm@PLT
	movq	%r13, %rcx
	movq	%r12, %rdx
	movl	%r14d, %edi
	movq	%rbx, 32(%rax)
	movq	%rax, %rsi
	call	_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_@PLT
	addq	$1, 56(%rbp)
.L158:
	movq	128(%rbp), %rdi
	movq	112(%rbp), %rax
	movq	%rbx, (%rsp)
	leaq	-8(%rdi), %rdx
	cmpq	%rdx, %rax
	je	.L154
	movq	%rbx, (%rax)
	addq	$8, %rax
	movq	%rax, 112(%rbp)
.L155:
	movl	$1, %eax
.L140:
	movq	8(%rsp), %rdi
	subq	%fs:40, %rdi
	jne	.L174
	addq	$16, %rsp
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
.L147:
	.cfi_restore_state
	testq	%rdx, %rdx
	je	.L150
	movq	%rdx, %r12
	jmp	.L168
	.p2align 4,,10
	.p2align 3
.L141:
	movq	40(%rdi), %r12
	cmpq	%r12, %r13
	je	.L164
	movq	%r13, %r12
.L152:
	movq	%r12, %rdi
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base@PLT
	cmpq	%rbx, 32(%rax)
	jnb	.L158
	jmp	.L157
	.p2align 4,,10
	.p2align 3
.L150:
	cmpq	%r12, 40(%rbp)
	jne	.L152
	jmp	.L157
.L154:
	movq	%rsp, %rsi
	leaq	64(%rbp), %rdi
	call	_ZNSt5dequeIPN8opendnp317IScheduleCallbackESaIS2_EE16_M_push_back_auxIJS2_EEEvDpOT_@PLT
	jmp	.L155
.L173:
	xorl	%r14d, %r14d
	cmpq	32(%r12), %rbx
	setb	%r14b
	jmp	.L153
.L174:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1198:
	.size	_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE, .-_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE
	.type	_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE, @function
_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE:
.LFB1196:
	.cfi_startproc
	movzbl	8(%rdi), %eax
	testb	%al, %al
	je	.L182
	movq	144(%rdi), %rdx
	testq	%rdx, %rdx
	je	.L177
	cmpq	%rdx, %rsi
	je	.L182
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZN8opendnp317MultidropTaskLock17AddIfNotContainedERNS_17IScheduleCallbackE@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L182:
	ret
	.p2align 4,,10
	.p2align 3
.L177:
	movq	%rsi, 144(%rdi)
	ret
	.cfi_endproc
.LFE1196:
	.size	_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE, .-_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE
	.weak	_ZTSN8opendnp39ITaskLockE
	.section	.rodata._ZTSN8opendnp39ITaskLockE,"aG",@progbits,_ZTSN8opendnp39ITaskLockE,comdat
	.align 16
	.type	_ZTSN8opendnp39ITaskLockE, @object
	.size	_ZTSN8opendnp39ITaskLockE, 22
_ZTSN8opendnp39ITaskLockE:
	.string	"N8opendnp39ITaskLockE"
	.weak	_ZTIN8opendnp39ITaskLockE
	.section	.data.rel.ro._ZTIN8opendnp39ITaskLockE,"awG",@progbits,_ZTIN8opendnp39ITaskLockE,comdat
	.align 8
	.type	_ZTIN8opendnp39ITaskLockE, @object
	.size	_ZTIN8opendnp39ITaskLockE, 16
_ZTIN8opendnp39ITaskLockE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp39ITaskLockE
	.weak	_ZTSN8opendnp317MultidropTaskLockE
	.section	.rodata._ZTSN8opendnp317MultidropTaskLockE,"aG",@progbits,_ZTSN8opendnp317MultidropTaskLockE,comdat
	.align 16
	.type	_ZTSN8opendnp317MultidropTaskLockE, @object
	.size	_ZTSN8opendnp317MultidropTaskLockE, 31
_ZTSN8opendnp317MultidropTaskLockE:
	.string	"N8opendnp317MultidropTaskLockE"
	.weak	_ZTIN8opendnp317MultidropTaskLockE
	.section	.data.rel.ro._ZTIN8opendnp317MultidropTaskLockE,"awG",@progbits,_ZTIN8opendnp317MultidropTaskLockE,comdat
	.align 8
	.type	_ZTIN8opendnp317MultidropTaskLockE, @object
	.size	_ZTIN8opendnp317MultidropTaskLockE, 24
_ZTIN8opendnp317MultidropTaskLockE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8opendnp317MultidropTaskLockE
	.quad	_ZTIN8opendnp39ITaskLockE
	.weak	_ZTVN8opendnp317MultidropTaskLockE
	.section	.data.rel.ro._ZTVN8opendnp317MultidropTaskLockE,"awG",@progbits,_ZTVN8opendnp317MultidropTaskLockE,comdat
	.align 8
	.type	_ZTVN8opendnp317MultidropTaskLockE, @object
	.size	_ZTVN8opendnp317MultidropTaskLockE, 32
_ZTVN8opendnp317MultidropTaskLockE:
	.quad	0
	.quad	_ZTIN8opendnp317MultidropTaskLockE
	.quad	_ZN8opendnp317MultidropTaskLock7AcquireERNS_17IScheduleCallbackE
	.quad	_ZN8opendnp317MultidropTaskLock7ReleaseERNS_17IScheduleCallbackE
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
