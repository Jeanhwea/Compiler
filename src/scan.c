#include "lexical.h"

// see scan.h
char token_data[MAXTOKENSIZE + 1];
extern int token_line;

// source line buffer
#define BUFLEN 1024
// hold current line
static char line_buf[BUFLEN];
// hold current read postion in line_buf
static int pos = 0;
