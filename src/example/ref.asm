
ref.o:     file format elf32-i386


Disassembly of section .text:

00000000 <P$V_VALUE$SMALLINT>:
   0:	55                   	push   %ebp
   1:	89 e5                	mov    %esp,%ebp
   3:	83 ec 04             	sub    $0x4,%esp
   6:	89 45 fc             	mov    %eax,-0x4(%ebp)
   9:	8b 45 fc             	mov    -0x4(%ebp),%eax
   c:	66 c7 00 07 00       	movw   $0x7,(%eax)
  11:	c9                   	leave  
  12:	c3                   	ret    
  13:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi
  1a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi

00000020 <PASCALMAIN>:
  20:	55                   	push   %ebp
  21:	89 e5                	mov    %esp,%ebp
  23:	83 ec 04             	sub    $0x4,%esp
  26:	89 5d fc             	mov    %ebx,-0x4(%ebp)
  29:	e8 fc ff ff ff       	call   2a <PASCALMAIN+0xa>
  2e:	b8 38 00 00 00       	mov    $0x38,%eax
  33:	e8 fc ff ff ff       	call   34 <PASCALMAIN+0x14>
  38:	e8 fc ff ff ff       	call   39 <PASCALMAIN+0x19>
  3d:	89 c3                	mov    %eax,%ebx
  3f:	0f bf 0d 38 00 00 00 	movswl 0x38,%ecx
  46:	89 da                	mov    %ebx,%edx
  48:	b8 00 00 00 00       	mov    $0x0,%eax
  4d:	e8 fc ff ff ff       	call   4e <PASCALMAIN+0x2e>
  52:	e8 fc ff ff ff       	call   53 <PASCALMAIN+0x33>
  57:	89 d8                	mov    %ebx,%eax
  59:	e8 fc ff ff ff       	call   5a <PASCALMAIN+0x3a>
  5e:	e8 fc ff ff ff       	call   5f <PASCALMAIN+0x3f>
  63:	e8 fc ff ff ff       	call   64 <PASCALMAIN+0x44>
  68:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  6b:	c9                   	leave  
  6c:	c3                   	ret    
  6d:	00 00                	add    %al,(%eax)
	...
