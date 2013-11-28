; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_TestCase09$IR
J_TestCase09$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 124
	mov	ecx, 0x1
	mov	[ebp - 8], ecx	; J_TestCase09$IR_a
	mov	ecx, 0x2
	mov	[ebp - 12], ecx	; J_TestCase09$IR_b
	mov	ecx, 0x1
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x2
	mov	eax, [ebp - 12]	; J_TestCase09$IR_b
	lea	edi, [ebp - 56]	; J_TestCase09$IR_f
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 96], ecx	; J_TestCase09$IR_&1
	mov	eax, [ebp - 96]	; J_TestCase09$IR_&1
	mov	ecx, [ebp - 8]	; J_TestCase09$IR_a
	cmp	eax, ecx
	jg	..@l1
	mov	eax, 0x2
	call	print_int
	jmp	..@l2
..@l1:
	mov	eax, 0x1
	call	print_int
..@l2:
	mov	eax, [ebp - 12]	; J_TestCase09$IR_b
	lea	edi, [ebp - 56]	; J_TestCase09$IR_f
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 100], ecx	; J_TestCase09$IR_&2
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 104], ecx	; J_TestCase09$IR_&3
	mov	eax, [ebp - 100]	; J_TestCase09$IR_&2
	mov	ecx, [ebp - 104]	; J_TestCase09$IR_&3
	cmp	eax, ecx
	jnl	..@l3
	mov	eax, 0x4
	call	print_int
	jmp	..@l4
..@l3:
	mov	eax, 0x3
	call	print_int
..@l4:
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 108], ecx	; J_TestCase09$IR_&4
	mov	eax, [ebp - 108]	; J_TestCase09$IR_&4
	mov	ecx, [ebp - 8]	; J_TestCase09$IR_a
	cmp	eax, ecx
	jz	..@l5
	mov	eax, 0x7
	call	print_int
	jmp	..@l6
..@l5:
	mov	eax, 0x6
	call	print_int
..@l6:
	mov	eax, [ebp - 12]	; J_TestCase09$IR_b
	lea	edi, [ebp - 56]	; J_TestCase09$IR_f
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 112], ecx	; J_TestCase09$IR_&5
	mov	eax, [ebp - 112]	; J_TestCase09$IR_&5
	mov	ecx, [ebp - 8]	; J_TestCase09$IR_a
	cmp	eax, ecx
	jnz	..@l7
	mov	eax, 0x9
	call	print_int
	jmp	..@l8
..@l7:
	mov	eax, 0x8
	call	print_int
..@l8:
	mov	eax, [ebp - 12]	; J_TestCase09$IR_b
	lea	edi, [ebp - 56]	; J_TestCase09$IR_f
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 116], ecx	; J_TestCase09$IR_&6
	mov	eax, [ebp - 116]	; J_TestCase09$IR_&6
	mov	ecx, [ebp - 8]	; J_TestCase09$IR_a
	cmp	eax, ecx
	jl	..@l9
	mov	eax, 0xb
	call	print_int
	jmp	..@l10
..@l9:
	mov	eax, 0xa
	call	print_int
..@l10:
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 120], ecx	; J_TestCase09$IR_&7
	mov	eax, [ebp - 12]	; J_TestCase09$IR_b
	mov	ecx, [ebp - 120]	; J_TestCase09$IR_&7
	cmp	eax, ecx
	jng	..@l11
	mov	eax, 0xd
	call	print_int
	jmp	..@l12
..@l11:
	mov	eax, 0xc
	call	print_int
..@l12:
	mov	eax, [ebp - 8]	; J_TestCase09$IR_a
	lea	edi, [ebp - 16]	; J_TestCase09$IR_e
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 124], ecx	; J_TestCase09$IR_&8
	mov	eax, [ebp - 124]	; J_TestCase09$IR_&8
	mov	ecx, [ebp - 8]	; J_TestCase09$IR_a
	cmp	eax, ecx
	jnz	..@l13
	mov	eax, 0xe
	call	print_int
	jmp	..@l14
..@l13:
	mov	eax, 0xd
	call	print_int
..@l14:
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
	lea	ecx, [ebp - 8]	; J_k
	push	ecx
	push	ebp		; push current ebp
	call	J_TestCase09$IR
	add	esp, 8
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
