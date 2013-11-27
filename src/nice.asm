; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_outter$IV_writeoo
J_outter$IV_writeoo:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, 0x8ae
	call	print_int
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_outter$IV_foo$IV_pcd$IV_sum$IR
J_outter$IV_foo$IV_pcd$IV_sum$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 20
	mov	esi, [ebp + 24]
	mov	ecx, [esi]	; *J_outter$IV_foo$IV_pcd$IV_sum$IR_x
	mov	edx, 0x1
	sub	ecx, edx
	mov	[ebp - 12], ecx	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&1
	mov	ecx, [ebp - 12]	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&1
	mov	[ebp - 8], ecx	; J_outter$IV_foo$IV_pcd$IV_sum$IR_t
	mov	esi, [ebp + 24]
	mov	eax, [esi]	; *J_outter$IV_foo$IV_pcd$IV_sum$IR_x
	mov	ecx, 0x1
	cmp	eax, ecx	
	jz	..@l1
	lea	ecx, [ebp - 8]	; J_outter$IV_foo$IV_pcd$IV_sum$IR_t
	push	ecx
	mov	edi, [ebp + 20]
	push	edi		; dup old ebp
	mov	edi, [ebp + 16]
	push	edi		; dup old ebp
	mov	edi, [ebp + 12]
	push	edi		; dup old ebp
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_outter$IV_foo$IV_pcd$IV_sum$IR
	add	esp, 20
	mov	[ebp - 16], eax	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&2
	mov	ecx, [ebp - 16]	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&2
	mov	esi, [ebp + 24]
	mov	edx, [esi]	; *J_outter$IV_foo$IV_pcd$IV_sum$IR_x
	add	ecx, edx
	mov	[ebp - 20], ecx	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&3
	mov	ecx, [ebp - 20]	; J_outter$IV_foo$IV_pcd$IV_sum$IR_&3
	mov	[ebp - 4], ecx	; set return value
	jmp	..@l2
..@l1:
	mov	ecx, 0x1
	mov	[ebp - 4], ecx	; set return value
..@l2:
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_outter$IV_foo$IV_pcd$IV
J_outter$IV_foo$IV_pcd$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 12
	mov	ecx, [ebp + 20]	; J_outter$IV_foo$IV_pcd$IV_x
	mov	[ebp - 8], ecx	; J_outter$IV_foo$IV_pcd$IV_t
	lea	ecx, [ebp - 8]	; J_outter$IV_foo$IV_pcd$IV_t
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 16]
	push	edi		; push old ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_outter$IV_foo$IV_pcd$IV_sum$IR
	add	esp, 20
	mov	[ebp - 12], eax	; J_outter$IV_foo$IV_pcd$IV_&4
	mov	ecx, [ebp - 12]	; J_outter$IV_foo$IV_pcd$IV_&4
	mov	esi, [ebp + 8]	; display var
	mov	[esi - 12], ecx	; J_out
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_outter$IV_foo$IV
J_outter$IV_foo$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, [ebp + 16]	; J_outter$IV_foo$IV_y
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_outter$IV_foo$IV_pcd$IV
	add	esp, 16
	mov	edi, [ebp + 12]
	push	edi		; dup old ebp
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_outter$IV_writeoo
	add	esp, 8
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_outter$IV
J_outter$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, [ebp + 12]	; J_outter$IV_y
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_outter$IV_foo$IV
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
	sub	esp, 84
	mov	ecx, 0x20
	mov	eax, 0x0
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x2
	mov	eax, 0x1
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x80
	mov	eax, 0x2
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	ecx, 0x20
	mov	eax, 0x3
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, 0x0
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 60], ecx	; J_&5
	mov	eax, 0x1
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 68], ecx	; J_&7
	xor	edx, edx
	mov	eax, [ebp - 60]	; J_&5
	mov	ecx, [ebp - 68]	; J_&7
	div	ecx
	mov	[ebp - 64], eax	; J_&6
	mov	eax, [ebp - 64]	; J_&6
	call	print_int
	mov	eax, 0x1
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 72], ecx	; J_&8
	mov	eax, 0x3
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 80], ecx	; J_&10
	mov	ecx, [ebp - 72]	; J_&8
	mov	edx, [ebp - 80]	; J_&10
	imul	ecx, edx
	mov	[ebp - 76], ecx	; J_&9
	mov	eax, [ebp - 76]	; J_&9
	call	print_int
	mov	ecx, 0x0
	mov	[ebp - 16], ecx	; J_i
..@l3:
	mov	eax, [ebp - 16]	; J_i
	mov	ecx, 0x3
	cmp	eax, ecx	
	jg	..@l4
	mov	eax, [ebp - 16]	; J_i
	lea	edi, [ebp - 20]	; J_A
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 84], ecx	; J_&11
	mov	eax, [ebp - 84]	; J_&11
	call	print_int
	mov	ecx, [ebp - 16]	; J_i
	inc	ecx
	mov	[ebp - 16], ecx	; J_i
	jmp	..@l3
..@l4:
	mov	ecx, 0x64
	mov	[ebp - 8], ecx	; J_vn
	mov	ecx, [ebp - 8]	; J_vn
	push	ecx
	push	ebp		; push current ebp
	call	J_outter$IV
	add	esp, 8
	mov	eax, [ebp - 12]	; J_out
	call	print_int
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
