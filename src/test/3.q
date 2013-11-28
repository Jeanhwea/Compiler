J_hh_pri_he:
	AARR	0x2, J_hh_i, J_hh_ar
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 4
***********************************************************
J_hh_pri:
	ASS	0x1, -, J_hh_i
	CALL	J_hh_pri_he, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      he             J_hh_pri_he       5	Proc_Obj_t	Nop_Type_t      -1       3      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 3
***********************************************************
J_hh:
	CALL	J_hh_pri, -, -
	LOAD	J_hh_ar, J_hh_i, J_hh_&1
	WRI	-, -, J_hh_&1
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     pri                J_hh_pri       4	Proc_Obj_t	Nop_Type_t      -1       2      -1
      &1                 J_hh_&1      -1	Tmp_Obj_t	Int_Type_t      -1       2       0
       i                  J_hh_i       3	Var_Obj_t	Int_Type_t      -1       2      10
      ar                 J_hh_ar       2	Array_Obj_t	Int_Type_t      10       2       0
-----------------------------------------------------------
var = 11; tmp = 1; para = 0; level = 2
***********************************************************
main:
	CALL	J_hh, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      hh                    J_hh       1	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 1
***********************************************************
