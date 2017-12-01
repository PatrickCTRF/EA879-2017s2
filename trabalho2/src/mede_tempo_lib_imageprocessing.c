#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "imageprocessing.h"
#include <sys/mman.h>
#include <FreeImage.h>

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

char *nome_global; float brilho_global;

imagem abrir_imagem(char *nome_do_arquivo) {
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      idx = i + (j*x);

      I.r[idx] = color.rgbRed;
      I.g[idx] = color.rgbGreen;
      I.b[idx] = color.rgbBlue;
    }
   }
  return I;

}


////////////////////





imagem abrir_imagemCOMBRILHO(char *nome_do_arquivo, float brilho) {



  nome_global = nome_do_arquivo; brilho_global = brilho;

	struct timeval rt0, rt1, drt;

  	gettimeofday(&rt0, NULL);
  	
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;
  


  float VALORBRILHO = 0.0;

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);



  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      

      idx = i + (j*x);

	VALORBRILHO = color.rgbRed * brilho;
	if(VALORBRILHO <= 255.0)
	{
		I.r[idx] = VALORBRILHO;
	}
	else I.r[idx] = 255.0;

      
	VALORBRILHO = color.rgbGreen * brilho;
	if(VALORBRILHO <= 255.0)
	{
		I.g[idx] = VALORBRILHO;
	}
	else I.g[idx] = 255.0;

	VALORBRILHO = color.rgbBlue * brilho;
	if(VALORBRILHO <= 255.0)
	{
		I.b[idx] = VALORBRILHO;
	}
	else I.b[idx] = 255.0;





   }
   }
   
  gettimeofday(&rt1, NULL);
    
  timersub(&rt1, &rt0, &drt);  
  float tempo = drt.tv_sec + 0.000001*drt.tv_usec;
  printf("\nTEMPO Por Colunas: %f segundos\n\n", tempo);
  
  
  return I;

}

///////////////////////////////////////


imagem valor_maximo(char *nome_do_arquivo) {
  
  FIBITMAP *bitmapIn;
  int x, y;
  RGBQUAD color;
  imagem I;


	float MAXPIX = 0;

	float temp = 0;	


  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

  if (bitmapIn == 0) {
    printf("Erro! Nao achei arquivo - %s\n", nome_do_arquivo);
  } else {
    printf("Arquivo lido corretamente!\n");
   }

  x = FreeImage_GetWidth(bitmapIn);
  y = FreeImage_GetHeight(bitmapIn);

  I.width = x;
  I.height = y;
  I.r = malloc(sizeof(float) * x * y);
  I.g = malloc(sizeof(float) * x * y);
  I.b = malloc(sizeof(float) * x * y);

   for (int i=0; i<x; i++) {
     for (int j=0; j <y; j++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      

      idx = i + (j*x);

      
	temp = 	sqrt( pow(color.rgbRed,2.0) + pow(color.rgbGreen,2.0) + pow(color.rgbBlue,2.0));

		
	MAXPIX = (temp > MAXPIX) ? temp : MAXPIX;


   }
   }
  
	printf("Valor Máximo = %f \n", MAXPIX);


	return I;

}





//////////////////////////////////////////







void liberar_imagem(imagem *I) {
  free(I->r);
  free(I->g);
  free(I->b);
}

void salvar_imagem(char *nome_do_arquivo, imagem *I) {
  FIBITMAP *bitmapOut;
  RGBQUAD color;

  printf("Salvando imagem %d por %d...\n", I->width, I->height);
  bitmapOut = FreeImage_Allocate(I->width, I->height, 24, 0, 0, 0);

   for (int i=0; i<I->width; i++) {
     for (int j=0; j<I->height; j++) {
      int idx;

      idx = i + (j*I->width);
      color.rgbRed = I->r[idx];
      color.rgbGreen = I->g[idx];
      color.rgbBlue = I->b[idx];

      FreeImage_SetPixelColor(bitmapOut, i, j, &color);
    }
  }

  FreeImage_Save(FIF_JPEG, bitmapOut, nome_do_arquivo, JPEG_DEFAULT);
}

