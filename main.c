#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;


typedef struct table_row {
	int token;
	char* name;
	int value;
	struct table_row * next;
} Row;

Row* table[13];

Row getToken(void);

int main(void) 
{
	
	Row rowtoken;

	rowtoken = getToken();
	while(rowtoken.token) {
		printf("%d\n", rowtoken.token);
		printf(rowtoken.name);
		rowtoken = getToken();
	}
	return 0;
}

Row getToken(void){
	Row myRow;
	int token = yylex();
	myRow.token = token;
	if(token==INTEGER)
		myRow.value = atof(yytext);
	else
		myRow.name = yytext;
	return myRow;
}
