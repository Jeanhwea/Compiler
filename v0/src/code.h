/**
 * File: code.h
 * Date: Nov 19, 2013
 * Author: Jeanhwea
 */
#ifndef CODE_H

#define CODE_H

#define OBJ(a) (res->obj==(a))
#define OBJ2(a,b) ((res->obj==(a))||(res->obj==(b)))
#define OBJ3(a,b,c) ((res->obj==(a))||(res->obj==(b))||(res->obj==(c)))
#define OBJ4(a,b,c,d) ((res->obj==(a))||(res->obj==(b))||(res->obj==(c))\
		||(res->obj==(d)))
#define OBJ5(a,b,c,d,e) ((res->obj==(a))||(res->obj==(b))||(res->obj==(c))\
		||(res->obj==(d))||(res->obj==(e)))
#define TYPE(a) (res->type==(a))
#define TYPE2(a,b) ((res->type==(a))||(res->type==(b)))
#define TYPE3(a,b,c) ((res->type==(a))||(res->type==(b))||(res->type==(c)))
#define TYPE4(a,b,c,d) ((res->type==(a))||(res->type==(b))\
		||(res->type==(c))||(res->type==(d)))

void coder(PgmSP t);
#endif /* end of include guard: CODE_H */
