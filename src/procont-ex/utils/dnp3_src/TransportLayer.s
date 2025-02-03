	.file	"TransportLayer.cpp"
	.text
	.section	.text._ZN7openpal5ArrayIhjED2Ev,"axG",@progbits,_ZN7openpal5ArrayIhjED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal5ArrayIhjED2Ev
	.type	_ZN7openpal5ArrayIhjED2Ev, @function
_ZN7openpal5ArrayIhjED2Ev:
.LFB2307:
	.cfi_startproc
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	addq	$16, %rax
	movq	%rax, (%rdi)
	movq	16(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L1
	jmp	_ZdaPv@PLT
	.p2align 4,,10
	.p2align 3
.L1:
	ret
	.cfi_endproc
.LFE2307:
	.size	_ZN7openpal5ArrayIhjED2Ev, .-_ZN7openpal5ArrayIhjED2Ev
	.weak	_ZN7openpal5ArrayIhjED1Ev
	.set	_ZN7openpal5ArrayIhjED1Ev,_ZN7openpal5ArrayIhjED2Ev
	.section	.text._ZN7openpal5ArrayIhjED0Ev,"axG",@progbits,_ZN7openpal5ArrayIhjED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7openpal5ArrayIhjED0Ev
	.type	_ZN7openpal5ArrayIhjED0Ev, @function
_ZN7openpal5ArrayIhjED0Ev:
.LFB2309:
	.cfi_startproc
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	addq	$16, %rax
	movq	%rax, (%rdi)
	movq	16(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L5
	call	_ZdaPv@PLT
.L5:
	movq	%rbp, %rdi
	movl	$24, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE2309:
	.size	_ZN7openpal5ArrayIhjED0Ev, .-_ZN7openpal5ArrayIhjED0Ev
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Layer offline"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(54)"
	.section	.rodata.str1.1
.LC2:
	.string	"APDU cannot be empty"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(60)"
	.align 8
.LC4:
	.string	"Invalid BeginTransmit call, already transmitting"
	.align 8
.LC5:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(66)"
	.align 8
.LC6:
	.string	"Can't send without an attached link layer"
	.align 8
.LC7:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(72)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.type	_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE, @function
_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE:
.LFB2298:
	.cfi_startproc
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movzbl	64(%rdi), %r12d
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%r12b, %r12b
	je	.L30
	movl	(%rsi), %eax
	testl	%eax, %eax
	je	.L31
	cmpb	$0, 65(%rdi)
	jne	.L32
	cmpq	$0, 56(%rdi)
	je	.L33
	movb	$1, 65(%rdi)
	leaq	160(%rdi), %rbp
	movq	%rbp, %rdi
	call	_ZN8opendnp311TransportTx9ConfigureERKN7openpal6RSliceE@PLT
	movq	56(%rbx), %rdi
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*16(%rax)
.L10:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L34
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r12d, %eax
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
.L30:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L12
.L29:
	xorl	%r12d, %r12d
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L33:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L29
	movq	%r12, %rsi
	leaq	.LC6(%rip), %rcx
	movq	%rbp, %rdi
	xorl	%r12d, %r12d
	leaq	.LC7(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L12:
	leaq	.LC0(%rip), %rcx
	leaq	.LC1(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L31:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L29
	movq	%r12, %rsi
	leaq	.LC2(%rip), %rcx
	movq	%rbp, %rdi
	xorl	%r12d, %r12d
	leaq	.LC3(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L32:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L29
	leaq	.LC4(%rip), %rcx
	leaq	.LC5(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L29
.L34:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2298:
	.size	_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE, .-_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.section	.rodata.str1.8
	.align 8
.LC8:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(100)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE
	.type	_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE, @function
_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE:
.LFB2299:
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
	movq	%rdi, %rbx
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	movzbl	64(%rdi), %ebp
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	testb	%bpl, %bpl
	je	.L36
	leaq	72(%rdi), %rdi
	call	_ZN8opendnp311TransportRx14ProcessReceiveERKN7openpal6RSliceE@PLT
	movl	%eax, (%rsp)
	movq	%rdx, 8(%rsp)
	testl	%eax, %eax
	jne	.L47
.L37:
	movl	%ebp, %eax
.L35:
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L48
	addq	$32, %rsp
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
.L36:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	movq	%rsp, %r12
	movl	$2, (%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L35
	leaq	.LC0(%rip), %rcx
	leaq	.LC8(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$2, (%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L35
	.p2align 4,,10
	.p2align 3
.L47:
	movq	48(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L37
	movq	(%rdi), %rax
	movq	%rsp, %rsi
	call	*32(%rax)
	jmp	.L37
.L48:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2299:
	.size	_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE, .-_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE
	.section	.text._ZN8opendnp314TransportLayerD2Ev,"axG",@progbits,_ZN8opendnp314TransportLayerD5Ev,comdat
	.p2align 4
	.weak	_ZThn8_N8opendnp314TransportLayerD1Ev
	.type	_ZThn8_N8opendnp314TransportLayerD1Ev, @function
_ZThn8_N8opendnp314TransportLayerD1Ev:
.LFB2990:
	.cfi_startproc
	movq	_ZTVN8opendnp314TransportLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	488(%rdi), %r12
	movq	%rax, %xmm0
	movq	_ZTVN8opendnp311TransportTxE@GOTPCREL(%rip), %rax
	movq	%rdx, %xmm1
	movq	%rdi, %rbx
	punpcklqdq	%xmm1, %xmm0
	addq	$16, %rax
	movups	%xmm0, -8(%rdi)
	movq	%rax, 152(%rdi)
	testq	%r12, %r12
	je	.L51
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L97
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L53:
	cmpl	$1, %eax
	je	.L98
.L51:
	movq	472(%rbx), %r12
	testq	%r12, %r12
	je	.L58
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L99
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L60:
	cmpl	$1, %eax
	je	.L100
.L58:
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	movq	136(%rbx), %rdi
	addq	$16, %rax
	movq	%rax, 120(%rbx)
	testq	%rdi, %rdi
	je	.L64
	call	_ZdaPv@PLT
.L64:
	movq	88(%rbx), %r12
	testq	%r12, %r12
	je	.L66
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L101
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L68:
	cmpl	$1, %eax
	je	.L102
.L66:
	movq	72(%rbx), %r12
	testq	%r12, %r12
	je	.L73
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L103
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L75:
	cmpl	$1, %eax
	je	.L104
.L73:
	movq	32(%rbx), %r12
	testq	%r12, %r12
	je	.L80
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L105
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L82:
	cmpl	$1, %eax
	je	.L106
.L80:
	movq	16(%rbx), %r12
	testq	%r12, %r12
	je	.L49
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L107
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L89:
	cmpl	$1, %eax
	je	.L108
.L49:
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
.L98:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L109
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L56:
	cmpl	$1, %eax
	jne	.L51
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L100:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L110
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L63:
	cmpl	$1, %eax
	jne	.L58
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L102:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L111
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L71:
	cmpl	$1, %eax
	jne	.L66
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L66
	.p2align 4,,10
	.p2align 3
.L104:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L112
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L78:
	cmpl	$1, %eax
	jne	.L73
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L73
	.p2align 4,,10
	.p2align 3
.L106:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L113
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L85:
	cmpl	$1, %eax
	jne	.L80
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L80
	.p2align 4,,10
	.p2align 3
.L108:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L114
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L92:
	cmpl	$1, %eax
	jne	.L49
	movq	(%r12), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L101:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L105:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L82
	.p2align 4,,10
	.p2align 3
.L107:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L89
	.p2align 4,,10
	.p2align 3
.L97:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L53
	.p2align 4,,10
	.p2align 3
.L99:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L103:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L75
	.p2align 4,,10
	.p2align 3
.L109:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L114:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L92
	.p2align 4,,10
	.p2align 3
.L110:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L63
	.p2align 4,,10
	.p2align 3
.L111:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L71
	.p2align 4,,10
	.p2align 3
.L112:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L113:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L85
	.cfi_endproc
.LFE2990:
	.size	_ZThn8_N8opendnp314TransportLayerD1Ev, .-_ZThn8_N8opendnp314TransportLayerD1Ev
	.align 2
	.p2align 4
	.weak	_ZN8opendnp314TransportLayerD2Ev
	.type	_ZN8opendnp314TransportLayerD2Ev, @function
_ZN8opendnp314TransportLayerD2Ev:
.LFB2942:
	.cfi_startproc
	movq	_ZTVN8opendnp314TransportLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	496(%rdi), %r12
	movq	%rax, %xmm0
	movq	_ZTVN8opendnp311TransportTxE@GOTPCREL(%rip), %rax
	movq	%rdx, %xmm1
	movq	%rdi, %rbx
	punpcklqdq	%xmm1, %xmm0
	addq	$16, %rax
	movups	%xmm0, (%rdi)
	movq	%rax, 160(%rdi)
	testq	%r12, %r12
	je	.L117
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L163
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L119:
	cmpl	$1, %eax
	je	.L164
.L117:
	movq	480(%rbx), %r12
	testq	%r12, %r12
	je	.L124
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L165
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L126:
	cmpl	$1, %eax
	je	.L166
.L124:
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	movq	144(%rbx), %rdi
	addq	$16, %rax
	movq	%rax, 128(%rbx)
	testq	%rdi, %rdi
	je	.L130
	call	_ZdaPv@PLT
.L130:
	movq	96(%rbx), %r12
	testq	%r12, %r12
	je	.L132
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L167
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L134:
	cmpl	$1, %eax
	je	.L168
.L132:
	movq	80(%rbx), %r12
	testq	%r12, %r12
	je	.L139
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L169
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L141:
	cmpl	$1, %eax
	je	.L170
.L139:
	movq	40(%rbx), %r12
	testq	%r12, %r12
	je	.L146
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L171
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L148:
	cmpl	$1, %eax
	je	.L172
.L146:
	movq	24(%rbx), %r12
	testq	%r12, %r12
	je	.L115
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L173
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L155:
	cmpl	$1, %eax
	je	.L174
.L115:
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
.L164:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L175
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L122:
	cmpl	$1, %eax
	jne	.L117
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L117
	.p2align 4,,10
	.p2align 3
.L166:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L176
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L129:
	cmpl	$1, %eax
	jne	.L124
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L124
	.p2align 4,,10
	.p2align 3
.L168:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L177
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L137:
	cmpl	$1, %eax
	jne	.L132
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L132
	.p2align 4,,10
	.p2align 3
.L170:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L178
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L144:
	cmpl	$1, %eax
	jne	.L139
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L139
	.p2align 4,,10
	.p2align 3
.L172:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L179
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L151:
	cmpl	$1, %eax
	jne	.L146
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L146
	.p2align 4,,10
	.p2align 3
.L174:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L180
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L158:
	cmpl	$1, %eax
	jne	.L115
	movq	(%r12), %rax
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r12, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L167:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L134
	.p2align 4,,10
	.p2align 3
.L171:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L148
	.p2align 4,,10
	.p2align 3
.L173:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L155
	.p2align 4,,10
	.p2align 3
.L163:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L119
	.p2align 4,,10
	.p2align 3
.L165:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L126
	.p2align 4,,10
	.p2align 3
.L169:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L141
	.p2align 4,,10
	.p2align 3
.L175:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L122
	.p2align 4,,10
	.p2align 3
.L180:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L158
	.p2align 4,,10
	.p2align 3
.L176:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L129
	.p2align 4,,10
	.p2align 3
.L177:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L137
	.p2align 4,,10
	.p2align 3
.L178:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L144
	.p2align 4,,10
	.p2align 3
.L179:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L151
	.cfi_endproc
.LFE2942:
	.size	_ZN8opendnp314TransportLayerD2Ev, .-_ZN8opendnp314TransportLayerD2Ev
	.weak	_ZN8opendnp314TransportLayerD1Ev
	.set	_ZN8opendnp314TransportLayerD1Ev,_ZN8opendnp314TransportLayerD2Ev
	.section	.text._ZN8opendnp314TransportLayerD0Ev,"axG",@progbits,_ZN8opendnp314TransportLayerD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp314TransportLayerD0Ev
	.type	_ZN8opendnp314TransportLayerD0Ev, @function
_ZN8opendnp314TransportLayerD0Ev:
.LFB2944:
	.cfi_startproc
	movq	_ZTVN8opendnp314TransportLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	leaq	88(%rax), %rdx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	496(%rdi), %r12
	movq	%rax, %xmm0
	movq	_ZTVN8opendnp311TransportTxE@GOTPCREL(%rip), %rax
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	addq	$16, %rax
	movups	%xmm0, (%rdi)
	movq	%rax, 160(%rdi)
	testq	%r12, %r12
	je	.L183
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L229
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L185:
	cmpl	$1, %eax
	je	.L230
.L183:
	movq	480(%rbp), %r12
	testq	%r12, %r12
	je	.L190
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L231
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L192:
	cmpl	$1, %eax
	je	.L232
.L190:
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	movq	144(%rbp), %rdi
	addq	$16, %rax
	movq	%rax, 128(%rbp)
	testq	%rdi, %rdi
	je	.L196
	call	_ZdaPv@PLT
.L196:
	movq	96(%rbp), %r12
	testq	%r12, %r12
	je	.L198
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L233
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L200:
	cmpl	$1, %eax
	je	.L234
.L198:
	movq	80(%rbp), %r12
	testq	%r12, %r12
	je	.L205
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L235
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L207:
	cmpl	$1, %eax
	je	.L236
.L205:
	movq	40(%rbp), %r12
	testq	%r12, %r12
	je	.L212
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L237
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L214:
	cmpl	$1, %eax
	je	.L238
.L212:
	movq	24(%rbp), %r12
	testq	%r12, %r12
	je	.L219
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbx
	testq	%rbx, %rbx
	jne	.L239
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L221:
	cmpl	$1, %eax
	je	.L240
.L219:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	movl	$520, %esi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L230:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L241
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L188:
	cmpl	$1, %eax
	jne	.L183
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L183
	.p2align 4,,10
	.p2align 3
.L232:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L242
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L195:
	cmpl	$1, %eax
	jne	.L190
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L190
	.p2align 4,,10
	.p2align 3
.L234:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L243
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L203:
	cmpl	$1, %eax
	jne	.L198
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L198
	.p2align 4,,10
	.p2align 3
.L236:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L244
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L210:
	cmpl	$1, %eax
	jne	.L205
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L205
	.p2align 4,,10
	.p2align 3
.L238:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L245
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L217:
	cmpl	$1, %eax
	jne	.L212
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L212
	.p2align 4,,10
	.p2align 3
.L240:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbx, %rbx
	jne	.L246
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L224:
	cmpl	$1, %eax
	jne	.L219
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L219
	.p2align 4,,10
	.p2align 3
.L233:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L200
	.p2align 4,,10
	.p2align 3
.L237:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L214
	.p2align 4,,10
	.p2align 3
.L239:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L221
	.p2align 4,,10
	.p2align 3
.L229:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L185
	.p2align 4,,10
	.p2align 3
.L231:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L192
	.p2align 4,,10
	.p2align 3
.L235:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L207
	.p2align 4,,10
	.p2align 3
.L241:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L188
	.p2align 4,,10
	.p2align 3
.L246:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L224
	.p2align 4,,10
	.p2align 3
.L242:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L195
	.p2align 4,,10
	.p2align 3
.L243:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L203
	.p2align 4,,10
	.p2align 3
.L244:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L210
	.p2align 4,,10
	.p2align 3
.L245:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L217
	.cfi_endproc
.LFE2944:
	.size	_ZN8opendnp314TransportLayerD0Ev, .-_ZN8opendnp314TransportLayerD0Ev
	.p2align 4
	.weak	_ZThn8_N8opendnp314TransportLayerD0Ev
	.type	_ZThn8_N8opendnp314TransportLayerD0Ev, @function
_ZThn8_N8opendnp314TransportLayerD0Ev:
.LFB2989:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	leaq	-8(%rdi), %r13
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
	movq	_ZTVN8opendnp314TransportLayerE@GOTPCREL(%rip), %rax
	movq	488(%rdi), %r12
	leaq	88(%rax), %rdx
	addq	$16, %rax
	movq	%rax, %xmm0
	movq	_ZTVN8opendnp311TransportTxE@GOTPCREL(%rip), %rax
	movq	%rdx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	addq	$16, %rax
	movups	%xmm0, -8(%rdi)
	movq	%rax, 152(%rdi)
	testq	%r12, %r12
	je	.L249
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L295
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L251:
	cmpl	$1, %eax
	je	.L296
.L249:
	movq	472(%rbx), %r12
	testq	%r12, %r12
	je	.L256
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L297
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L258:
	cmpl	$1, %eax
	je	.L298
.L256:
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	movq	136(%rbx), %rdi
	addq	$16, %rax
	movq	%rax, 120(%rbx)
	testq	%rdi, %rdi
	je	.L262
	call	_ZdaPv@PLT
.L262:
	movq	88(%rbx), %r12
	testq	%r12, %r12
	je	.L264
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L299
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L266:
	cmpl	$1, %eax
	je	.L300
.L264:
	movq	72(%rbx), %r12
	testq	%r12, %r12
	je	.L271
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L301
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L273:
	cmpl	$1, %eax
	je	.L302
.L271:
	movq	32(%rbx), %r12
	testq	%r12, %r12
	je	.L278
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L303
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L280:
	cmpl	$1, %eax
	je	.L304
.L278:
	movq	16(%rbx), %r12
	testq	%r12, %r12
	je	.L285
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %rbp
	testq	%rbp, %rbp
	jne	.L305
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L287:
	cmpl	$1, %eax
	je	.L306
.L285:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movq	%r13, %rdi
	movl	$520, %esi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L296:
	.cfi_restore_state
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L307
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L254:
	cmpl	$1, %eax
	jne	.L249
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L249
	.p2align 4,,10
	.p2align 3
.L298:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L308
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L261:
	cmpl	$1, %eax
	jne	.L256
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L256
	.p2align 4,,10
	.p2align 3
.L300:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L309
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L269:
	cmpl	$1, %eax
	jne	.L264
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L264
	.p2align 4,,10
	.p2align 3
.L302:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L310
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L276:
	cmpl	$1, %eax
	jne	.L271
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L271
	.p2align 4,,10
	.p2align 3
.L304:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L311
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L283:
	cmpl	$1, %eax
	jne	.L278
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L278
	.p2align 4,,10
	.p2align 3
.L306:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	testq	%rbp, %rbp
	jne	.L312
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L290:
	cmpl	$1, %eax
	jne	.L285
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L285
	.p2align 4,,10
	.p2align 3
.L299:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L266
	.p2align 4,,10
	.p2align 3
.L303:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L280
	.p2align 4,,10
	.p2align 3
.L305:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L287
	.p2align 4,,10
	.p2align 3
.L295:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L251
	.p2align 4,,10
	.p2align 3
.L297:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L258
	.p2align 4,,10
	.p2align 3
.L301:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L273
	.p2align 4,,10
	.p2align 3
.L307:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L254
	.p2align 4,,10
	.p2align 3
.L312:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L290
	.p2align 4,,10
	.p2align 3
.L308:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L261
	.p2align 4,,10
	.p2align 3
.L309:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L269
	.p2align 4,,10
	.p2align 3
.L310:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L276
	.p2align 4,,10
	.p2align 3
.L311:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L283
	.cfi_endproc
.LFE2989:
	.size	_ZThn8_N8opendnp314TransportLayerD0Ev, .-_ZThn8_N8opendnp314TransportLayerD0Ev
	.text
	.p2align 4
	.globl	_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.type	_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE, @function
_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE:
.LFB2991:
	.cfi_startproc
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movzbl	56(%rdi), %r12d
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%r12b, %r12b
	je	.L333
	movl	(%rsi), %eax
	testl	%eax, %eax
	je	.L334
	cmpb	$0, 57(%rdi)
	jne	.L335
	cmpq	$0, 48(%rdi)
	je	.L336
	movb	$1, 57(%rdi)
	leaq	152(%rdi), %rbp
	movq	%rbp, %rdi
	call	_ZN8opendnp311TransportTx9ConfigureERKN7openpal6RSliceE@PLT
	movq	48(%rbx), %rdi
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*16(%rax)
.L313:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L337
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r12d, %eax
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
.L333:
	.cfi_restore_state
	leaq	8(%rdi), %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L315
.L332:
	xorl	%r12d, %r12d
	jmp	.L313
	.p2align 4,,10
	.p2align 3
.L336:
	leaq	8(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L332
	movq	%r12, %rsi
	leaq	.LC6(%rip), %rcx
	movq	%rbp, %rdi
	xorl	%r12d, %r12d
	leaq	.LC7(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L313
	.p2align 4,,10
	.p2align 3
.L315:
	leaq	.LC0(%rip), %rcx
	leaq	.LC1(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L313
	.p2align 4,,10
	.p2align 3
.L334:
	leaq	8(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L332
	movq	%r12, %rsi
	leaq	.LC2(%rip), %rcx
	movq	%rbp, %rdi
	xorl	%r12d, %r12d
	leaq	.LC3(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L313
	.p2align 4,,10
	.p2align 3
.L335:
	leaq	8(%rdi), %rbp
	leaq	4(%rsp), %r12
	movl	$2, 4(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L332
	leaq	.LC4(%rip), %rcx
	leaq	.LC5(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L332
.L337:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2991:
	.size	_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE, .-_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.section	.rodata.str1.1
.LC9:
	.string	"Layer already online"
	.section	.rodata.str1.8
	.align 8
.LC10:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(150)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv
	.type	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv, @function
_ZN8opendnp314TransportLayer14OnLowerLayerUpEv:
.LFB2304:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	subq	$40, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpb	$0, 64(%rdi)
	jne	.L368
	movb	$1, 64(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L364
	movq	(%rdi), %rax
	leaq	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv.localalias(%rip), %rdx
	movq	16(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L342
	cmpb	$0, 64(%rdi)
	jne	.L367
	movb	$1, 64(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L364
	movq	(%rdi), %rdx
	movq	16(%rdx), %rdx
	cmpq	%rax, %rdx
	jne	.L345
	cmpb	$0, 64(%rdi)
	jne	.L367
	movb	$1, 64(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L364
	movq	(%rdi), %rax
	call	*16(%rax)
	movl	$1, %eax
	jmp	.L338
	.p2align 4,,10
	.p2align 3
.L342:
	call	*%rax
	.p2align 4,,10
	.p2align 3
.L364:
	movl	$1, %eax
.L338:
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L369
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L368:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	leaq	20(%rsp), %r12
	movl	$2, 20(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L338
	leaq	.LC9(%rip), %rcx
	leaq	.LC10(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movl	$2, 20(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	xorl	%eax, %eax
	jmp	.L338
	.p2align 4,,10
	.p2align 3
.L367:
	leaq	16(%rdi), %rbp
	leaq	20(%rsp), %r12
	movl	$2, 20(%rsp)
	movq	%r12, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L364
	leaq	.LC9(%rip), %rcx
	leaq	.LC10(%rip), %rdx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movb	%al, 15(%rsp)
	movl	$2, 20(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	movzbl	15(%rsp), %eax
	jmp	.L338
	.p2align 4,,10
	.p2align 3
.L345:
	call	*%rdx
	movl	$1, %eax
	jmp	.L338
.L369:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2304:
	.size	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv, .-_ZN8opendnp314TransportLayer14OnLowerLayerUpEv
	.set	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv.localalias,_ZN8opendnp314TransportLayer14OnLowerLayerUpEv
	.section	.rodata.str1.1
.LC11:
	.string	"Layer already offline"
	.section	.rodata.str1.8
	.align 8
.LC12:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(166)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv
	.type	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv, @function
_ZN8opendnp314TransportLayer16OnLowerLayerDownEv:
.LFB2305:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movzbl	64(%rdi), %r12d
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%r12b, %r12b
	je	.L400
	xorl	%ecx, %ecx
	leaq	72(%rdi), %rdi
	movw	%cx, -8(%rdi)
	call	_ZN8opendnp311TransportRx5ResetEv@PLT
	movq	48(%rbp), %rbp
	testq	%rbp, %rbp
	je	.L370
	movq	0(%rbp), %rax
	movq	24(%rax), %rbx
	leaq	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv.localalias(%rip), %rax
	cmpq	%rax, %rbx
	jne	.L374
	movzbl	64(%rbp), %r13d
	testb	%r13b, %r13b
	je	.L399
	xorl	%edx, %edx
	leaq	72(%rbp), %rdi
	movw	%dx, 64(%rbp)
	call	_ZN8opendnp311TransportRx5ResetEv@PLT
	movq	48(%rbp), %rbp
	testq	%rbp, %rbp
	je	.L370
	movq	0(%rbp), %rax
	movq	24(%rax), %rax
	cmpq	%rbx, %rax
	jne	.L377
	movzbl	64(%rbp), %ebx
	testb	%bl, %bl
	je	.L399
	xorl	%eax, %eax
	leaq	72(%rbp), %rdi
	movw	%ax, 64(%rbp)
	call	_ZN8opendnp311TransportRx5ResetEv@PLT
	movq	48(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L370
	movq	(%rdi), %rax
	movl	%ebx, %r12d
	call	*24(%rax)
	.p2align 4,,10
	.p2align 3
.L370:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L401
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r12d, %eax
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
.L400:
	.cfi_restore_state
	addq	$16, %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L370
	leaq	.LC11(%rip), %rcx
	leaq	.LC12(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L399:
	addq	$16, %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	movl	%eax, %ebx
	testb	%al, %al
	je	.L370
	leaq	.LC11(%rip), %rcx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	%ebx, %r12d
	leaq	.LC12(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L374:
	movq	%rbp, %rdi
	call	*%rbx
	jmp	.L370
	.p2align 4,,10
	.p2align 3
.L377:
	movq	%rbp, %rdi
	movl	%r13d, %r12d
	call	*%rax
	jmp	.L370
.L401:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2305:
	.size	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv, .-_ZN8opendnp314TransportLayer16OnLowerLayerDownEv
	.set	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv.localalias,_ZN8opendnp314TransportLayer16OnLowerLayerDownEv
	.section	.rodata.str1.8
	.align 8
.LC13:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(109)"
	.section	.rodata.str1.1
.LC14:
	.string	"Invalid send callback"
	.section	.rodata.str1.8
	.align 8
.LC15:
	.string	"/home/master/projects/Procont_EE/utils/dnp3_src/cpp/libs/src/opendnp3/transport/TransportLayer.cpp(115)"
	.text
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer12OnSendResultEb
	.type	_ZN8opendnp314TransportLayer12OnSendResultEb, @function
_ZN8opendnp314TransportLayer12OnSendResultEb:
.LFB2300:
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 64
	movzbl	64(%rdi), %r12d
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testb	%r12b, %r12b
	je	.L445
	movzbl	65(%rdi), %r12d
	testb	%r12b, %r12b
	je	.L446
	movb	$0, 65(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L402
	movq	(%rdi), %rax
	leaq	_ZN8opendnp314TransportLayer12OnSendResultEb.localalias(%rip), %rdx
	movzbl	%sil, %esi
	movq	40(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L409
	cmpb	$0, 64(%rdi)
	je	.L442
	movzbl	65(%rdi), %ebp
	testb	%bpl, %bpl
	je	.L444
	movb	$0, 65(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L402
	movq	(%rdi), %rdx
	movq	40(%rdx), %rdx
	cmpq	%rax, %rdx
	jne	.L413
	cmpb	$0, 64(%rdi)
	je	.L442
	movzbl	65(%rdi), %ebp
	testb	%bpl, %bpl
	je	.L444
	movb	$0, 65(%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L402
	movq	(%rdi), %rax
	movl	%ebp, %r12d
	call	*40(%rax)
	.p2align 4,,10
	.p2align 3
.L402:
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L447
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	movl	%r12d, %eax
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
.L445:
	.cfi_restore_state
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	jne	.L404
.L407:
	xorl	%r12d, %r12d
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L404:
	leaq	.LC0(%rip), %rcx
	leaq	.LC13(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L446:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r13
	movl	$2, 4(%rsp)
	movq	%r13, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	testb	%al, %al
	je	.L407
	leaq	.LC14(%rip), %rcx
	leaq	.LC15(%rip), %rdx
	movq	%r13, %rsi
	movq	%rbp, %rdi
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L442:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r14
	movl	$2, 4(%rsp)
	movq	%r14, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	movl	%eax, %r13d
	testb	%al, %al
	je	.L402
	leaq	.LC0(%rip), %rcx
	movq	%r14, %rsi
	movq	%rbp, %rdi
	movl	%r13d, %r12d
	leaq	.LC13(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L409:
	call	*%rax
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L444:
	leaq	16(%rdi), %rbp
	leaq	4(%rsp), %r14
	movl	$2, 4(%rsp)
	movq	%r14, %rsi
	movq	%rbp, %rdi
	call	_ZNK7openpal6Logger9IsEnabledERKNS_10LogFiltersE@PLT
	movl	%eax, %r13d
	testb	%al, %al
	je	.L402
	leaq	.LC14(%rip), %rcx
	movq	%r14, %rsi
	movq	%rbp, %rdi
	movl	%r13d, %r12d
	leaq	.LC15(%rip), %rdx
	movl	$2, 4(%rsp)
	call	_ZN7openpal6Logger3LogERKNS_10LogFiltersEPKcS5_@PLT
	jmp	.L402
	.p2align 4,,10
	.p2align 3
.L413:
	call	*%rdx
	movl	%ebp, %r12d
	jmp	.L402
.L447:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2300:
	.size	_ZN8opendnp314TransportLayer12OnSendResultEb, .-_ZN8opendnp314TransportLayer12OnSendResultEb
	.set	_ZN8opendnp314TransportLayer12OnSendResultEb.localalias,_ZN8opendnp314TransportLayer12OnSendResultEb
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
	je	.L450
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L464
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L452:
	cmpl	$1, %eax
	je	.L465
.L450:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L448
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L466
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L459:
	cmpl	$1, %eax
	je	.L467
.L448:
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
.L465:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L468
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L455:
	cmpl	$1, %eax
	jne	.L450
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L450
	.p2align 4,,10
	.p2align 3
.L467:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L469
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L462:
	cmpl	$1, %eax
	jne	.L448
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
.L464:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L452
	.p2align 4,,10
	.p2align 3
.L466:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L459
	.p2align 4,,10
	.p2align 3
.L468:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L455
	.p2align 4,,10
	.p2align 3
.L469:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L462
	.cfi_endproc
.LFE2091:
	.size	_ZN7openpal6LoggerD2Ev, .-_ZN7openpal6LoggerD2Ev
	.weak	_ZN7openpal6LoggerD1Ev
	.set	_ZN7openpal6LoggerD1Ev,_ZN7openpal6LoggerD2Ev
	.section	.text._ZN8opendnp311TransportRxD2Ev,"axG",@progbits,_ZN8opendnp311TransportRxD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8opendnp311TransportRxD2Ev
	.type	_ZN8opendnp311TransportRxD2Ev, @function
_ZN8opendnp311TransportRxD2Ev:
.LFB2294:
	.cfi_startproc
	movq	_ZTVN7openpal5ArrayIhjEE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rax, 56(%rdi)
	movq	72(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L471
	call	_ZdaPv@PLT
.L471:
	movq	24(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L473
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L490
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L475:
	cmpl	$1, %eax
	je	.L491
.L473:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L470
	movq	_ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip), %r12
	testq	%r12, %r12
	jne	.L492
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L482:
	cmpl	$1, %eax
	je	.L493
.L470:
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
.L491:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L494
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L478:
	cmpl	$1, %eax
	jne	.L473
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L473
	.p2align 4,,10
	.p2align 3
.L493:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	testq	%r12, %r12
	jne	.L495
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L485:
	cmpl	$1, %eax
	jne	.L470
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
.L490:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L475
	.p2align 4,,10
	.p2align 3
.L492:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L482
	.p2align 4,,10
	.p2align 3
.L494:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L478
	.p2align 4,,10
	.p2align 3
.L495:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L485
	.cfi_endproc
.LFE2294:
	.size	_ZN8opendnp311TransportRxD2Ev, .-_ZN8opendnp311TransportRxD2Ev
	.weak	_ZN8opendnp311TransportRxD1Ev
	.set	_ZN8opendnp311TransportRxD1Ev,_ZN8opendnp311TransportRxD2Ev
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB16:
	.text
.LHOTB16:
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj
	.type	_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj, @function
_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj:
.LFB2296:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2296
	movq	_ZTVN8opendnp314TransportLayerE@GOTPCREL(%rip), %rax
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	leaq	88(%rax), %rcx
	addq	$16, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rax, %xmm0
	movq	(%rsi), %rax
	movq	%rcx, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movq	%rax, 16(%rdi)
	movq	8(%rsi), %rax
	movups	%xmm0, (%rdi)
	movq	%rax, 24(%rdi)
	testq	%rax, %rax
	je	.L497
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L513
	addl	$1, 8(%rax)
.L497:
	movq	16(%rbp), %rax
	movq	%rax, 32(%rbx)
	movq	24(%rbp), %rax
	movq	%rax, 40(%rbx)
	testq	%rax, %rax
	je	.L499
	cmpq	$0, _ZL28__gthrw___pthread_key_createPjPFvPvE@GOTPCREL(%rip)
	jne	.L514
	addl	$1, 8(%rax)
.L499:
	xorl	%eax, %eax
	pxor	%xmm0, %xmm0
	leaq	72(%rbx), %r12
	movq	%rbp, %rsi
	movw	%ax, 64(%rbx)
	movq	%r12, %rdi
	movups	%xmm0, 48(%rbx)
.LEHB0:
	call	_ZN8opendnp311TransportRxC1ERKN7openpal6LoggerEj@PLT
.LEHE0:
	leaq	160(%rbx), %rdi
	movq	%rbp, %rsi
.LEHB1:
	call	_ZN8opendnp311TransportTxC1ERKN7openpal6LoggerE@PLT
.LEHE1:
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
.L513:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	jmp	.L497
	.p2align 4,,10
	.p2align 3
.L514:
	lock addl	$1, 8(%rax)
	jmp	.L499
.L503:
	movq	%rax, %rbp
	jmp	.L502
.L504:
	movq	%rax, %rbp
	jmp	.L501
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2296:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2296-.LLSDACSB2296
.LLSDACSB2296:
	.uleb128 .LEHB0-.LFB2296
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L503-.LFB2296
	.uleb128 0
	.uleb128 .LEHB1-.LFB2296
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L504-.LFB2296
	.uleb128 0
.LLSDACSE2296:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC2296
	.type	_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj.cold, @function
_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj.cold:
.LFSB2296:
.L501:
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	%r12, %rdi
	call	_ZN8opendnp311TransportRxD1Ev@PLT
.L502:
	leaq	16(%rbx), %rdi
	call	_ZN7openpal6LoggerD1Ev@PLT
	movq	%rbp, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.LEHE2:
	.cfi_endproc
.LFE2296:
	.section	.gcc_except_table
.LLSDAC2296:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC2296-.LLSDACSBC2296
.LLSDACSBC2296:
	.uleb128 .LEHB2-.LCOLDB16
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSEC2296:
	.section	.text.unlikely
	.text
	.size	_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj, .-_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj
	.section	.text.unlikely
	.size	_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj.cold, .-_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj.cold
.LCOLDE16:
	.text
.LHOTE16:
	.globl	_ZN8opendnp314TransportLayerC1ERKN7openpal6LoggerEj
	.set	_ZN8opendnp314TransportLayerC1ERKN7openpal6LoggerEj,_ZN8opendnp314TransportLayerC2ERKN7openpal6LoggerEj
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer11SetAppLayerERNS_11IUpperLayerE
	.type	_ZN8opendnp314TransportLayer11SetAppLayerERNS_11IUpperLayerE, @function
_ZN8opendnp314TransportLayer11SetAppLayerERNS_11IUpperLayerE:
.LFB2301:
	.cfi_startproc
	movq	%rsi, 48(%rdi)
	ret
	.cfi_endproc
.LFE2301:
	.size	_ZN8opendnp314TransportLayer11SetAppLayerERNS_11IUpperLayerE, .-_ZN8opendnp314TransportLayer11SetAppLayerERNS_11IUpperLayerE
	.align 2
	.p2align 4
	.globl	_ZN8opendnp314TransportLayer12SetLinkLayerERNS_10ILinkLayerE
	.type	_ZN8opendnp314TransportLayer12SetLinkLayerERNS_10ILinkLayerE, @function
_ZN8opendnp314TransportLayer12SetLinkLayerERNS_10ILinkLayerE:
.LFB2302:
	.cfi_startproc
	movq	%rsi, 56(%rdi)
	ret
	.cfi_endproc
.LFE2302:
	.size	_ZN8opendnp314TransportLayer12SetLinkLayerERNS_10ILinkLayerE, .-_ZN8opendnp314TransportLayer12SetLinkLayerERNS_10ILinkLayerE
	.align 2
	.p2align 4
	.globl	_ZNK8opendnp314TransportLayer13GetStatisticsEv
	.type	_ZNK8opendnp314TransportLayer13GetStatisticsEv, @function
_ZNK8opendnp314TransportLayer13GetStatisticsEv:
.LFB2303:
	.cfi_startproc
	movl	120(%rsi), %edx
	movdqu	104(%rsi), %xmm0
	movq	%rdi, %rax
	movl	%edx, 16(%rdi)
	movl	504(%rsi), %edx
	movups	%xmm0, (%rdi)
	movl	%edx, 20(%rdi)
	ret
	.cfi_endproc
.LFE2303:
	.size	_ZNK8opendnp314TransportLayer13GetStatisticsEv, .-_ZNK8opendnp314TransportLayer13GetStatisticsEv
	.weak	_ZTSN7openpal7HasSizeIjEE
	.section	.rodata._ZTSN7openpal7HasSizeIjEE,"aG",@progbits,_ZTSN7openpal7HasSizeIjEE,comdat
	.align 16
	.type	_ZTSN7openpal7HasSizeIjEE, @object
	.size	_ZTSN7openpal7HasSizeIjEE, 22
_ZTSN7openpal7HasSizeIjEE:
	.string	"N7openpal7HasSizeIjEE"
	.weak	_ZTIN7openpal7HasSizeIjEE
	.section	.data.rel.ro._ZTIN7openpal7HasSizeIjEE,"awG",@progbits,_ZTIN7openpal7HasSizeIjEE,comdat
	.align 8
	.type	_ZTIN7openpal7HasSizeIjEE, @object
	.size	_ZTIN7openpal7HasSizeIjEE, 16
_ZTIN7openpal7HasSizeIjEE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN7openpal7HasSizeIjEE
	.weak	_ZTSN7openpal5ArrayIhjEE
	.section	.rodata._ZTSN7openpal5ArrayIhjEE,"aG",@progbits,_ZTSN7openpal5ArrayIhjEE,comdat
	.align 16
	.type	_ZTSN7openpal5ArrayIhjEE, @object
	.size	_ZTSN7openpal5ArrayIhjEE, 21
_ZTSN7openpal5ArrayIhjEE:
	.string	"N7openpal5ArrayIhjEE"
	.weak	_ZTIN7openpal5ArrayIhjEE
	.section	.data.rel.ro._ZTIN7openpal5ArrayIhjEE,"awG",@progbits,_ZTIN7openpal5ArrayIhjEE,comdat
	.align 8
	.type	_ZTIN7openpal5ArrayIhjEE, @object
	.size	_ZTIN7openpal5ArrayIhjEE, 40
_ZTIN7openpal5ArrayIhjEE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN7openpal5ArrayIhjEE
	.long	0
	.long	1
	.quad	_ZTIN7openpal7HasSizeIjEE
	.quad	2050
	.weak	_ZTSN8opendnp37IUpDownE
	.section	.rodata._ZTSN8opendnp37IUpDownE,"aG",@progbits,_ZTSN8opendnp37IUpDownE,comdat
	.align 16
	.type	_ZTSN8opendnp37IUpDownE, @object
	.size	_ZTSN8opendnp37IUpDownE, 20
_ZTSN8opendnp37IUpDownE:
	.string	"N8opendnp37IUpDownE"
	.weak	_ZTIN8opendnp37IUpDownE
	.section	.data.rel.ro._ZTIN8opendnp37IUpDownE,"awG",@progbits,_ZTIN8opendnp37IUpDownE,comdat
	.align 8
	.type	_ZTIN8opendnp37IUpDownE, @object
	.size	_ZTIN8opendnp37IUpDownE, 16
_ZTIN8opendnp37IUpDownE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp37IUpDownE
	.weak	_ZTSN8opendnp311IUpperLayerE
	.section	.rodata._ZTSN8opendnp311IUpperLayerE,"aG",@progbits,_ZTSN8opendnp311IUpperLayerE,comdat
	.align 16
	.type	_ZTSN8opendnp311IUpperLayerE, @object
	.size	_ZTSN8opendnp311IUpperLayerE, 25
_ZTSN8opendnp311IUpperLayerE:
	.string	"N8opendnp311IUpperLayerE"
	.weak	_ZTIN8opendnp311IUpperLayerE
	.section	.data.rel.ro._ZTIN8opendnp311IUpperLayerE,"awG",@progbits,_ZTIN8opendnp311IUpperLayerE,comdat
	.align 8
	.type	_ZTIN8opendnp311IUpperLayerE, @object
	.size	_ZTIN8opendnp311IUpperLayerE, 24
_ZTIN8opendnp311IUpperLayerE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8opendnp311IUpperLayerE
	.quad	_ZTIN8opendnp37IUpDownE
	.weak	_ZTSN8opendnp311ILowerLayerE
	.section	.rodata._ZTSN8opendnp311ILowerLayerE,"aG",@progbits,_ZTSN8opendnp311ILowerLayerE,comdat
	.align 16
	.type	_ZTSN8opendnp311ILowerLayerE, @object
	.size	_ZTSN8opendnp311ILowerLayerE, 25
_ZTSN8opendnp311ILowerLayerE:
	.string	"N8opendnp311ILowerLayerE"
	.weak	_ZTIN8opendnp311ILowerLayerE
	.section	.data.rel.ro._ZTIN8opendnp311ILowerLayerE,"awG",@progbits,_ZTIN8opendnp311ILowerLayerE,comdat
	.align 8
	.type	_ZTIN8opendnp311ILowerLayerE, @object
	.size	_ZTIN8opendnp311ILowerLayerE, 16
_ZTIN8opendnp311ILowerLayerE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8opendnp311ILowerLayerE
	.weak	_ZTSN8opendnp314TransportLayerE
	.section	.rodata._ZTSN8opendnp314TransportLayerE,"aG",@progbits,_ZTSN8opendnp314TransportLayerE,comdat
	.align 16
	.type	_ZTSN8opendnp314TransportLayerE, @object
	.size	_ZTSN8opendnp314TransportLayerE, 28
_ZTSN8opendnp314TransportLayerE:
	.string	"N8opendnp314TransportLayerE"
	.weak	_ZTIN8opendnp314TransportLayerE
	.section	.data.rel.ro._ZTIN8opendnp314TransportLayerE,"awG",@progbits,_ZTIN8opendnp314TransportLayerE,comdat
	.align 8
	.type	_ZTIN8opendnp314TransportLayerE, @object
	.size	_ZTIN8opendnp314TransportLayerE, 56
_ZTIN8opendnp314TransportLayerE:
	.quad	_ZTVN10__cxxabiv121__vmi_class_type_infoE+16
	.quad	_ZTSN8opendnp314TransportLayerE
	.long	0
	.long	2
	.quad	_ZTIN8opendnp311IUpperLayerE
	.quad	2
	.quad	_ZTIN8opendnp311ILowerLayerE
	.quad	2050
	.weak	_ZTVN7openpal5ArrayIhjEE
	.section	.data.rel.ro._ZTVN7openpal5ArrayIhjEE,"awG",@progbits,_ZTVN7openpal5ArrayIhjEE,comdat
	.align 8
	.type	_ZTVN7openpal5ArrayIhjEE, @object
	.size	_ZTVN7openpal5ArrayIhjEE, 32
_ZTVN7openpal5ArrayIhjEE:
	.quad	0
	.quad	_ZTIN7openpal5ArrayIhjEE
	.quad	_ZN7openpal5ArrayIhjED1Ev
	.quad	_ZN7openpal5ArrayIhjED0Ev
	.weak	_ZTVN8opendnp314TransportLayerE
	.section	.data.rel.ro._ZTVN8opendnp314TransportLayerE,"awG",@progbits,_ZTVN8opendnp314TransportLayerE,comdat
	.align 8
	.type	_ZTVN8opendnp314TransportLayerE, @object
	.size	_ZTVN8opendnp314TransportLayerE, 112
_ZTVN8opendnp314TransportLayerE:
	.quad	0
	.quad	_ZTIN8opendnp314TransportLayerE
	.quad	_ZN8opendnp314TransportLayerD1Ev
	.quad	_ZN8opendnp314TransportLayerD0Ev
	.quad	_ZN8opendnp314TransportLayer14OnLowerLayerUpEv
	.quad	_ZN8opendnp314TransportLayer16OnLowerLayerDownEv
	.quad	_ZN8opendnp314TransportLayer9OnReceiveERKN7openpal6RSliceE
	.quad	_ZN8opendnp314TransportLayer12OnSendResultEb
	.quad	_ZN8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.quad	-8
	.quad	_ZTIN8opendnp314TransportLayerE
	.quad	_ZThn8_N8opendnp314TransportLayerD1Ev
	.quad	_ZThn8_N8opendnp314TransportLayerD0Ev
	.quad	_ZThn8_N8opendnp314TransportLayer13BeginTransmitERKN7openpal6RSliceE
	.weakref	_ZL28__gthrw___pthread_key_createPjPFvPvE,__pthread_key_create
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
