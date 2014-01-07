; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
SECTION .DATA
	fmt_int_r:  DB "%d", 0
	fmt_int_w:  DB "%d", 10, 0
	fmt_char_r: DB 10, "%c", 0
	fmt_char_w: DB "%c", 10, 0
	fmt_string: DB "%s", 10, 0

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
	sub	esp, 144
	push	ebx
	push	esi
	push	edi
	mov	eax, 0
	mov	[ebp - 128], eax	; J_ge_index
..@l1:
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, 9
	cmp	eax, ecx
	jg	..@l2
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, [ebp - 128]	; J_ge_index
	lea	edi, [ebp - 88]	; J_ge_c
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, [ebp - 128]	; J_ge_index
	inc	eax
	mov	[ebp - 128], eax	; J_ge_index
	jmp	..@l1
..@l2:
	mov	eax, [ebp - 128]	; J_ge_index
	dec	eax
	mov	[ebp - 128], eax	; J_ge_index
	mov	eax, 0
	mov	[ebp - 128], eax	; J_ge_index
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
	mov	[ebp - 132], ecx	; J_ge_&1
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, [ebp - 132]	; J_ge_&1
	lea	edi, [ebp - 48]	; J_ge_b
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, [ebp - 128]	; J_ge_index
	inc	eax
	mov	[ebp - 128], eax	; J_ge_index
	jmp	..@l3
..@l4:
	mov	eax, [ebp - 128]	; J_ge_index
	dec	eax
	mov	[ebp - 128], eax	; J_ge_index
	mov	eax, 0
	mov	[ebp - 128], eax	; J_ge_index
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
	mov	[ebp - 136], ecx	; J_ge_&2
	mov	eax, [ebp - 136]	; J_ge_&2
	lea	edi, [ebp - 48]	; J_ge_b
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 140], ecx	; J_ge_&3
	mov	eax, [ebp - 128]	; J_ge_index
	mov	ecx, [ebp - 140]	; J_ge_&3
	lea	edi, [ebp - 8]	; J_ge_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, [ebp - 128]	; J_ge_index
	inc	eax
	mov	[ebp - 128], eax	; J_ge_index
	jmp	..@l5
..@l6:
	mov	eax, [ebp - 128]	; J_ge_index
	dec	eax
	mov	[ebp - 128], eax	; J_ge_index
	mov	eax, 0
	mov	[ebp - 128], eax	; J_ge_index
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
	mov	[ebp - 144], ecx	; J_ge_&4
	mov	eax, [ebp - 144]	; J_ge_&4
	call	print_int
	mov	eax, [ebp - 128]	; J_ge_index
	inc	eax
	mov	[ebp - 128], eax	; J_ge_index
	jmp	..@l7
..@l8:
	mov	eax, [ebp - 128]	; J_ge_index
	dec	eax
	mov	[ebp - 128], eax	; J_ge_index
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
