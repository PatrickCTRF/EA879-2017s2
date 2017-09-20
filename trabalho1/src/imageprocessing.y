%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <math.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  int     ival;
  float valor;
}
%token <strval> STRING
%token <ival> VAR IGUAL EOL ASPA DIVIDIDO VEZES COLCHETEABERTO COLCHETEFECHADO
%token <valor> VALOR
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO EOL
        |
        ;

EXPRESSAO:
    | STRING IGUAL STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }



	| STRING IGUAL STRING VEZES VALOR {

			printf("Copiando %s para %s\n", $3, $1);
			imagem I = abrir_imagemCOMBRILHO($3, $5);
			printf("NÚMERO =  %f\n", $5);
			printf("Li imagem %d por %d\n", I.width, I.height);
			salvar_imagem($1, &I);
			liberar_imagem(&I);
		
					}



	| STRING IGUAL STRING DIVIDIDO VALOR {

			printf("Copiando %s para %s\n", $3, $1);
			imagem I = abrir_imagemCOMBRILHO($3, (1/$5));
			printf("NÚMERO =  %f\n", (1/$5));
			printf("Li imagem %d por %d\n", I.width, I.height);
			salvar_imagem($1, &I);
			liberar_imagem(&I);
		
					}


	| COLCHETEABERTO STRING COLCHETEFECHADO {


					printf("Verificando o valor máximo dos pixels do arquivo: %s \n", $2);
					imagem I = valor_maximo($2);




						}




    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
