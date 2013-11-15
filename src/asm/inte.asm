sys_exit	equ	1
sys_write	equ	4
stdout		equ	1

section	.text
	global _start

_start:
	mov	ecx, 0x40
	jmp	write


write:
	mov	eax, sys_write
	mov	ebx, stdout
	mov	edx, 1
	int	0x80
	jmp	exit

exit:
	mov	eax, sys_exit
	xor	ebx, ebx
	int	0x80
