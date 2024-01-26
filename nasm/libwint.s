section .text
        global  _start

_libwint:
        push    ebp
        mov     ebp, esp
        push    esi
        push    edi
        push    ebx
        xor     edi, edi
        cmp     eax, 0
        jnl     _noneneg@wint
        inc     edi
        neg     eax
_noneneg@wint:
        mov     ebx, 10
        xor     ecx, ecx
        mov     esi, _intbuf+15
_loopdigit@wint:
        xor     edx, edx
        div     ebx
        add     edx, '0'
        mov     byte[esi], dl
        dec     esi
        inc     ecx
        test    eax, eax
        jnz     _loopdigit@wint
        test    edi, edi
        jnz     _negsign@wint
        inc     esi
        jmp     _syswrite@wint
_negsign@wint:
        mov     byte[esi], '-'
        inc     ecx
_syswrite@wint:
        mov     edx, ecx
        mov     eax, 4
        mov     ebx, 1
        mov     ecx, esi
        int     0x80
        pop     ebx
        pop     edi
        pop     esi
        mov     esp, ebp
        pop     ebp
        ret

_start:
        mov     eax, 123
        call    _libwint
        mov     eax, 1
        xor     ebx, ebx
        int     0x80

section .data
        _intbuf db '????????????????', 0
