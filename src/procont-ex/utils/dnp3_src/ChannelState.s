	.file	"ChannelState.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"SHUTDOWN"
.LC1:
	.string	"OPEN"
.LC2:
	.string	"OPENING"
.LC3:
	.string	"CLOSED"
	.text
	.p2align 4
	.globl	_ZN8opendnp320ChannelStateToStringENS_12ChannelStateE
	.type	_ZN8opendnp320ChannelStateToStringENS_12ChannelStateE, @function
_ZN8opendnp320ChannelStateToStringENS_12ChannelStateE:
.LFB0:
	.cfi_startproc
	leaq	.LC2(%rip), %rax
	cmpb	$1, %dil
	je	.L1
	leaq	.LC1(%rip), %rax
	cmpb	$2, %dil
	je	.L1
	testb	%dil, %dil
	leaq	.LC0(%rip), %rax
	leaq	.LC3(%rip), %rdx
	cmove	%rdx, %rax
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8opendnp320ChannelStateToStringENS_12ChannelStateE, .-_ZN8opendnp320ChannelStateToStringENS_12ChannelStateE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
