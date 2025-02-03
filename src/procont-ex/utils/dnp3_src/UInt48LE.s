	.file	"UInt48LE.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN7openpal8UInt48LE4ReadEPKh
	.type	_ZN7openpal8UInt48LE4ReadEPKh, @function
_ZN7openpal8UInt48LE4ReadEPKh:
.LFB45:
	.cfi_startproc
	movzbl	4(%rdi), %eax
	movzbl	5(%rdi), %edx
	salq	$32, %rax
	salq	$40, %rdx
	orq	%rdx, %rax
	movl	(%rdi), %edx
	orq	%rdx, %rax
	ret
	.cfi_endproc
.LFE45:
	.size	_ZN7openpal8UInt48LE4ReadEPKh, .-_ZN7openpal8UInt48LE4ReadEPKh
	.align 2
	.p2align 4
	.globl	_ZN7openpal8UInt48LE5WriteEPhNS_10UInt48TypeE
	.type	_ZN7openpal8UInt48LE5WriteEPhNS_10UInt48TypeE, @function
_ZN7openpal8UInt48LE5WriteEPhNS_10UInt48TypeE:
.LFB46:
	.cfi_startproc
	movabsq	$281474976710655, %rax
	cmpq	%rax, %rsi
	cmovg	%rax, %rsi
	movq	%rsi, %rax
	movl	%esi, (%rdi)
	sarq	$40, %rsi
	sarq	$32, %rax
	movb	%sil, 5(%rdi)
	movb	%al, 4(%rdi)
	ret
	.cfi_endproc
.LFE46:
	.size	_ZN7openpal8UInt48LE5WriteEPhNS_10UInt48TypeE, .-_ZN7openpal8UInt48LE5WriteEPhNS_10UInt48TypeE
	.ident	"GCC: (GNU) 10.3.1 20210703 (ALT Sisyphus 10.3.1-alt2)"
	.section	.note.GNU-stack,"",@progbits
