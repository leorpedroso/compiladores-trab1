	.file	"t1.c"
	.text
	.globl	a
	.data
	.align 8
	.type	a, @object
	.size	a, 12
a:
	.long	10
	.long	20
	.long	30
	.globl	b
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.long	1
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.long	100
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp

	movl	b(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, c(%rip)

	movl	c(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
	