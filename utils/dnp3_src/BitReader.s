	.file	"BitReader.cpp"
	.text
	.p2align 4
	.globl	_ZN8opendnp314NumBytesInBitsEj
	.type	_ZN8opendnp314NumBytesInBitsEj, @function
_ZN8opendnp314NumBytesInBitsEj:
.LFB78:
	.cfi_startproc
	movl	%edi, %eax
	andl	$7, %edi
	shrl	$3, %eax
	cmpl	$1, %edi
	sbbl	$-1, %eax
	ret
	.cfi_endproc
.LFE78:
	.size	_ZN8opendnp314NumBytesInBitsEj, .-_ZN8opendnp314NumBytesInBitsEj
	.p2align 4
	.globl	_ZN8opendnp36GetBitERKN7openpal6RSliceEj
	.type	_ZN8opendnp36GetBitERKN7openpal6RSliceEj, @function
_ZN8opendnp36GetBitERKN7openpal6RSliceEj:
.LFB79:
	.cfi_startproc
	movq	8(%rdi), %rdx
	movl	%esi, %eax
	movl	%esi, %ecx
	shrl	$3, %eax
	andl	$7, %ecx
	movzbl	(%rdx,%rax), %eax
	sarl	%cl, %eax
	andl	$1, %eax
	ret
	.cfi_endproc
.LFE79:
	.size	_ZN8opendnp36GetBitERKN7openpal6RSliceEj, .-_ZN8opendnp36GetBitERKN7openpal6RSliceEj
	.p2align 4
	.globl	_ZN8opendnp320NumBytesInDoubleBitsEj
	.type	_ZN8opendnp320NumBytesInDoubleBitsEj, @function
_ZN8opendnp320NumBytesInDoubleBitsEj:
.LFB80:
	.cfi_startproc
	movl	%edi, %eax
	andl	$3, %edi
	shrl	$2, %eax
	cmpl	$1, %edi
	sbbl	$-1, %eax
	ret
	.cfi_endproc
.LFE80:
	.size	_ZN8opendnp320NumBytesInDoubleBitsEj, .-_ZN8opendnp320NumBytesInDoubleBitsEj
	.p2align 4
	.globl	_ZN8opendnp312GetDoubleBitERKN7openpal6RSliceEj
	.type	_ZN8opendnp312GetDoubleBitERKN7openpal6RSliceEj, @function
_ZN8opendnp312GetDoubleBitERKN7openpal6RSliceEj:
.LFB81:
	.cfi_startproc
	movl	%esi, %eax
	movq	8(%rdi), %rdx
	andl	$3, %esi
	shrl	$2, %eax
	leal	(%rsi,%rsi), %ecx
	movzbl	(%rdx,%rax), %edi
	sarl	%cl, %edi
	andl	$3, %edi
	jmp	_ZN8opendnp317DoubleBitFromTypeEh@PLT
	.cfi_endproc
.LFE81:
	.size	_ZN8opendnp312GetDoubleBitERKN7openpal6RSliceEj, .-_ZN8opendnp312GetDoubleBitERKN7openpal6RSliceEj
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
