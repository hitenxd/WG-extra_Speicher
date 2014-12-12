.section .data

n:	.quad	10		# define the fibonacci number that should be calculated

.section .text

.include "print.asm"

.global _start

_start:
	# call Fibonacci function f(n)

	pushq	(n)		# parameter: fibonacci number to calculate

	call	f		# call function
	addq	$8, %rsp	# remove parameter from stack

	# print calculated Fibonacci number on stdout
	call	printnumber

	# exit process with exit code 0
	movq	$1, %rax
	movq	$0, %rbx
	int	$0x80

# f: Calculates a Fibonacci number
#   f(n) = {n, if n<=1; f(n-1)+f(n-2), else}.
#   Parameter: Integer n >= 0, passed on stack
#   Returns:   Fibonacci number f(n), returned in rax
.type f, @function
f:
	
	pushq %rbp
	movq %rsp,%rbp
	subq $16,%rsp
	movq 16(%rbp),%rdx
	cmp $1,%rdx
	jle recend
	dec %rdx	
	pushq %rdx
	call f
	popq %rdx
	movq %rax,-8(%rbp)
	dec %rdx
	pushq %rdx
	call f
	popq %rdx
	movq %rax,-16(%rbp)
	jmp weiter
recend:	
	movq %rdx,-8(%rbp)
	movq $0,-16(%rbp)
weiter:
	movq -8(%rbp),%rax
	addq -16(%rbp),%rax
	
	# ...
	leave
	ret
