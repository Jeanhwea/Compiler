#ifndef _ERROR_H_
#define _ERROR_H_

#define ERRTOK 100
#define DUPSYM 110
#define BADSYM 111
#define BADCTG 112
#define ERTYPE 113
#define BADLEN 114
#define BADREF 115
#define OBJREF 106
#define ENOCMD 995
#define EPANIC 996
#define EABORT 997
#define EARGMT 998

#define rescue(err, fmt, args...)                                              \
	do {                                                                   \
		errnum = err;                                                  \
		printf("ERROR: ");                                             \
		printf(fmt, ##args);                                           \
		printf("\n");                                                  \
	} while (0)

#define giveup(err, fmt, args...)                                              \
	do {                                                                   \
		errnum = err;                                                  \
		printf(fmt, ##args);                                           \
		printf("\n");                                                  \
		exit(err);                                                     \
	} while (0)

#define chkerr(fmt)                                                            \
	do {                                                                   \
		if (errnum > 0) {                                              \
			printf(fmt);                                           \
			printf("\n");                                          \
			exit(errnum);                                          \
		}                                                              \
	} while (0)

#endif /* End of _ERROR_H_ */
