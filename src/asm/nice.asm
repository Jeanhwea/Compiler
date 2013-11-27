%include "io.asm"
section .text
	global main

main:
	nop
	push	ebp
	mov	ebp, esp
	call	nice
	xor	eax, eax
	pop	ebp
	ret
section .text
	global nice
nice:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, 8
	mov	[ebp - 4], ecx
	mov	ecx, [ebp - 4]
	mov	eax, [ebp - 4]
	lea	esi, [ebp - 4]
	mov	eax, esi
	pop	ebp
	ret
