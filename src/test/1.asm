; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_fac$IV
J_fac$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	mov	eax, [ebp + 12]	; J_fac$IV_n
	mov	ecx, 0x0
	cmp	eax, ecx
	jz	..@l1
	mov	ecx, [ebp + 12]	; J_fac$IV_n
	mov	edx, 0x1
	sub	ecx, edx
	mov	[ebp - 8], ecx	; J_fac$IV_&1
	mov	ecx, [ebp - 8]	; J_fac$IV_&1
	push	ecx
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_fac$IV
	add	esp, 8
	mov	[ebp - 12], eax	; J_fac$IV_&2
	mov	ecx, [ebp - 12]	; J_fac$IV_&2
	mov	edx, [ebp + 12]	; J_fac$IV_n
	imul	ecx, edx
	mov	[ebp - 16], ecx	; J_fac$IV_&3
	mov	ecx, [ebp - 16]	; J_fac$IV_&3
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
	GLOBAL main
main:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	mov	ecx, 0x0
	mov	[ebp - 8], ecx	; J_vn
..@l3:
	mov	eax, [ebp - 8]	; J_vn
	mov	ecx, 0x4
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
	mov	ecx, [ebp - 8]	; J_vn
	inc	ecx
	mov	[ebp - 8], ecx	; J_vn
	jmp	..@l3
..@l4:
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
