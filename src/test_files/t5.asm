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
	GLOBAL J_sa_pri_f$IV
J_sa_pri_f$IV:
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	push	ebx
	push	esi
	push	edi
	mov	eax, [ebp + 20]	; J_sa_pri_f$IV_n
	mov	ecx, 3
	cmp	eax, ecx
	jl	..@l1
	mov	ecx, [ebp + 20]	; J_sa_pri_f$IV_n
	mov	edx, 1
	sub	ecx, edx
	mov	[ebp - 8], ecx	; J_sa_pri_f$IV_&1
	mov	ecx, [ebp - 8]	; J_sa_pri_f$IV_&1
	push	ecx
	mov	edi, [ebp + 16]
	push	edi		; dup old ebp
	mov	edi, [ebp + 12]
	push	edi		; dup old ebp
	mov	edi, [ebp + 8]
	push	edi		; dup old ebp
	call	J_sa_pri_f$IV
	add	esp, 16
	mov	[ebp - 12], eax	; J_sa_pri_f$IV_&2
	mov	ecx, [ebp + 20]	; J_sa_pri_f$IV_n
	mov	edx, [ebp - 12]	; J_sa_pri_f$IV_&2
	imul	ecx, edx
	mov	[ebp - 16], ecx	; J_sa_pri_f$IV_&3
	mov	ecx, [ebp - 16]	; J_sa_pri_f$IV_&3
	mov	[ebp - 4], ecx	; set return value
	jmp	..@l2
..@l1:
	mov	ecx, [ebp + 20]	; J_sa_pri_f$IV_n
	mov	[ebp - 4], ecx	; set return value
..@l2:
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_sa_pri_prr
J_sa_pri_prr:
	push	ebp
	mov	ebp, esp
	sub	esp, 32
	push	ebx
	push	esi
	push	edi
	mov	ecx, 2
	mov	eax, 1
	mov	esi, [ebp + 16]
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, 1
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 8], ecx	; J_sa_pri_prr_&4
	mov	ecx, 2
	mov	eax, [ebp - 8]	; J_sa_pri_prr_&4
	mov	esi, [ebp + 16]
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, 1
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 12], ecx	; J_sa_pri_prr_&5
	mov	eax, [ebp - 12]	; J_sa_pri_prr_&5
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 16], ecx	; J_sa_pri_prr_&6
	mov	eax, 1
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 20], ecx	; J_sa_pri_prr_&7
	mov	ecx, [ebp - 16]	; J_sa_pri_prr_&6
	mov	eax, [ebp - 20]	; J_sa_pri_prr_&7
	mov	esi, [ebp + 16]
	lea	edi, [esi - 48]	; J_sa_pri_pe
	imul	eax, 4
	sub	edi, eax
	mov	[edi], ecx
	mov	eax, 1
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 24], ecx	; J_sa_pri_prr_&8
	mov	eax, [ebp - 24]	; J_sa_pri_prr_&8
	mov	esi, [ebp + 16]	; display array
	lea	edi, [esi - 48]	; J_sa_pri_pe
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 28], ecx	; J_sa_pri_prr_&9
	mov	eax, [ebp - 28]	; J_sa_pri_prr_&9
	call	print_int
	mov	esi, [ebp + 16]
	mov	ecx, [esi - 88]	; J_sa_pri_i
	mov	esi, [ebp + 16]
	mov	edx, [esi - 92]	; J_sa_pri_j
	add	ecx, edx
	mov	[ebp - 32], ecx	; J_sa_pri_prr_&10
	mov	ecx, [ebp - 32]	; J_sa_pri_prr_&10
	mov	esi, [ebp + 16]	; display var
	mov	[esi - 88], ecx	; J_sa_pri_i
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_sa_pri
J_sa_pri:
	push	ebp
	mov	ebp, esp
	sub	esp, 108
	push	ebx
	push	esi
	push	edi
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_sa_pri_prr
	add	esp, 12
	mov	ecx, 6
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 12]
	push	edi		; push old ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_sa_pri_f$IV
	add	esp, 16
	mov	[ebp - 96], eax	; J_sa_pri_&11
	mov	eax, 1
	lea	edi, [ebp - 8]	; J_sa_pri_he
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 100], ecx	; J_sa_pri_&12
	mov	eax, [ebp - 100]	; J_sa_pri_&12
	lea	edi, [ebp - 48]	; J_sa_pri_pe
	imul	eax, 4
	sub	edi, eax
	mov	ecx, [edi]
	mov	[ebp - 104], ecx	; J_sa_pri_&13
	xor	edx, edx
	mov	eax, [ebp - 96]	; J_sa_pri_&11
	mov	ecx, [ebp - 104]	; J_sa_pri_&13
	div	ecx
	mov	[ebp - 108], eax	; J_sa_pri_&14
	mov	eax, [ebp - 108]	; J_sa_pri_&14
	call	print_int
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_sa
J_sa:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ebx
	push	esi
	push	edi
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_sa_pri
	add	esp, 8
	pop	edi
	pop	esi
	pop	ebx
	mov	eax, [ebp - 4]
	mov	esp, ebp
	pop	ebp
	ret

SECTION .TEXT
	GLOBAL J_prn_fe$IR
J_prn_fe$IR:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	push	ebx
	push	esi
	push	edi
	mov	ecx, 22
	mov	esi, [ebp + 16]
	mov	[esi], ecx	; *J_prn_fe$IR_i
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
	sub	esp, 8
	push	ebx
	push	esi
	push	edi
	lea	ecx, [ebp - 8]	; J_prn_he
	push	ecx
	push	ebp		; push current ebp
	mov	edi, [ebp + 8]
	push	edi		; push old ebp
	call	J_prn_fe$IR
	add	esp, 12
	mov	eax, [ebp - 8]	; J_prn_he
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
	call	J_sa
	add	esp, 4
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
