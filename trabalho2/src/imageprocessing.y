%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>
#include <math.h>
#include <string.h>

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
	
			printf("NÚMERO =  %f\n", $5);
			//printf("Li imagem %d por %d\n", I_threads.width, I_threads.height);
			char str[80];

			printf("Copiando %s para %s\n", $3, $1);
			imagem I_processos = abrir_imagemCOMBRILHO_Processos($3, $5);
			strcpy(str, "_Processos_");
			strcat(str, $1);	
			salvar_imagem(str, &I_processos);
			liberar_imagem(&I_processos);
			
			
			imagem I_threads = abrir_imagemCOMBRILHO_Threads($3, $5);
			strcpy(str, "_Thread_");
			strcat(str, $1);
			salvar_imagem(str, &I_threads);
			liberar_imagem(&I_threads);
			
			
			imagem I_colunas = abrir_imagemCOMBRILHO_Colunas($3, $5);
			strcpy(str, "_Colunas_");
			strcat(str, $1);
			salvar_imagem(str, &I_colunas);
			liberar_imagem(&I_colunas);
			
			
			imagem I_linhas = abrir_imagemCOMBRILHO_Linhas($3, $5);
			strcpy(str, "_Linhas_");
			strcat(str, $1);
			salvar_imagem(str, &I_linhas);
			liberar_imagem(&I_linhas);
			
			
			
			
			
			
			
			
			
			
			
		
			}



	| STRING IGUAL STRING DIVIDIDO VALOR {

			
			printf("NÚMERO =  %f\n", $5);
			//printf("Li imagem %d por %d\n", I_threads.width, I_threads.height);
			char str[80];

			printf("Copiando %s para %s\n", $3, $1);
			imagem I_processos = abrir_imagemCOMBRILHO_Processos($3, 1/$5);
			strcpy(str, "_Processos_");
			strcat(str, $1);	
			salvar_imagem(str, &I_processos);
			liberar_imagem(&I_processos);
			
			
			imagem I_threads = abrir_imagemCOMBRILHO_Threads($3, 1/$5);
			strcpy(str, "_Thread_");
			strcat(str, $1);
			salvar_imagem(str, &I_threads);
			liberar_imagem(&I_threads);
			
			
			imagem I_colunas = abrir_imagemCOMBRILHO_Colunas($3, 1/$5);
			strcpy(str, "_Colunas_");
			strcat(str, $1);
			salvar_imagem(str, &I_colunas);
			liberar_imagem(&I_colunas);
			
			
			imagem I_linhas = abrir_imagemCOMBRILHO_Linhas($3, 1/$5);
			strcpy(str, "_Linhas_");
			strcat(str, $1);
			salvar_imagem(str, &I_linhas);
			liberar_imagem(&I_linhas);
		
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
