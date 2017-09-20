
#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H


typedef struct {
  unsigned int width, height;
  float *r, *g, *b;
} imagem;

imagem abrir_imagem(char *nome_do_arquivo);



imagem abrir_imagemCOMBRILHO(char *nome_do_arquivo, float brilho); /////////////////////


imagem valor_maximo(char *nome_do_arquivo); /////////////////////




void salvar_imagem(char *nome_do_arquivo, imagem *I);
void liberar_imagem(imagem *i);

#endif
