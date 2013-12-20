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
	GLOBAL J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR
J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 6
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 6
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 6
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 6
	mov	esi, [ebp + 24]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	mov	ecx, 6
	mov	esi, [ebp + 28]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	mov	ecx, 6
	mov	[ebp - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_i6
	mov	esi, [ebp + 12]
	mov	eax, [esi - 8]	; J_h1$IR_i1
	call	print_int
	mov	esi, [ebp + 16]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_i2
	call	print_int
	mov	esi, [ebp + 20]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_i3
	call	print_int
	mov	esi, [ebp + 24]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	call	print_int
	mov	esi, [ebp + 28]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	call	print_int
	mov	eax, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_i6
	call	print_int
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR
J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 5
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 5
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 5
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 5
	mov	esi, [ebp + 24]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	mov	ecx, 5
	mov	[ebp - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	mov	esi, [ebp + 12]
	mov	eax, [esi - 8]	; J_h1$IR_i1
	call	print_int
	mov	esi, [ebp + 16]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_i2
	call	print_int
	mov	esi, [ebp + 20]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_i3
	call	print_int
	mov	esi, [ebp + 24]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	call	print_int
	mov	eax, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	call	print_int
	lea	ecx, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 24]
	push	edi		; push old ebp
	mov	edi, [ebp + 20]
	push	edi		; push old ebp
	mov	edi, [ebp + 16]
	push	edi		; push old ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR
	add	esp, 28
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR_h3$IR_h4$IR
J_h1$IR_h2$IR_h3$IR_h4$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 4
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 4
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 4
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 4
	mov	[ebp - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	mov	esi, [ebp + 12]
	mov	eax, [esi - 8]	; J_h1$IR_i1
	call	print_int
	mov	esi, [ebp + 16]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_i2
	call	print_int
	mov	esi, [ebp + 20]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_h3$IR_i3
	call	print_int
	mov	eax, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	call	print_int
	lea	ecx, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 20]
	push	edi		; push old ebp
	mov	edi, [ebp + 16]
	push	edi		; push old ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR
	add	esp, 24
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR_h3$IR
J_h1$IR_h2$IR_h3$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 3
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 3
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 3
	mov	[ebp - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	esi, [ebp + 12]
	mov	eax, [esi - 8]	; J_h1$IR_i1
	call	print_int
	mov	esi, [ebp + 16]
	mov	eax, [esi - 8]	; J_h1$IR_h2$IR_i2
	call	print_int
	mov	eax, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_i3
	call	print_int
	lea	ecx, [ebp - 8]	; J_h1$IR_h2$IR_h3$IR_i3
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 16]
	push	edi		; push old ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR_h3$IR_h4$IR
	add	esp, 20
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR
J_h1$IR_h2$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 2
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 2
	mov	[ebp - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	esi, [ebp + 12]
	mov	eax, [esi - 8]	; J_h1$IR_i1
	call	print_int
	mov	eax, [ebp - 8]	; J_h1$IR_h2$IR_i2
	call	print_int
	lea	ecx, [ebp - 8]	; J_h1$IR_h2$IR_i2
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR_h3$IR
	add	esp, 16
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_h1$IR
J_h1$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	mov	ecx, 1
	mov	[ebp - 8], ecx	; J_h1$IR_i1
	mov	eax, [ebp - 8]	; J_h1$IR_i1
	call	print_int
	lea	ecx, [ebp - 8]	; J_h1$IR_i1
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_h1$IR_h2$IR
	add	esp, 12
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
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	lea	ecx, [ebp - 8]	; J_i0
	push	ecx
	push	ebp		; push current ebp
	call	J_h1$IR
	add	esp, 8
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
