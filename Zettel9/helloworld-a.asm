.section .data

str:	.ascii	"Hello world!\n"
	strlen = . - str

num:	.long	1337

.section .text

.global _start			

_start:
	movl	$4, %eax		#Output to console
	movl	$1, %ebx		#File-Descriptor
	movl	$str, %ecx		#ausgabe-Platz
	movl	$strlen, %edx		#länge der asugabe
	int	$0x80			# Kernel-Call

	movl	$1, %eax		#programm beenden
	movl	$0, %ebx
	int	$0x80
