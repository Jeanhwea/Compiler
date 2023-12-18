#include "global.h"
#include "x86.h"
#include "asm.h"

void asm_add_op(inst_t *x)
{
	reg_t *r1 = getreg();
	reg_t *r2 = getreg();
	x86_mov(r1, x->r);
	x86_mov(r2, x->s);
	x86_add(r1, r2);
	x86_mov2(x->d, r1);
}

void asm_sub_op(inst_t *x)
{
}

void asm_mul_op(inst_t *x)
{
}

void asm_div_op(inst_t *x)
{
}

void asm_inc_op(inst_t *x)
{
}

void asm_dec_op(inst_t *x)
{
}

void asm_neg_op(inst_t *x)
{
}

void asm_load_op(inst_t *x)
{
}

void asm_ass_op(inst_t *x)
{
}

void asm_asa_op(inst_t *x)
{
}

void asm_equ_op(inst_t *x)
{
}

void asm_neq_op(inst_t *x)
{
}

void asm_gtt_op(inst_t *x)
{
}

void asm_geq_op(inst_t *x)
{
}

void asm_lst_op(inst_t *x)
{
}

void asm_leq_op(inst_t *x)
{
}

void asm_jmp_op(inst_t *x)
{
}

void asm_push_op(inst_t *x)
{
}

void asm_padr_op(inst_t *x)
{
}

void asm_pop_op(inst_t *x)
{
}

void asm_call_op(inst_t *x)
{
}

void asm_sret_op(inst_t *x)
{
}

void asm_ent_op(inst_t *x)
{
}

void asm_fin_op(inst_t *x)
{
}

void asm_rdi_op(inst_t *x)
{
}

void asm_rdc_op(inst_t *x)
{
}

void asm_wrs_op(inst_t *x)
{
}

void asm_wri_op(inst_t *x)
{
}

void asm_wrc_op(inst_t *x)
{
}

void asm_lab_op(inst_t *x)
{
}

void *assemble()
{
	for (inst_t *x = xhead; x; x = x->next) {
		switch (x->op) {
		case ADD_OP:
			asm_add_op(x);
			break;
		case SUB_OP:
			asm_sub_op(x);
			break;
		case MUL_OP:
			asm_mul_op(x);
			break;
		case DIV_OP:
			asm_div_op(x);
			break;
		case INC_OP:
			asm_inc_op(x);
			break;
		case DEC_OP:
			asm_dec_op(x);
			break;
		case NEG_OP:
			asm_neg_op(x);
			break;
		case LOAD_OP:
			asm_load_op(x);
			break;
		case ASS_OP:
			asm_ass_op(x);
			break;
		case ASA_OP:
			asm_asa_op(x);
			break;
		case EQU_OP:
			asm_equ_op(x);
			break;
		case NEQ_OP:
			asm_neq_op(x);
			break;
		case GTT_OP:
			asm_gtt_op(x);
			break;
		case GEQ_OP:
			asm_geq_op(x);
			break;
		case LST_OP:
			asm_lst_op(x);
			break;
		case LEQ_OP:
			asm_leq_op(x);
			break;
		case JMP_OP:
			asm_jmp_op(x);
			break;
		case PUSH_OP:
			asm_push_op(x);
			break;
		case PADR_OP:
			asm_padr_op(x);
			break;
		case POP_OP:
			asm_pop_op(x);
			break;
		case CALL_OP:
			asm_call_op(x);
			break;
		case SRET_OP:
			asm_sret_op(x);
			break;
		case ENT_OP:
			asm_ent_op(x);
			break;
		case FIN_OP:
			asm_fin_op(x);
			break;
		case RDI_OP:
			asm_rdi_op(x);
			break;
		case RDC_OP:
			asm_rdc_op(x);
			break;
		case WRS_OP:
			asm_wrs_op(x);
			break;
		case WRI_OP:
			asm_wri_op(x);
			break;
		case WRC_OP:
			asm_wrc_op(x);
			break;
		case LAB_OP:
			asm_lab_op(x);
			break;
		default:
			unlikely();
		}
	}
	phase = SUCCESS;
}
