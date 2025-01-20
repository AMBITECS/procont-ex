	.file	"DoubleFloat.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7openpal11DoubleFloat4ReadEPKh
	.type	_ZN7openpal11DoubleFloat4ReadEPKh, @function
_ZN7openpal11DoubleFloat4ReadEPKh:
.LFB44:
	.cfi_startproc
	movq	_ZN7openpal14FloatByteOrder5ORDERE@GOTPCREL(%rip), %r11
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movzbl	7(%rdi), %ebp
	cmpb	$0, (%r11)
	movzbl	6(%rdi), %edx
	movzbl	5(%rdi), %ecx
	movzbl	4(%rdi), %esi
	movzbl	3(%rdi), %ebx
	movzbl	2(%rdi), %r8d
	movzbl	1(%rdi), %r9d
	movzbl	(%rdi), %r10d
	jne	.L2
	movzbl	%bpl, %eax
	movzbl	%bl, %edi
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	salq	$8, %rax
	orq	%rdx, %rax
	salq	$8, %rax
	orq	%rcx, %rax
	salq	$8, %rax
	orq	%rsi, %rax
	salq	$8, %rax
	orq	%rdi, %rax
	salq	$8, %rax
	orq	%r8, %rax
	salq	$8, %rax
	orq	%r9, %rax
	salq	$8, %rax
	orq	%r10, %rax
	movq	%rax, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	.cfi_restore_state
	movzbl	%r10b, %eax
	movzbl	%bl, %edi
	popq	%rbx
	.cfi_def_cfa_offset 16
	salq	$8, %rax
	orq	%r9, %rax
	salq	$8, %rax
	orq	%r8, %rax
	salq	$8, %rax
	orq	%rdi, %rax
	salq	$8, %rax
	orq	%rsi, %rax
	salq	$8, %rax
	orq	%rcx, %rax
	salq	$8, %rax
	orq	%rdx, %rax
	movzbl	%bpl, %edx
	popq	%rbp
	.cfi_def_cfa_offset 8
	salq	$8, %rax
	orq	%rdx, %rax
	movq	%rax, %xmm0
	ret
	.cfi_endproc
.LFE44:
	.size	_ZN7openpal11DoubleFloat4ReadEPKh, .-_ZN7openpal11DoubleFloat4ReadEPKh
	.align 2
	.p2align 4
	.globl	_ZN7openpal11DoubleFloat10ReadBufferERNS_6RSliceE
	.type	_ZN7openpal11DoubleFloat10ReadBufferERNS_6RSliceE, @function
_ZN7openpal11DoubleFloat10ReadBufferERNS_6RSliceE:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rdi), %rdi
	call	_ZN7openpal11DoubleFloat4ReadEPKh@PLT
	movq	%rbp, %rdi
	movl	$8, %esi
	movsd	%xmm0, 8(%rsp)
	call	_ZN7openpal6RSlice7AdvanceEj@PLT
	movsd	8(%rsp), %xmm0
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE42:
	.size	_ZN7openpal11DoubleFloat10ReadBufferERNS_6RSliceE, .-_ZN7openpal11DoubleFloat10ReadBufferERNS_6RSliceE
	.align 2
	.p2align 4
	.globl	_ZN7openpal11DoubleFloat5WriteEPhd
	.type	_ZN7openpal11DoubleFloat5WriteEPhd, @function
_ZN7openpal11DoubleFloat5WriteEPhd:
.LFB45:
	.cfi_startproc
	movq	_ZN7openpal14FloatByteOrder5ORDERE@GOTPCREL(%rip), %rax
	movq	%xmm0, %rdx
	cmpb	$0, (%rax)
	jne	.L9
	movq	%xmm0, (%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	movzbl	%dl, %eax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%xmm0, %r10
	movzbl	%dh, %ebx
	salq	$8, %rax
	shrq	$16, %r10
	movq	%xmm0, %r9
	movq	%xmm0, %r8
	orq	%rbx, %rax
	movzbl	%r10b, %r10d
	shrq	$24, %r9
	movq	%xmm0, %rsi
	salq	$8, %rax
	movzbl	%r9b, %r9d
	shrq	$32, %r8
	popq	%rbx
	.cfi_def_cfa_offset 8
	orq	%r10, %rax
	movzbl	%r8b, %r8d
	shrq	$40, %rsi
	movq	%xmm0, %rcx
	salq	$8, %rax
	movzbl	%sil, %esi
	shrq	$48, %rcx
	orq	%r9, %rax
	movzbl	%cl, %ecx
	shrq	$56, %rdx
	salq	$8, %rax
	orq	%r8, %rax
	salq	$8, %rax
	orq	%rsi, %rax
	salq	$8, %rax
	orq	%rcx, %rax
	salq	$8, %rax
	orq	%rdx, %rax
	movq	%rax, (%rdi)
	ret
	.cfi_endproc
.LFE45:
	.size	_ZN7openpal11DoubleFloat5WriteEPhd, .-_ZN7openpal11DoubleFloat5WriteEPhd
	.align 2
	.p2align 4
	.globl	_ZN7openpal11DoubleFloat11WriteBufferERNS_6WSliceEd
	.type	_ZN7openpal11DoubleFloat11WriteBufferERNS_6WSliceEd, @function
_ZN7openpal11DoubleFloat11WriteBufferERNS_6WSliceEd:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	movq	8(%rdi), %rdi
	call	_ZN7openpal11DoubleFloat5WriteEPhd@PLT
	movq	%rbp, %rdi
	movl	$8, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN7openpal6WSlice7AdvanceEj@PLT
	.cfi_endproc
.LFE43:
	.size	_ZN7openpal11DoubleFloat11WriteBufferERNS_6WSliceEd, .-_ZN7openpal11DoubleFloat11WriteBufferERNS_6WSliceEd
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_DoubleFloat.cpp, @function
_GLOBAL__sub_I_DoubleFloat.cpp:
.LFB47:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZN7openpal8MaxValueIdEET_v@PLT
	movq	_ZN7openpal11DoubleFloat3MaxE@GOTPCREL(%rip), %rax
	movsd	%xmm0, (%rax)
	call	_ZN7openpal8MinValueIdEET_v@PLT
	movq	_ZN7openpal11DoubleFloat3MinE@GOTPCREL(%rip), %rax
	movsd	%xmm0, (%rax)
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE47:
	.size	_GLOBAL__sub_I_DoubleFloat.cpp, .-_GLOBAL__sub_I_DoubleFloat.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_DoubleFloat.cpp
	.globl	_ZN7openpal11DoubleFloat3MinE
	.bss
	.align 8
	.type	_ZN7openpal11DoubleFloat3MinE, @object
	.size	_ZN7openpal11DoubleFloat3MinE, 8
_ZN7openpal11DoubleFloat3MinE:
	.zero	8
	.globl	_ZN7openpal11DoubleFloat3MaxE
	.align 8
	.type	_ZN7openpal11DoubleFloat3MaxE, @object
	.size	_ZN7openpal11DoubleFloat3MaxE, 8
_ZN7openpal11DoubleFloat3MaxE:
	.zero	8
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
