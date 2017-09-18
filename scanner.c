#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
int yylinecounter = 10;
int yylinelastcount= 1;

typedef struct table_row 
	{
	int token;
	char* name;
	struct table_row * next;
	} 
	Row;

Row* table[11]; //symbol table 4 later
int tokencount[11];
// *tokencount  [1];  //this should be a dynamic array of tokencount arrays

Row getToken(void);

FILE* file;
char* texsource = "source.tex";

int main(void) 
	{
	file = fopen(texsource,"w");
	Row rowtoken;
	rowtoken = getToken();
	while(rowtoken.token) 
		{
		fprintf(file,"%d\n", rowtoken.token);
		fprintf(file,"%s\n",rowtoken.name);
		if(yylineno>=(yylinelastcount+yylinecounter))
			{
			yylinelastcount=yylinelastcount+yylinecounter;
			fprintf(file,"new line counter reached: %d\n",yylineno);
			}
		rowtoken = getToken();
		}
	return 0;
	}

Row getToken(void)
	{
	Row myRow;
	int token = yylex();
	myRow.token = token;
	myRow.name = yytext;
	return myRow;
	}

void writeToEOF(char* text, int token)
	{
	//f = fopen("contacts.pcl", "a");
	//this is incompletely incomplete
	//fclose(f);
	}
