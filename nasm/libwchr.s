section .text
	global	_start

_libwchr:
	push	ebp
	mov	ebp, esp
	push	esi
	push	edi
	push	ebx
	mov	[_chrbuf], eax
	mov	eax, 4
	mov	ebx, 1
	mov	ecx, _chrbuf
	mov	edx, 1
	int	0x80
	pop	ebx
	pop	edi
	pop	esi
	mov	esp, ebp
	pop	ebp
	ret

_start:
	mov	eax, 'a'
	call	_libwchr
	mov	eax, 1
	xor	ebx, ebx
	int	0x80

section .data
	_chrbuf db 'x', 0
