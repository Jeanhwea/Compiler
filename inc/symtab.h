#ifndef _SYMTAB_H_
#define _SYMTAB_H_

#define MAXBUCKETS 16

typedef sym_table *sym_table_p;
typedef sym_bucket *sym_bucket_p;
typedef sym_entry *sym_entry_p;

struct _sym_entry_struct {
	char *name;
	char *label;
	// array length, const value, unsigned value
	int value;
} sym_entry;

struct _sym_bucket_struct {
	sym_entry_p entry;
	sym_bucket_p next;
} sym_bucket;

struct _sym_table_struct {
	sym_bucket buckets[MAXBUCKETS];
} sym_table;

#endif /* End of _SYMTAB_H_ */
