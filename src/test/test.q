main:
	AARR	1, 0, J_A
	NEG	-, -, J_&1
	AARR	J_&1, 1, J_A
	AARR	0, 2, J_A
	AARR	3, 3, J_A
	AARR	32, 4, J_A
	ASS	4, -, J_N
	ASS	0, -, J_i
..@l1:
	GTT	J_i, J_N, ..@l2
	ASS	J_i, -, J_j
..@l3:
	GTT	J_j, J_N, ..@l4
	LOAD	J_A, J_i, J_&2
	LOAD	J_A, J_j, J_&3
	GTT	J_&2, J_&3, ..@l5
	JMP	-, -, ..@l6
..@l5:
	LOAD	J_A, J_i, J_&4
	ASS	J_&4, -, J_t
	LOAD	J_A, J_j, J_&5
	AARR	J_&5, J_i, J_A
	AARR	J_t, J_j, J_A
..@l6:
	INC	-, -, J_j
	JMP	-, -, ..@l3
..@l4:
	INC	-, -, J_i
	JMP	-, -, ..@l1
..@l2:
	ASS	20, -, J_blank
	WRS	-, -, after sorted
	WRC	-, -, J_blank
	ASS	0, -, J_i
..@l7:
	GTT	J_i, J_N, ..@l8
	LOAD	J_A, J_i, J_&6
	WRI	-, -, J_&6
	INC	-, -, J_i
	JMP	-, -, ..@l7
..@l8:
	FIN	-, -, -

