; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_ge
J_ge:
	push	ebp
	mov	ebp, esp
	sub	esp, 196
	mov	ecx, 0x0
	mov	[ebp - 128], ecx	; J_ge_index
..@l1:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 0x9
	cmp	eax, ecx
	jg	..@l2
	mov	ecx, [ebp - 128]	; J_ge_index
	mov	eax, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 128]	; J_ge_index
	inc	ecx
	mov	[ebp - 128], ecx	; J_ge_index
	jmp	..@l1
..@l2:
	mov	ecx, 0x0
	mov	[ebp - 128], ecx	; J_ge_index
..@l3:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 0x9
	cmp	eax, ecx
	jg	..@l4
	mov	eax, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 136], ecx	; J_ge_&1
	mov	ecx, [ebp - 128]	; J_ge_index
	mov	eax, [ebp - 136]	; J_ge_&1
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 128]	; J_ge_index
	inc	ecx
	mov	[ebp - 128], ecx	; J_ge_index
	jmp	..@l3
..@l4:
	mov	ecx, 0x0
	mov	[ebp - 128], ecx	; J_ge_index
..@l5:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 0x9
	cmp	eax, ecx
	jg	..@l6
	mov	eax, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 144], ecx	; J_ge_&3
	mov	eax, [ebp - 144]	; J_ge_&3
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 140], ecx	; J_ge_&2
	mov	ecx, [ebp - 128]	; J_ge_index
	mov	eax, [ebp - 140]	; J_ge_&2
	lea	edi, [ebp - 8]	; J_ge_a
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 128]	; J_ge_index
	inc	ecx
	mov	[ebp - 128], ecx	; J_ge_index
	jmp	..@l5
..@l6:
	mov	eax, 0x5
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 148], ecx	; J_ge_&4
	mov	eax, 0x1
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 160], ecx	; J_ge_&7
	mov	eax, [ebp - 160]	; J_ge_&7
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 156], ecx	; J_ge_&6
	mov	ecx, [ebp - 148]	; J_ge_&4
	mov	edx, [ebp - 156]	; J_ge_&6
	imul	ecx, edx
	mov	[ebp - 152], ecx	; J_ge_&5
	mov	eax, 0x2
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 176], ecx	; J_ge_&11
	mov	eax, [ebp - 176]	; J_ge_&11
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 172], ecx	; J_ge_&10
	mov	eax, 0x2
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 184], ecx	; J_ge_&13
	mov	ecx, [ebp - 172]	; J_ge_&10
	mov	edx, [ebp - 184]	; J_ge_&13
	imul	ecx, edx
	mov	[ebp - 180], ecx	; J_ge_&12
	mov	eax, [ebp - 180]	; J_ge_&12
	lea	edi, [ebp - 8]	; J_ge_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 168], ecx	; J_ge_&9
	mov	ecx, [ebp - 152]	; J_ge_&5
	mov	edx, [ebp - 168]	; J_ge_&9
	add	ecx, edx
	mov	[ebp - 164], ecx	; J_ge_&8
	mov	eax, 0x2
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 192], ecx	; J_ge_&15
	mov	ecx, [ebp - 164]	; J_ge_&8
	mov	edx, [ebp - 192]	; J_ge_&15
	sub	ecx, edx
	mov	[ebp - 188], ecx	; J_ge_&14
	mov	ecx, [ebp - 188]	; J_ge_&14
	mov	[ebp - 132], ecx	; J_ge_final
	mov	ecx, 0x0
	mov	[ebp - 128], ecx	; J_ge_index
..@l7:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 0x9
	cmp	eax, ecx
	jg	..@l8
	mov	eax, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 8]	; J_ge_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 196], ecx	; J_ge_&16
	mov	eax, [ebp - 196]	; J_ge_&16
	call	print_int
	mov	ecx, [ebp - 128]	; J_ge_index
	inc	ecx
	mov	[ebp - 128], ecx	; J_ge_index
	jmp	..@l7
..@l8:
	mov	eax, [ebp - 132]	; J_ge_final
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
	call	J_ge
	add	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
