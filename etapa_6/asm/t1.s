	.file	"t1.c"
	.text
	.globl	a1
	.data
	.align 4
	.type	a1, @object
	.size	a1, 4
a1:
	.long	1
	.globl	b1
	.align 4
	.type	b1, @object
	.size	b1, 4
b1:
	.long	2
	.globl	c1
	.align 4
	.type	c1, @object
	.size	c1, 4
c1:
	.long	3
	.globl	d1
	.align 4
	.type	d1, @object
	.size	d1, 4
d1:
	.long	4
	.globl	e1
	.align 4
	.type	e1, @object
	.size	e1, 4
e1:
	.long	5
	.globl	f1
	.align 4
	.type	f1, @object
	.size	f1, 4
f1:
	.long	6
	.globl	g1
	.align 4
	.type	g1, @object
	.size	g1, 4
g1:
	.long	7
	.globl	h1
	.align 4
	.type	h1, @object
	.size	h1, 4
h1:
	.long	8
	.globl	i1
	.align 4
	.type	i1, @object
	.size	i1, 4
i1:
	.long	9
	.text
	.globl	fun
	.type	fun, @function
fun:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	cmpl	$1, -8(%rbp)
	jle	.L2
	movl	$300, %eax
	jmp	.L3
.L2:
	movl	$700, %eax
.L3:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fun, .-fun
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	h1(%rip), %r8d
	movl	g1(%rip), %edi
	movl	f1(%rip), %r9d
	movl	e1(%rip), %r10d
	movl	d1(%rip), %ecx
	movl	c1(%rip), %edx
	movl	b1(%rip), %esi
	movl	a1(%rip), %eax
	pushq	%r8
	pushq	%rdi
	movl	%r10d, %r8d
	movl	%eax, %edi
	call	fun
	addq	$16, %rsp
	movl	%eax, a1(%rip)
	movl	a1(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
