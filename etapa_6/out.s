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

## TAC_VEC_ACCESS
	movl	_2(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique0(%rip)

## TAC_VEC_ACCESS
	movl	_1(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique1(%rip)

## TAC_SUB
 movl	_MyTempThisMustBeUnique0(%rip), %edx
 movl	_MyTempThisMustBeUnique1(%rip), %eax
 subl	%eax, %edx
 movl	%edx, _MyTempThisMustBeUnique2(%rip)

## TAC_VEC_ACCESS
	movl	_0(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique3(%rip)

## TAC_DIV
 movl	_MyTempThisMustBeUnique2(%rip), %eax
 movl	_MyTempThisMustBeUnique3(%rip), %ecx
 cltd
 idivl	%ecx
 movl	%eax, _MyTempThisMustBeUnique4(%rip)

## TAC_COPY
 movl  _MyTempThisMustBeUnique4(%rip), %edx
 movl  %edx, _b(%rip)

## TAC_VEC_ACCESS
	movl	_b(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique5(%rip)

## TAC_PRINT_INT
  movl	_MyTempThisMustBeUnique5(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_PRINT_STR
	leaq	_.str1(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_SUB
 movl	_2(%rip), %edx
 movl	_2(%rip), %eax
 subl	%eax, %edx
 movl	%edx, _MyTempThisMustBeUnique6(%rip)

## TAC_VEC_ACCESS
	movl	_MyTempThisMustBeUnique6(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_a(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique7(%rip)

## TAC_PRINT_INT
  movl	_MyTempThisMustBeUnique7(%rip), %eax
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

## TAC_ENDFUN
  popq	%rbp
  ret

## DATA SECTION
	.data

_0:	.long	0
_1:	.long	1
_2:	.long	2
_3:	.long	3
_MyTempThisMustBeUnique0:	.long	0
_MyTempThisMustBeUnique4:	.long	0
_10:	.long	10
_20:	.long	20
_MyTempThisMustBeUnique1:	.long	0
_MyTempThisMustBeUnique5:	.long	0
_30:	.long	30
_MyTempThisMustBeUnique2:	.long	0
_.str0:	.string	"KKKKKKKK"
_MyTempThisMustBeUnique6:	.long	0
_.str1:	.string	"\n"
_MyTempThisMustBeUnique3:	.long	0
_MyTempThisMustBeUnique7:	.long	0
_a:
	.long	10
	.long	20
	.long	30
_b:	.long	0
_x:	.long	3
