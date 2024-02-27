section .data
	hello db 'Hello, World!', 10, 0

section .text
	global _start

_start:
	; write the string to stdout
	mov eax, 4         ; system call number for sys_write
	mov ebx, 1         ; file descriptor 1 is stdout
	mov ecx, hello     ; pointer to the message
	mov edx, 14        ; length of the message
	int 0x80           ; interrupt to invoke system call

	; exit the program
	mov eax, 1         ; system call number for sys_exit
	xor ebx, ebx       ; exit code 0
	int 0x80           ; interrupt to invoke system call
