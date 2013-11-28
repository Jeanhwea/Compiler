J_ge:
	ASS	0x0, -, J_ge_index
..@l1:
	GTT	J_ge_index, 0x9, ..@l2
	AARR	J_ge_index, J_ge_index, J_ge_c
	INC	-, -, J_ge_index
	JMP	-, -, ..@l1
..@l2:
	ASS	0x0, -, J_ge_index
..@l3:
	GTT	J_ge_index, 0x9, ..@l4
	LOAD	J_ge_c, J_ge_index, J_ge_&1
	AARR	J_ge_index, J_ge_&1, J_ge_b
	INC	-, -, J_ge_index
	JMP	-, -, ..@l3
..@l4:
	ASS	0x0, -, J_ge_index
..@l5:
	GTT	J_ge_index, 0x9, ..@l6
	LOAD	J_ge_c, J_ge_index, J_ge_&3
	LOAD	J_ge_b, J_ge_&3, J_ge_&2
	AARR	J_ge_index, J_ge_&2, J_ge_a
	INC	-, -, J_ge_index
	JMP	-, -, ..@l5
..@l6:
	LOAD	J_ge_c, 0x5, J_ge_&4
	LOAD	J_ge_c, 0x1, J_ge_&7
	LOAD	J_ge_b, J_ge_&7, J_ge_&6
	MUL	J_ge_&4, J_ge_&6, J_ge_&5
	LOAD	J_ge_c, 0x2, J_ge_&11
	LOAD	J_ge_b, J_ge_&11, J_ge_&10
	LOAD	J_ge_c, 0x2, J_ge_&13
	MUL	J_ge_&10, J_ge_&13, J_ge_&12
	LOAD	J_ge_a, J_ge_&12, J_ge_&9
	ADD	J_ge_&5, J_ge_&9, J_ge_&8
	LOAD	J_ge_b, 0x2, J_ge_&15
	SUB	J_ge_&8, J_ge_&15, J_ge_&14
	ASS	J_ge_&14, -, J_ge_final
	ASS	0x0, -, J_ge_index
..@l7:
	GTT	J_ge_index, 0x9, ..@l8
	LOAD	J_ge_a, J_ge_index, J_ge_&16
	WRI	-, -, J_ge_&16
	INC	-, -, J_ge_index
	JMP	-, -, ..@l7
..@l8:
	WRI	-, -, J_ge_final
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     &10                J_ge_&10      -1	Tmp_Obj_t	Int_Type_t      -1       2       9
     &11                J_ge_&11      -1	Tmp_Obj_t	Int_Type_t      -1       2      10
     &12                J_ge_&12      -1	Tmp_Obj_t	Int_Type_t      -1       2      11
     &13                J_ge_&13      -1	Tmp_Obj_t	Int_Type_t      -1       2      12
     &14                J_ge_&14      -1	Tmp_Obj_t	Int_Type_t      -1       2      13
     &15                J_ge_&15      -1	Tmp_Obj_t	Int_Type_t      -1       2      14
     &16                J_ge_&16      -1	Tmp_Obj_t	Int_Type_t      -1       2      15
      &1                 J_ge_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
      &2                 J_ge_&2      -1	Tmp_Obj_t	Int_Type_t      -1       2       1
      &3                 J_ge_&3      -1	Tmp_Obj_t	Int_Type_t      -1       2       2
      &4                 J_ge_&4      -1	Tmp_Obj_t	Int_Type_t      -1       2       3
      &5                 J_ge_&5      -1	Tmp_Obj_t	Int_Type_t      -1       2       4
      &6                 J_ge_&6      -1	Tmp_Obj_t	Int_Type_t      -1       2       5
      &7                 J_ge_&7      -1	Tmp_Obj_t	Int_Type_t      -1       2       6
      &8                 J_ge_&8      -1	Tmp_Obj_t	Int_Type_t      -1       2       7
      &9                 J_ge_&9      -1	Tmp_Obj_t	Int_Type_t      -1       2       8
       a                  J_ge_a       2	Array_Obj_t	Int_Type_t      10       2       0
       b                  J_ge_b       3	Array_Obj_t	Int_Type_t      10       2      10
       c                  J_ge_c       4	Array_Obj_t	Int_Type_t      10       2      20
   final              J_ge_final       6	Var_Obj_t	Int_Type_t      -1       2      31
   index              J_ge_index       5	Var_Obj_t	Int_Type_t      -1       2      30
-----------------------------------------------------------
var = 32; tmp = 16; para = 0; level = 2
***********************************************************
main:
	CALL	J_ge, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      ge                    J_ge       1	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 1
***********************************************************
