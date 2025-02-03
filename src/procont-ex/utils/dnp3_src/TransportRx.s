	.file	"TransportRx.cpp"
	.text
	.section	.text._ZN7openpal6LoggerD2Ev,"axG",@progbits,_ZN7openpal6LoggerD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal6LoggerD2Ev
	.type	_ZN7openpal6LoggerD2Ev, @function
_ZN7openpal6LoggerD2Ev:
.LFB2091:
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
	movq	24(%rdi), %rbp
	movq	%rdi, %rbx
	testq	%rbp, %rbp
	je	.L3
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L18
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L5:
	cmpl	$1, %eax
	je	.L19
.L3:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L1
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L20
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L12:
	cmpl	$1, %eax
	je	.L21
.L1:
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
.L19:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L22
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L8:
	cmpl	$1, %eax
	jne	.L3
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L21:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L23
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L15:
	cmpl	$1, %eax
	jne	.L1
	movq	0(%rbp), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L20:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L22:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L23:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L15
	.cfi_endproc
.LFE2091:
	.size	_ZN7openpal6LoggerD2Ev, .-_ZN7openpal6LoggerD2Ev
	.weak	_ZN7openpal6LoggerD1Ev
	.set	_ZN7openpal6LoggerD1Ev,_ZN7openpal6LoggerD2Ev
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj
	.type	_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj, @function
_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj:
.LFB2151:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2151
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	%edx, %r8d
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	(%rsi), %rax
	movq	%rax, (%rdi)
	movq	8(%rsi), %rax
	movq	%rax, 8(%rdi)
	testq	%rax, %rax
	je	.L25
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L39
	addl	$1, 8(%rax)
.L25:
	movq	16(%rsi), %rax
	movq	%rax, 16(%rbp)
	movq	24(%rsi), %rax
	movq	%rax, 24(%rbp)
	testq	%rax, %rax
	je	.L27
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L40
	addl	$1, 8(%rax)
.L27:
	movl	$0, 48(%rbp)
	pxor	%xmm0, %xmm0
	leaq	56(%rbp), %rdi
	movl	%r8d, %esi
	movups	%xmm0, 32(%rbp)
.LEHB0:
	call	_ZN7openpal6BufferC1Ej@PLT
.LEHE0:
	movl	$0, 80(%rbp)
	movb	$0, 84(%rbp)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L39:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L40:
	lock addl	$1, 8(%rax)
	jmp	.L27
.L30:
	movq	%rax, %r12
	jmp	.L29
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2151:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2151-.LLSDACSB2151
.LLSDACSB2151:
	.uleb128 .LEHB0-.LFB2151
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L30-.LFB2151
	.uleb128 0
.LLSDACSE2151:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC2151
	.type	_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj.cold, @function
_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj.cold:
.LFSB2151:
.L29:
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	%rbp, %rdi
	call	_ZN7openpal6LoggerD1Ev@PLT
	movq	%r12, %rdi
.LEHB1:
	call	_Unwind_Resume@PLT
.LEHE1:
	.cfi_endproc
.LFE2151:
	.section	.gcc_except_table
.LLSDAC2151:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC2151-.LLSDACSBC2151
.LLSDACSBC2151:
	.uleb128 .LEHB1-.LCOLDB0
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSEC2151:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj, .-_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj
	.section	.text.unlikely
	.size	_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj.cold, .-_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj.cold
.LCOLDE0:
	.text
.LHOTE0:
	.globl	_ZN8opendnp311TransportRxC1ERKN7openpal6LoggerEj
	.set	_ZN8opendnp311TransportRxC1ERKN7openpal6LoggerEj,_ZN8opendnp311TransportRxC2ERKN7openpal6LoggerEj
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRx13ClearRxBufferEv
	.type	_ZN8opendnp311TransportRx13ClearRxBufferEv, @function
_ZN8opendnp311TransportRx13ClearRxBufferEv:
.LFB2154:
	.cfi_startproc
	movl	$0, 80(%rdi)
	ret
	.cfi_endproc
.LFE2154:
	.size	_ZN8opendnp311TransportRx13ClearRxBufferEv, .-_ZN8opendnp311TransportRx13ClearRxBufferEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRx5ResetEv
	.type	_ZN8opendnp311TransportRx5ResetEv, @function
_ZN8opendnp311TransportRx5ResetEv:
.LFB2153:
	.cfi_startproc
	movb	$0, 84(%rdi)
	jmp	_ZN8opendnp311TransportRx13ClearRxBufferEv@PLT
	.cfi_endproc
.LFE2153:
	.size	_ZN8opendnp311TransportRx5ResetEv, .-_ZN8opendnp311TransportRx5ResetEv
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRx12GetAvailableEv
	.type	_ZN8opendnp311TransportRx12GetAvailableEv, @function
