%define sys_exit 1
%define sys_read 3
%define sys_write 4
%define stdout 1

section .data
	newline:	db 0x0a

section .bss
	char:	resb 1

section .text
	global main

main:
	push	ebp
	mov	ebp, esp
	call	read
	call	write
	mov	esp, ebp
	pop	ebp
	xor	eax, eax
	jmp	exit

write:
	push	ebp
	mov	ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	mov	eax, sys_write
	mov	ebx, stdout
	mov	ecx, char
	mov	edx, 0x1
	int	0x80 
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	mov	esp, ebp
	pop	ebp
	ret

read:
	push	ebp
	mov	ebp, esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	mov	eax, sys_read
	mov	ebx, stdout
	mov	ecx, char
	mov	edx, 0x1
	int	0x80
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	mov	esp, ebp
	pop	ebp
	ret

exit:
	mov	eax, sys_exit
	int	0x80
