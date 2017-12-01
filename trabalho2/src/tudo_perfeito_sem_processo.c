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
#include <unistd.h> 

/*
imagem abrir_imagem(char *nome_do_arquivo);
void salvar_imagem(char *nome_do_arquivo);
void liberar_imagem(imagem *i);
 */

char *nome_global; float brilho_global;
imagem I;
struct timeval rt0, rt1, drt, rt2, rt3, drt2;
float tempo, tempo1;

FIBITMAP *bitmapIn;
int x, y;
RGBQUAD color;
float VALORBRILHO = 0.0;





void *myThreadFun(void *vargp_void)
{

  int *vargp = vargp_void;
	

  int inicio = (vargp[0]-1)*x/7.99999f;
  int fim = (vargp[0])*x/7.99999f;
  
  
	RGBQUAD color;

	float VALORBRILHO = 0.0;
  
  
   for (int j=0; j <y; j++) {
     for (int i=inicio; i<fim; i++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      

      idx = i + (j*x);

	VALORBRILHO = color.rgbRed * brilho_global;
	if(VALORBRILHO <= 255.0)
	{
		I.r[idx] = VALORBRILHO;
	}
	else I.r[idx] = 255.0;

      
	VALORBRILHO = color.rgbGreen * brilho_global;
	if(VALORBRILHO <= 255.0)
	{
		I.g[idx] = VALORBRILHO;
	}
	else I.g[idx] = 255.0;

	VALORBRILHO = color.rgbBlue * brilho_global;
	if(VALORBRILHO <= 255.0)
	{
		I.b[idx] = VALORBRILHO;
	}
	else I.b[idx] = 255.0;





   }
   }
   
    if(vargp[1] == 8){
    	
	  gettimeofday(&rt3, NULL);
    
	  timersub(&rt3, &rt2, &drt2);  
	  tempo1 = drt2.tv_sec + 0.000001*drt2.tv_usec;
	  printf("\nTEMPO Por THREADS: %f segundos\n\n", tempo1);
    	
	}
    
    return NULL;
}




imagem abrir_imagemCOMBRILHO_Threads(char *nome_do_arquivo, float brilho){
		
	nome_global = nome_do_arquivo; brilho_global = brilho;

	bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);


	if (bitmapIn == 0) {
		printf("Erro! Nao achei arquivo - %s\n", nome_global);
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
  
//======POR-Threads=======================================================================
  
  
  	int valor[] = {1, 2, 3, 4, 5, 6, 7, 8};
  	
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	pthread_t t6;
	pthread_t t7;
	pthread_t t8;
  
  	pthread_create(&t1, NULL, myThreadFun, &valor[0]);
	pthread_create(&t2, NULL, myThreadFun, &valor[1]);
	pthread_create(&t3, NULL, myThreadFun, &valor[2]);
	pthread_create(&t4, NULL, myThreadFun, &valor[3]);
	pthread_create(&t5, NULL, myThreadFun, &valor[4]);
	pthread_create(&t6, NULL, myThreadFun, &valor[5]);
	pthread_create(&t7, NULL, myThreadFun, &valor[6]);
	pthread_create(&t8, NULL, myThreadFun, &valor[7]);

	
	gettimeofday(&rt2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);  
	
	sleep(1);
	
	
  
//======POR-Threads-FIM===================================================================
	
	return I;
	
}

imagem abrir_imagemCOMBRILHO_Colunas(char *nome_do_arquivo, float brilho){
	
	nome_global = nome_do_arquivo; brilho_global = brilho;

	bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);
	
//======POR-Colunas======================================================================

  gettimeofday(&rt0, NULL);

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

   for (int j=0; j <y; j++) {
     for (int i=0; i<x; i++) {
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
  tempo = drt.tv_sec + 0.000001*drt.tv_usec;
  printf("\nTEMPO Por Colunas: %f segundos\n\n", tempo);
  
//======POR-Colunas-FIM===================================================================

	return I;
	
}

imagem abrir_imagemCOMBRILHO_Linhas(char *nome_do_arquivo, float brilho){
	
	nome_global = nome_do_arquivo; brilho_global = brilho;

	bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);

//======POR-Linhas=======================================================================

  gettimeofday(&rt0, NULL);

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
  tempo = drt.tv_sec + 0.000001*drt.tv_usec;
  printf("\nTEMPO Por Linhas: %f segundos\n\n", tempo);
  
//======POR-Linhas-FIM===================================================================
  
  return I;
		
}

imagem abrir_imagemCOMBRILHO(char *nome_do_arquivo, float brilho) {



  nome_global = nome_do_arquivo; brilho_global = brilho;

  	
  

  bitmapIn = FreeImage_Load(FIF_JPEG, nome_do_arquivo, 0);



  
//======POR-Threads=======================================================================
  
  
  	int valor[] = {1, 2, 3, 4, 5, 6, 7, 8};
  	
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_t t4;
	pthread_t t5;
	pthread_t t6;
	pthread_t t7;
	pthread_t t8;
  
  	pthread_create(&t1, NULL, myThreadFun, &valor[0]);
	pthread_create(&t2, NULL, myThreadFun, &valor[1]);
	pthread_create(&t3, NULL, myThreadFun, &valor[2]);
	pthread_create(&t4, NULL, myThreadFun, &valor[3]);
	pthread_create(&t5, NULL, myThreadFun, &valor[4]);
	pthread_create(&t6, NULL, myThreadFun, &valor[5]);
	pthread_create(&t7, NULL, myThreadFun, &valor[6]);
	pthread_create(&t8, NULL, myThreadFun, &valor[7]);

	
	gettimeofday(&rt2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);  
	
	sleep(1);
	
	
  
//======POR-Threads-FIM===================================================================
  
  
  
//======POR-LINHAS======================================================================

  gettimeofday(&rt0, NULL);

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

   for (int j=0; j <y; j++) {
     for (int i=0; i<x; i++) {
      int idx;
      FreeImage_GetPixelColor(bitmapIn, i, j, &color);

      

      idx = j + (i*y);

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
  tempo = drt.tv_sec + 0.000001*drt.tv_usec;
  printf("\nTEMPO Por Linhas: %f segundos\n\n", tempo);
  
//======POR-LINHAS-FIM===================================================================
  
  
//======POR-COLUNAS=======================================================================

  gettimeofday(&rt0, NULL);

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
  tempo = drt.tv_sec + 0.000001*drt.tv_usec;
  printf("\nTEMPO Por Colunas: %f segundos\n\n", tempo);
  
//======POR-COLUNAS-FIM===================================================================
  
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