_ZN8opendnp311TransportRx12GetAvailableEv:
.LFB2155:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	addq	$56, %rdi
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	call	_ZN7openpal6Buffer9GetWSliceEv@PLT
	movl	80(%rbx), %esi
	movq	%rsp, %rdi
	movq	%rdx, 8(%rsp)
	movl	%eax, (%rsp)
	call	_ZNK7openpal6WSlice4SkipEj@PLT
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L46
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L46:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2155:
	.size	_ZN8opendnp311TransportRx12GetAvailableEv, .-_ZN8opendnp311TransportRx12GetAvailableEv
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"FIR received mid-fragment, discarding previous bytes"
	.align 8
.LC2:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(122)"
	.align 8
.LC3:
	.string	"non-FIR packet with 0 prior bytes"
	.align 8
.LC4:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(131)"
	.align 8
.LC5:
	.string	"Ignoring bad sequence, got %u, expected %u"
	.align 8
.LC6:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(138)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRx14ValidateHeaderEbh
	.type	_ZN8opendnp311TransportRx14ValidateHeaderEbh, @function
_ZN8opendnp311TransportRx14ValidateHeaderEbh:
.LFB2157:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	movl	%edx, %r14d
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
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
	movl	%esi, %ebx
	subq	$144, %rsp
	.cfi_def_cfa_offset 192
	movq	%fs:40, %rax
	movq	%rax, 136(%rsp)
	movl	80(%rdi), %eax
	testb	%sil, %sil
	jne	.L64
	testl	%eax, %eax
	je	.L65
	cmpb	84(%rdi), %dl
	jne	.L66
.L54:
	movl	$1, %eax
.L47:
	movq	136(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L67
	addq	$144, %rsp
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
.L64:
	.cfi_restore_state
	movb	%dl, 84(%rbp)
	testl	%eax, %eax
	je	.L54
	addl	$1, 44(%rdi)
	leaq	12(%rsp), %r12
	movq	%r12, %rsi
	movl	$4, 12(%rsp)
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L68
.L51:
	movl	$0, 80(%rbp)
	movl	%ebx, %eax
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L66:
	addl	$1, 48(%rdi)
	leaq	12(%rsp), %r12
	movq	%r12, %rsi
	movl	$4, 12(%rsp)
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L69
.L55:
	movl	%ebx, %eax
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L69:
	movzbl	84(%rbp), %eax
	leaq	16(%rsp), %r13
	subq	$8, %rsp
	.cfi_def_cfa_offset 200
	movzbl	%r14b, %r9d
	leaq	.LC5(%rip), %r8
	movl	$120, %ecx
	movl	$1, %edx
	movq	%r13, %rdi
	pushq	%rax
	.cfi_def_cfa_offset 208
	movl	$120, %esi
	xorl	%eax, %eax
	call	__snprintf_chk@PLT
	movq	%r13, %rcx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 28(%rsp)
	popq	%rax
	.cfi_def_cfa_offset 200
	popq	%rdx
	.cfi_def_cfa_offset 192
	leaq	.LC6(%rip), %rdx
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L65:
	addl	$1, 48(%rdi)
	leaq	12(%rsp), %r12
	movq	%r12, %rsi
	movl	$4, 12(%rsp)
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L55
	leaq	.LC3(%rip), %rcx
	leaq	.LC4(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 12(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L68:
	leaq	.LC1(%rip), %rcx
	leaq	.LC2(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$4, 12(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L51
.L67:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2157:
	.size	_ZN8opendnp311TransportRx14ValidateHeaderEbh, .-_ZN8opendnp311TransportRx14ValidateHeaderEbh
	.section	.rodata.str1.8
	.align 8
.LC7:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(66)"
	.align 8
.LC8:
	.string	"FIR: %d FIN: %d SEQ: %u LEN: %u"
	.align 8
.LC9:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(78)"
	.align 8
.LC10:
	.string	"Exceeded the buffer size before a complete fragment was read"
	.align 8
.LC11:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportRx.cpp(91)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE
	.type	_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE, @function
_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE:
.LFB2156:
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
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$184, %rsp
	.cfi_def_cfa_offset 240
	movq	%fs:40, %rax
	movq	%rax, 168(%rsp)
	xorl	%eax, %eax
	movl	(%rsi), %eax
	addl	$1, 32(%rdi)
	testl	%eax, %eax
	jne	.L71
	leaq	32(%rsp), %r12
	movl	$4, 32(%rsp)
	movq	%r12, %rsi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L92
.L72:
	addl	$1, 36(%rbp)
	movq	168(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L91
	addq	$184, %rsp
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
	jmp	_ZN7openpal6RSlice5EmptyEv@PLT
	.p2align 4,,10
	.p2align 3
.L71:
	.cfi_restore_state
	movq	8(%rsi), %rax
	movq	%rsi, %rdi
	leaq	32(%rsp), %r13
	movl	$1, %esi
	movzbl	(%rax), %ebx
	call	_ZNK7openpal6RSlice4SkipEj@PLT
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$512, 32(%rsp)
	movl	%ebx, %r12d
	movl	%eax, (%rsp)
	movl	%ebx, %r14d
	movq	%rdx, 8(%rsp)
	shrb	$6, %r12b
	andl	$63, %r14d
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	andl	$1, %r12d
	testb	%al, %al
	jne	.L93
.L74:
	movl	%r14d, %edx
	movl	%r12d, %esi
	movq	%rbp, %rdi
	call	_ZN8opendnp311TransportRx14ValidateHeaderEbh@PLT
	testb	%al, %al
	jne	.L75
	addl	$1, 36(%rbp)
	call	_ZN7openpal6RSlice5EmptyEv@PLT
.L76:
	movq	168(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L91
	addq	$184, %rsp
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
.L75:
	.cfi_restore_state
	movq	%rbp, %rdi
	call	_ZN8opendnp311TransportRx12GetAvailableEv@PLT
	movl	%eax, 16(%rsp)
	movq	%rdx, 24(%rsp)
	cmpl	(%rsp), %eax
	jnb	.L77
	addl	$1, 40(%rbp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$4, 32(%rsp)
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L94
.L78:
	movq	%rbp, %rdi
	call	_ZN8opendnp311TransportRx13ClearRxBufferEv@PLT
	call	_ZN7openpal6RSlice5EmptyEv@PLT
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L92:
	leaq	48(%rsp), %rcx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movb	$0, 76(%rsp)
	movdqa	.LC12(%rip), %xmm0
	leaq	.LC7(%rip), %rdx
	movabsq	$7307126058369706100, %rax
	movl	$1919247457, 72(%rsp)
	movq	%rax, 64(%rsp)
	movl	$4, 32(%rsp)
	movups	%xmm0, 48(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L72
	.p2align 4,,10
	.p2align 3
.L93:
	leaq	48(%rsp), %r15
	subq	$8, %rsp
	.cfi_def_cfa_offset 248
	movl	%r12d, %r9d
	movl	$120, %ecx
	movl	8(%rsp), %eax
	movq	%r15, %rdi
	movl	$1, %edx
	leaq	.LC8(%rip), %r8
	movl	$120, %esi
	pushq	%rax
	.cfi_def_cfa_offset 256
	movsbl	%bl, %eax
	shrl	$31, %eax
	pushq	%r14
	.cfi_def_cfa_offset 264
	pushq	%rax
	.cfi_def_cfa_offset 272
	xorl	%eax, %eax
	call	__snprintf_chk@PLT
	movq	%r15, %rcx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$512, 64(%rsp)
	leaq	.LC9(%rip), %rdx
	addq	$32, %rsp
	.cfi_def_cfa_offset 240
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L74
	.p2align 4,,10
	.p2align 3
.L77:
	leaq	16(%rsp), %rsi
	movq	%rsp, %rdi
	call	_ZNK7openpal6RSlice6CopyToERNS_6WSliceE@PLT
	movl	(%rsp), %eax
	addl	%eax, 80(%rbp)
	movzbl	84(%rbp), %eax
	addl	$1, %eax
	andl	$63, %eax
	movb	%al, 84(%rbp)
	testb	%bl, %bl
	js	.L95
	call	_ZN7openpal6RSlice5EmptyEv@PLT
	jmp	.L76
	.p2align 4,,10
	.p2align 3
.L95:
	leaq	56(%rbp), %rdi
	call	_ZNK7openpal6Buffer8ToRSliceEv@PLT
	movl	80(%rbp), %esi
	movq	%r13, %rdi
	movl	%eax, 32(%rsp)
	movq	%rdx, 40(%rsp)
	call	_ZNK7openpal6RSlice4TakeEj@PLT
	movq	%rbp, %rdi
	movq	%rdx, %r12
	movq	%rax, %rbx
	call	_ZN8opendnp311TransportRx13ClearRxBufferEv@PLT
	movq	%rbx, %rax
	movq	%r12, %rdx
	jmp	.L76
.L91:
	call	__stack_chk_fail@PLT
	.p2align 4,,10
	.p2align 3
.L94:
	leaq	.LC10(%rip), %rcx
	leaq	.LC11(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$4, 32(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L78
	.cfi_endproc
.LFE2156:
	.size	_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE, .-_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC12:
	.quad	7234318571485226322
	.quad	7599578584779355168
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
