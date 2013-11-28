J_prn_swap$IR$IR:
	ASS	J_prn_swap$IR$IR_i, -, J_prn_swap$IR$IR_temp
	ASS	J_prn_swap$IR$IR_j, -, J_prn_swap$IR$IR_i
	ASS	J_prn_swap$IR$IR_temp, -, J_prn_swap$IR$IR_j
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
    temp   J_prn_swap$IR$IR_temp       6	Var_Obj_t	Int_Type_t      -1       3       0
       i      J_prn_swap$IR$IR_i       5	Para_Ref_Obj_t	Int_Type_t      -1       3       0
       j      J_prn_swap$IR$IR_j       5	Para_Ref_Obj_t	Int_Type_t      -1       3       1
-----------------------------------------------------------
var = 1; tmp = 0; para = 2; level = 3
paralist = J_prn_swap$IR$IR_i
paralist = J_prn_swap$IR$IR_j
***********************************************************
J_prn:
	AARR	0x1, 0x0, J_prn_he
	AARR	0x3, 0x1, J_prn_he
	AARR	0x2, 0x2, J_prn_he
	AARR	0x4, 0x3, J_prn_he
	AARR	0x5, 0x4, J_prn_he
	ASS	0x0, -, J_prn_i
..@l1:
	GTT	J_prn_i, 0x4, ..@l2
	ASS	0x0, -, J_prn_j
..@l3:
	GTT	J_prn_j, 0x4, ..@l4
	LOAD	J_prn_he, J_prn_i, J_prn_&1
	LOAD	J_prn_he, J_prn_j, J_prn_&2
	GTT	J_prn_&1, J_prn_&2, ..@l5
	JMP	-, -, ..@l6
..@l5:
	PUSHA	-, J_prn_i, *J_prn_he
	PUSHA	-, J_prn_j, *J_prn_he
	CALL	J_prn_swap$IR$IR, -, -
..@l6:
	INC	-, -, J_prn_j
	JMP	-, -, ..@l3
..@l4:
	INC	-, -, J_prn_i
	JMP	-, -, ..@l1
..@l2:
	ASS	0x0, -, J_prn_i
..@l7:
	LOAD	J_prn_he, J_prn_i, J_prn_&3
	ADD	J_prn_&3, 0x1, J_prn_&4
	AARR	J_prn_&4, J_prn_i, J_prn_he
	ADD	J_prn_i, 0x1, J_prn_&5
	ASS	J_prn_&5, -, J_prn_i
	LOAD	J_prn_he, J_prn_i, J_prn_&6
	EQU	J_prn_&6, 0x4, ..@l8
	JMP	-, -, ..@l7
..@l8:
	ASS	0x0, -, J_prn_i
..@l9:
	GTT	J_prn_i, 0x4, ..@l10
	LOAD	J_prn_he, J_prn_i, J_prn_&7
	WRI	-, -, J_prn_&7
	INC	-, -, J_prn_i
	JMP	-, -, ..@l9
..@l10:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1                J_prn_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
      &2                J_prn_&2      -1	Tmp_Obj_t	Int_Type_t      -1       2       1
      &3                J_prn_&3      -1	Tmp_Obj_t	Int_Type_t      -1       2       2
      &4                J_prn_&4      -1	Tmp_Obj_t	Int_Type_t      -1       2       3
      &5                J_prn_&5      -1	Tmp_Obj_t	Int_Type_t      -1       2       4
      &6                J_prn_&6      -1	Tmp_Obj_t	Int_Type_t      -1       2       5
      &7                J_prn_&7      -1	Tmp_Obj_t	Int_Type_t      -1       2       6
      he                J_prn_he       2	Array_Obj_t	Int_Type_t      10       2       0
       i                 J_prn_i       3	Var_Obj_t	Int_Type_t      -1       2      10
       j                 J_prn_j       3	Var_Obj_t	Int_Type_t      -1       2      11
    swap        J_prn_swap$IR$IR       5	Proc_Obj_t	Nop_Type_t      -1       2      -1
-----------------------------------------------------------
var = 12; tmp = 7; para = 0; level = 2
***********************************************************
main:
	CALL	J_prn, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     prn                   J_prn       1	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 1
***********************************************************
