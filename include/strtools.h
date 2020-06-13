#ifndef _STRING_H_
#define _STRING_H_ 1

#define STRING_NOT_FOUND -1

int stringSize(const char *);
int stringFind(const char *,const char *,const int);
char *stringCopy(const char *);
char *stringSep(const char *,const char sep);
char *stringCut(const char *,const int, const int);
char *stringInsert(const char *,const char *, const int);
char *stringSubstitute(const char *,const char *, const char *);

#endif
