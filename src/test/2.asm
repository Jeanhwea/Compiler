; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_prn_swap$IR$IR
J_prn_swap$IR$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	esi, [ebp + 20]
	mov	ecx, [esi]	; *J_prn_swap$IR$IR_i
	mov	[ebp - 8], ecx	; J_prn_swap$IR$IR_temp
	mov	esi, [ebp + 16]
	mov	ecx, [esi]	; *J_prn_swap$IR$IR_j
	mov	esi, [ebp + 20]
	mov	[esi], ecx		; *J_prn_swap$IR$IR_i
	mov	ecx, [ebp - 8]	; J_prn_swap$IR$IR_temp
	mov	esi, [ebp + 16]
	mov	[esi], ecx		; *J_prn_swap$IR$IR_j
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_prn
J_prn:
	push	ebp
	mov	ebp, esp
	sub	esp, 80
	mov	ecx, 0x1
	mov	eax, 0x0
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x3
	mov	eax, 0x1
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x2
	mov	eax, 0x2
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x4
	mov	eax, 0x3
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x5
	mov	eax, 0x4
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x0
	mov	[ebp - 48], ecx	; J_prn_i
..@l1:
	mov	eax, [ebp - 48]	; J_prn_i
	mov	ecx, 0x4
	cmp	eax, ecx
	jg	..@l2
	mov	ecx, 0x0
	mov	[ebp - 52], ecx	; J_prn_j
..@l3:
	mov	eax, [ebp - 52]	; J_prn_j
	mov	ecx, 0x4
	cmp	eax, ecx
	jg	..@l4
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 56], ecx	; J_prn_&1
	mov	eax, [ebp - 52]	; J_prn_j
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 60], ecx	; J_prn_&2
	mov	eax, [ebp - 56]	; J_prn_&1
	mov	ecx, [ebp - 60]	; J_prn_&2
	cmp	eax, ecx
	jg	..@l5
	jmp	..@l6
..@l5:
	mov	edx, [ebp - 48]	; J_prn_i
	lea	ecx, [ebp - 8]	; J_prn_he
	imul	edx, 4
	sub	ecx, edx
	push	ecx
	mov	edx, [ebp - 52]	; J_prn_j
	lea	ecx, [ebp - 8]	; J_prn_he
	imul	edx, 4
	sub	ecx, edx
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_prn_swap$IR$IR
	add	esp, 16
..@l6:
	mov	ecx, [ebp - 52]	; J_prn_j
	inc	ecx
	mov	[ebp - 52], ecx	; J_prn_j
	jmp	..@l3
..@l4:
	mov	ecx, [ebp - 48]	; J_prn_i
	inc	ecx
	mov	[ebp - 48], ecx	; J_prn_i
	jmp	..@l1
..@l2:
	mov	ecx, 0x0
	mov	[ebp - 48], ecx	; J_prn_i
..@l7:
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 64], ecx	; J_prn_&3
	mov	ecx, [ebp - 64]	; J_prn_&3
	mov	edx, 0x1
	add	ecx, edx
	mov	[ebp - 68], ecx	; J_prn_&4
	mov	ecx, [ebp - 68]	; J_prn_&4
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 48]	; J_prn_i
	mov	edx, 0x1
	add	ecx, edx
	mov	[ebp - 72], ecx	; J_prn_&5
	mov	ecx, [ebp - 72]	; J_prn_&5
	mov	[ebp - 48], ecx	; J_prn_i
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 76], ecx	; J_prn_&6
	mov	eax, [ebp - 76]	; J_prn_&6
	mov	ecx, 0x4
	cmp	eax, ecx
	jz	..@l8
	jmp	..@l7
..@l8:
	mov	ecx, 0x0
	mov	[ebp - 48], ecx	; J_prn_i
..@l9:
	mov	eax, [ebp - 48]	; J_prn_i
	mov	ecx, 0x4
	cmp	eax, ecx
	jg	..@l10
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 80], ecx	; J_prn_&7
	mov	eax, [ebp - 80]	; J_prn_&7
	call	print_int
	mov	ecx, [ebp - 48]	; J_prn_i
	inc	ecx
	mov	[ebp - 48], ecx	; J_prn_i
	jmp	..@l9
..@l10:
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
	call	J_prn
	add	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
