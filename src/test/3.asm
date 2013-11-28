; ELF32 on Ubuntu 12.04 
; NASM version 2.09.10 
; GCC version 4.6.3 
%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_hh_pri_he
J_hh_pri_he:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, 0x2
	mov	esi, [ebp + 12]
	mov	eax, [esi - 48]	; J_hh_i
	mov	esi, [ebp + 12]
	lea	edi, [esi - 8]	; J_hh_ar
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_hh_pri
J_hh_pri:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	ecx, 0x1
	mov	esi, [ebp + 12]	; display var
	mov	[esi - 48], ecx	; J_hh_i
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_hh_pri_he
	add	esp, 12
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_hh
J_hh:
	push	ebp
	mov	ebp, esp
	sub	esp, 52
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_hh_pri
	add	esp, 8
	mov	eax, [ebp - 48]	; J_hh_i
	lea	edi, [ebp - 8]	; J_hh_ar
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 52], ecx	; J_hh_&1
	mov	eax, [ebp - 52]	; J_hh_&1
	call	print_int
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
	push	ebp		; push current ebp
	call	J_hh
	add	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
