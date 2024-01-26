section .text
        global  _start

_libwstr:
        push    ebp
        mov     ebp, esp
        push    esi
        push    edi
        push    ebx
        mov     esi, eax
        xor     ecx, ecx
_nextchar@wstr:
        mov     cl, byte[esi]
        test    ecx, ecx
        jz      _syswrite@wstr
        inc     esi
        jmp     _nextchar@wstr
_syswrite@wstr:
        sub     esi, eax
        mov     ecx, eax
        mov     eax, 4
        mov     ebx, 1
        mov     edx, esi
        int     0x80
        pop     ebx
        pop     edi
        pop     esi
        mov     esp, ebp
        pop     ebp
        ret

_start:
        lea     eax, msg
        call    _libwstr
        mov     eax, 1
        xor     ebx, ebx
        int     0x80

section .data
        msg db 'hello', 0
