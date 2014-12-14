.section .data

str:	.ascii	"Hello world!\n"
	strlen = . - str

msg: 	.ascii 

num:	.long	1337

.section .text

.global _start			

_start:
	movl	$4, %eax		#Output to console
	movl	$1, %ebx		#File-Descriptor
	movl	$str, %ecx		#ausgabe-Platz
	movl	$strlen, %edx		#länge der asugabe
	int	$0x80			# Kernel-Call

	movl	num,%eax
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
	int  $0x80
	add $4, %esp
	jmp	next
exit:
	

	movl	$1, %eax		#programm beenden
	movl	$0, %ebx
	int	$0x80
