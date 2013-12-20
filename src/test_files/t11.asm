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
	GLOBAL J_prn_swap$IR$IR
J_prn_swap$IR$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	esi, [ebp + 20]
	mov	ecx, [esi]	; *J_prn_swap$IR$IR_i
	mov	[ebp - 8], ecx	; J_prn_swap$IR$IR_temp
	mov	esi, [ebp + 16]
	mov	ecx, [esi]	; *J_prn_swap$IR$IR_j
	mov	esi, [ebp + 20]
	mov	[esi], ecx	; *J_prn_swap$IR$IR_i
	mov	ecx, [ebp - 8]	; J_prn_swap$IR$IR_temp
	mov	esi, [ebp + 16]
	mov	[esi], ecx	; *J_prn_swap$IR$IR_j
	pop	edi
	pop	esi
	pop	ebx
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
	push	ebx
	push	esi
	push	edi
	mov	ecx, 1
	mov	eax, 0
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 3
	mov	eax, 1
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 2
	mov	eax, 2
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 4
	mov	eax, 3
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 5
	mov	eax, 4
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0
	mov	[ebp - 48], ecx	; J_prn_i
..@l1:
	mov	eax, [ebp - 48]	; J_prn_i
	mov	ecx, 4
	cmp	eax, ecx
	jg	..@l2
	mov	ecx, 0
	mov	[ebp - 52], ecx	; J_prn_j
..@l3:
	mov	eax, [ebp - 52]	; J_prn_j
	mov	ecx, 4
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
	mov	ecx, 0
	mov	[ebp - 48], ecx	; J_prn_i
..@l7:
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 64], ecx	; J_prn_&3
	mov	ecx, [ebp - 64]	; J_prn_&3
	mov	edx, 1
	add	ecx, edx
	mov	[ebp - 68], ecx	; J_prn_&4
	mov	ecx, [ebp - 68]	; J_prn_&4
	mov	eax, [ebp - 48]	; J_prn_i
	lea	edi, [ebp - 8]	; J_prn_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, [ebp - 48]	; J_prn_i
	mov	edx, 1
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
	mov	ecx, 4
	cmp	eax, ecx
	jz	..@l8
	jmp	..@l7
..@l8:
	mov	ecx, 0
	mov	[ebp - 48], ecx	; J_prn_i
..@l9:
	mov	eax, [ebp - 48]	; J_prn_i
	mov	ecx, 4
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
	call	J_prn
	add	esp, 4
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
