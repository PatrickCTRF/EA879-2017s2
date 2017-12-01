
%{
#include <stdlib.h>
#include <string.h>

#include <math.h>

void yyerror(char *);

#include "y.tab.h"
%}



%%

[a-z]  {
        yylval.ival = yytext[0] - 'a';
        return VAR;
       }


\" { return ASPA; }

[a-zA-Z0-9\.]+  {
        for (int i = 0; i < yyleng; i++ )
          yylval.strval[i] = yytext[i];

        yylval.strval[yyleng] = '\0';
        printf ("Achei nome: %s\n", yylval.strval);
        return STRING;
       }

[=]     {
          return IGUAL;
        }




[/]	{ return DIVIDIDO;}

[*]	{ return VEZES;}

[0-9]+(\.[0-9]+)?$ { 

		yylval.valor = strtof(yytext, NULL);
		return VALOR;
}

[\[] { return COLCHETEABERTO;}

[\]] { return COLCHETEFECHADO;}






\n   {
         return EOL;
       }

[ \t]+ ;

.     {printf("**%s**\n", yytext);
yyerror("Token nao reconhecido!\n");}

%%

int  yywrap() {
  return 1;
}