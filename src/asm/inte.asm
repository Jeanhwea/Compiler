sys_exit	equ	1
sys_write	equ	4
stdout		equ	1

section .data
	hello: db "hello", 10
	len: equ $-hello

section	.text
	global _start

_start:
	mov	ecx, hello
	mov	edx, len
	jmp	write


write:
	mov	eax, sys_write
	mov	ebx, stdout
	int	0x80
	jmp	exit

exit:
	mov	eax, sys_exit
	xor	ebx, ebx
	int	0x80
