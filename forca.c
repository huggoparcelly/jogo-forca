#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void cabecalho() {
  printf("***************************\n");
  printf("Bem vindo ao jogo da forca!\n");
  printf("***************************\n");
}

void chuta() {
  char chute;
  scanf(" %c", &chute);

  chutes[chutesdados] = chute;
  chutesdados++;
}

int jachutou(char letra) {
  int achou = 0;
  for (int j = 0; j < chutesdados; j++) {
    if (chutes[j] == letra) {
      achou = 1;
      break;
    }
  }
  return achou;
}

void desenhaforca() {
  for (int i = 0; i < strlen(palavrasecreta); i++) {

    int achou = jachutou(palavrasecreta[i]);

    if (achou) {
      printf("%c ", palavrasecreta[i]);
    }
    else {
      printf("_ ");
    }
  }
  printf("\n");
}

int numrandomico(int max) {
  srand(time(0));
  return rand() % max;
}

void addpalavra() {
  char quer;

  printf("Gostaria de adicionar uma nova palavra? (S/N)\n");
  scanf(" %c", &quer);

  if(quer == 'S') {
    char novapalavra[TAMANHO_PALAVRA];
    printf("Qual a nova palavra? \n");
    scanf("%s", novapalavra);

    FILE* f;

    f = fopen("palavras.txt", "r+");
    if(f == 0) {
      printf("Banco de dados não disoponível");
      exit(1);
    }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }

}

void checkfile(FILE* f) {
  
}

void escolhepalavra() {
  FILE* f;
  f = fopen("palavras.txt", "r");
  if(f == 0) {
    printf("Banco de dados não disoponível");
    exit(1);
  }

  int qtdpalavras;
  fscanf(f, "%d", &qtdpalavras);

  int randomico = numrandomico(qtdpalavras);

  for(int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }
  
  fclose(f);
}

int enforcou() {
  int erros = 0;

  for(int i =0; i < chutesdados; i++) {
    int existe = 0;

    for(int j =0; j < strlen(palavrasecreta); j++) {
      if(chutes[i] == palavrasecreta[j]) {
        existe = 1;
        break;
      }
    }
    if(!existe) erros++;
  }
  return erros >= 5;
}

int acertou() {
  for(int i =0; i < strlen(palavrasecreta); i++) {
    if(!jachutou(palavrasecreta[i])) {
      return 0;
    }
  }
  return 1;
}

int main() {

  escolhepalavra();
  cabecalho();

  do {
    desenhaforca();
    chuta();
  } while (!acertou() && !enforcou());
  
  if(acertou()) {
    printf("Parabéns você ganhou!\n");
  } 
  if(enforcou()) {
    printf("Poxa, não foi dessa vez. Tente novamente!\n");
  }
  addpalavra();
  return 0;
}
