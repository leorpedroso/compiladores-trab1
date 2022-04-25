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
	pushq	%rbp
	movq	%rsp, %rbp
	
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	%r8d, -20(%rbp)
	movl	%r9d, -24(%rbp)
	movl	16(%rbp), %edx
	movl	24(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	nop
	popq	%rbp
	ret
	
.LFE0:
	.size	fun, .-fun
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	
	movl	i1(%rip), %r9d
	movl	h1(%rip), %r8d
	movl	g1(%rip), %edi
	movl	f1(%rip), %r11d
	movl	e1(%rip), %r10d
	movl	d1(%rip), %ecx
	movl	c1(%rip), %edx
	movl	b1(%rip), %esi
	movl	a1(%rip), %eax
	pushq	%r9
	pushq	%r8
	pushq	%rdi
	movl	%r11d, %r9d
	movl	%r10d, %r8d
	movl	%eax, %edi
	call	fun
	addq	$24, %rsp
	movl	$0, %eax

	leave
	ret
	