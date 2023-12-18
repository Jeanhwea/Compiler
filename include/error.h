#ifndef _ERROR_H_
#define _ERROR_H_

#define DUPSYM 100
#define BADSYM 101
#define BADCTG 102
#define ERTYPE 103
#define BADLEN 104
#define BADREF 105
#define OBJREF 106
#define EPANIC 996
#define EABORT 997
#define EARGMT 998

#define rescue(err, fmt, args...)                                              \
	do {                                                                   \
		errnum = err;                                                  \
		printf(fmt, ##args);                                           \
	} while (0)

#define giveup(err, fmt, args...)                                              \
	do {                                                                   \
		errnum = err;                                                  \
		printf(fmt, ##args);                                           \
		exit(err);                                                     \
	} while (0)

#define chkerr(fmt)                                                            \
	do {                                                                   \
		if (errnum > 0) {                                              \
			printf(fmt);                                           \
			exit(errnum);                                          \
		}                                                              \
	} while (0)

#endif /* End of _ERROR_H_ */
