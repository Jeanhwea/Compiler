; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_pri_f$IV
J_pri_f$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	mov	eax, [ebp + 16]	; J_pri_f$IV_n
	mov	ecx, 0x3
	cmp	eax, ecx
	jl	..@l1
	mov	ecx, [ebp + 16]	; J_pri_f$IV_n
	mov	edx, 0x1
	sub	ecx, edx
	mov	[ebp - 12], ecx	; J_pri_f$IV_&2
	mov	ecx, [ebp - 12]	; J_pri_f$IV_&2
	push	ecx
	mov	edi, [ebp + 12]
	push	edi		; dup old ebp
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_pri_f$IV
	add	esp, 12
	mov	[ebp - 16], eax	; J_pri_f$IV_&3
	mov	ecx, [ebp + 16]	; J_pri_f$IV_n
	mov	edx, [ebp - 16]	; J_pri_f$IV_&3
	imul	ecx, edx
	mov	[ebp - 8], ecx	; J_pri_f$IV_&1
	mov	ecx, [ebp - 8]	; J_pri_f$IV_&1
	mov	[ebp - 4], ecx	; set return value
	jmp	..@l2
..@l1:
	mov	ecx, [ebp + 16]	; J_pri_f$IV_n
	mov	[ebp - 4], ecx	; set return value
..@l2:
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_pri
J_pri:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ecx, 0x5
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_pri_f$IV
	add	esp, 12
	mov	[ebp - 8], eax	; J_pri_&4
	mov	eax, [ebp - 8]	; J_pri_&4
	call	print_int
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL main
main:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ebp		; push current ebp
	call	J_pri
	add	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
