; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR_h3$IR
J_h1$IR_h2$IR_h3$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, 0x9
	mov	esi, [ebp + 20]
	mov	[esi], ecx		; *J_h1$IR_h2$IR_h3$IR_i
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR
J_h1$IR_h2$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR_h3$IR
	add	esp, 16
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR
J_h1$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR
	add	esp, 12
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL main
main:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	lea	ecx, [ebp - 8]	; J_i
	push	ecx
	push	ebp		; push current ebp
	call	J_h1$IR
	add	esp, 8
	mov	eax, [ebp - 8]	; J_i
	call	print_int
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
