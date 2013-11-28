J_pri_f$IV:
	LST	J_pri_f$IV_n, 0x3, ..@l1
	SUB	J_pri_f$IV_n, 0x1, J_pri_f$IV_&2
	PUSH	-, -, J_pri_f$IV_&2
	CALL	J_pri_f$IV, -, J_pri_f$IV_&3
	MUL	J_pri_f$IV_n, J_pri_f$IV_&3, J_pri_f$IV_&1
	SRET	J_pri_f$IV_&1, -, J_pri_f$IV
	JMP	-, -, ..@l2
..@l1:
	SRET	J_pri_f$IV_n, -, J_pri_f$IV
..@l2:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1           J_pri_f$IV_&1      -1	Tmp_Obj_t	Int_Type_t      -1       3       0
      &2           J_pri_f$IV_&2      -1	Tmp_Obj_t	Int_Type_t      -1       3       1
      &3           J_pri_f$IV_&3      -1	Tmp_Obj_t	Int_Type_t      -1       3       2
       n            J_pri_f$IV_n       2	Para_Val_Obj_t	Int_Type_t      -1       3       0
-----------------------------------------------------------
var = 0; tmp = 3; para = 1; level = 3
paralist = J_pri_f$IV_n
***********************************************************
J_pri:
	PUSH	-, -, 0x5
	CALL	J_pri_f$IV, -, J_pri_&4
	WRI	-, -, J_pri_&4
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &4                J_pri_&4      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
       f              J_pri_f$IV       2	Fun_Obj_t	Int_Type_t      -1       2      -1
-----------------------------------------------------------
var = 0; tmp = 1; para = 0; level = 2
***********************************************************
main:
	CALL	J_pri, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     pri                   J_pri       1	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 1
***********************************************************
