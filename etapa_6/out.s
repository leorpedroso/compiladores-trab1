## FIXED INIT
  .section	.rodata
  .text
  print_int: .string "%d"
  print_str: .string "%s"

## TAC_BEGINFUN
  .globl	main
  .type	main, @function
main:
  pushq	%rbp
  movq	%rsp, %rbp

## TAC_PRINT_INT
  movl	_a(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_PRINT_STR
	leaq	_.str0(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_PRINT_STR
	leaq	_.str1(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_PRINT_STR
	leaq	_.str0(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_PRINT_INT
  movl	_x(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_ENDFUN
  popq	%rbp
  ret

## DATA SECTION
	.data

_1:	.long	1
_2:	.long	2
_3:	.long	3
_.str0:	.string	"garuda"
_.str1:	.string	"\n"
_a:	.long	1
_b:	.long	2
_x:	.long	3
