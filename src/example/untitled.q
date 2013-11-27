J_outter$IV_writeoo:
	WRI	-, -, 0x8ae
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 3
***********************************************************
J_outter$IV_foo$IV_pcd$IV_sum$IR:
	SUB	J_outter$IV_foo$IV_pcd$IV_sum$IR_x, 0x1, J_outter$IV_foo$IV_pcd$IV_sum$IR_&1
	ASS	J_outter$IV_foo$IV_pcd$IV_sum$IR_&1, -, J_outter$IV_foo$IV_pcd$IV_sum$IR_t
	EQU	J_outter$IV_foo$IV_pcd$IV_sum$IR_x, 0x1, ..@l1
	PUSHA	-, -, *J_outter$IV_foo$IV_pcd$IV_sum$IR_t
	CALL	J_outter$IV_foo$IV_pcd$IV_sum$IR, -, J_outter$IV_foo$IV_pcd$IV_sum$IR_&2
	ADD	J_outter$IV_foo$IV_pcd$IV_sum$IR_&2, J_outter$IV_foo$IV_pcd$IV_sum$IR_x, J_outter$IV_foo$IV_pcd$IV_sum$IR_&3
	SRET	J_outter$IV_foo$IV_pcd$IV_sum$IR_&3, -, J_outter$IV_foo$IV_pcd$IV_sum$IR
	JMP	-, -, ..@l2
..@l1:
	SRET	0x1, -, J_outter$IV_foo$IV_pcd$IV_sum$IR
..@l2:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1J_outter$IV_foo$IV_pcd$IV_sum$IR_&1      -1	Tmp_Obj_t	Int_Type_t      -1       5       0
      &2J_outter$IV_foo$IV_pcd$IV_sum$IR_&2      -1	Tmp_Obj_t	Int_Type_t      -1       5       1
      &3J_outter$IV_foo$IV_pcd$IV_sum$IR_&3      -1	Tmp_Obj_t	Int_Type_t      -1       5       2
       tJ_outter$IV_foo$IV_pcd$IV_sum$IR_t      13	Var_Obj_t	Int_Type_t      -1       5       0
       xJ_outter$IV_foo$IV_pcd$IV_sum$IR_x      12	Para_Ref_Obj_t	Int_Type_t      -1       5       0
-----------------------------------------------------------
var = 1; tmp = 3; para = 1; level = 5
paralist = J_outter$IV_foo$IV_pcd$IV_sum$IR_x
***********************************************************
J_outter$IV_foo$IV_pcd$IV:
	ASS	J_outter$IV_foo$IV_pcd$IV_x, -, J_outter$IV_foo$IV_pcd$IV_t
	PUSHA	-, -, *J_outter$IV_foo$IV_pcd$IV_t
	CALL	J_outter$IV_foo$IV_pcd$IV_sum$IR, -, J_outter$IV_foo$IV_pcd$IV_&4
	ASS	J_outter$IV_foo$IV_pcd$IV_&4, -, J_out
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &4J_outter$IV_foo$IV_pcd$IV_&4      -1	Tmp_Obj_t	Int_Type_t      -1       4       0
       tJ_outter$IV_foo$IV_pcd$IV_t      11	Var_Obj_t	Int_Type_t      -1       4       0
       xJ_outter$IV_foo$IV_pcd$IV_x      10	Para_Val_Obj_t	Int_Type_t      -1       4       0
     sumJ_outter$IV_foo$IV_pcd$IV_sum$IR      12	Fun_Obj_t	Int_Type_t      -1       4      -1
-----------------------------------------------------------
var = 1; tmp = 1; para = 1; level = 4
paralist = J_outter$IV_foo$IV_pcd$IV_x
***********************************************************
J_outter$IV_foo$IV:
	PUSH	-, -, J_outter$IV_foo$IV_y
	CALL	J_outter$IV_foo$IV_pcd$IV, -, -
	CALL	J_outter$IV_writeoo, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
       y    J_outter$IV_foo$IV_y       9	Para_Val_Obj_t	Int_Type_t      -1       3       0
     pcdJ_outter$IV_foo$IV_pcd$IV      10	Proc_Obj_t	Nop_Type_t      -1       3      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 3
paralist = J_outter$IV_foo$IV_y
***********************************************************
J_outter$IV:
	PUSH	-, -, J_outter$IV_y
	CALL	J_outter$IV_foo$IV, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
 writeoo     J_outter$IV_writeoo       5	Proc_Obj_t	Nop_Type_t      -1       2      -1
       y           J_outter$IV_y       4	Para_Val_Obj_t	Int_Type_t      -1       2       0
     foo      J_outter$IV_foo$IV       9	Proc_Obj_t	Nop_Type_t      -1       2      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 2
paralist = J_outter$IV_y
***********************************************************
main:
	AARR	0x20, 0x0, J_A
	AARR	0x2, 0x1, J_A
	AARR	0x80, 0x2, J_A
	AARR	0x20, 0x3, J_A
	LOAD	J_A, 0x0, J_&5
	LOAD	J_A, 0x1, J_&7
	DIV	J_&5, J_&7, J_&6
	WRI	-, -, J_&6
	LOAD	J_A, 0x1, J_&8
	LOAD	J_A, 0x3, J_&10
	MUL	J_&8, J_&10, J_&9
	WRI	-, -, J_&9
	ASS	0x0, -, J_i
..@l3:
	GTT	J_i, 0x3, ..@l4
	LOAD	J_A, J_i, J_&11
	WRI	-, -, J_&11
	INC	-, -, J_i
	JMP	-, -, ..@l3
..@l4:
	ASS	0x64, -, J_vn
	PUSH	-, -, J_vn
	CALL	J_outter$IV, -, -
	WRI	-, -, J_out
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     &10                   J_&10      -1	Tmp_Obj_t	Int_Type_t      -1       1       5
     &11                   J_&11      -1	Tmp_Obj_t	Int_Type_t      -1       1       6
     out                   J_out       2	Var_Obj_t	Int_Type_t      -1       1       1
      &5                    J_&5      -1	Tmp_Obj_t	Int_Type_t      -1       1       0
      &6                    J_&6      -1	Tmp_Obj_t	Int_Type_t      -1       1       1
      &7                    J_&7      -1	Tmp_Obj_t	Int_Type_t      -1       1       2
      &8                    J_&8      -1	Tmp_Obj_t	Int_Type_t      -1       1       3
      &9                    J_&9      -1	Tmp_Obj_t	Int_Type_t      -1       1       4
  outter             J_outter$IV       4	Proc_Obj_t	Nop_Type_t      -1       1      -1
       A                     J_A       3	Array_Obj_t	Int_Type_t      10       1       3
      vn                    J_vn       2	Var_Obj_t	Int_Type_t      -1       1       0
       i                     J_i       2	Var_Obj_t	Int_Type_t      -1       1       2
-----------------------------------------------------------
var = 13; tmp = 7; para = 0; level = 1
***********************************************************
