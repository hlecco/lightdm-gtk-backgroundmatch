#include<stdio.h>
#include<stdlib.h>
#include<strtools.h>


int stringSize(const char *str) {
	int size;
	size=0;

	while(str[size]) size++;
	
	return size;
}


int stringFind(const char *str,const char *match,const int offset) {	// Returns first occurrence of 'match' in 'str', starting from the 'offset'
	for(int i=offset; i<stringSize(str); i++) {
		for(int j=0; j<stringSize(match); j++) {
			if (str[i+j]!=match[j]) break;
			else if (j==stringSize(match)-1) {
				return i;
			}
		}
	}

	return STRING_NOT_FOUND;
}

char *stringCopy(const char *input) {	// Allocates memory, copies 'input' and returns the address of the copy
	char *dest;
	dest = NULL;
	int pos;
	pos = 0;
	do {
		if (pos % 4096 ==0) {
			dest =(char *) realloc(dest, ((pos / 4096)+1)*4096);
		}
		dest[pos]=input[pos];
		pos+=1;
	}
	while(input[pos-1] != 0);

	dest=(char *)realloc(dest,pos);
	return dest;
}

char *stringSep(const char *str,const char sep) { // Copies a string until the separator
	char *output;
	output=NULL;
	int i;
	i=0;
	do {
		if(i%4096==0) {
			output=(char *) realloc(output,((i/4096)+1)*4096);
		}
		output[i]=str[i];
		i++;
	}
	while(str[i-1]!=sep && str[i-1]!=0);

	output[i-1]=0;

	output=realloc(output,i);
	return output;
}

char *stringCut(const char *str,const int in,const int out) {	// Cuts positions from 'in' to 'out' on string 'str' (returns a new string)
	char *cut;
	cut = (char *)malloc(stringSize(str)-(out-in));

	for(int i = 0; i<in; i++) {
		cut[i]=str[i];
	}
	for(int i = out+1; i<stringSize(str); i++) {
		cut[in-1+i-out]=str[i];
	}
	cut[stringSize(str)-(out-in+1)]=0;

	return cut;
}

char *stringInsert(const char *str,const char *insert,const int position) {	// Inserts string 'insert' at position 'position' (before it)
	char *newstr;

	if(position>stringSize(str)) {
		newstr = stringCopy(str);
		return newstr;
	}

	newstr = (char *)malloc(stringSize(str)+stringSize(insert)+1);

	for(int i=0; i<position; i++) {
		newstr[i]=str[i];
	}
	for(int i=0; i<stringSize(insert); i++) {
		newstr[position+i]=insert[i];
	}
	for(int i=position; i<stringSize(str); i++) {
		newstr[i+stringSize(insert)]=str[i];
	}
	newstr[stringSize(insert)+stringSize(str)]=0;

	return newstr;
}

char *stringSubstitute(const char *string,const char *old,const char *new) {	// Substitutes all ocurrences of 'old' for 'new' in 'string'
	char *newstr1;
	char *newstr2;

	newstr2 = stringCopy(string);

	int position;
	position=0;

	do {
		position = stringFind(newstr2,old,position);
		if (position != -1) {
			newstr1 = stringCut(newstr2,position,position+stringSize(old)-1);
			free(newstr2);
			newstr2 = stringInsert(newstr1,new,position);
			free(newstr1);
			position+=stringSize(new);
		}
	}
	while(position!=-1);

	return newstr2;
}

int stringCompare(const char *str1, const char *str2) {
	int size1,size2;
	size1 = stringSize(str1);
	size2 = stringSize(str2);

	if (size1!=size2) return 0;

	for(int i=0; i<size1&&i<size2; i++) {
		if (str1[i]!=str2[i]) return 0;
	}

	return 1;
}
