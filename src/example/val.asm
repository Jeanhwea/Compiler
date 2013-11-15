
val.o:     file format elf32-i386


Disassembly of section .text:

00000000 <P$V_VALUE$SMALLINT>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 04             	sub    $0x4,%esp
   6:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
   a:	66 c7 45 fc 07 00    	movw   $0x7,-0x4(%ebp)
  10:	c9                   	leave  
  11:	c3                   	ret    
  12:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  19:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00000020 <PASCALMAIN>:
  20:	55                   	push   %ebp
  21:	89 e5                	mov    %esp,%ebp
  23:	83 ec 04             	sub    $0x4,%esp
  26:	89 5d fc             	mov    %ebx,-0x4(%ebp)
  29:	e8 fc ff ff ff       	call   2a <PASCALMAIN+0xa>
  2e:	66 a1 38 00 00 00    	mov    0x38,%ax
  34:	e8 fc ff ff ff       	call   35 <PASCALMAIN+0x15>
  39:	e8 fc ff ff ff       	call   3a <PASCALMAIN+0x1a>
  3e:	89 c3                	mov    %eax,%ebx
  40:	0f bf 0d 38 00 00 00 	movswl 0x38,%ecx
  47:	89 da                	mov    %ebx,%edx
  49:	b8 00 00 00 00       	mov    $0x0,%eax
  4e:	e8 fc ff ff ff       	call   4f <PASCALMAIN+0x2f>
  53:	e8 fc ff ff ff       	call   54 <PASCALMAIN+0x34>
  58:	89 d8                	mov    %ebx,%eax
  5a:	e8 fc ff ff ff       	call   5b <PASCALMAIN+0x3b>
  5f:	e8 fc ff ff ff       	call   60 <PASCALMAIN+0x40>
  64:	e8 fc ff ff ff       	call   65 <PASCALMAIN+0x45>
  69:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  6c:	c9                   	leave  
  6d:	c3                   	ret    
	...
