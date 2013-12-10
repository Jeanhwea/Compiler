J_qsort$IV$IV_swap$IR$IR:
	ASS	J_qsort$IV$IV_swap$IR$IR_i, -, J_qsort$IV$IV_swap$IR$IR_temp
	ASS	J_qsort$IV$IV_swap$IR$IR_j, -, J_qsort$IV$IV_swap$IR$IR_i
	ASS	J_qsort$IV$IV_swap$IR$IR_temp, -, J_qsort$IV$IV_swap$IR$IR_j
	FIN	-, -, -

J_qsort$IV$IV:
	ASS	J_qsort$IV$IV_l, -, J_qsort$IV$IV_i
	ASS	J_qsort$IV$IV_h, -, J_qsort$IV$IV_j
	ADD	J_qsort$IV$IV_i, J_qsort$IV$IV_j, J_qsort$IV$IV_&2
	DIV	J_qsort$IV$IV_&2, 2, J_qsort$IV$IV_&3
	LOAD	J_a, J_qsort$IV$IV_&3, J_qsort$IV$IV_&1
	ASS	J_qsort$IV$IV_&1, -, J_qsort$IV$IV_m
..@l1:
	LOAD	J_a, J_qsort$IV$IV_i, J_qsort$IV$IV_&4
	LST	J_qsort$IV$IV_&4, J_qsort$IV$IV_m, ..@l3
	JMP	-, -, ..@l4
..@l3:
..@l5:
	ADD	J_qsort$IV$IV_i, 1, J_qsort$IV$IV_&5
	ASS	J_qsort$IV$IV_&5, -, J_qsort$IV$IV_i
	LOAD	J_a, J_qsort$IV$IV_i, J_qsort$IV$IV_&6
	GEQ	J_qsort$IV$IV_&6, J_qsort$IV$IV_m, ..@l6
	JMP	-, -, ..@l5
..@l6:
..@l4:
	LOAD	J_a, J_qsort$IV$IV_j, J_qsort$IV$IV_&7
	LST	J_qsort$IV$IV_m, J_qsort$IV$IV_&7, ..@l7
	JMP	-, -, ..@l8
..@l7:
..@l9:
	SUB	J_qsort$IV$IV_j, 1, J_qsort$IV$IV_&8
	ASS	J_qsort$IV$IV_&8, -, J_qsort$IV$IV_j
	LOAD	J_a, J_qsort$IV$IV_j, J_qsort$IV$IV_&9
	GEQ	J_qsort$IV$IV_m, J_qsort$IV$IV_&9, ..@l10
	JMP	-, -, ..@l9
..@l10:
..@l8:
	LEQ	J_qsort$IV$IV_i, J_qsort$IV$IV_j, ..@l11
	JMP	-, -, ..@l12
..@l11:
	PUSHA	-, J_qsort$IV$IV_i, *J_a
	PUSHA	-, J_qsort$IV$IV_j, *J_a
	CALL	J_qsort$IV$IV_swap$IR$IR, -, -
	ADD	J_qsort$IV$IV_i, 1, J_qsort$IV$IV_&10
	ASS	J_qsort$IV$IV_&10, -, J_qsort$IV$IV_i
	SUB	J_qsort$IV$IV_j, 1, J_qsort$IV$IV_&11
	ASS	J_qsort$IV$IV_&11, -, J_qsort$IV$IV_j
..@l12:
	GTT	J_qsort$IV$IV_i, J_qsort$IV$IV_j, ..@l2
	JMP	-, -, ..@l1
..@l2:
	GTT	J_qsort$IV$IV_j, J_qsort$IV$IV_l, ..@l13
	JMP	-, -, ..@l14
..@l13:
	PUSH	-, -, J_qsort$IV$IV_l
	PUSH	-, -, J_qsort$IV$IV_j
	CALL	J_qsort$IV$IV, -, -
..@l14:
	LST	J_qsort$IV$IV_i, J_qsort$IV$IV_h, ..@l15
	JMP	-, -, ..@l16
..@l15:
	PUSH	-, -, J_qsort$IV$IV_i
	PUSH	-, -, J_qsort$IV$IV_h
	CALL	J_qsort$IV$IV, -, -
..@l16:
	FIN	-, -, -

main:
	WRS	-, -, please input number(<10): 
	READ	-, -, J_num
	ASS	1, -, J_index
..@l17:
	GTT	J_index, J_num, ..@l18
	WRS	-, -, please input number> 
	READC	-, -, J_temp
	SUB	J_index, 1, J_&12
	AARR	J_temp, J_&12, J_a
	INC	-, -, J_index
	JMP	-, -, ..@l17
..@l18:
	PUSH	-, -, 0
	SUB	J_num, 1, J_&13
	PUSH	-, -, J_&13
	CALL	J_qsort$IV$IV, -, -
	SUB	J_num, 1, J_&14
	ASS	0, -, J_index
..@l19:
	GTT	J_index, J_&14, ..@l20
	LOAD	J_a, J_index, J_&15
	WRC	-, -, J_&15
	INC	-, -, J_index
	JMP	-, -, ..@l19
..@l20:
	FIN	-, -, -

