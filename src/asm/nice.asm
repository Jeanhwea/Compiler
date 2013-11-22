%include "io.asm"

section .text
	global main

section .data
	msg: db "Hello World", 10, 0

main:
	nop
	push	ebp
	mov	ebp, esp
	mov	eax, msg
	call	print_string
	call	scan_int
	call	print_char
	xor	eax, eax
	leave
	ret

