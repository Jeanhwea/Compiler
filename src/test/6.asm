; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR
J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	ecx, 0x6
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 0x6
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 0x6
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 0x6
	mov	esi, [ebp + 24]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	mov	ecx, 0x6
	mov	esi, [ebp + 28]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	mov	ecx, 0x6
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
	mov	ecx, 0x5
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 0x5
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 0x5
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 0x5
	mov	esi, [ebp + 24]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	mov	ecx, 0x5
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
	mov	ecx, 0x4
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 0x4
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 0x4
	mov	esi, [ebp + 20]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_h3$IR_i3
	mov	ecx, 0x4
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
	mov	ecx, 0x3
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 0x3
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_h2$IR_i2
	mov	ecx, 0x3
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
	mov	ecx, 0x2
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 8], ecx	; J_h1$IR_i1
	mov	ecx, 0x2
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
	mov	ecx, 0x1
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
	lea	ecx, [ebp - 8]	; J_i0
	push	ecx
	push	ebp		; push current ebp
	call	J_h1$IR
	add	esp, 8
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
