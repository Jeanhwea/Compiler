#include "debug.h"
#include "global.h"
#include "symtab.h"
#include "x86.h"
#include "asm.h"

static void loadvar(reg_t *reg, syment_t *var)
{
	switch (var->cate) {
	case CONST_OBJ:
	case NUM_OBJ:
		x86_mov6(reg, var->initval);
		break;
	case VAR_OBJ:
	case TMP_OBJ:
	case BYVAL_OBJ:
	case BYREF_OBJ:
		x86_mov(reg, var);
		break;
		x86_mov(reg, var);
		break;
	default:
		unlikely();
	}
}

static void savevar(syment_t *var, reg_t *reg)
{
	switch (var->cate) {
	case VAR_OBJ:
	case TMP_OBJ:
	case BYVAL_OBJ:
	case BYREF_OBJ:
		x86_mov2(var, reg);
		break;
	default:
		unlikely();
	}
}

static void loadptr(reg_t *reg, syment_t *var)
{
	switch (var->cate) {
	case VAR_OBJ:
	case TMP_OBJ:
		x86_lea(reg, var);
		break;
	default:
		unlikely();
	}
}

static void loadptr2(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		x86_lea2(reg, arr, off);
		break;
	default:
		unlikely();
	}
}

static void loadarr(reg_t *reg, syment_t *arr, reg_t *off)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		x86_mov3(reg, arr, off);
		break;
	default:
		unlikely();
	}
}

static void savearr(syment_t *arr, reg_t *off, reg_t *reg)
{
	switch (arr->cate) {
	case ARRAY_OBJ:
		x86_mov4(arr, off, reg);
		break;
	default:
		unlikely();
	}
}

void asmbl_add_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_add(r1, r2);
	savevar(x->d, r1);

	freereg(r1);
	freereg(r2);
}

void asmbl_sub_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_sub(r1, r2);
	savevar(x->d, r1);

	freereg(r1);
	freereg(r2);
}

void asmbl_mul_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_mul(r1, r2);
	savevar(x->d, r1);

	freereg(r1);
	freereg(r2);
}

void asmbl_div_op(inst_t *x)
{
	// idiv use specific registers
	reg_t *eax = lockreg("eax");
	reg_t *edx = lockreg("edx");
	reg_t *r = allocreg();

	loadvar(eax, x->r);
	loadvar(edx, x->s);
	x86_div(r);
	savevar(x->d, eax);

	freereg(eax);
	freereg(edx);
	freereg(r);
}

void asmbl_inc_op(inst_t *x)
{
	reg_t *r = allocreg();

	loadvar(r, x->d);
	x86_inc(r);
	savevar(x->d, r);

	freereg(r);
}

void asmbl_dec_op(inst_t *x)
{
	reg_t *r = allocreg();

	loadvar(r, x->d);
	x86_dec(r);
	savevar(x->d, r);

	freereg(r);
}

void asmbl_neg_op(inst_t *x)
{
	reg_t *r = allocreg();

	loadvar(r, x->r);
	x86_neg(r);
	savevar(x->d, r);

	freereg(r);
}

void asmbl_load_op(inst_t *x)
{
	reg_t *r1 = allocreg();

	if (x->s) { // load array
		reg_t *r2 = allocreg(); // offset
		loadvar(r2, x->s);
		loadptr2(r1, x->r, r2);
		savevar(x->d, r1);
		freereg(r2);
	} else {
		loadptr(r1, x->r);
		savevar(x->d, r1);
	}

	freereg(r1);
}

void asmbl_ass_op(inst_t *x)
{
	reg_t *r1 = allocreg();

	loadvar(r1, x->r);
	savevar(x->d, r1);

	freereg(r1);
}

void asmbl_asa_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->s); // r1 = offset
	loadvar(r2, x->r);
	savearr(x->d, r1, r2);

	freereg(r1);
	freereg(r2);
}

