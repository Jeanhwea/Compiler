BITS 32

EXTERN	fpc_get_output
EXTERN	fpc_write_text_sint
EXTERN	FPC_IOCHECK
EXTERN	fpc_writeln_end
EXTERN	fpc_write_text_shortstr
EXTERN	FPC_INITIALIZEUNITS
EXTERN	FPC_DO_EXIT
EXTERN	INIT$_SYSTEM
EXTERN	THREADVARLIST_SYSTEM
EXTERN	THREADVARLIST_SI_PRC
; Begin asmlist al_begin
; End asmlist al_begin
; Begin asmlist al_stabs
; End asmlist al_stabs
; Begin asmlist al_procedures

SECTION .text
	ALIGN 16
	GLOBAL P$DUPFUN_BAR$SMALLINT$SMALLINT$SMALLINT$SMALLINT$SMALLINT$CHAR
P$DUPFUN_BAR$SMALLINT$SMALLINT$SMALLINT$SMALLINT$SMALLINT$CHAR:
..@c1:
		push	ebp
..@c3:
..@c4:
		mov	ebp,esp
..@c5:
		sub	esp,12
		mov	word [ebp-4],ax
		mov	word [ebp-8],dx
		mov	word [ebp-12],cx
		movsx	eax,word [ebp-4]
		movsx	edx,word [ebp-8]
		add	eax,edx
		movsx	edx,word [ebp-12]
		add	eax,edx
		movsx	edx,word [ebp+16]
		add	eax,edx
		movsx	edx,word [ebp+12]
		add	eax,edx
		mov	word [U_P$DUPFUN_A],ax
		leave
		ret	12
..@c2:

SECTION .text
	ALIGN 16
	GLOBAL P$DUPFUN_NICE
P$DUPFUN_NICE:
..@c6:
		push	ebp
..@c8:
..@c9:
		mov	ebp,esp
..@c10:
		leave
		ret
..@c7:

SECTION .text
	ALIGN 16
	GLOBAL P$DUPFUN_FOO$$SMALLINT
P$DUPFUN_FOO$$SMALLINT:
..@c11:
		push	ebp
..@c13:
..@c14:
		mov	ebp,esp
..@c15:
		sub	esp,8
		mov	eax,ebp
		call	NEAR P$DUPFUN_FOO$$SMALLINT_BAR
		mov	ax,word [U_P$DUPFUN_A]
		mov	word [ebp-4],ax
		mov	ax,word [ebp-4]
		leave
		ret
..@c12:

SECTION .text
	ALIGN 16
	GLOBAL P$DUPFUN_FOO$$SMALLINT_BAR
P$DUPFUN_FOO$$SMALLINT_BAR:
..@c16:
		push	ebp
..@c18:
..@c19:
		mov	ebp,esp
..@c20:
		sub	esp,4
		mov	dword [ebp-4],eax
		mov	eax,dword [ebp-4]
		mov	word [eax-8],1
		leave
		ret
..@c17:

SECTION .text
	ALIGN 16
	GLOBAL PASCALMAIN
PASCALMAIN:
	GLOBAL main
main:
..@c21:
		push	ebp
..@c23:
..@c24:
		mov	ebp,esp
..@c25:
		sub	esp,4
		mov	dword [ebp-4],ebx
		call	NEAR FPC_INITIALIZEUNITS
		call	NEAR fpc_get_output
		mov	ebx,eax
		movsx	ecx,word [U_P$DUPFUN_A]
		mov	edx,ebx
		mov	eax,0
		call	NEAR fpc_write_text_sint
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		call	NEAR fpc_get_output
		mov	ebx,eax
		mov	edx,ebx
		mov	ecx,dword _$DUPFUN$_Ld1
		mov	eax,0
		call	NEAR fpc_write_text_shortstr
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		call	NEAR FPC_DO_EXIT
		mov	ebx,dword [ebp-4]
		leave
		ret
..@c22:

SECTION .text
; End asmlist al_procedures
; Begin asmlist al_globals

SECTION .bss
U_P$DUPFUN_A:	RESB	2

SECTION .bss
U_P$DUPFUN_B:	RESB	2

SECTION .bss
U_P$DUPFUN_C:	RESB	2

SECTION .bss
U_P$DUPFUN_D:	RESB	2

SECTION .bss
U_P$DUPFUN_E:	RESB	2

SECTION .bss
U_P$DUPFUN_CH:	RESB	1

SECTION .bss
U_P$DUPFUN_AAAAAAAAA:	RESB	20

SECTION .data
	ALIGN 4
	GLOBAL THREADVARLIST_P$DUPFUN
