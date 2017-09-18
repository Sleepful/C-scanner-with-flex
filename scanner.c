#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#define TKNS 11


extern int yylex();
extern int yylineno;
extern char* yytext;
int yylinecounter = 250;
int yylinelastcount= 1;

typedef struct table_row 
	{
	int token;
	char* text;
	struct table_row * next;
	} 
	Row;

Row getToken(void);
void writetoken(Row rowtoken, FILE* file);
void beginwritting(FILE* file);
void finishwritting(FILE* file);

Row* table[TKNS]; //symbol table 4 later
int tokencount[TKNS];
// *tokencount  [1];  //this should be a dynamic array of tokencount arrays
char* names[TKNS] = {"KEYWORD","IDENTIFIER","CONSTANTLITERAL","OPERATOR","PUNCTUATOR","COMMENT","PREPROCESSOR","CONSTANTCHAR","CONSTANTSTRING","ERROR","BLANK"};
char* colors[TKNS] = {"BurntOrange","Aquamarine","ForestGreen","Goldenrod","Fuchsia","Rhodamine","Gray","GreenYellow","Emerald","Red","White"};

FILE* file;
char* texsource = "source.tex";

int main(void) 
	{
	file = fopen(texsource,"w");
	Row rowtoken;
	rowtoken = getToken();
	beginwritting(file);
	while(rowtoken.token) 
		{
		writetoken(rowtoken,file);
		rowtoken = getToken();
		}
	finishwritting(file);
	return 0;
	}

void beginwritting(FILE* file)
	{
	fprintf(file,"\\begin{frame}[fragile,allowframebreaks]{Syntax Highlighting}~");
	}
void finishwritting(FILE* file)
	{
	fprintf(file,"\n\\end{frame}\n");
	}

void writetoken(Row rowtoken,FILE* file)
		{
		if(yylineno>=(yylinelastcount+yylinecounter))
			{
			fprintf(file,"\n\\end{frame}\n\\begin{frame}[fragile,allowframebreaks]{Syntax Highlighting}~");
			yylinelastcount=yylinelastcount+yylinecounter;
			//fprintf(file,"new line counter reached: %d\n",yylineno);
			}
		if(rowtoken.token==BLANK)
			{
			if(rowtoken.text[0]==0x9)
				fprintf(file,"\\tab");
			if(rowtoken.text[0]==0xa)
				fprintf(file,"\\newline");
			if(rowtoken.text[0]==' ')
				fprintf(file," ");
			}
		if(rowtoken.token==COMMENT)
			{
			fprintf(file,"\\color{%s}\\begin{verbatim}%s\\end{verbatim}\\leavevmode",colors[rowtoken.token-1],rowtoken.text);
			}
		if(rowtoken.token!=COMMENT&&rowtoken.token!=BLANK)
			{
			fprintf(file,"\\color{%s}\\verb$%s$", colors[rowtoken.token-1],rowtoken.text);
			}
		}


Row getToken(void)
	{
	Row myRow;
	int token = yylex();
	myRow.token = token;
	myRow.text = yytext;
	return myRow;
	}

