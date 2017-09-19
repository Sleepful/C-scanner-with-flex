#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#define TKNS 11
#define NEWFRM 250
#define HSTGRM_LINES 50
#define HSTGRM_SIZE 10
#define DEBUG 0

extern int yylex();
extern int yylineno;
extern char* yytext;
int yylinecounter = NEWFRM;
int yylinelastcount = 1;
int yylinecounter_H = HSTGRM_LINES;
int yylinelastcount_H = 1;

char* names[TKNS] = {"KEYWORD","IDENTIFIER","CONSTANTLITERAL","OPERATOR","PUNCTUATOR","COMMENT","PREPROCESSOR","CONSTANTCHAR","CONSTANTSTRING","ERROR","BLANK"};
char* colors[TKNS] = {"BurntOrange","Aquamarine","ForestGreen","Goldenrod","Fuchsia","Rhodamine","Gray","GreenYellow","Emerald","Red","White"};

char * commands[]={"gnuplot \"histogram_script.gnu\"","pdflatex beamer.tex","okular beamer.pdf --presentation"};

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
void writetokens_dat(void);

Row* table[TKNS]; //symbol table 4 later

typedef struct
	{
	int token_count[TKNS];
	}
	fragment_info;

fragment_info* histogram;
int current_Hist_i; //index
int current_Hist_s; //size

FILE* file;
char* texsource = "source.tex";

int main(void) 
	{
	histogram = malloc (HSTGRM_SIZE * sizeof(*histogram));
	current_Hist_s = HSTGRM_SIZE;
	#if DEBUG
	for (int i=0;i<TKNS;i++)
		printf(" n:%d ",histogram[0].token_count[i]);
	#endif
	file = fopen(texsource,"w");
	Row rowtoken;
	rowtoken = getToken();
	beginwritting(file);
	while(rowtoken.token) 
		{
		writetoken(rowtoken,file);
		rowtoken = getToken();
		#if DEBUG
		for (int i=0;i<TKNS;i++)
			printf(" n:%d ",histogram[current_Hist_i].token_count[i]);
		printf(" end line:%d\n", current_Hist_i);
		#endif
		}
	finishwritting(file);
	fclose(file);
	writetokens_dat();
	system(commands[0]); //gnuplot
	system(commands[1]); //pdflatex
	system(commands[2]); //okular
	return 0;
	}

void writetokens_dat(void)
	{
	file = fopen("datafile.dat","w");
	fprintf(file, "x ");
	for(int i=0;i<TKNS-1;i++)
		fprintf(file,"%s ",names[i]);
	fprintf(file, "\n");
	for(int i=0;i<=current_Hist_i;i++)
		{
		fprintf(file,"%d-%d ",i*HSTGRM_LINES,i*HSTGRM_LINES+HSTGRM_LINES);
		for(int a=0;a<=TKNS-2;a++)
			{
			fprintf(file,"%d ",histogram[i].token_count[a]);
			}
		fprintf(file,"\n");
		}
	fclose(file);
	}

void extend_histogram()
	{
	#if DEBUG
	for (int i=0;i<TKNS;i++)
		printf(" n:%d ",histogram[current_Hist_i-1].token_count[i]);
	#endif
	fragment_info *tmp;
	current_Hist_s=current_Hist_s+HSTGRM_SIZE;
	tmp = realloc(histogram, current_Hist_s*sizeof(*histogram));
	if (!tmp)
		{
		printf("failed to realloc");
	  exit(9); //failed to realloc
		}
	else
		{
		#if DEBUG
		printf("extended hist to %d\n",current_Hist_s);
		for (int i=0;i<TKNS;i++)
			printf(" n:%d ",histogram[current_Hist_i].token_count[i]);
			printf("^ new line of extended hist\n");
		#endif
		histogram = tmp;
		//zero out the rows
		for(int a=0;a<HSTGRM_SIZE;a++)
			for(int i=0;i<TKNS;i++)
				histogram[a+current_Hist_i].token_count[i]=0;
		#if DEBUG
		printf("extended hist to %d\n",current_Hist_s);
		for (int i=0;i<TKNS;i++)
			printf(" n:%d ",histogram[current_Hist_i].token_count[i]);
			printf("^ new line of extended hist\n");
		#endif
		}
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
	if(yylineno>=(yylinelastcount+yylinecounter)) //break beamer frames cuz LaTeX sucks
		{
		fprintf
			(
			file,
			"\n\\end{frame}\n\\begin{frame}[fragile,allowframebreaks]{Syntax Highlighting}~"
			);
		yylinelastcount=yylinelastcount+yylinecounter;
		}
	if(yylineno>=(yylinelastcount_H+yylinecounter_H)) //Histogram array index and realloc
		{
		current_Hist_i++;
		#if DEBUG
		printf("hist index ++:%d, yylineno:%d\n",current_Hist_i,yylineno);
		#endif
		if(current_Hist_i%HSTGRM_SIZE==0)
			{
			extend_histogram();
			}
		yylinelastcount_H=yylinelastcount_H+yylinecounter_H;
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
		fprintf
			(
			file,
			"\\color{%s}\\begin{verbatim}%s\\end{verbatim}\\leavevmode",
			colors[rowtoken.token-1],
			rowtoken.text
			);
		}
	if(rowtoken.token!=COMMENT&&rowtoken.token!=BLANK)
		{
		fprintf(file,"\\color{%s}\\verb$%s$", colors[rowtoken.token-1],rowtoken.text);
		}
		/* important: increase the token count in respective histogram index */
		histogram[current_Hist_i].token_count[rowtoken.token-1]++; 
	}


Row getToken(void)
	{
	Row myRow;
	int token = yylex();
	myRow.token = token;
	myRow.text = yytext;
	return myRow;
	}

