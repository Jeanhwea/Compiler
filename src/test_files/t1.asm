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
	GLOBAL J_fac$IV
J_fac$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	push	ebx
	push	esi
	push	edi
	mov	eax, [ebp + 12]	; J_fac$IV_n
	mov	ecx, 0
	cmp	eax, ecx
	jz	..@l1
	mov	eax, [ebp + 12]	; J_fac$IV_n
	mov	ecx, 1
	sub	eax, ecx
	mov	[ebp - 8], eax	; J_fac$IV_&1
	mov	ecx, [ebp - 8]	; J_fac$IV_&1
	push	ecx
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_fac$IV
	add	esp, 8
	mov	[ebp - 12], eax	; J_fac$IV_&2
	mov	eax, [ebp - 12]	; J_fac$IV_&2
	mov	ecx, [ebp + 12]	; J_fac$IV_n
	imul	eax, ecx
	mov	[ebp - 16], eax	; J_fac$IV_&3
	mov	eax, [ebp - 16]	; J_fac$IV_&3
	mov	[ebp - 4], eax	; set return value
	jmp	..@l2
..@l1:
	mov	eax, 1
	mov	[ebp - 4], eax	; set return value
..@l2:
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
	sub	esp, 16
	push	ebx
	push	esi
	push	edi
	mov	eax, 0
	mov	[ebp - 8], eax	; J_vn
..@l3:
	mov	eax, [ebp - 8]	; J_vn
	mov	ecx, 4
	cmp	eax, ecx
	jg	..@l4
	mov	ecx, [ebp - 8]	; J_vn
	push	ecx
	push	ebp		; push current ebp
	call	J_fac$IV
	add	esp, 8
	mov	[ebp - 16], eax	; J_&4
	mov	eax, [ebp - 16]	; J_&4
	call	print_int
	mov	eax, [ebp - 8]	; J_vn
	inc	eax
	mov	[ebp - 8], eax	; J_vn
	jmp	..@l3
..@l4:
	mov	eax, [ebp - 8]	; J_vn
	dec	eax
	mov	[ebp - 8], eax	; J_vn
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
