BITS 32

EXTERN	fpc_get_output
EXTERN	fpc_write_text_shortstr
EXTERN	FPC_IOCHECK
EXTERN	fpc_writeln_end
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
	GLOBAL PASCALMAIN
PASCALMAIN:
	GLOBAL main
main:
..@c1:
		push	ebp
..@c3:
..@c4:
		mov	ebp,esp
..@c5:
		sub	esp,4
		mov	dword [ebp-4],ebx
		call	NEAR FPC_INITIALIZEUNITS
		mov	word [U_P$FORSTMT_B],1
		dec	word [U_P$FORSTMT_B]
	ALIGN 4
..@j5:
		inc	word [U_P$FORSTMT_B]
		call	NEAR fpc_get_output
		mov	ebx,eax
		mov	edx,ebx
		mov	ecx,dword _$FORSTMT$_Ld1
		mov	eax,0
		call	NEAR fpc_write_text_shortstr
		call	NEAR FPC_IOCHECK
		mov	eax,ebx
		call	NEAR fpc_writeln_end
		call	NEAR FPC_IOCHECK
		cmp	word [U_P$FORSTMT_B],10
		jl	NEAR ..@j5
		call	NEAR FPC_DO_EXIT
		mov	ebx,dword [ebp-4]
		leave
		ret
..@c2:

SECTION .text
; End asmlist al_procedures
; Begin asmlist al_globals

SECTION .bss
U_P$FORSTMT_B:	RESB	2

SECTION .bss
U_P$FORSTMT_CH:	RESB	1

SECTION .data
	ALIGN 4
	GLOBAL THREADVARLIST_P$FORSTMT
THREADVARLIST_P$FORSTMT:
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
	DD	THREADVARLIST_SYSTEM,THREADVARLIST_SI_PRC,THREADVARLIST_P$FORSTMT

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
_$FORSTMT$_Ld1:
		DB	2,"ha",0
; End asmlist al_typedconsts
; Begin asmlist al_rotypedconsts

SECTION .data
	ALIGN 2
TC_P$FORSTMT_A:
	DW	4
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
..@c6:
	DD	..@c8-..@c7
..@c7:
	DD	-1
	DB	1,0
	DB	8,12
	DB	5
	ALIGN 4
..@c8:
	DD	..@c10-..@c9
..@c9:
	DD	..@c6,..@c1,..@c2-..@c1
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
..@c10:
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

