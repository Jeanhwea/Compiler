#ifndef _ERROR_H_
#define _ERROR_H_

#define DUPSYM 100
#define BADSYM 101
#define ERTYPE 102
#define BADLEN 103
#define EPANIC 996
#define EABORT 997

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

#endif /* End of _ERROR_H_ */
