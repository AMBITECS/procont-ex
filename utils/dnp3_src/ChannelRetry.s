	.file	"ChannelRetry.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE
	.type	_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE, @function
_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE:
.LFB18:
	.cfi_startproc
	movq	%rsi, (%rdi)
	movq	%rdx, 8(%rdi)
	movq	%rcx, 16(%rdi)
	ret
	.cfi_endproc
.LFE18:
	.size	_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE, .-_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE
	.globl	_ZN7asiopal12ChannelRetryC1EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE
	.set	_ZN7asiopal12ChannelRetryC1EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE,_ZN7asiopal12ChannelRetryC2EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE
	.align 2
	.p2align 4
	.globl	_ZN7asiopal12ChannelRetry7DefaultEv
	.type	_ZN7asiopal12ChannelRetry7DefaultEv, @function
_ZN7asiopal12ChannelRetry7DefaultEv:
.LFB20:
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
	movq	%rdi, %r12
	call	_ZN7asiopal26ExponentialBackoffStrategy8InstanceEv@PLT
	movl	$1, %edi
	movq	%rax, %r14
	call	_ZN7openpal12TimeDuration7MinutesEl@PLT
	movl	$1, %edi
	movq	%rax, %r13
	call	_ZN7openpal12TimeDuration7SecondsEl@PLT
	movq	%r14, %rcx
	movq	%r13, %rdx
	movq	%r12, %rdi
	movq	%rax, %rsi
	call	_ZN7asiopal12ChannelRetryC1EN7openpal12TimeDurationES2_RNS_18IOpenDelayStrategyE@PLT
	movq	%r12, %rax
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE20:
	.size	_ZN7asiopal12ChannelRetry7DefaultEv, .-_ZN7asiopal12ChannelRetry7DefaultEv
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
