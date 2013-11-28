J_TestCase09$IR:
	ASS	0x1, -, J_TestCase09$IR_a
	ASS	0x2, -, J_TestCase09$IR_b
	AARR	0x1, J_TestCase09$IR_a, J_TestCase09$IR_e
	AARR	0x2, J_TestCase09$IR_b, J_TestCase09$IR_f
	LOAD	J_TestCase09$IR_e, J_TestCase09$IR_a, J_TestCase09$IR_&1
	GTT	J_TestCase09$IR_&1, J_TestCase09$IR_a, ..@l1
	WRI	-, -, 0x2
	JMP	-, -, ..@l2
..@l1:
	WRI	-, -, 0x1
..@l2:
	LOAD	J_TestCase09$IR_f, J_TestCase09$IR_b, J_TestCase09$IR_&2
	LOAD	J_TestCase09$IR_e, J_TestCase09$IR_a, J_TestCase09$IR_&3
	GEQ	J_TestCase09$IR_&2, J_TestCase09$IR_&3, ..@l3
	WRI	-, -, 0x4
	JMP	-, -, ..@l4
..@l3:
	WRI	-, -, 0x3
..@l4:
	LOAD	J_TestCase09$IR_e, J_TestCase09$IR_a, J_TestCase09$IR_&4
	EQU	J_TestCase09$IR_&4, J_TestCase09$IR_a, ..@l5
	WRI	-, -, 0x7
	JMP	-, -, ..@l6
..@l5:
	WRI	-, -, 0x6
..@l6:
	LOAD	J_TestCase09$IR_f, J_TestCase09$IR_b, J_TestCase09$IR_&5
	NEQ	J_TestCase09$IR_&5, J_TestCase09$IR_a, ..@l7
	WRI	-, -, 0x9
	JMP	-, -, ..@l8
..@l7:
	WRI	-, -, 0x8
..@l8:
	LOAD	J_TestCase09$IR_f, J_TestCase09$IR_b, J_TestCase09$IR_&6
	LST	J_TestCase09$IR_&6, J_TestCase09$IR_a, ..@l9
	WRI	-, -, 0xb
	JMP	-, -, ..@l10
..@l9:
	WRI	-, -, 0xa
..@l10:
	LOAD	J_TestCase09$IR_e, J_TestCase09$IR_a, J_TestCase09$IR_&7
	LEQ	J_TestCase09$IR_b, J_TestCase09$IR_&7, ..@l11
	WRI	-, -, 0xd
	JMP	-, -, ..@l12
..@l11:
	WRI	-, -, 0xc
..@l12:
	LOAD	J_TestCase09$IR_e, J_TestCase09$IR_a, J_TestCase09$IR_&8
	NEQ	J_TestCase09$IR_&8, J_TestCase09$IR_a, ..@l13
	WRI	-, -, 0xe
	JMP	-, -, ..@l14
..@l13:
	WRI	-, -, 0xd
..@l14:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1      J_TestCase09$IR_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
      &2      J_TestCase09$IR_&2      -1	Tmp_Obj_t	Int_Type_t      -1       2       1
      &3      J_TestCase09$IR_&3      -1	Tmp_Obj_t	Int_Type_t      -1       2       2
      &4      J_TestCase09$IR_&4      -1	Tmp_Obj_t	Int_Type_t      -1       2       3
      &5      J_TestCase09$IR_&5      -1	Tmp_Obj_t	Int_Type_t      -1       2       4
      &6      J_TestCase09$IR_&6      -1	Tmp_Obj_t	Int_Type_t      -1       2       5
      &7      J_TestCase09$IR_&7      -1	Tmp_Obj_t	Int_Type_t      -1       2       6
      &8      J_TestCase09$IR_&8      -1	Tmp_Obj_t	Int_Type_t      -1       2       7
       a       J_TestCase09$IR_a       3	Var_Obj_t	Int_Type_t      -1       2       0
       b       J_TestCase09$IR_b       3	Var_Obj_t	Int_Type_t      -1       2       1
       e       J_TestCase09$IR_e       4	Array_Obj_t	Int_Type_t      10       2       2
       f       J_TestCase09$IR_f       4	Array_Obj_t	Int_Type_t      10       2      12
       k       J_TestCase09$IR_k       2	Para_Ref_Obj_t	Int_Type_t      -1       2       0
-----------------------------------------------------------
var = 22; tmp = 8; para = 1; level = 2
paralist = J_TestCase09$IR_k
***********************************************************
main:
	PUSHA	-, -, *J_k
	CALL	J_TestCase09$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
       k                     J_k       1	Var_Obj_t	Int_Type_t      -1       1       0
TestCase09         J_TestCase09$IR       2	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 1; tmp = 0; para = 0; level = 1
***********************************************************
