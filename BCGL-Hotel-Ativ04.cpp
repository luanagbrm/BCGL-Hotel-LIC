//BCGL-Hotel-Ativ04 - Programa Hotel.
//Grupo: Beatriz Lima Morais, Carolina Olmos Gracio Castanho, Grazielle Batista de Almeida e Luana Gabrielle Rodrigues Macedo - (09/06/2024).
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

#include <stdio.h>
#include <stdlib.h>

//Structures importantes para o programa

// Estrutura para representar os quartos do hotel
typedef struct
{
    char situacao; // indica o status do apartamento: "." = livre, "R" = reservado, "O" = ocupado
} quarto;

// Fun��es importantes para o funcionamento do programa
void fInicializarMatriz(quarto matriz[20][14]);  
void fMapaHotel(quarto matriz[20][14]);
int fVerificaApartamento(quarto matriz[20][14], int andar, int apto);
void fReserva(quarto matriz[20][14]);
void fTaxaOcupacao(quarto matriz[20][14]);
void fCancelarReserva(quarto matriz[20][14]);
void fCheckIn(quarto matriz[20][14]);
void fCheckOut(quarto matriz[20][14]);

// Corpo do programa e interface do usu�rio
int main(void) 
{
    quarto Tab[20][14]; // Matriz de quartos
    int opcao;

    fInicializarMatriz(Tab);

    printf("Bem vindo ao Hotel Sweet Home!");

    do 
	{
      //Menu para o usu�rio
        printf("\n---------------------------------------\n");
        printf("O que deseja fazer?\n");
        printf("1 - Verificar a ocupa��o dos quartos\n");
        printf("2 - Reservar um quarto\n");
        printf("3 - Check-in de hospede\n");
        printf("4 - Check-out de hospede\n");
        printf("5 - Cancelar reserva\n");
        printf("6 - Ver m�tricas de ocupa��o dos quartos\n");
        printf("7 - Sair\n");
        printf("---------------------------------------\n");
        scanf("%d", &opcao);

        switch(opcao) 
        {
            case 1:
                fMapaHotel(Tab);
                break;
            case 2:
                fReserva(Tab);
                break;
            case 3:
                fCheckIn(Tab);
                break;
            case 4:
                fCheckOut(Tab);
                break;
            case 5:
                fCancelarReserva(Tab);
                break;
            case 6:
                fTaxaOcupacao(Tab);
                break;
            case 7:
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }

    } while(opcao != 7);

    return 0;
}

// Inicializa a matriz de quartos
void fInicializarMatriz(quarto matriz[20][14]) 
{
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 14; j++) 
        matriz[i][j].situacao = '.'; // Define todos os quartos como livres inicialmente
}

// Apresenta o mapa de ocupa��o do hotel
void fMapaHotel(quarto matriz[20][14]) 
{
    system("cls||clear");
    printf("---------------------------------------\n");
    printf("MAPA - HOTEL\n");
    printf("---------------------------------------\n");
  
    printf("Aptos->\t\t");
    for (int j = 0; j < 14; j++)
      printf("%d\t", j + 1);
    printf("\n\n");

    for (int i = 0; i < 20; i++) 
	{
        printf("Andar %d \t", (20 - i));
        for (int j = 0; j < 14; j++)
            printf("%c \t", matriz[i][j].situacao);
        printf("\n");
    }
}

// Verifica o status de um apartamento
int fVerificaApartamento(quarto matriz[20][14], int andar, int apto) 
{
    int a = 20 - andar, b = apto - 1;

    // retorna um n�mero a partir do status do apartamento
    if (matriz[a][b].situacao == 'R')         
      return 1;     // Reservado

    if (matriz[a][b].situacao == 'O')
      return 2;    // Ocupado

    // Verifica se o andar e apto informados est�o dentro da faixa de valores da matriz do hotel
    if ((b < 0 || b > 13) || (a < 0 || a > 19))
      return 3;   // Inv�lido

    // caso nada se aplique, o quarto est� livre
    return 4;      // Livre
}

