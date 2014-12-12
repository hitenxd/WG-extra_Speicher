
printnumber:
	pushq %rbp
	movq %rsp,%rbp
	movq	$0,%rsi
loop:
	
	movq 	$0, %rdx
	movq	$10,%rbx
	divq	%rbx		#edx= rest , eax=zahl/10
	addq	$48,%rdx
	pushq	%rdx
	inc	%rsi
	cmp	$0,%rax
	jz	next
	jmp	loop

next:
	cmp	$0,%rsi
	jz	exit
	dec 	%rsi
	movq	$4,%rax
	movq	8(%rsp),%rcx
	movq	$1,%rbx
	movq	$8,%rdx
	int  	$0x80
	addq 	$8,%rsp
	jmp	next
exit:
	leave
	ret

