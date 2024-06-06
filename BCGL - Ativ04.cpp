//BCGL-Ativ04 - Programa Hotel.
//Integrantes do grupo: Beatriz, Carolina, Grazielle e Luana - (09/06/2024).
//O Hotel deve conter 20 andares e 14 apartamentos por andar.
/*Apresentar um menu acess�vel para o �suario.
O Menu deve permitir ao �suario:
1 - Verificar a ocupacao dos quartos, mostrando os andares e apartamentos do hotel;
2 - Reservar um quarto (Deve aparecer 'R' para Reservado e 'O' para Ocupado); 
3 - Realizar o check-in de hospede a partir de uma reserva realizada. E tornar poss�vel
realizar o check-in no hotel de hospede que n�o fez reserva;
4 - Realizar o check-out de hospede, isto �, liberar o apartamento que estava ocupado;
5 - Cancelar uma reserva;
6 - Verificar a taxa de ocupa��o e reservas do hotel;
7 - Permitir que o �suario saia do programa;
*/


//colocar dentro do swtich para aparecer o mapa d(check)
//o usuario deve poder sair depois de clicar
//comentar o codigo
//logica boa
//funcao para inicializacao do programa


#include <stdio.h>

void fConteudoMatriz(char matriz[20][14]);  
void fMapaOcupacao(char matriz[20][14]);
int fVerificaApartamento(char matriz[20][14], int andar, int apto);
void fReserva(char matriz[20][14]);
void fTaxaOcupacao(char matriz[20][14]);
void fCancelarReserva(char matriz[20][14]);
void fCheckIn(char matriz[20][14]);
void fcheckOut(char matriz[20][14]);


int main(void) {
  char Tab[20][14];
  int opcao;
  fConteudoMatriz(Tab);

  printf("Bem vindo ao Hotel Sweet Home!\n");
  do{
    printf("\n O que deseja fazer?\n");
    printf("1 - Verificar a ocupacao dos quartos\n");
    printf("2 - Reservar um quarto\n");
    printf("3 - Check-in de hospede\n");
    printf("4 - Check-out de hospede\n");
    printf("5 - Cancelar reserva\n");
    printf("6 - Metricas de ocupacao dos quartos\n");
    printf("7 - informacoes do hospede\n");
    printf("8 - Sair\n");
    scanf("%d", &opcao);

    switch(opcao){
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
      case 8:
//        printf("n");
        break;
      default:
        printf("Opcao invalida. Tente novamente.\n");
    }
  } while(opcao != 8);

  return 0;
}

//Apresenta o mapa do hotel
void fConteudoMatriz(char matriz[20][14]) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 14; j++)
      matriz[i][j] = '.';
  }
}

