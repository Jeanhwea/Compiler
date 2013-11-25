%include "asm/io.asm"

SECTION .TEXT
	GLOBAL J_pcd$IV$IV_sec_thr
J_pcd$IV$IV_sec_thr:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_pcd$IV$IV_sec
J_pcd$IV$IV_sec:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_pcd$IV$IV_sec1
J_pcd$IV$IV_sec1:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	edi, [ebp + 8]
	push	edi		; display
	call	J_pcd$IV$IV_sec
	add	esp, 8
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_pcd$IV$IV
J_pcd$IV$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 20
	mov	esi, [ebp + 8]	; J_vn
	mov	ecx, [esi - 8]
	mov	[ebp - 12], ecx	; J_pcd$IV$IV_vn2
	mov	ecx, [ebp + 16]	; J_pcd$IV$IV_x
	mov	[ebp - 12], ecx	; J_pcd$IV$IV_vn2
	mov	ecx, 0x5
	mov	[ebp - 16], ecx	; J_pcd$IV$IV_vn3
	mov	ecx, [ebp - 12]	; J_pcd$IV$IV_vn2
	mov	edx, [ebp - 16]	; J_pcd$IV$IV_vn3
	add	ecx, edx
	mov	[ebp - 20], ecx	; J_pcd$IV$IV_&1
	mov	ecx, [ebp - 20]	; J_pcd$IV$IV_&1
	mov	esi, [ebp + 8]
	mov	[esi - 8], ecx	; J_vn
	push	ebp		; display new
	mov	edi, [ebp + 8]
	push	edi		; display new
	call	J_pcd$IV$IV_sec1
	add	esp, 8
	mov	eax, [ebp + 12]	; J_pcd$IV$IV_y
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
	sub	esp, 24
	mov	ecx, 0x1
	mov	[ebp - 8], ecx	; J_vn
	mov	ecx, 0x8
	mov	eax, 0x1
	lea	edi, [ebp - 12]	; J_A
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, [ebp - 8]	; J_vn
	lea	edi, [ebp - 12]	; J_A
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 24], ecx	; J_&2
	mov	eax, [ebp - 24]	; J_&2
	call	print_int
	push	0x4
	mov	ecx, [ebp - 8]	; J_vn
	push	ecx
	push	ebp		; display new
	call	J_pcd$IV$IV
	add	esp, 12
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret
