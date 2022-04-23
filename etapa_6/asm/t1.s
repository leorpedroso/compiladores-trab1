	.file	"t1.c"
	.text
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	1
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	2
	.globl	x
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	3
	.comm	c,8,8
	.section	.rodata
.LC0:
	.string	"\n"
.LC1:
	.string	"%s"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	
	leaq	.LC0(%rip), %rax
	movq	%rax, c(%rip)
	movq	c(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
	