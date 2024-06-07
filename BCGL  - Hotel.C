//BCGL-Ativ04 - Programa Hotel.
//Integrantes do grupo: Beatriz, Carolina, Grazielle e Luana - (09/06/2024).
//O Hotel deve conter 20 andares e 14 apartamentos por andar.
/*Apresentar um menu acessível para o úsuario.
O Menu deve permitir ao úsuario:
1 - Verificar a ocupacao dos quartos, mostrando os andares e apartamentos do hotel;
2 - Reservar um quarto (Deve aparecer 'R' para Reservado e 'O' para Ocupado); 
3 - Realizar o check-in de hospede a partir de uma reserva realizada. E tornar possível
realizar o check-in no hotel de hospede que não fez reserva;
4 - Realizar o check-out de hospede, isto é, liberar o apartamento que estava ocupado;
5 - Cancelar uma reserva;
6 - Verificar a taxa de ocupação e reservas do hotel;
7 - Permitir que o úsuario saia do programa;
*/

#include <stdio.h>

//Structures importantes para o programa

// Estrutura para representar os quartos do hotel
typedef struct {
    char situation; // indica o status do apartamento
} room;

// Funções importantes para o funcionamento do programa
void fConteudoMatriz(room matriz[20][14]);  
void fMapaOcupacao(room matriz[20][14]);
int fVerificaApartamento(room matriz[20][14], int andar, int apto);
void fReserva(room matriz[20][14]);
void fTaxaOcupacao(room matriz[20][14]);
void fCancelarReserva(room matriz[20][14]);
void fCheckIn(room matriz[20][14]);
void fcheckOut(room matriz[20][14]);
void fProgramAvaluation(int choice);

// Corpo do programa e interface do usuário
int main(void) {
    room Tab[20][14]; // Matriz de quartos
    int opcao;

    fConteudoMatriz(Tab);

    printf("Bem vindo ao Hotel Sweet Home!\n");

    do {
        printf("\nO que deseja fazer?\n");
        printf("1 - Verificar a ocupacao dos quartos\n");
        printf("2 - Reservar um quarto\n");
        printf("3 - Check-in de hospede\n");
        printf("4 - Check-out de hospede\n");
        printf("5 - Cancelar reserva\n");
        printf("6 - Metricas de ocupacao dos quartos\n");
        printf("7 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                fMapaOcupacao(Tab);
                break;
            case 2:
                fReserva(Tab);
                break;
            case 3:
                fCheckIn(Tab);
                break;
            case 4:
                fcheckOut(Tab);
                break;
            case 5:
                fCancelarReserva(Tab);
                break;
            case 6:
                fTaxaOcupacao(Tab);
                break;
            case 7:
                fProgramAvaluation(opcao);
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while(opcao != 7);

    return 0;
}

// Inicializa a matriz de quartos
void fConteudoMatriz(room matriz[20][14]) {
    // Define todos os quartos como livres inicialmente
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 14; j++) {
            matriz[i][j].situation = '.';
        }
    }
}

// Apresenta o mapa de ocupação do hotel

void fMapaOcupacao(room matriz[20][14]) {
    printf("Aptos->\t\t");
    for (int j = 0; j < 14; j++)
        printf("%d\t", j + 1);
    printf("\n\n");

    for (int i = 0; i < 20; i++) {
        printf("Andar %d \t", (20 - i));
        for (int j = 0; j < 14; j++)
            printf("%c \t", matriz[i][j].situation);
        printf("\n");
    }
}


// Verifica o status de um apartamento
int fVerificaApartamento(room matriz[20][14], int andar, int apto) {
    int a = 20 - andar, b = apto - 1;

    if (matriz[a][b].situation == 'R')
        return 1; // Reservado
    if (matriz[a][b].situation == 'O')
        return 2; // Ocupado
    if ((b < 0 || b > 13) || (a < 0 || a > 19))
        return 3; // Inválido

    return 4; // Livre
}

// Função para reservar um apartamento
void fReserva(room matriz[20][14]) {
    int status;
    int a, b;

    do {
        printf("Escolha um andar(0 para sair): ");
        scanf("%d", &a);

        if (a == 0) break;

        printf("Escolha um apartamento: ");
        scanf("%d", &b);

        status = fVerificaApartamento(matriz, a, b);

        if (status == 2 || status == 1) {
            printf("Apartamento ocupado. Tente outro\n");
            continue;
        }

        if (status == 4) {
            matriz[20 - a][b - 1].situation = 'R';
            printf("Reserva realizada com sucesso\n\n");
            fMapaOcupacao(matriz);
            break;
        }

        if (status == 3)
            printf("Apartamento inexistente. Tente outro\n");

    } while (status != 2 || status != 1);
}

// Realiza o check-in do hospede em um apartamento

