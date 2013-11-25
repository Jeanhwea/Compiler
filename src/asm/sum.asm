; input an integer n
; print a value that equals \sum_1^n i
%include "io.asm"

section .text
	global main

sum:
	push	ebp
	mov 	ebp, esp
	mov	ecx, [ebp + 8]
	cmp	ecx, 1
	jz	one
	push	ecx
	dec	ecx

	push	ecx
	call	sum
	pop	ecx

	pop	ecx
	add	eax, ecx
	jmp	end
one:	
	mov	eax, 1
	jmp	end
end:
	pop	ebp
	ret
	;pop	esi
	;push	eax
	;mov	eax, esi
	;call	print_int
	;pop	eax
	;jmp	esi

main:
	push	ebp
	mov	ebp, esp
	call	scan_int
	push	eax
	call	sum
	; add	eip, 4
	; push	eip
	; jmp	sum
	call	print_int
	pop	ecx
	pop	ebp
	ret

