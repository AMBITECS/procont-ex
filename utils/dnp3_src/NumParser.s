	.file	"NumParser.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE
	.type	_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE, @function
_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE:
.LFB2159:
	.cfi_startproc
	movq	8(%rdi), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$1, %esi
	movzbl	(%rax), %ebx
	call	_ZN7openpal6RSlice7AdvanceEj@PLT
	movzbl	%bl, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2159:
	.size	_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE, .-_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE
	.section	.text._ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE,"axG",@progbits,_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE,comdat
	.p2align 4
	.weak	_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE
	.type	_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE, @function
_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE:
.LFB2433:
	.cfi_startproc
	movq	8(%rdi), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$2, %esi
	movzwl	(%rax), %r12d
	call	_ZN7openpal6RSlice7AdvanceEj@PLT
	movl	%r12d, %eax
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2433:
	.size	_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE, .-_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh
	.type	_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh, @function
_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh:
.LFB2152:
	.cfi_startproc
	movq	%rsi, (%rdi)
	movb	%dl, 8(%rdi)
	ret
	.cfi_endproc
.LFE2152:
	.size	_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh, .-_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh
	.globl	_ZN8opendnp39NumParserC1EPFtRN7openpal6RSliceEEh
	.set	_ZN8opendnp39NumParserC1EPFtRN7openpal6RSliceEEh,_ZN8opendnp39NumParserC2EPFtRN7openpal6RSliceEEh
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39NumParser8NumBytesEv
	.type	_ZNK8opendnp39NumParser8NumBytesEv, @function
_ZNK8opendnp39NumParser8NumBytesEv:
.LFB2154:
	.cfi_startproc
	movzbl	8(%rdi), %eax
	ret
	.cfi_endproc
.LFE2154:
	.size	_ZNK8opendnp39NumParser8NumBytesEv, .-_ZNK8opendnp39NumParser8NumBytesEv
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE
	.type	_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE, @function
_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE:
.LFB2157:
	.cfi_startproc
	movq	%rdi, %r8
	movq	%rsi, %rdi
	jmp	*(%r8)
	.cfi_endproc
.LFE2157:
	.size	_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE, .-_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Not enough data for start / stop"
	.align 8
.LC1:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/app/parsing/NumParser.cpp(70)"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"start (%u) > stop (%u)"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/app/parsing/NumParser.cpp(84)"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39NumParser10ParseRangeERN7openpal6RSliceERNS_5RangeEPNS1_6LoggerE
	.type	_ZNK8opendnp39NumParser10ParseRangeERN7openpal6RSliceERNS_5RangeEPNS1_6LoggerE, @function
_ZNK8opendnp39NumParser10ParseRangeERN7openpal6RSliceERNS_5RangeEPNS1_6LoggerE:
.LFB2156:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rcx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$152, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	xorl	%eax, %eax
	movzbl	8(%rdi), %eax
	addl	%eax, %eax
	cmpl	(%rsi), %eax
	ja	.L28
	movq	%rdx, %rbx
	movq	%rdi, %rbp
	movq	%rsi, %r12
	call	_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE@PLT
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movw	%ax, (%rbx)
	call	_ZNK8opendnp39NumParser7ReadNumERN7openpal6RSliceE@PLT
	xorl	%r8d, %r8d
	movw	%ax, 2(%rbx)
	cmpw	(%rbx), %ax
	jb	.L29
.L9:
	movq	136(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L30
	addq	$152, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r8d, %eax
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
.L29:
	.cfi_restore_state
	testq	%r13, %r13
	je	.L27
	leaq	12(%rsp), %rbp
	movq	%r13, %rdi
	movl	$4, 12(%rsp)
	movq	%rbp, %rsi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L31
.L27:
	movl	$10, %r8d
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L28:
	testq	%rcx, %rcx
	je	.L11
	leaq	12(%rsp), %rbp
	movq	%rcx, %rdi
	movl	$4, 12(%rsp)
	movq	%rbp, %rsi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L11
	leaq	.LC0(%rip), %rcx
	leaq	.LC1(%rip), %rdx
	movq	%rbp, %rsi
	movq	%r13, %rdi
	movl	$4, 12(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	movl	$3, %r8d
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L11:
	movl	$3, %r8d
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L31:
	movzwl	2(%rbx), %eax
	leaq	16(%rsp), %r12
	subq	$8, %rsp
	.cfi_def_cfa_offset 200
	movzwl	(%rbx), %r9d
	movq	%r12, %rdi
	movl	$120, %ecx
	movl	$1, %edx
	movl	$120, %esi
	pushq	%rax
	.cfi_def_cfa_offset 208
	leaq	.LC2(%rip), %r8
	xorl	%eax, %eax
	call	__snprintf_chk@PLT
	movq	%r12, %rcx
	movq	%rbp, %rsi
	movq	%r13, %rdi
	movl	$4, 28(%rsp)
	popq	%rax
	.cfi_def_cfa_offset 200
	popq	%rdx
	.cfi_def_cfa_offset 192
	leaq	.LC3(%rip), %rdx
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L27
.L30:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2156:
	.size	_ZNK8opendnp39NumParser10ParseRangeERN7openpal6RSliceERNS_5RangeEPNS1_6LoggerE, .-_ZNK8opendnp39NumParser10ParseRangeERN7openpal6RSliceERNS_5RangeEPNS1_6LoggerE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE
	.type	_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE, @function
_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE:
.LFB2158:
	.cfi_startproc
	movq	%rdi, %rax
	movq	%rdx, %rdi
	movzbl	8(%rax), %edx
	cmpl	(%rdi), %edx
	ja	.L35
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rsi, %rbx
	call	*(%rax)
	movl	$1, %r8d
	movw	%ax, (%rbx)
	movl	%r8d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	.cfi_restore 3
	xorl	%r8d, %r8d
	movl	%r8d, %eax
	ret
	.cfi_endproc
.LFE2158:
	.size	_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE, .-_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE
	.section	.rodata.str1.1
.LC4:
	.string	"count of 0"
	.section	.rodata.str1.8
	.align 8
.LC5:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/app/parsing/NumParser.cpp(51)"
	.section	.rodata.str1.1
.LC6:
	.string	"Not enough data for count"
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/app/parsing/NumParser.cpp(61)"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp39NumParser10ParseCountERN7openpal6RSliceERtPNS1_6LoggerE
	.type	_ZNK8opendnp39NumParser10ParseCountERN7openpal6RSliceERtPNS1_6LoggerE, @function
_ZNK8opendnp39NumParser10ParseCountERN7openpal6RSliceERtPNS1_6LoggerE:
.LFB2155:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rcx, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdx, %rbx
	movq	%rsi, %rdx
	movq	%rbx, %rsi
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZNK8opendnp39NumParser4ReadERtRN7openpal6RSliceE@PLT
	testb	%al, %al
	je	.L41
	xorl	%eax, %eax
	cmpw	$0, (%rbx)
	je	.L59
.L40:
	movq	8(%rsp), %rbx
	subq	%fs:40, %rbx
	jne	.L60
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
.L59:
	.cfi_restore_state
	testq	%rbp, %rbp
	je	.L43
	leaq	4(%rsp), %r12
	movq	%rbp, %rdi
	movl	$4, 4(%rsp)
	movq	%r12, %rsi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L61
.L43:
	movl	$11, %eax
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L41:
	testq	%rbp, %rbp
	je	.L58
	leaq	4(%rsp), %r12
	movq	%rbp, %rdi
	movl	$4, 4(%rsp)
	movq	%r12, %rsi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L62
.L58:
	movl	$3, %eax
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L61:
	leaq	.LC4(%rip), %rcx
	leaq	.LC5(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	movl	$11, %eax
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L62:
	leaq	.LC6(%rip), %rcx
	leaq	.LC7(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L58
.L60:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2155:
	.size	_ZNK8opendnp39NumParser10ParseCountERN7openpal6RSliceERtPNS1_6LoggerE, .-_ZNK8opendnp39NumParser10ParseCountERN7openpal6RSliceERtPNS1_6LoggerE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39NumParser7OneByteEv
	.type	_ZN8opendnp39NumParser7OneByteEv, @function
_ZN8opendnp39NumParser7OneByteEv:
.LFB2160:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	_ZN8opendnp39NumParser8ReadByteERN7openpal6RSliceE@GOTPCREL(%rip), %rsi
	movl	$1, %edx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_ZN8opendnp39NumParserC1EPFtRN7openpal6RSliceEEh@PLT
	movq	(%rsp), %rax
	movq	8(%rsp), %rdx
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L66
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L66:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2160:
	.size	_ZN8opendnp39NumParser7OneByteEv, .-_ZN8opendnp39NumParser7OneByteEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp39NumParser7TwoByteEv
	.type	_ZN8opendnp39NumParser7TwoByteEv, @function
_ZN8opendnp39NumParser7TwoByteEv:
.LFB2161:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	_ZN7openpal7Bit16LEItE10ReadBufferERNS_6RSliceE@GOTPCREL(%rip), %rsi
	movl	$2, %edx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_ZN8opendnp39NumParserC1EPFtRN7openpal6RSliceEEh@PLT
	movq	(%rsp), %rax
	movq	8(%rsp), %rdx
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L70
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L70:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2161:
	.size	_ZN8opendnp39NumParser7TwoByteEv, .-_ZN8opendnp39NumParser7TwoByteEv
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
