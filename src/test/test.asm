; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL main
main:
	nop
	nop
	push	ebp
	mov	ebp, esp
	sub	esp, 128
	push	ebx
	push	esi
	push	edi
	mov	ecx, 1
	mov	eax, 0
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 1
	neg	ecx
	mov	[ebp - 108], ecx	; J_&1
	mov	ecx, [ebp - 108]	; J_&1
	mov	eax, 1
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0
	mov	eax, 2
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 3
	mov	eax, 3
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 32
	mov	eax, 4
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 4
	mov	[ebp - 16], ecx	; J_N
	mov	ecx, 0
	mov	[ebp - 8], ecx	; J_i
..@l1:
	mov	eax, [ebp - 8]	; J_i
	mov	ecx, [ebp - 16]	; J_N
	cmp	eax, ecx
	jg	..@l2
	mov	ecx, [ebp - 8]	; J_i
	mov	[ebp - 12], ecx	; J_j
..@l3:
	mov	eax, [ebp - 12]	; J_j
	mov	ecx, [ebp - 16]	; J_N
	cmp	eax, ecx
	jg	..@l4
	mov	eax, [ebp - 8]	; J_i
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 112], ecx	; J_&2
	mov	eax, [ebp - 12]	; J_j
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 116], ecx	; J_&3
	mov	eax, [ebp - 112]	; J_&2
	mov	ecx, [ebp - 116]	; J_&3
	cmp	eax, ecx
	jg	..@l5
	jmp	..@l6
..@l5:
	mov	eax, [ebp - 8]	; J_i
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 120], ecx	; J_&4
	mov	ecx, [ebp - 120]	; J_&4
	mov	[ebp - 20], ecx	; J_t
	mov	eax, [ebp - 12]	; J_j
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 124], ecx	; J_&5
	mov	ecx, [ebp - 124]	; J_&5
	mov	eax, [ebp - 8]	; J_i
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 20]	; J_t
	mov	eax, [ebp - 12]	; J_j
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
..@l6:
	mov	ecx, [ebp - 12]	; J_j
	inc	ecx
	mov	[ebp - 12], ecx	; J_j
	jmp	..@l3
..@l4:
	mov	ecx, [ebp - 8]	; J_i
	inc	ecx
	mov	[ebp - 8], ecx	; J_i
	jmp	..@l1
..@l2:
	mov	ecx, 20
	mov	[ebp - 104], ecx	; J_blank
	mov	eax, ..@s1
	call	print_string
	mov	eax, [ebp - 104]	; J_blank
	call	print_char
	mov	ecx, 0
	mov	[ebp - 8], ecx	; J_i
..@l7:
	mov	eax, [ebp - 8]	; J_i
	mov	ecx, [ebp - 16]	; J_N
	cmp	eax, ecx
	jg	..@l8
	mov	eax, [ebp - 8]	; J_i
	lea	edi, [ebp - 24]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 128], ecx	; J_&6
	mov	eax, [ebp - 128]	; J_&6
	call	print_int
	mov	ecx, [ebp - 8]	; J_i
	inc	ecx
	mov	[ebp - 8], ecx	; J_i
	jmp	..@l7
..@l8:
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
SECTION .DATA
	..@s1: DB "after sorted", 0
