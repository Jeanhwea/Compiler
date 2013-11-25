J_pcd$I:
	ASS	J_pcd$I_x, -, J_pcd$I_vn2
	ASS	0x5, -, J_pcd$I_vn3
	ADD	J_pcd$I_vn2, J_pcd$I_vn3, J_pcd$I_&1
	ASS	J_pcd$I_&1, -, J_vn
	FIN	-, -, -
J: 
	PUSH	-, -, 0x4
	CALL	J_pcd$I, -, -
	WRI	-, -, J_vn
	FIN	-, -, -