void asmbl_equ_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jz(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_neq_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jnz(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_gtt_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jg(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_geq_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jnl(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_lst_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jl(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_leq_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();

	loadvar(r1, x->r);
	loadvar(r2, x->s);
	x86_cmp(r1, r2);
	x86_jng(x->d);

	freereg(r1);
	freereg(r2);
}

void asmbl_jmp_op(inst_t *x)
{
	x86_jmp(x->d);
}

void asmbl_push_op(inst_t *x)
{
	reg_t *r = allocreg();
	loadvar(r, x->d);
	x86_push(r);
	freereg(r);
}

void asmbl_padr_op(inst_t *x)
{
	reg_t *r1 = allocreg();
	reg_t *r2 = allocreg();
	if (x->r) {
		loadvar(r2, x->r); // offset
		loadptr2(r1, x->d, r2);
	} else {
		loadptr(r1, x->d);
	}
	x86_push(r1);
	freereg(r1);
	freereg(r2);
}

void asmbl_pop_op(inst_t *x)
{
	reg_t *r = allocreg();
	x86_pop(r);
	freereg(r);
}

void asmbl_call_op(inst_t *x)
{
}

void asmbl_sret_op(inst_t *x)
{
}

void asmbl_ent_op(inst_t *x)
{
	x86_enter(x->d);
}

void asmbl_fin_op(inst_t *x)
{
}

void asmbl_rdi_op(inst_t *x)
{
}

void asmbl_rdc_op(inst_t *x)
{
}

void asmbl_wrs_op(inst_t *x)
{
}

void asmbl_wri_op(inst_t *x)
{
}

void asmbl_wrc_op(inst_t *x)
{
}

void asmbl_lab_op(inst_t *x)
{
}

void assemble()
{
	x86_init();
	for (inst_t *x = xhead; x; x = x->next) {
		switch (x->op) {
		case ADD_OP:
			asmbl_add_op(x);
			break;
		case SUB_OP:
			asmbl_sub_op(x);
			break;
		case MUL_OP:
			asmbl_mul_op(x);
			break;
		case DIV_OP:
			asmbl_div_op(x);
			break;
		case INC_OP:
			asmbl_inc_op(x);
			break;
		case DEC_OP:
			asmbl_dec_op(x);
			break;
		case NEG_OP:
			asmbl_neg_op(x);
			break;
		case LOAD_OP:
			asmbl_load_op(x);
			break;
		case ASS_OP:
			asmbl_ass_op(x);
			break;
		case ASA_OP:
			asmbl_asa_op(x);
			break;
		case EQU_OP:
			asmbl_equ_op(x);
			break;
		case NEQ_OP:
			asmbl_neq_op(x);
			break;
		case GTT_OP:
			asmbl_gtt_op(x);
			break;
		case GEQ_OP:
			asmbl_geq_op(x);
			break;
		case LST_OP:
			asmbl_lst_op(x);
			break;
		case LEQ_OP:
			asmbl_leq_op(x);
			break;
		case JMP_OP:
			asmbl_jmp_op(x);
			break;
		case PUSH_OP:
			asmbl_push_op(x);
			break;
		case PADR_OP:
			asmbl_padr_op(x);
			break;
		case POP_OP:
			asmbl_pop_op(x);
			break;
		case CALL_OP:
			asmbl_call_op(x);
			break;
		case SRET_OP:
			asmbl_sret_op(x);
			break;
		case ENT_OP:
			asmbl_ent_op(x);
			break;
		case FIN_OP:
			asmbl_fin_op(x);
			break;
		case RDI_OP:
			asmbl_rdi_op(x);
			break;
		case RDC_OP:
			asmbl_rdc_op(x);
			break;
		case WRS_OP:
			asmbl_wrs_op(x);
			break;
		case WRI_OP:
			asmbl_wri_op(x);
			break;
		case WRC_OP:
			asmbl_wrc_op(x);
			break;
		case LAB_OP:
			asmbl_lab_op(x);
			break;
		default:
			unlikely();
		}
	}
	chkerr("assemble fail and exit.");
	phase = SUCCESS;
	progdump();
}
