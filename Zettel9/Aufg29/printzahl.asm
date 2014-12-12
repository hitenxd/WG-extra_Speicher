
printzahl:
	movl	$0,%esi
loop:
	
	movl 	$0, %edx
	movl	$10,%ebx
	div	%ebx		#edx= rest , eax=zahl/10
	addl	$48,%edx
	push	%edx
	inc	%esi
	cmp	$0,%eax
	jz	next
	jmp	loop

next:
	cmp	$0,%esi
	jz	exit
	dec 	%esi
	movl	$4,%eax
	movl	%esp,%ecx
	movl	$1,%ebx
	movl	$4,%edx
	int  	$0x80
	add 	$4, %esp
	jmp	next
exit:
	ret

