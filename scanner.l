%{
#include "scanner.h"
%}
%option nounput yylineno

%%

		/* comments in c! */
			/* multi line */
"/*"((("*"[^/])?)|[^*])*"*/" return COMMENT;
			/* single line */
"//".*					return COMMENT;


[a-zA-Z][_a-zA-Z0-9]*	return IDENTIFIER;
[1-9][0-9]*				return INTEGER;
		/* skip new lines and blank spaces */
[ \t\n]					;
		/* skip preprocessor lines */
^"#".*					return PREPROCESSOR;
.					{printf("unexpected character\n");printf("%s\n",yytext);}

%%

int yywrap(void)
{
	return 1;
}


