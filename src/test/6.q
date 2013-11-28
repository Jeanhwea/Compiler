J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR:
	ASS	0x6, -, J_h1$IR_i1
	ASS	0x6, -, J_h1$IR_h2$IR_i2
	ASS	0x6, -, J_h1$IR_h2$IR_h3$IR_i3
	ASS	0x6, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	ASS	0x6, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	ASS	0x6, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_i6
	WRI	-, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_h2$IR_i2
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_i3
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_i6
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      i6J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_i6      13	Var_Obj_t	Int_Type_t      -1       7       0
       zJ_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_z      12	Para_Ref_Obj_t	Int_Type_t      -1       7       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 7
paralist = J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR_z
***********************************************************
J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR:
	ASS	0x5, -, J_h1$IR_i1
	ASS	0x5, -, J_h1$IR_h2$IR_i2
	ASS	0x5, -, J_h1$IR_h2$IR_h3$IR_i3
	ASS	0x5, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	ASS	0x5, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	WRI	-, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_h2$IR_i2
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_i3
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	PUSHA	-, -, *J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5
	CALL	J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h6J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_h6$IR      12	Proc_Obj_t	Nop_Type_t      -1       6      -1
      i5J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_i5      11	Var_Obj_t	Int_Type_t      -1       6       0
       yJ_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_y      10	Para_Ref_Obj_t	Int_Type_t      -1       6       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 6
paralist = J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR_y
***********************************************************
J_h1$IR_h2$IR_h3$IR_h4$IR:
	ASS	0x4, -, J_h1$IR_i1
	ASS	0x4, -, J_h1$IR_h2$IR_i2
	ASS	0x4, -, J_h1$IR_h2$IR_h3$IR_i3
	ASS	0x4, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	WRI	-, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_h2$IR_i2
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_i3
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	PUSHA	-, -, *J_h1$IR_h2$IR_h3$IR_h4$IR_i4
	CALL	J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h5J_h1$IR_h2$IR_h3$IR_h4$IR_h5$IR      10	Proc_Obj_t	Nop_Type_t      -1       5      -1
      i4J_h1$IR_h2$IR_h3$IR_h4$IR_i4       9	Var_Obj_t	Int_Type_t      -1       5       0
       xJ_h1$IR_h2$IR_h3$IR_h4$IR_x       8	Para_Ref_Obj_t	Int_Type_t      -1       5       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 5
paralist = J_h1$IR_h2$IR_h3$IR_h4$IR_x
***********************************************************
J_h1$IR_h2$IR_h3$IR:
	ASS	0x3, -, J_h1$IR_i1
	ASS	0x3, -, J_h1$IR_h2$IR_i2
	ASS	0x3, -, J_h1$IR_h2$IR_h3$IR_i3
	WRI	-, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_h2$IR_i2
	WRI	-, -, J_h1$IR_h2$IR_h3$IR_i3
	PUSHA	-, -, *J_h1$IR_h2$IR_h3$IR_i3
	CALL	J_h1$IR_h2$IR_h3$IR_h4$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h4J_h1$IR_h2$IR_h3$IR_h4$IR       8	Proc_Obj_t	Nop_Type_t      -1       4      -1
      i3  J_h1$IR_h2$IR_h3$IR_i3       7	Var_Obj_t	Int_Type_t      -1       4       0
       k   J_h1$IR_h2$IR_h3$IR_k       6	Para_Ref_Obj_t	Int_Type_t      -1       4       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 4
paralist = J_h1$IR_h2$IR_h3$IR_k
***********************************************************
J_h1$IR_h2$IR:
	ASS	0x2, -, J_h1$IR_i1
	ASS	0x2, -, J_h1$IR_h2$IR_i2
	WRI	-, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_h2$IR_i2
	PUSHA	-, -, *J_h1$IR_h2$IR_i2
	CALL	J_h1$IR_h2$IR_h3$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h3     J_h1$IR_h2$IR_h3$IR       6	Proc_Obj_t	Nop_Type_t      -1       3      -1
      i2        J_h1$IR_h2$IR_i2       5	Var_Obj_t	Int_Type_t      -1       3       0
       j         J_h1$IR_h2$IR_j       4	Para_Ref_Obj_t	Int_Type_t      -1       3       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 3
paralist = J_h1$IR_h2$IR_j
***********************************************************
J_h1$IR:
	ASS	0x1, -, J_h1$IR_i1
	WRI	-, -, J_h1$IR_i1
	PUSHA	-, -, *J_h1$IR_i1
	CALL	J_h1$IR_h2$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h2           J_h1$IR_h2$IR       4	Proc_Obj_t	Nop_Type_t      -1       2      -1
      i1              J_h1$IR_i1       3	Var_Obj_t	Int_Type_t      -1       2       0
       i               J_h1$IR_i       2	Para_Ref_Obj_t	Int_Type_t      -1       2       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 1; level = 2
paralist = J_h1$IR_i
***********************************************************
main:
	PUSHA	-, -, *J_i0
	CALL	J_h1$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h1                 J_h1$IR       2	Proc_Obj_t	Nop_Type_t      -1       1      -1
      i0                    J_i0       1	Var_Obj_t	Int_Type_t      -1       1       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 0; level = 1
***********************************************************
