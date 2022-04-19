## FIXED INIT
	.section	.rodata
	.text

	print_int:	.string	"%d"
	print_str: 	.string "%s"

## TAC_BEGINFUN
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp

## TAC_COPY
	movl	_888(%rip), %eax

## TAC_PRINT
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	
## TAC_ENDFUN
	popq	%rbp
	ret

## DATA SECTION
	.data

.LC0:	.string	"%d\n"
a: .long	6
_888: .long 888
