section .data
section .bss
	extern putchar
section .text
	global main

main:
	nop
	enter 	0, 0
	pusha
	pushf

	mov	eax, 0x50
	call	print_char_ln

	popf
	popa
	mov	eax, 0 
	leave
	ret

print_char_ln:
	enter 0, 0
	pusha
	pushf
	push	eax
	call	print_char
	mov	eax, 0x0a
	call	print_char
	pop	eax
	popf
	popa
	leave
	ret

print_char:
	enter	0,0
	pusha
	pushf
	push	eax
	call	putchar
	pop	eax
	popf
	popa
	leave
	ret

