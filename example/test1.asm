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
	GLOBAL J_swap$IR$IR
J_swap$IR$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	esi, [ebp + 16]
	mov	eax, [esi]	; *J_swap$IR$IR_x
	mov	[ebp - 8], eax	; J_swap$IR$IR_t
	mov	esi, [ebp + 12]
	mov	eax, [esi]	; *J_swap$IR$IR_y
	mov	esi, [ebp + 16]
	mov	[esi], eax	; *J_swap$IR$IR_x
	mov	eax, [ebp - 8]	; J_swap$IR$IR_t
	mov	esi, [ebp + 12]
	mov	[esi], eax	; *J_swap$IR$IR_y
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
	sub	esp, 44
	push	ebx
	push	esi
	push	edi
	mov	eax, 4
	mov	ecx, 0
	lea	edi, [ebp - 8]	; J_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, 5
	mov	ecx, 1
	lea	edi, [ebp - 8]	; J_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, 2
	mov	ecx, 2
	lea	edi, [ebp - 8]	; J_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, 7
	mov	ecx, 3
	lea	edi, [ebp - 8]	; J_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, 0
	mov	ecx, 4
	lea	edi, [ebp - 8]	; J_a
	imul	ecx, 4
	sub	edi, ecx
	mov	[edi], eax
	mov	eax, 0
	mov	[ebp - 28], eax	; J_i
..@l1:
	mov	eax, [ebp - 28]	; J_i
	mov	ecx, 4
	cmp	eax, ecx
	jg	..@l2
	mov	eax, [ebp - 28]	; J_i
	mov	[ebp - 32], eax	; J_j
..@l3:
	mov	eax, [ebp - 32]	; J_j
	mov	ecx, 4
	cmp	eax, ecx
	jg	..@l4
	mov	eax, [ebp - 28]	; J_i
	lea	edi, [ebp - 8]	; J_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 36], ecx	; J_&1
	mov	eax, [ebp - 32]	; J_j
	lea	edi, [ebp - 8]	; J_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 40], ecx	; J_&2
	mov	eax, [ebp - 36]	; J_&1
	mov	ecx, [ebp - 40]	; J_&2
	cmp	eax, ecx
	jg	..@l5
	jmp	..@l6
..@l5:
	mov	edx, [ebp - 28]	; J_i
	lea	ecx, [ebp - 8]	; J_a
	imul	edx, 4
	sub	ecx, edx
	push	ecx
	mov	edx, [ebp - 32]	; J_j
	lea	ecx, [ebp - 8]	; J_a
	imul	edx, 4
	sub	ecx, edx
	push	ecx
	push	ebp		; push current ebp
	call	J_swap$IR$IR
	add	esp, 12
..@l6:
	mov	eax, [ebp - 32]	; J_j
	inc	eax
	mov	[ebp - 32], eax	; J_j
	jmp	..@l3
..@l4:
	mov	eax, [ebp - 32]	; J_j
	dec	eax
	mov	[ebp - 32], eax	; J_j
	mov	eax, [ebp - 28]	; J_i
	inc	eax
	mov	[ebp - 28], eax	; J_i
	jmp	..@l1
..@l2:
	mov	eax, [ebp - 28]	; J_i
	dec	eax
	mov	[ebp - 28], eax	; J_i
	mov	eax, 0
	mov	[ebp - 28], eax	; J_i
..@l7:
	mov	eax, [ebp - 28]	; J_i
	mov	ecx, 4
	cmp	eax, ecx
	jg	..@l8
	mov	eax, [ebp - 28]	; J_i
	lea	edi, [ebp - 8]	; J_a
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 44], ecx	; J_&3
	mov	eax, [ebp - 44]	; J_&3
	call	print_int
	mov	eax, [ebp - 28]	; J_i
	inc	eax
	mov	[ebp - 28], eax	; J_i
	jmp	..@l7
..@l8:
	mov	eax, [ebp - 28]	; J_i
	dec	eax
	mov	[ebp - 28], eax	; J_i
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
