	.file	"SingleFloat.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7openpal11SingleFloat4ReadEPKh
	.type	_ZN7openpal11SingleFloat4ReadEPKh, @function
_ZN7openpal11SingleFloat4ReadEPKh:
.LFB44:
	.cfi_startproc
	movq	_ZN7openpal14FloatByteOrder5ORDERE@GOTPCREL(%rip), %rax
	movzbl	3(%rdi), %r8d
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movzbl	1(%rdi), %ecx
	movzbl	2(%rdi), %ebx
	cmpb	$0, (%rax)
	movzbl	(%rdi), %esi
	jne	.L2
	sall	$16, %ebx
	xorl	%edx, %edx
	sall	$24, %r8d
	movb	%sil, %dl
	movb	%cl, %dh
	movzwl	%dx, %edx
	orl	%ebx, %edx
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	orl	%r8d, %edx
	movd	%edx, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	.cfi_restore_state
	sall	$16, %ecx
	xorl	%eax, %eax
	sall	$24, %esi
	movb	%r8b, %al
	movb	%bl, %ah
	popq	%rbx
	.cfi_def_cfa_offset 8
	movzwl	%ax, %eax
	orl	%ecx, %eax
	orl	%esi, %eax
	movd	%eax, %xmm0
	ret
	.cfi_endproc
.LFE44:
	.size	_ZN7openpal11SingleFloat4ReadEPKh, .-_ZN7openpal11SingleFloat4ReadEPKh
	.align 2
	.p2align 4
	.globl	_ZN7openpal11SingleFloat10ReadBufferERNS_6RSliceE
	.type	_ZN7openpal11SingleFloat10ReadBufferERNS_6RSliceE, @function
_ZN7openpal11SingleFloat10ReadBufferERNS_6RSliceE:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rdi), %rdi
	call	_ZN7openpal11SingleFloat4ReadEPKh@PLT
	movq	%rbp, %rdi
	movl	$4, %esi
	movss	%xmm0, 12(%rsp)
	call	_ZN7openpal6RSlice7AdvanceEj@PLT
	movss	12(%rsp), %xmm0
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE42:
	.size	_ZN7openpal11SingleFloat10ReadBufferERNS_6RSliceE, .-_ZN7openpal11SingleFloat10ReadBufferERNS_6RSliceE
	.align 2
	.p2align 4
	.globl	_ZN7openpal11SingleFloat5WriteEPhf
	.type	_ZN7openpal11SingleFloat5WriteEPhf, @function
_ZN7openpal11SingleFloat5WriteEPhf:
.LFB45:
	.cfi_startproc
	movq	_ZN7openpal14FloatByteOrder5ORDERE@GOTPCREL(%rip), %rdx
	movd	%xmm0, %eax
	cmpb	$0, (%rdx)
	je	.L11
	movd	%xmm0, %ecx
	xorl	%edx, %edx
	shrl	$24, %ecx
	movb	%cl, %dl
	movd	%xmm0, %ecx
	shrl	$16, %ecx
	movb	%cl, %dh
	movzbl	%ah, %ecx
	sall	$24, %eax
	sall	$16, %ecx
	movzwl	%dx, %edx
	orl	%ecx, %edx
	orl	%edx, %eax
.L11:
	movl	%eax, (%rdi)
	ret
	.cfi_endproc
.LFE45:
	.size	_ZN7openpal11SingleFloat5WriteEPhf, .-_ZN7openpal11SingleFloat5WriteEPhf
	.align 2
	.p2align 4
	.globl	_ZN7openpal11SingleFloat11WriteBufferERNS_6WSliceEf
	.type	_ZN7openpal11SingleFloat11WriteBufferERNS_6WSliceEf, @function
_ZN7openpal11SingleFloat11WriteBufferERNS_6WSliceEf:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	movq	8(%rdi), %rdi
	call	_ZN7openpal11SingleFloat5WriteEPhf@PLT
	movq	%rbp, %rdi
	movl	$4, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZN7openpal6WSlice7AdvanceEj@PLT
	.cfi_endproc
.LFE43:
	.size	_ZN7openpal11SingleFloat11WriteBufferERNS_6WSliceEf, .-_ZN7openpal11SingleFloat11WriteBufferERNS_6WSliceEf
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I_SingleFloat.cpp, @function
_GLOBAL__sub_I_SingleFloat.cpp:
.LFB47:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	_ZN7openpal8MaxValueIfEET_v@PLT
	movq	_ZN7openpal11SingleFloat3MaxE@GOTPCREL(%rip), %rax
	movss	%xmm0, (%rax)
	call	_ZN7openpal8MinValueIfEET_v@PLT
	movq	_ZN7openpal11SingleFloat3MinE@GOTPCREL(%rip), %rax
	movss	%xmm0, (%rax)
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE47:
	.size	_GLOBAL__sub_I_SingleFloat.cpp, .-_GLOBAL__sub_I_SingleFloat.cpp
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_SingleFloat.cpp
	.globl	_ZN7openpal11SingleFloat3MinE
	.bss
	.align 4
	.type	_ZN7openpal11SingleFloat3MinE, @object
	.size	_ZN7openpal11SingleFloat3MinE, 4
_ZN7openpal11SingleFloat3MinE:
	.zero	4
	.globl	_ZN7openpal11SingleFloat3MaxE
	.align 4
	.type	_ZN7openpal11SingleFloat3MaxE, @object
	.size	_ZN7openpal11SingleFloat3MaxE, 4
_ZN7openpal11SingleFloat3MaxE:
	.zero	4
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
