#include <stdio.h>
#include <string.h>


void cabecalho() {
  printf("***************************\n");
  printf("Bem vindo ao jogo da forca!\n");
  printf("***************************\n");
}

void chuta(char chutes[], int* tentativas) {
  char chute;
  scanf(" %c", &chute);

  chutes[*tentativas] = chute;
  (*tentativas)++;
}


int main() {
  
  char palavrasecreta[20];

  sprintf(palavrasecreta, "MELANCIA");

  int acertou = 0;
  int enforcou = 0;

  char chutes[26];
  int tentativas = 0;

  cabecalho();

  do {

    for(int i = 0; i < strlen(palavrasecreta); i++) {
      
      int achou = 0;

      for(int j = 0; j < tentativas; j++) {
        if(chutes[j] == palavrasecreta[i]) {
          achou = 1;
          break;
        }
      }

      if(achou) {
        printf("%c ", palavrasecreta[i]);
      } else {
        printf("_ ");
      }
      
    }
    printf("\n");

    chuta(chutes, &tentativas);

  } while (!acertou && !enforcou);
  

  return 0;
}
