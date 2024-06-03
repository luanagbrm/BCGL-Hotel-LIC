#include <stdio.h>

void fConteudoMatriz(char matriz[20][14]);
void fMapaOcupacao(char matriz[20][14]);
int fVerificaApartamento(char matriz[20][14], int andar, int apto);
void fReserva(char matriz[20][14]);
void fTaxaOcupacao(char matriz[20][14]);
void fCancelarReserva(char matriz[20][14]);

int main(void) {
  char Tab[20][14];
  int opcao;
  fConteudoMatriz(Tab);
  
  do{
    printf("Hotel. O que deseja fazer?\n");
    printf("1 - Verificar a ocupação dos quartos\n");
    printf("2 - Reservar um quarto\n");
    printf("3 - Check-in de hospede\n");
    printf("4 - Check-out de hospede\n");
    printf("5 - Cancelar reserva\n");
    printf("6 - Métricas de ocupação dos quartos\n");
    printf("7 - Sair\n");
    scanf("%d", &opcao);

    if(opcao == 7)
        break;

    switch(opcao){
      case 1:
        fMapaOcupacao(Tab);
        break;
      case 2:
        fReserva(Tab);
        break;
      case 5:
        fCancelarReserva(Tab);
        break;
      case 6:
        fTaxaOcupacao(Tab);
    }
  } while(opcao != 4);

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
  int a = 20 - andar, b = apto - 1;
  
  if (matriz[a][b] == 'R')
    return 1;

  if (matriz[a][b] == 'O')
    return 2;

  if ((b < 0 || b > 13) || (a < 0 || a > 19))
    return 3;

  return 4;
}


//Função para reservar um apartamento utilizando a função fVerificaApartamento para validação
void fReserva(char matriz[20][14]) {
  int status; //variável para receber o status do apartamento
  int a, b;

  do {

    printf("Escolha um andar: ");
    scanf("%d", &a);

    printf("Escolha um apartamento: ");
    scanf("%d", &b);

    status = fVerificaApartamento(matriz, a, b);

    if(status == 2 || status == 1) {
      printf("Apartamento ocupado. Tente outro\n");
      continue;
    }
      

    if (status == 4) {
      matriz[20 - a][b-1] = 'R';
      printf("Reserva realizada com sucesso\n");
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");
    printf("Tente outro\n");

  } while (status != 2 || status != 1); //Enquanto não for livre
}

void fCancelarReserva(char matriz[20][14]) {
  int status; //variável para receber o status do apartamento
  int a, b;

  do {

    printf("Escolha um andar: ");
    scanf("%d", &a);

    printf("Escolha um apartamento: ");
    scanf("%d", &b);

    if(a == 0 || b == 0)
      break;

    status = fVerificaApartamento(matriz, a, b);

    if(status == 2 || status == 4) { //se o quarto estiver livre ou ocupado não é possível cancelar a reserva
      printf("Operação indisponível para esse quarto. Tente outro (Digite 0 para cancelar a operação)\n");
      continue;
    }


    if (status == 1) {
      matriz[20 - a][b-1] = '.';
      printf("A reserva do quarto %d do andar %d foi cancelada\n", a, b);
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");

    printf("Tente outro (Digite 0 para cancelar a operação)\n");

  } while (status != 4 || (a != 0 || b != 0)); //Enquanto o status do quarto digitado não for "reservado" ou o usuário não digitar 0 para cancelar a operação
}

//nao é so isso aqui coloquei só o basico do basico obg
void fTaxaOcupacao(char matriz[20][14]){
  double contadorOcupado = 0;
  double contadorReservado = 0;

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 14; j++)
      if(matriz[i][j] == 'R')
        contadorReservado++;
      else if(matriz[i][j] == 'O')
        contadorOcupado++;
  }

  printf("%.2f estão ocupados\n", (contadorOcupado/280)*100);
  printf("%.2f estão reservados\n", (contadorReservado/280)*100);
  printf("%.2f estão livres\n", ((280-contadorReservado+contadorOcupado)/280)*100);
}