//Apresenta o mapa de ocupa��o do hotel, sinalizando o andar e o apartamento.
void fMapaOcupacao(char matriz[20][14]) {
  printf("Apartamentos ->\t\t");
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
3 = inv�lido 
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


//Fun��o para reservar um apartamento utilizando a fun��o fVerificaApartamento para valida��o
void fReserva(char matriz[20][14]) {
  int status; //vari�vel para receber o status do apartamento
  int a, b;
  
  do {
    
    printf("Escolha um andar(0 para sair): ");
    scanf("%d", &a);
    
    if( a == 0){
    	printf("Saindo do programa...\n");
    	break;
	}

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
       fMapaOcupacao(matriz);
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");
    printf("Tente outro\n");

  } while (status != 2 || status != 1); //Enquanto n�o for livre
}
//Realiza o check-in do hospode em um apartamento reservado ou em um n�o reservado
void fCheckIn(char matriz[20][14]){
    int status; 
    int a, b;
    int booked;

    do{
        printf("Voce ja reservou algum apartamento? (1-Sim e 0-Nao): ");
        scanf("%d", &booked);

        if (booked == 1) {
            printf("Nos diga o andar da reserva( 0 para sair): ");
            scanf("%d", &a);
            
             if( a == 0){
    			printf("Saindo do programa...\n");
    			break;
			}
			
            printf("Nos diga o quarto reservado: ");
            scanf("%d", &b);

            status = fVerificaApartamento(matriz, a, b);

            if (status == 1) {
                matriz[20-a][b-1] = 'O';
                printf("O check-in foi realizado com sucesso para o quarto %d no andar %d. Tenha uma boa estadia!\n", b, a);		   
                break;
            } else if (status == 3) {
                printf("O apartamento nao existe, por favor tente outro.\n");
            } else {
                printf("Apartamento nao esta' reservado. Tente outro.\n");
            }
        } else {
            printf("Digite um andar: ");
            scanf("%d", &a);
            printf("Digite um apartamento: ");
            scanf("%d", &b);

            status = fVerificaApartamento(matriz, a, b);

            if (status == 4) {
                matriz[20 - a][b - 1] = 'O';
                printf("O check-in foi realizado com sucesso para o quarto %d no andar %d. Tenha uma boa estadia!\n", b, a);
                break;
            } else if (status == 3) {
                printf("O apartamento nao existe, por favor tente outro.\n");
            } else {
                printf("Apartamento n�o esta' disponivel. Tente outro.\n");
            }
        }
    } while (1); //continua o loop at� um check-in for realizado com sucesso
    fMapaOcupacao(matriz);
}
//Realiza o check-out do hospede, mudando a apresenta��o do mapa de ocupa��o do hotel 
void fcheckOut(char matriz[20][14]){
  int status, a, b;

  do{
    printf("Obrigada por escolher o nosso hotel! Para fazer o check-out precisamos de algumas informacoes: \n");

    printf("O Andar do apartamento que voce esta ocupando: ");
    scanf("%d", &a);

    printf("O quarto que voce estava ocupando: ");
    scanf("%d", &b);

    if(a == 0 || b == 0)
        break;
 ;

    if(status == 2){
      matriz[20-a][b-1] = '.';
        printf("O check-out foi realizado com sucesso para o quarto %d no andar %d!\n",b,a);		   
        break;
        }else if(status == 3){
        printf("O apartamento escolhido parece nao existir.Por favor, tente outro\n");
      }else if(status == 4){
        printf("O quarto escolhido ja estava livre. Por favor, tente outro\n");
    }
//		   }else if(status == 3){
//		   	printf("O apartamento escolhido nao existe. Por favor, tente outro");
//		   }
    }while(1);// enquanto o quarto escolhido existir
    fMapaOcupacao(matriz);
  }
//Cancela a reserva do hospede e retira a visualiza��o do apartamento reservado ('R') 
void fCancelarReserva(char matriz[20][14]) {
  int status; //vari�vel para receber o status do apartamento
  int a, b;

  do {

    printf("Escolha um andar: ");
    scanf("%d", &a);

    printf("Escolha um apartamento: ");
    scanf("%d", &b);

    if(a == 0 || b == 0)
      break;

    status = fVerificaApartamento(matriz, a, b);

    if(status == 2 || status == 4) { //se o quarto estiver livre ou ocupado n�o � poss�vel cancelar a reserva
      printf("Operacao indisponivel para esse quarto. Tente outro (Digite 0 para cancelar a operacao)\n");
      continue;
    }


    if (status == 1) {
      matriz[20 - a][b-1] = '.';
      printf("A reserva do quarto %d do andar %d foi cancelada\n", a, b);
      break;
    }

    if (status == 3)
      printf("Apartamento inexistente. ");

    printf("Tente outro (Digite 0 para cancelar a operacao)\n");

  } while (status != 4 || (a != 0 || b != 0));  //Enquanto o status do quarto digitado n�o for "reservado" 
                                                //ou o usu�rio n�o digitar 0 para cancelar a opera��o
                                                
    fMapaOcupacao(matriz);
}

//nao � so isso aqui coloquei s� o basico do basico obg
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

 printf(" ----------------------------------------\n");
  printf("|%.2f%% dos apartamentos estao ocupados  |\n", (contadorOcupado/280)*100);
  printf("|%.2f%% dos apartamentos estao reservados|\n", (contadorReservado/280)*100);
  printf("|%.2f%% dos apartamentos estao livres  |\n",
    ((280-contadorReservado+contadorOcupado)/280)*100);
  printf("-----------------------------------------");

}