// Fun��o para reservar um apartamento
void fReserva(quarto matriz[20][14])
{
    int status, andar, apto;

    system("cls||clear"); //Limpa as opera��es anteriores da tela (tanto no Windows como no Linux)
    printf("---------------------------------------\n");
    printf("RESERVAR UM QUARTO\n");
    printf("---------------------------------------\n");

    do
	{
        printf("Escolha um andar(0 para sair): ");
        scanf("%d", &andar);

        if (andar == 0)  // caso o usu�rio queira sair da fun��o sem sair do programa 
            break;

        printf("Escolha um apartamento: ");
        scanf("%d", &apto);

        if (apto == 0) 
            break;

        status = fVerificaApartamento(matriz, andar, apto); //define o status do apartamento conforme as informa��es antes definidas na fun��o

        if (status == 2 || status == 1)
		{
            printf("Apartamento ocupado. Tente outro\n\n");
        }

        if (status == 4)
	    {
            matriz[20 - andar][apto - 1].situacao = 'R';
            printf("\nReserva realizada com sucesso do quarto %d no andar %d\n\n", apto, andar);
            fMapaHotel(matriz);
            break;
        }

        if (status == 3)
        {
        	printf("Apartamento inexistente. Tente outro\n\n");
		}
    } while (status != 4 || (apto != 0 && andar != 0)); //enquanto o status for diferente de 4 (livre) ou o usu�rio n�o quiser sair da fun��o
}

//Realiza o check-in do hospede em um apartamento reservado ou em um n�o reservado
void fCheckIn(quarto matriz[20][14])
{
    int status, andar, apto, booked; // vari�vel para saber se o usu�rio possui reserva pr�via ou n�o (retorna 1 para reservado e 0 caso contr�rio)

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CHECK-IN DE HOSPEDE\n");
    printf("---------------------------------------\n");

    do 
	{
        printf("J� foi feita uma reserva previamente? (1-Sim e 0-Nao): ");
        scanf("%d", &booked);

        if (booked != 1 && booked != 0)
	    {
            printf("Op��o inv�lida. Por favor, tente novamente escolhendo entre (1-Sim e 0-Nao)\n\n");
        } 
	    else 
	    {
            printf("Informe o andar do quarto a ser ocupado (0 para sair): ");
            scanf("%d", &andar);

            if (andar == 0)  // caso o usu�rio queira sair da fun��o sem sair do programa
                break;

            printf("Informe o n�mero do quarto a ser ocupado (0 para sair): ");
            scanf("%d", &apto);

            if (apto == 0)  // caso o usu�rio queira sair da fun��o sem sair do programa
                break;

            status = fVerificaApartamento(matriz, andar, apto);

            if (status == 3)
			{
                printf("O apartamento informado n�o existe. Por favor, tente outro.\n\n");
                continue;
            }

            // Se a situa��o do apartamento for "reservado" e o hospede possuir reserva pr�via OU se a situa��o do apartamento for "livre" e o hospede n�o possuir reserva, o check-in � realizado
            if (status == 1 && booked || status == 4 && !booked)
			{ 
                matriz[20 - andar][apto - 1].situacao = 'O'; // Marca o quarto como ocupado
                printf("\nO check-in foi realizado com sucesso para o quarto %d no andar %d\n", apto, andar);
                fMapaHotel(matriz);
                break;
            } 
		    else 
		    { 
                if(booked) //Se foi informado que o hospede possui reserva pr�via, o apartamento existe mas esta ocupado ou livre, ent�o n�o h� reserva
                    printf("N�o h� reserva para esse apartamento. Tente outro\n\n");
                else
                    printf("Apartamento n�o est� dispon�vel. Tente outro.\n\n");
            }
        }
    } while (1); //continua o loop at� que um check-in seja realizado com sucesso
}

