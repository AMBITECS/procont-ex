	.file	"WSlice.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSliceC2Ev
	.type	_ZN7openpal6WSliceC2Ev, @function
_ZN7openpal6WSliceC2Ev:
.LFB43:
	.cfi_startproc
	movl	$0, (%rdi)
	movq	$0, 8(%rdi)
	ret
	.cfi_endproc
.LFE43:
	.size	_ZN7openpal6WSliceC2Ev, .-_ZN7openpal6WSliceC2Ev
	.globl	_ZN7openpal6WSliceC1Ev
	.set	_ZN7openpal6WSliceC1Ev,_ZN7openpal6WSliceC2Ev
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSlice5EmptyEv
	.type	_ZN7openpal6WSlice5EmptyEv, @function
_ZN7openpal6WSlice5EmptyEv:
.LFB41:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_ZN7openpal6WSliceC1Ev@PLT
	movq	(%rsp), %rax
	movq	8(%rsp), %rdx
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L6
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE41:
	.size	_ZN7openpal6WSlice5EmptyEv, .-_ZN7openpal6WSlice5EmptyEv
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSlice8SetAllToEh
	.type	_ZN7openpal6WSlice8SetAllToEh, @function
_ZN7openpal6WSlice8SetAllToEh:
.LFB45:
	.cfi_startproc
	movl	(%rdi), %edx
	movq	8(%rdi), %rdi
	movzbl	%sil, %esi
	jmp	memset@PLT
	.cfi_endproc
.LFE45:
	.size	_ZN7openpal6WSlice8SetAllToEh, .-_ZN7openpal6WSlice8SetAllToEh
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSliceC2EPhj
	.type	_ZN7openpal6WSliceC2EPhj, @function
_ZN7openpal6WSliceC2EPhj:
.LFB47:
	.cfi_startproc
	movl	%edx, (%rdi)
	movq	%rsi, 8(%rdi)
	ret
	.cfi_endproc
.LFE47:
	.size	_ZN7openpal6WSliceC2EPhj, .-_ZN7openpal6WSliceC2EPhj
	.globl	_ZN7openpal6WSliceC1EPhj
	.set	_ZN7openpal6WSliceC1EPhj,_ZN7openpal6WSliceC2EPhj
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSlice5ClearEv
	.type	_ZN7openpal6WSlice5ClearEv, @function
_ZN7openpal6WSlice5ClearEv:
.LFB49:
	.cfi_startproc
	movq	$0, 8(%rdi)
	movl	$0, (%rdi)
	ret
	.cfi_endproc
.LFE49:
	.size	_ZN7openpal6WSlice5ClearEv, .-_ZN7openpal6WSlice5ClearEv
	.align 2
	.p2align 4
	.globl	_ZN7openpal6WSlice7AdvanceEj
	.type	_ZN7openpal6WSlice7AdvanceEj, @function
_ZN7openpal6WSlice7AdvanceEj:
.LFB50:
	.cfi_startproc
	movl	(%rdi), %edx
	movl	%esi, %eax
	cmpl	%esi, %edx
	cmovbe	%edx, %eax
	subl	%eax, %edx
	movl	%eax, %ecx
	addq	%rcx, 8(%rdi)
	movl	%edx, (%rdi)
	ret
	.cfi_endproc
.LFE50:
	.size	_ZN7openpal6WSlice7AdvanceEj, .-_ZN7openpal6WSlice7AdvanceEj
	.align 2
	.p2align 4
	.globl	_ZNK7openpal6WSlice4SkipEj
	.type	_ZNK7openpal6WSlice4SkipEj, @function
_ZNK7openpal6WSlice4SkipEj:
.LFB51:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	(%rdi), %edx
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	cmpl	%esi, %edx
	cmovbe	%edx, %esi
	subl	%esi, %edx
	movl	%esi, %esi
	addq	8(%rdi), %rsi
	movq	%rsp, %rdi
	call	_ZN7openpal6WSliceC1EPhj@PLT
	movq	(%rsp), %rax
	movq	8(%rsp), %rdx
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L14
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L14:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE51:
	.size	_ZNK7openpal6WSlice4SkipEj, .-_ZNK7openpal6WSlice4SkipEj
	.align 2
	.p2align 4
	.globl	_ZNK7openpal6WSlice8ToRSliceEv
	.type	_ZNK7openpal6WSlice8ToRSliceEv, @function
_ZNK7openpal6WSlice8ToRSliceEv:
.LFB52:
	.cfi_startproc
	subq	$40, %rsp
	.cfi_def_cfa_offset 48
	movl	(%rdi), %edx
	movq	8(%rdi), %rsi
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %r8
	movq	%r8, %rdi
	call	_ZN7openpal6RSliceC1EPKhj@PLT
	movq	(%rsp), %rax
	movq	8(%rsp), %rdx
	movq	24(%rsp), %rcx
	subq	%fs:40, %rcx
	jne	.L18
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L18:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE52:
	.size	_ZNK7openpal6WSlice8ToRSliceEv, .-_ZNK7openpal6WSlice8ToRSliceEv
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
