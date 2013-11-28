J_fac$IV:
	EQU	J_fac$IV_n, 0x0, ..@l1
	SUB	J_fac$IV_n, 0x1, J_fac$IV_&1
	PUSH	-, -, J_fac$IV_&1
	CALL	J_fac$IV, -, J_fac$IV_&2
	MUL	J_fac$IV_&2, J_fac$IV_n, J_fac$IV_&3
	SRET	J_fac$IV_&3, -, J_fac$IV
	JMP	-, -, ..@l2
..@l1:
	SRET	0x1, -, J_fac$IV
..@l2:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1             J_fac$IV_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
      &2             J_fac$IV_&2      -1	Tmp_Obj_t	Int_Type_t      -1       2       1
      &3             J_fac$IV_&3      -1	Tmp_Obj_t	Int_Type_t      -1       2       2
       n              J_fac$IV_n       3	Para_Val_Obj_t	Int_Type_t      -1       2       0
-----------------------------------------------------------
var = 0; tmp = 3; para = 1; level = 2
paralist = J_fac$IV_n
***********************************************************
main:
	ASS	0x0, -, J_vn
..@l3:
	GTT	J_vn, 0x4, ..@l4
	PUSH	-, -, J_vn
	CALL	J_fac$IV, -, J_&4
	WRI	-, -, J_&4
	INC	-, -, J_vn
	JMP	-, -, ..@l3
..@l4:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     out                   J_out       2	Var_Obj_t	Int_Type_t      -1       1       1
      &4                    J_&4      -1	Tmp_Obj_t	Int_Type_t      -1       1       0
      vn                    J_vn       2	Var_Obj_t	Int_Type_t      -1       1       0
     fac                J_fac$IV       3	Fun_Obj_t	Int_Type_t      -1       1      -1
-----------------------------------------------------------
var = 2; tmp = 1; para = 0; level = 1
***********************************************************
