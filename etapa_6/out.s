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
	movl  _0(%rip), %edx
	movl  %edx, _a(%rip)

## TAC_SUB
 movl	_a(%rip), %edx
 movl	_i(%rip), %eax
 subl	%eax, %edx
 movl	%edx, _MyTempThisMustBeUnique0(%rip)

## TAC_COPY
	movl  _MyTempThisMustBeUnique0(%rip), %edx
	movl  %edx, _a(%rip)

## TAC_COPY
	movl  _5(%rip), %edx
	movl  %edx, _a(%rip)

## TAC_VEC_COPY
	movl	_a(%rip), %edx
	movl	%edx, 0+_v(%rip)

## TAC_VEC_ACCESS
	movl	_5(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_v(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _MyTempThisMustBeUnique1(%rip)

## TAC_PRINT_INT
  movl	_MyTempThisMustBeUnique1(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_PRINT_INT
  movl	_a(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_COPY
	movl  _2(%rip), %edx
	movl  %edx, _i(%rip)

## TAC_PRINT_STR
	leaq	_.str3(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_READ
	leaq	_MyTempThisMustBeUnique2(%rip), %rsi
	leaq	print_int(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT

## TAC_COPY
	movl  _MyTempThisMustBeUnique2(%rip), %edx
	movl  %edx, _a(%rip)

MyLabelThisMustBeUnique0:

## TAC_LT
 movl	_i(%rip), %edx
 movl	_10(%rip), %eax
 cmpl	%eax, %edx
 setl	%al
 movzbl	%al, %eax
 movl	%eax, _MyTempThisMustBeUnique3(%rip)

## TAC_JFALSE
	movl	_MyTempThisMustBeUnique3(%rip), %eax
	testl	%eax, %eax
	je	MyLabelThisMustBeUnique1

## TAC_ADD
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _MyTempThisMustBeUnique4(%rip)

## TAC_COPY
	movl  _MyTempThisMustBeUnique4(%rip), %edx
	movl  %edx, _i(%rip)

## TAC_ARG
	movl _1(%rip), %edx
	pushq %rdx

## TAC_ARG
	movl _a(%rip), %edx
	pushq %rdx

## TAC_CALL
	call incn
	addq $16, %rsp
	movl %eax, _MyTempThisMustBeUnique5(%rip)
## TAC_COPY
	movl  _MyTempThisMustBeUnique5(%rip), %edx
	movl  %edx, _a(%rip)
	jmp	MyLabelThisMustBeUnique0

MyLabelThisMustBeUnique1:

## TAC_PRINT_STR
	leaq	_.str1(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_PRINT_INT
  movl	_a(%rip), %eax
  movl	%eax, %esi
  leaq	print_int(%rip), %rdi
  movl	$0, %eax
  call	printf@PLT

## TAC_PRINT_STR
	leaq	_.str5(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

## TAC_EQ
 movl	_a(%rip), %edx
 movl	_15(%rip), %eax
 cmpl	%eax, %edx
 sete	%al
 movzbl	%al, %eax
 movl	%eax, _MyTempThisMustBeUnique6(%rip)

## TAC_JFALSE
	movl	_MyTempThisMustBeUnique6(%rip), %eax
	testl	%eax, %eax
	je	MyLabelThisMustBeUnique2

label.x:

## TAC_SUB
 movl	_a(%rip), %edx
 movl	_1(%rip), %eax
 subl	%eax, %edx
 movl	%edx, _MyTempThisMustBeUnique7(%rip)

## TAC_COPY
	movl  _MyTempThisMustBeUnique7(%rip), %edx
	movl  %edx, _a(%rip)

## TAC_PRINT_STR
	leaq	_.str4(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

MyLabelThisMustBeUnique2:

## TAC_EQ
 movl	_i(%rip), %edx
 movl	_100(%rip), %eax
 cmpl	%eax, %edx
 sete	%al
 movzbl	%al, %eax
 movl	%eax, _MyTempThisMustBeUnique8(%rip)

## TAC_JFALSE
	movl	_MyTempThisMustBeUnique8(%rip), %eax
	testl	%eax, %eax
	je	MyLabelThisMustBeUnique3

## TAC_PRINT_STR
	leaq	_.str2(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	MyLabelThisMustBeUnique4

MyLabelThisMustBeUnique3:

## TAC_PRINT_STR
	leaq	_.str0(%rip), %rax
	movq	%rax, %rsi
	leaq	print_str(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax

MyLabelThisMustBeUnique4:

## TAC_GT
 movl	_a(%rip), %edx
 movl	_0(%rip), %eax
 cmpl	%eax, %edx
 setg	%al
 movzbl	%al, %eax
 movl	%eax, _MyTempThisMustBeUnique9(%rip)

## TAC_JFALSE
	movl	_MyTempThisMustBeUnique9(%rip), %eax
	testl	%eax, %eax
	je	MyLabelThisMustBeUnique5
	jmp	label.x

MyLabelThisMustBeUnique5:

## TAC_ENDFUN
  popq	%rbp
  ret

## TAC_BEGINFUN
  .globl	incn
  .type	incn, @function
incn:
  pushq	%rbp
  movq	%rsp, %rbp
	movl	16(%rbp), %edx
	movl	%edx, _x(%rip)
	movl	24(%rbp), %edx
	movl	%edx, _n(%rip)

## TAC_ADD
	movl	_x(%rip), %edx
	movl	_n(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _MyTempThisMustBeUnique10(%rip)

## TAC_ENDFUN
  popq	%rbp
  ret

## DATA SECTION
	.data

_0:	.long	0
_1:	.long	1
_2:	.long	2
_3:	.long	3
_5:	.long	5
_'x':	.long	'x'
_n:	.long	0
_x:	.long	0
_.str0:	.string	"OK!\n"
_'A':	.long	'A'
_MyTempThisMustBeUnique0:	.long	0
_MyTempThisMustBeUnique4:	.long	0
_MyTempThisMustBeUnique8:	.long	0
_100:	.long	100
_.str1:	.string	"Incrementado algumas vezes a fica "
_10:	.long	10
_MyTempThisMustBeUnique1:	.long	0
_MyTempThisMustBeUnique5:	.long	0
_MyTempThisMustBeUnique9:	.long	0
_.str2:	.string	"Nao tem como isso...\n"
_15:	.long	15
_.str3:	.string	"Digite um numero: \n"
_MyTempThisMustBeUnique2:	.long	0
_MyTempThisMustBeUnique6:	.long	0
_55:	.long	55
_MyTempThisMustBeUnique10:	.long	0
_.str4:	.string	"A era=15\n"
_.str5:	.string	"\n"
_MyTempThisMustBeUnique3:	.long	0
_MyTempThisMustBeUnique7:	.long	0
_'a':	.long	'a'
_c:	.long	'x'
_d:	.long	100
_a:	.long	'A'
_i:	.long	1
_v:
	.long	'a'
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
_matrix:	.zero
