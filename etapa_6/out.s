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

## TAC_COPY
 movl  _5(%rip), %edx
 movl  %edx, _a(%rip)

## TAC_COPY
 movl  _777(%rip), %edx
 movl  %edx, _b(%rip)

## TAC_DIV
 movl	_99(%rip), %eax
 movl	_a(%rip), %ecx
 cltd
 idivl	%ecx
 movl	%eax, _MyTempThisMustBeUnique0(%rip)

## TAC_COPY
 movl  _MyTempThisMustBeUnique0(%rip), %edx
 movl  %edx, _x(%rip)

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
_5:	.long	5
_a:	.long	0
_b:	.long	0
_x:	.long	0
_MyTempThisMustBeUnique0:	.long	0
_99:	.long	99
_777:	.long	777
