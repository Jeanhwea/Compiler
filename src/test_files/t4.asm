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
	GLOBAL J_pri_f$IV
J_pri_f$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	push	ebx
	push	esi
	push	edi
	mov	eax, [ebp + 16]	; J_pri_f$IV_n
	mov	ecx, 3
	cmp	eax, ecx
	jl	..@l1
	mov	eax, [ebp + 16]	; J_pri_f$IV_n
	mov	ecx, 1
	sub	eax, ecx
	mov	[ebp - 8], eax	; J_pri_f$IV_&1
	mov	ecx, [ebp - 8]	; J_pri_f$IV_&1
	push	ecx
	mov	edi, [ebp + 12]
	push	edi		; dup old ebp
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_pri_f$IV
	add	esp, 12
	mov	[ebp - 12], eax	; J_pri_f$IV_&2
	mov	eax, [ebp + 16]	; J_pri_f$IV_n
	mov	ecx, [ebp - 12]	; J_pri_f$IV_&2
	imul	eax, ecx
	mov	[ebp - 16], eax	; J_pri_f$IV_&3
	mov	eax, [ebp - 16]	; J_pri_f$IV_&3
	mov	[ebp - 4], eax	; set return value
	jmp	..@l2
..@l1:
	mov	eax, [ebp + 16]	; J_pri_f$IV_n
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
	GLOBAL J_pri
J_pri:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 5
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_pri_f$IV
	add	esp, 12
	mov	[ebp - 8], eax	; J_pri_&4
	mov	eax, [ebp - 8]	; J_pri_&4
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
	call	J_pri
	add	esp, 4
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
