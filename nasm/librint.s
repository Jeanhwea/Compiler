section .text
        global  _start

_librint:
        push    ebp
        mov     ebp, esp
        push    esi
        push    edi
        push    ebx
_sysread@rint:
        mov     eax, 3
        mov     ebx, 0
        mov     ecx, _scanint
        mov     edx, 16
        int     0x80
_init@rint:
        xor     eax, eax
        xor     ecx, ecx
        mov     ebx, 1
        mov     esi, _scanint
_begchar@rint:
        mov     cl, byte[esi]
        cmp     ecx, '-'
        jz      _negnum@rint
        cmp     ecx, '0'
        jl      _skipchar@rint
        cmp     ecx, '9'
        jg      _skipchar@rint
        jmp     _numchar@rint
_skipchar@rint:
        inc     esi
        jmp     _begchar@rint
_negnum@rint:
        mov     ebx, -1
        inc     esi
_numchar@rint:
        mov     cl, byte[esi]
        cmp     ecx, '0'
        jl      _notdigit@rint
        cmp     ecx, '9'
        jg      _notdigit@rint
        sub     ecx, '0'
        imul    eax, 10
        add     eax, ecx
        inc     esi
        jmp     _numchar@rint
_notdigit@rint:
        imul    eax, ebx
        pop     ebx
        pop     edi
        pop     esi
        mov     esp, ebp
        pop     ebp
        ret

_start:
        call    _librint
        mov     ebx, eax
        mov     eax, 1
        int     0x80

section .data
        _scanint db '????????????????', 0
