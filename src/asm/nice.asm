%include "io.asm"

section .text
	global main

section .data
	msg: db "Hello World", 10, 0

main:
	nop
	push	ebp
	push	0x5555
	pop	eax
	call	print_int
	mov	ebp, esp
	mov	eax, ebp
	call	print_int
	mov	eax, msg
	call	print_string
	call	nice
	call	print_int
	xor	eax, eax
	leave
	ret

nice:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, 8
	mov	[ebp - 4], ecx
	mov	ecx, [ebp - 4]
	mov	eax, [ebp - 4]
	call	print_int
	lea	esi, [ebp - 4]
	mov	eax, esi
	call	print_int
	leave
	ret
