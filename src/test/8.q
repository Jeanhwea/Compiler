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
	ASS	0x0, -, J_ge_index
..@l7:
	GTT	J_ge_index, 0x9, ..@l8
	LOAD	J_ge_a, J_ge_index, J_ge_&4
	WRI	-, -, J_ge_&4
	INC	-, -, J_ge_index
	JMP	-, -, ..@l7
..@l8:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1                 J_ge_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
      &2                 J_ge_&2      -1	Tmp_Obj_t	Int_Type_t      -1       2       1
      &3                 J_ge_&3      -1	Tmp_Obj_t	Int_Type_t      -1       2       2
      &4                 J_ge_&4      -1	Tmp_Obj_t	Int_Type_t      -1       2       3
       a                  J_ge_a       2	Array_Obj_t	Int_Type_t      10       2       0
       b                  J_ge_b       3	Array_Obj_t	Int_Type_t      10       2      10
       c                  J_ge_c       4	Array_Obj_t	Int_Type_t      10       2      20
   index              J_ge_index       5	Var_Obj_t	Int_Type_t      -1       2      30
-----------------------------------------------------------
var = 31; tmp = 4; para = 0; level = 2
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
