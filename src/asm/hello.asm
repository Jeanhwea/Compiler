SECTION	.DATA
	msg:	db 'Hello world!', 10
	len: equ $-msg

SECTION .TEXT
	GLOBAL _start 

_start:
	; Write 'Hello world' to screen
	nop
	mov	eax, 4		; 'write' system call
	mov	ebx, 1		; file descriptor 1
	mov	ecx, msg	; string to write
	mov	edx, len	; length of string
	int	0x80		; call the kernel

	; Terminate program
	mov	eax, 1		; 'exit' system call
	mov	ebx, 0		; exit with error code 0
	int	0x80		; call the kernel