//Realiza o check-in do hospede em um apartamento reservado ou em um não reservado
void fCheckIn(room matriz[20][14]) {
    int status;
    int a, b;
    int booked; // variável para saber se o usuário possui reserva prévia ou não (retorna 1 para reservado e 0 caso contrário)

    do {
        printf("Você já reservou algum apartamento? (1-Sim e 0-Não): ");
        scanf("%d", &booked);

        if (booked == 1) { // se reservou
            printf("Nos diga o andar da reserva (0 para sair): ");
            scanf("%d", &a);

            if (a == 0) { // caso o usuário queira sair da função sem sair do programa
                break;
            }

            printf("Nos diga o quarto reservado: ");
            scanf("%d", &b);

            status = fVerificaApartamento(matriz, a, b);

            if (status == 1) {
                matriz[20 - a][b - 1].situation = 'O'; // Marcar o quarto como ocupado
                printf("O check-in foi realizado com sucesso para o quarto %d no andar %d\n", b, a);
                fMapaOcupacao(matriz);
                break;
            } else if (status == 3) {
                printf("O apartamento não existe, por favor, tente outro.\n");
            } else {
                printf("Apartamento não está reservado. Tente outro.\n");
            }
        } else { // se o usuário não fez reserva
            printf("Digite um andar (0 para sair): ");
            scanf("%d", &a);

            if (a == 0) { // caso o usuário queira sair da função
                break;
            }

            printf("Digite um apartamento: ");
            scanf("%d", &b);

            status = fVerificaApartamento(matriz, a, b);

            if (status == 4) {
                matriz[20 - a][b - 1].situation = 'O';
                printf("O check-in foi realizado com sucesso para o quarto %d no andar %d. Tenha uma boa estadia!\n", b, a);
                fMapaOcupacao(matriz);
                break;
            } else if (status == 3) {
                printf("O apartamento não existe, por favor, tente outro.\n");
            } else {
                printf("Apartamento não está disponível. Tente outro.\n");
            }
        }
    } while (1); //continua o loop até um check-in for realizado com sucesso
}

//Realiza o check-out do hospede, mudando o status do apartamento escolhido no  mapa de ocupação do hotel 
void fcheckOut(room matriz[20][14]){
  int status, a, b;

  do{
    printf("Para fazer o check-out precisamos de algumas informacoes: \n");

    printf("O Andar do apartamento que o hospde esta ocupando(0 para sair): ");
    scanf("%d", &a);

    if(a == 0){// caso o usuário queira sair da função sem sair do programa
     break;
    }

    printf("O quarto que voce estava ocupando: ");
    scanf("%d", &b);

    if(a == 0 || b == 0)
        break;

     status = fVerificaApartamento(matriz, a, b);

    if (status == 2) {
        matriz[20 - a][b - 1].situation = '.';
        printf("O check-out foi realizado com sucesso para o quarto %d no andar %d!\n", b, a);
      break;
        fMapaOcupacao(matriz);
  } else if (status == 3) {
        printf("O apartamento escolhido parece não existir. Por favor, tente outro.\n");
  } else if (status == 4) {
        printf("O quarto escolhido já estava livre. Por favor, tente outro.\n");
}

    }while(1);// enquanto o quarto escolhido existir
  }

//Cancela a reserva do hospede e retira a visualização do apartamento reservado ('R') 
void fCancelarReserva(room matriz[20][14]) {
  int status; //variável para receber o status do apartamento
  int a, b;

  do {

    printf("Escolha um andar(0 para sair): ");
    scanf("%d", &a);

    if(a == 0) {
      break;
  }

    printf("Escolha um apartamento: ");
    scanf("%d", &b);

    if(a == 0 || b == 0)
      break;

    status = fVerificaApartamento(matriz, a, b);

    if(status == 2 || status == 4) { //se o quarto estiver livre ou ocupado não é possível cancelar a reserva
      printf("Operacao indisponivel para esse quarto. Tente outro \n");
      continue;
    }


    if (status == 1) {
      matriz[20 - a][b-1].situation = '.';
      printf("A reserva do quarto %d do andar %d foi cancelada\n", a, b);
      fMapaOcupacao(matriz);
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");

    printf("Tente outro\n");

  } while (status != 4 || (a != 0 || b != 0));  //Enquanto o status do quarto digitado não for "reservado" 
                                                //ou o usuário não digitar 0 para cancelar a operação
}

//mostra ao usuario a porcentagem de ocupacao em relacao a todos os quartos do hotel
void fTaxaOcupacao(room  matriz[20][14]){
  double contadorOcupado = 0;
  double contadorReservado = 0;

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 14; j++)
      if(matriz[i][j].situation == 'R')
        contadorReservado++;
      else if(matriz[i][j].situation == 'O')
        contadorOcupado++;
  } 

 printf(" ---------------------------------------\n");
  printf("|%.2f%% dos apartamentos estao ocupados  |\n", (contadorOcupado/280)*100);
  printf("|%.2f%% dos apartamentos estao reservados|\n", (contadorReservado/280)*100);
  printf("|%.2f%% dos apartamentos estao livres  |\n",
    ((280-contadorReservado+contadorOcupado)/280)*100);
  printf(" ---------------------------------------");

}

//Posibilita o usario avaliar o programa
void fProgramAvaluation(int choice){
  int aval;//variavel que indica a 

  do{

  printf("Antes de ir, gostaria de avaliar o nosso servico(1-sim e 0-nao):");
  scanf("%d", &choice);

  if(choice == 1){
    printf("Nos conte o que achou do nosso servico(1-pessimo, 2-bom, 3-muito bom):");
        scanf("%d", &aval);

        if ((aval != 1) && (aval != 2) && (aval != 3)) {
          printf("Escolha invalida. Por favor tente novamente\n\n");
          continue;
    }
        printf("Agradecemos pela a sua avaliacao!Tenha um bom dia");
        break;
  }else if(choice == 0){
    printf("Tenha um bom dia!");
    break;
  }else{
    printf("Escolha invalida. Por favor tente novamente\n\n");
    continue;
  }

  }while(1);//while a opcao nao seja 0}

}
