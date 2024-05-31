#include <stdio.h>

void fConteudoMatriz(char matriz[20][14]);
void fMapaOcupacao(char matriz[20][14]);
int fVerificaApartamento(char matriz[20][14], int andar, int apto);
void fReserva(char matriz[20][14], int andar, int apto);

int main(void) {
  char Tab[20][14];

  fConteudoMatriz(Tab);
  fMapaOcupacao(Tab);
  fReserva(Tab, 6, 10);
  fMapaOcupacao(Tab);

  return 0;
}

void fConteudoMatriz(char matriz[20][14]) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 14; j++)
      matriz[i][j] = '.';
  }
}

//Apresenta o mapa de ocupação do prédio, sinalizando o andar e o apartamento.
void fMapaOcupacao(char matriz[20][14]) {
  printf("Apto ->\t\t");
  for (int j = 0; j < 14; j++)
    printf("%d\t", j + 1);
  printf("\n\n");

  for (int i = 0; i < 20; i++) {
    printf("Andar %d \t", (20 - i));
    for (int j = 0; j < 14; j++)
      printf("%c \t", matriz[i][j]);
    printf("\n");
  }
}


/* Verifica o status do apartamento. 
1 = reservado
2 = ocupado
3 = inválido 
4 = livre
*/

int fVerificaApartamento(char matriz[20][14], int andar, int apto) {
  if (matriz[andar][apto] == 'R')
    return 1;

  if (matriz[andar][apto] == 'O')
    return 2;

  if ((apto < 0 || apto > 13) || (andar < 0 || andar > 19))
    return 3;

  return 4;
}


//Função para reservar um apartamento utilizando a função fVerificaApartamento para validação
void fReserva(char matriz[20][14], int andar, int apto) {
  int status; //variável para receber o status do apartamento
  int a = andar, b = apto;

  do {
    status = fVerificaApartamento(matriz, a, b); 

    if (status == 4) {
      matriz[a][b] = 'R';
      printf("Reserva realizada com sucesso\n");
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");
    else
      printf("Apartamento ocupado. ");

    printf("Tente outro\n");
    scanf("%d %d", &a, &b);

  } while (status != 4); //Enquanto não for livre
}
