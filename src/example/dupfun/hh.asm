section .text
	global main

main:
	push	ebp
	mov	ebp, esp

	mov	eax, 4
	mov	ebx, 1
	mov	ecx, msg
	mov	edx, len
	int	0x80

	pop	ebp
	ret

section .rodata
	msg: db "hello",0x0a
	len: equ $-msg
