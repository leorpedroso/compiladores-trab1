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

MyLabelThisMustBeUnique0:

## TAC_LT
 movl	_a(%rip), %edx
 movl	_3(%rip), %eax
 cmpl	%eax, %edx
 setl	%al
 movzbl	%al, %eax
 movl	%eax, _MyTempThisMustBeUnique0(%rip)

## TAC_JFALSE
	movl	_MyTempThisMustBeUnique0(%rip), %eax
	testl	%eax, %eax
	je	MyLabelThisMustBeUnique1

## TAC_ADD
	movl	_a(%rip), %edx
	movl	_1(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _MyTempThisMustBeUnique1(%rip)

## TAC_COPY
 movl  _MyTempThisMustBeUnique1(%rip), %edx
 movl  %edx, _a(%rip)

## TAC_PRINT_INT
  movl	_a(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT
	jmp	MyLabelThisMustBeUnique0

MyLabelThisMustBeUnique1:

## TAC_ENDFUN
  popq	%rbp
  ret

## DATA SECTION
	.data

_1:	.long	1
_2:	.long	2
_3:	.long	3
_MyTempThisMustBeUnique0:	.long	0
_MyTempThisMustBeUnique1:	.long	0
_a:	.long	1
_b:	.long	2
_x:	.long	3
