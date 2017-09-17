%{
#include "scanner.h"
%}
%option nounput yylineno
%x C_COMMENT

%%

		/* comments in c! */
			/* multi line */

"/*"            { BEGIN(C_COMMENT); return COMMENT; }
<C_COMMENT>"*/" { BEGIN(INITIAL); return COMMENT; }
<C_COMMENT>\n   { }
<C_COMMENT>.    { }
			/* single line */
"//".*					return COMMENT;


"db_port"				return IDENTIFIER;

[a-zA-Z][_a-zA-Z0-9]*	return IDENTIFIER;
[1-9][0-9]*				return INTEGER;
		/* skip new lines and blank spaces */
[ \t\n]					;
.					printf("unexpected character\n");

%%

int yywrap(void)
{
	return 1;
}