THREADVARLIST_P$DUPFUN:
	DD	0

SECTION .data
	ALIGN 4
	GLOBAL INITFINAL
INITFINAL	DD	1,0
	DD	INIT$_SYSTEM,0

SECTION .data
	ALIGN 4
	GLOBAL FPC_THREADVARTABLES
FPC_THREADVARTABLES	DD	3
	DD	THREADVARLIST_SYSTEM,THREADVARLIST_SI_PRC,THREADVARLIST_P$DUPFUN

SECTION .data
	ALIGN 4
	GLOBAL FPC_RESOURCESTRINGTABLES
FPC_RESOURCESTRINGTABLES	DD	0

SECTION .fpc
	ALIGN 8
		DB	"FPC 2.4.4-3.1 [2012/01/04] for i386 - Linux"

SECTION .data
	ALIGN 4
	GLOBAL __stklen
__stklen	DD	8388608

SECTION .data
	ALIGN 4
	GLOBAL __heapsize
__heapsize	DD	0

SECTION .data
	GLOBAL __fpc_valgrind
__fpc_valgrind	DB	0

SECTION .data
	ALIGN 4
	GLOBAL FPC_RESLOCATION
FPC_RESLOCATION	DD	0
; End asmlist al_globals
; Begin asmlist al_const
; End asmlist al_const
; Begin asmlist al_typedconsts

SECTION .rodata
	ALIGN 4
_$DUPFUN$_Ld1:
		DB	17,"too long llllllll",0
; End asmlist al_typedconsts
; Begin asmlist al_rotypedconsts

SECTION .data
	ALIGN 2
TC_P$DUPFUN_CCCCCCCCCCCONST:
	DW	1
; End asmlist al_rotypedconsts
; Begin asmlist al_threadvars
; End asmlist al_threadvars
; Begin asmlist al_imports
; End asmlist al_imports
; Begin asmlist al_exports
; End asmlist al_exports
; Begin asmlist al_resources
; End asmlist al_resources
; Begin asmlist al_rtti
; End asmlist al_rtti
; Begin asmlist al_dwarf_frame

SECTION .debug_frame
..@c26:
	DD	..@c28-..@c27
..@c27:
	DD	-1
	DB	1,0
	DB	8,12
	DB	5
	ALIGN 4
..@c28:
	DD	..@c30-..@c29
..@c29:
	DD	..@c26,..@c1,..@c2-..@c1
	DB	4
	DD	..@c3-..@c1
	DB	14
	DB	4
	DD	..@c4-..@c3
	DB	5
	DB	4
	DD	..@c5-..@c4
	DB	13
	ALIGN 4
..@c30:
	DD	..@c32-..@c31
..@c31:
	DD	..@c26,..@c6,..@c7-..@c6
	DB	4
	DD	..@c8-..@c6
	DB	14
	DB	4
	DD	..@c9-..@c8
	DB	5
	DB	4
	DD	..@c10-..@c9
	DB	13
	ALIGN 4
..@c32:
	DD	..@c34-..@c33
..@c33:
	DD	..@c26,..@c11,..@c12-..@c11
	DB	4
	DD	..@c13-..@c11
	DB	14
	DB	4
	DD	..@c14-..@c13
	DB	5
	DB	4
	DD	..@c15-..@c14
	DB	13
	ALIGN 4
..@c34:
	DD	..@c36-..@c35
..@c35:
	DD	..@c26,..@c16,..@c17-..@c16
	DB	4
	DD	..@c18-..@c16
	DB	14
	DB	4
	DD	..@c19-..@c18
	DB	5
	DB	4
	DD	..@c20-..@c19
	DB	13
	ALIGN 4
..@c36:
	DD	..@c38-..@c37
..@c37:
	DD	..@c26,..@c21,..@c22-..@c21
	DB	4
	DD	..@c23-..@c21
	DB	14
	DB	4
	DD	..@c24-..@c23
	DB	5
	DB	4
	DD	..@c25-..@c24
	DB	13
	ALIGN 4
..@c38:
; End asmlist al_dwarf_frame
; Begin asmlist al_dwarf_info
; End asmlist al_dwarf_info
; Begin asmlist al_dwarf_abbrev
; End asmlist al_dwarf_abbrev
; Begin asmlist al_dwarf_line
; End asmlist al_dwarf_line
; Begin asmlist al_picdata
; End asmlist al_picdata
; Begin asmlist al_resourcestrings
; End asmlist al_resourcestrings
; Begin asmlist al_end
; End asmlist al_end

