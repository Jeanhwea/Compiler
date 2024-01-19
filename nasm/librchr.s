section .text
	global	_start

_librchr:
	push	ebp
	mov	ebp, esp
	push	esi
	push	edi
	push	ebx
_sysread@rchr:
	mov	eax, 3
	mov	ebx, 0
	mov	ecx, _scanbuf
	mov	edx, 1
	int	0x80
	xor	ecx, ecx
	mov	cl, [_scanbuf]
	cmp	cl, 10
	jz	_sysread@rchr
	mov	eax, ecx
	pop	ebx
	pop	edi
	pop	esi
	mov	esp, ebp
	pop	ebp
	ret

_start:

section .data
	_scanbuf db '????????????????', 0
