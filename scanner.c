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
	struct table_row * next;
} Row;

Row* table[11]; //symbol table 4 later

int tokencount[11] = {0};

Row getToken(void);

int main(void) 
{
	
	Row rowtoken;

	rowtoken = getToken();
	while(rowtoken.token) {
		printf("%d\n", rowtoken.token);
		printf("%s\n",rowtoken.name);
		rowtoken = getToken();
	}
	return 0;
}

Row getToken(void){
	Row myRow;
	int token = yylex();
	myRow.token = token;
	myRow.name = yytext;
	return myRow;
}
