	.file	"ToHex.cpp"
	.text
	.p2align 4
	.globl	_ZN7openpal9ToHexCharEc
	.type	_ZN7openpal9ToHexCharEc, @function
_ZN7openpal9ToHexCharEc:
.LFB0:
	.cfi_startproc
	leal	55(%rdi), %edx
	leal	48(%rdi), %eax
	cmpb	$10, %dil
	cmovge	%edx, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN7openpal9ToHexCharEc, .-_ZN7openpal9ToHexCharEc
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
