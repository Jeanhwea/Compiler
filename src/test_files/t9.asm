; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
SECTION .DATA
	fmt_int_r:  DB "%d", 0
	fmt_int_w:  DB "%d", 10, 0
	fmt_char_r: DB 10, "%c", 0
	fmt_char_w: DB "%c", 10, 0
	fmt_string: DB "%s", 0

SECTION .TEXT
	EXTERN	scanf, printf
	GLOBAL	scan_int, scan_char
	GLOBAL	print_int, print_char, print_string

scan_int:
	push	ebp
	mov	ebp, esp
	sub	esp, 0x4
	lea	eax, [ebp - 4]
	push	eax
	push	fmt_int_r
	call	scanf
	pop	ecx
	pop	ecx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

scan_char:
	push	ebp
	mov	ebp, esp
	sub	esp, 0x4
	lea	eax, [ebp - 4]
	push	eax
	push	fmt_char_r
	call	scanf
	pop	ecx
	pop	ecx
	mov	eax, [ebp - 4]
	leave
	ret

print_int:
	push	ebp
	mov	ebp, esp
	push	eax
	push	fmt_int_w
	call	printf
	pop	ecx
	pop	ecx
	xor	eax, eax
	leave
	ret

print_char:
	push	ebp
	mov	ebp, esp
	push	eax
	push	fmt_char_w
	call	printf
	pop	ecx
	pop	ecx
	xor	eax, eax
	leave
	ret

print_string:
	push	ebp
	mov	ebp, esp
	push	eax
	push	fmt_string
	call	printf
	pop	ecx
	pop	ecx
	xor	eax, eax
	leave
	ret


SECTION .TEXT
	GLOBAL J_ge
J_ge:
	push	ebp
	mov	ebp, esp
	sub	esp, 196
	push	ebx
	push	esi
	push	edi
	mov	ecx, 0
	mov	[ebp - 128], ecx	; J_ge_index
..@l1:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 9
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
	mov	ecx, 0
	mov	[ebp - 128], ecx	; J_ge_index
..@l3:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 9
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
	mov	ecx, 0
	mov	[ebp - 128], ecx	; J_ge_index
..@l5:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 9
	cmp	eax, ecx
	jg	..@l6
	mov	eax, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 140], ecx	; J_ge_&2
	mov	eax, [ebp - 140]	; J_ge_&2
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 144], ecx	; J_ge_&3
	mov	ecx, [ebp - 128]	; J_ge_index
	mov	eax, [ebp - 144]	; J_ge_&3
	lea	edi, [ebp - 8]	; J_ge_a
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 128]	; J_ge_index
	inc	ecx
	mov	[ebp - 128], ecx	; J_ge_index
	jmp	..@l5
..@l6:
	mov	eax, 5
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 148], ecx	; J_ge_&4
	mov	eax, 1
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 152], ecx	; J_ge_&5
	mov	eax, [ebp - 152]	; J_ge_&5
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 156], ecx	; J_ge_&6
	mov	ecx, [ebp - 148]	; J_ge_&4
	mov	edx, [ebp - 156]	; J_ge_&6
	imul	ecx, edx
	mov	[ebp - 160], ecx	; J_ge_&7
	mov	eax, 2
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 164], ecx	; J_ge_&8
	mov	eax, [ebp - 164]	; J_ge_&8
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 168], ecx	; J_ge_&9
	mov	eax, 2
	lea	edi, [ebp - 88]	; J_ge_c
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 172], ecx	; J_ge_&10
	mov	ecx, [ebp - 168]	; J_ge_&9
	mov	edx, [ebp - 172]	; J_ge_&10
	imul	ecx, edx
	mov	[ebp - 176], ecx	; J_ge_&11
	mov	eax, [ebp - 176]	; J_ge_&11
	lea	edi, [ebp - 8]	; J_ge_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 180], ecx	; J_ge_&12
	mov	ecx, [ebp - 160]	; J_ge_&7
	mov	edx, [ebp - 180]	; J_ge_&12
	add	ecx, edx
	mov	[ebp - 184], ecx	; J_ge_&13
	mov	eax, 2
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 188], ecx	; J_ge_&14
	mov	ecx, [ebp - 184]	; J_ge_&13
	mov	edx, [ebp - 188]	; J_ge_&14
	sub	ecx, edx
	mov	[ebp - 192], ecx	; J_ge_&15
	mov	ecx, [ebp - 192]	; J_ge_&15
	mov	[ebp - 132], ecx	; J_ge_final
	mov	ecx, 0
	mov	[ebp - 128], ecx	; J_ge_index
..@l7:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 9
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
	pop	edi
	pop	esi
	pop	ebx
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
	push	ebx
	push	esi
	push	edi
	push	ebp		; push current ebp
	call	J_ge
	add	esp, 4
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