//Realiza o check-out do hospede, mudando o status do apartamento escolhido no mapa de ocupa��o do hotel 
void fCheckOut(quarto matriz[20][14]) 
{
    int status, andar, apto;

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CHECK-OUT DE HOSPEDE\n");
    printf("---------------------------------------\n");

    do 
	{
        printf("Para fazer o check-out precisamos de algumas informa��es: \n");

        printf("O Andar do apartamento que o hospede esta ocupando(0 para sair): ");
        scanf("%d", &andar);

        if(andar == 0)  // caso o usu�rio queira sair da fun��o sem sair do programa
            break;

        printf("O quarto que o hospede estava ocupando (0 para sair): ");
        scanf("%d", &apto);

        if(apto == 0)
            break;

        status = fVerificaApartamento(matriz, andar, apto);

        if (status == 1)
        {
            printf("O apartamento escolhido est� reservado. Por favor, tente outro.\n\n");
        }
        if (status == 2)
	    {
            matriz[20 - andar][apto - 1].situacao = '.';
            printf("\nO check-out foi realizado com sucesso para o apartamento %d no andar %d!\n", apto, andar);
            fMapaHotel(matriz);
            break;
        }

        if (status == 3)
        {
        	printf("O apartamento escolhido parece n�o existir. Por favor, tente outro.\n\n");
        }

        if (status == 4)
        {
        	printf("O apartamento escolhido j� estava livre. Por favor, tente outro.\n\n");
		}
    } while(1);// enquanto o quarto escolhido existir
}

//Cancela a reserva do hospede e retira a visualiza��o do apartamento reservado ('R') 
void fCancelarReserva(quarto matriz[20][14]) 
{
    int status; //vari�vel para receber o status do apartamento
    int a, b;

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CANCELAR RESERVA\n");
    printf("---------------------------------------\n");

    do 
	{
        printf("Escolha um andar(0 para sair): ");
        scanf("%d", &a);

        if(a == 0) // caso o usu�rio queira sair da fun��o sem sair do programa
            break;

        printf("Escolha um apartamento: ");
        scanf("%d", &b);

        if(b == 0)
            break;

        status = fVerificaApartamento(matriz, a, b);

        if(status == 2 || status == 4) //se o quarto estiver livre ou ocupado n�o � poss�vel cancelar a reserva
		{ 
            printf("Opera��o indispon�vel para esse quarto. Tente outro \n\n");
            continue;
        }

        if (status == 1)
	    {
            matriz[20 - a][b-1].situacao = '.';
            printf("\nA reserva do quarto %d do andar %d foi cancelada\n\n", a, b);
            fMapaHotel(matriz);
            break;
        }

        if (status == 3)
        {
        	printf("Apartamento inexistente. Tente outro\n\n");
		}
    } while (status != 1 || (a != 0 || b != 0));  //Enquanto o status do quarto digitado n�o for "reservado" 
                                                //ou o usu�rio n�o digitar 0 para cancelar a opera��o
}

//Mostra ao usuario a porcentagem de ocupacao em relacao a todos os quartos do hotel
void fTaxaOcupacao(quarto matriz[20][14])
{
    double contadorOcupado = 0;
    double contadorReservado = 0;

    for (int i = 0; i < 20; i++)
	{
        for (int j = 0; j < 14; j++)
		{
            if(matriz[i][j].situacao == 'R')
                contadorReservado++;
            else if(matriz[i][j].situacao == 'O')
                contadorOcupado++;
        }
    }
  
    system("cls||clear");
    printf("---------------------------------------\n");
    printf("M�TRICAS DE OCUPA��O DO HOTEL\n");
    printf("---------------------------------------\n\n");

  
    printf(" ---------------------------------------\n");
    printf("|%.2f%% dos apartamentos estao ocupados  |\n", (contadorOcupado/280)*100);
    printf("|%.2f%% dos apartamentos estao reservados|\n", (contadorReservado/280)*100);
    printf("|%.2f%% dos apartamentos estao livres  |\n",
        (((280-(contadorReservado+contadorOcupado))/280)*100));
    printf(" ---------------------------------------");
}