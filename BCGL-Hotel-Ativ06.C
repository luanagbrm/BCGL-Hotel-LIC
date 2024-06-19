//BCGL-Hotel-Ativ06 - Programa Hotel.
//Grupo: Beatriz Lima Morais, Carolina Olmos Gracio Castanho, Grazielle Batista de Almeida e Luana Gabrielle Rodrigues Macedo - (18/06/2024).
//O Hotel deve conter 20 andares e 14 apartamentos por andar.
/*Apresentar um menu acessível para o usuário.
O Menu deve permitir e encaminhar o usuário:
1 - Verificar a ocupação dos quartos, mostrando os andares e apartamentos do hotel;

2- Definir três tipos de apartamentos para o hotel: "Standard", "Master" e "Deluxe". 
    - "Standard" será o mais barato e contará com os apartamentos do andar 1 ao 14.
    - "Master" será um pouco mais caro e contará com os apartamentos do andar 15 ao 18.
    - "Deluxe" será o mais caro e contará com os apartamentos dos andares 19 e 20.
Além disso, o apartamento será decidido também a partir da quantidade de pessoas hospedadas. Sendo os apartamentos de 1 a 4 para até 2 pessoas (single), de 5 a 9 para até 3 pessoas (couple), de 10 a 14 para até 5 pessoas (family). 
    - O sistema dará preferência para ocupar os apartamentos de menor capacidade primeiro.

3 - Reservar um apartamento a partir da solicitação do cadastro do hospede, o tipo de apartamento que ele deseja, a
quantidade de dias de estadia, um andar de preferência e quantas pessoas ficarão hospedadas (Deve aparecer 'R' para Reservado e 'O' para Ocupado); 
    - Ao informar o andar de prefêrencia, o sistema buscará o andar mais próximo do informado pelo usuário dentro da faixa de andares que o tipo de apartamento que ele escolheu possui.
        - Ex: caso o tipo seja master e o andar de prefêrencia 11, o sistema tentará alocá-lo no andar 15, o mais próximo de 11 entre os andares do tipo 2.

4- O cadastro deve solicitar o nome, cpf, telefone, email, cep, endereço, bairro, cidade e uf do hospede;

5 - Realizar o check-in de hospede a partir de uma reserva realizada (solicitar o cpf para realizar o check-in com mais facilidade).
E tornar possível realizar o check-in no hotel de hospede que não fez reserva;

6 - Realizar o check-out de hospede, isto é, liberar o apartamento que estava ocupado. Além disso, é preciso mostrar 
uma ficha dos dados de estadia, contendo o tipo de apartamento escolhido, o valor da diária, os dias de estadia e o valor total a ser pago;

7- Tornar possível cancelar uma reserva;

8- Verificar disponibilidade dos quartos, assim, caso esteja ocupado informar os dados do hospede;

9- Ver informações do hospede;

10- Verificar métricas de ocupação dos quartos, mostrando a porcentagem dos apartamentos que estão ocupados, reservados e livres;

11 - Permitir que o úsuario saia do programa ao digitar 12;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structures importantes para o programa

//Estrutura para armazenar o endereco do hospede
typedef struct{
  char cep[14];
  char endereco[60];
  char bairro[30];
  char cidade[20];
  char uf[3];
}EndCompleto;

//Estrutura para armazenar as informacoes pessoais do hospede
typedef struct{
  char nome[40];
  char cpf[12];
  char telefone[12];
  char email[20];
  EndCompleto endereco; 
} Hospede; 

// Estrutura para armazenar a reserva do quarto
typedef struct
{
  int qntHospede;
  int diasEstadia;
} Reserva;


// Estrutura para representar os quartos do hotel
typedef struct
{
    char situacao; // indica o status do apartamento: "." = livre, "R" = reservado, "O" = ocupado
    int tipo; // 1 = standard, 2 = master, 3 = deluxe
    Hospede hospede;
    Reserva reserva;
} Quarto;


// Variáveis globais
//divisão por tipo de apartamento
int standard[2]={14,1}; 
int master[2]={18,15}; 
int deluxe[2]={20,19};

//divisao por qtd de hospedes
int single[2]={4,1};
int couple[2]={9,5};
int family[2]={14,10};

// Funções importantes para o funcionamento do programa
void fInicializarMatriz(Quarto matriz[20][14]);  
void fMapaHotel(Quarto matriz[20][14]);
int fVerificaApartamento(Quarto matriz[20][14], int andar, int apto);
void fTaxaOcupacao(Quarto matriz[20][14]);
void fclearBuffer();


// Funções relacionadas às informações do hospede
Hospede fHospedeInfo(Quarto matriz[20][14]);
int dataValiDation();
void fImprimirDados(Hospede hospede);
int fDadosHospedePorCPF(char cpf[12], Quarto matriz[20][14]);
void fHospedeQuarto (Quarto matriz[20][14]);
void fSolicitarCPF(Quarto matriz[20][14]);
int fVerificaHospede(char cpfReserva[12], Quarto matriz[20][14], int andarapto[2]);
int campoVazio(Hospede hospede);
int fRetornaTodas(char cpfReserva[12], Quarto matriz[20][14], int andarapto[2]);
int CpfApto(char cpf[12], int andar, int apto, Quarto matriz[20][14], int andarapto[2]);


// Funções relacionadas às funcionalidades da reserva
int fDadosReserva(Quarto matriz[20][14], int andarap[2]);
void fEfetuarReserva(Quarto matriz[20][14]);
void fReserva(int i, int j, Quarto matriz[20][14]);
int fVerificaTipoAndar(int tipo);
int fVerificaTipoApto(int qtd);
int fDeterminarMaisProximo(int sequencia[], int andarPref);
int fDeterminarAndar(int andarPref, int tipo);
int fDeterminarAndarApto(int andarPref, int tipoAndar, Quarto matriz[20][14], int qtd, int andarapto[2]);
void GuardarDadosQuarto(Quarto matriz[20][14], int i, int j, Hospede hospede, int qtd, int diasEstadia);
void fCancelarReserva(Quarto matriz[20][14]);

//Funções relacionadas às funcionalidades do check-in
void fCheckIn(Quarto matriz[20][14]);
void fRealizarCheckIn(Quarto matriz[20][14], int andarapto[2]);
void fCheckInComReserva(Quarto matriz[20][14]);
void fCheckInSemReserva(Quarto matriz[20][14]);

//Funções relacionadas às funcionalidades do checkout
void fCheckOut(Quarto matriz[20][14]);
int fDefinirValorTotal(int tipo, int dias);
void fDefinirNomeTipo(int tipo, char nomeTipo[9]);
int fDefinirValorTipo(int tipo);
void fDadosCheckOut(Quarto matriz[20][14], int andar, int apto);



// Corpo do programa e interface do usuário
int main(void) 
{
    Quarto Tab[20][14]; // Matriz de quartos
    int opcao;

    fInicializarMatriz(Tab);

    printf("Bem vindo ao Hotel Sweet Home!");

    do 
   {
      //Menu para o usuário
        printf("\n---------------------------------------\n");
        printf("O que deseja fazer?\n");
        printf("1 - Verificar a ocupacao dos apartamentos\n");
        printf("2 - Reservar um quarto\n");
        printf("3 - Check-in de hospede\n");
        printf("4 - Check-out de hospede\n");
        printf("5 - Cancelar reserva\n");
        printf("6 - Verificar disponibilidade do quarto\n");
        printf("7 - Ver informacoes do hospede\n");
        printf("8 - Ver metricas de ocupacao dos quartos\n");
        printf("9 - Sair\n");
        printf("---------------------------------------\n");
        scanf("%d", &opcao);

        switch(opcao) 
        {
            case 1:
                fMapaHotel(Tab);
                break;
            case 2:
                fEfetuarReserva(Tab);
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
                fHospedeQuarto(Tab);
                break;
            case 7:
                fSolicitarCPF(Tab);
                break;
            case 8:
                fTaxaOcupacao(Tab);
                break;
            case 9:
                printf("Saindo da aplicacao");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }

    } while(opcao != 9);

    return 0;
}

// Inicializa a matriz de quartos
void fInicializarMatriz(Quarto matriz[20][14]) 
{
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 14; j++) 
        matriz[i][j].situacao = '.'; // Define todos os quartos como livres inicialmente

    //Atribui o tipo de cada apartamento de acordo com a sua posição no mapa do hotel
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 14; j++) 
            matriz[i][j].tipo = 3;

    for (int i = 2; i < 6; i++)
        for (int j = 0; j < 14; j++) 
            matriz[i][j].tipo = 2;

    for (int i = 6; i < 20; i++)
        for (int j = 0; j < 14; j++) 
            matriz[i][j].tipo = 1;
}

// Apresenta o mapa de ocupação do hotel
void fMapaHotel(Quarto matriz[20][14]) 
{
    system("cls||clear"); //Limpa as operações anteriores da tela (tanto no Windows como no Linux)
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

//Guarda os dados do hospede para utilizações futuras
void GuardarDadosQuarto(Quarto matriz[20][14], int i, int j, Hospede hospede, int qtd, int diasEstadia)
{
    matriz[i][j].hospede = hospede;
    matriz[i][j].reserva.qntHospede = qtd;
    matriz[i][j].reserva.diasEstadia = diasEstadia;
}

// Verifica a situação de um apartamento
int fVerificaApartamento(Quarto matriz[20][14], int andar, int apto) 
{
    int a = 20 - andar, b = apto - 1;

    // retorna um número a partir do status do apartamento
    if (matriz[a][b].situacao == 'R')         
      return 1;     // Reservado

    if (matriz[a][b].situacao == 'O')
      return 2;    // Ocupado

    // Verifica se o andar e apto informados estão dentro da faixa de valores da matriz do hotel
    if ((b < 0 || b > 13) || (a < 0 || a > 19))
      return 3;   // Inválido

    // caso nada se aplique, o quarto está livre
    return 4;      // Livre
}
// Verifica a disponibilidade de um apartamento e exibe as informações do hóspede
void fHospedeQuarto(Quarto matriz[20][14]) 
{
    int andar, apto;

    fMapaHotel(matriz);
    printf("---------------------------------------\n");
    printf("VERIFICAR DISPONIBILIDADE DO APARTAMENTO\n");
    printf("---------------------------------------\n");

    printf("Digite o andar (0 para sair): ");
    scanf("%d", &andar);

    if (andar == 0) 
    {
        return; //dá um retorno vazio para sair da função
    }

    printf("Digite o apartamento (0 para sair): ");
    scanf("%d", &apto);

    if (apto == 0)
    {
        return;
    }

    int status = fVerificaApartamento(matriz, andar, apto);

    if (status == 1) 
    {
        printf("\nO apartamento %d no andar %d esta reservado.\n", apto, andar);
        Hospede hospede = matriz[20 - andar][apto - 1].hospede;
        fImprimirDados(hospede);
    }

    else if (status == 2) 
    {
        printf("\nO apartamento %d no andar %d esta ocupado.\n", apto, andar);
        Hospede hospede = matriz[20 - andar][apto - 1].hospede;
        fImprimirDados(hospede);
    } 

    else if (status == 4) 
    {
        printf("\nO apartamento %d no andar %d esta livre.\n", apto, andar);

    }

    else
    {
        printf("\nApartamento inexistente.\n");
    }

}

//Função para limpar o buffer
void fclearBuffer() 
{ 
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


//----------------------------------------------------
// FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DA RESERVA

//Determina o andar mais próximo possível ao que foi dado como preferência pelo usuário, levando em consideração o tipo de apartamento
int fDeterminarMaisProximo(int sequencia[], int andarPref) 
{
    int dif, menorDif = 99, posicao = 0, i = sequencia[1]; 

    //Percorre os andares que pertencem ao tipo de apartamento escolhido pelo usuário e os compara com o andar de preferência do usuário
    for (int i = sequencia[1]; i <= sequencia[0]; i++) 
    { 
        dif = andarPref - i; // diferença entre o andar de preferência e os andares possíveis
        if (dif < 0) 
        {
            dif = -dif; // valor absoluto da diferença
        }
        if (dif < menorDif) 
        {
            menorDif = dif;
            posicao = i; //armazena o andar da nova menor diferença
        }
    }

    return posicao;
}

int fDeterminarAndar(int andarPref, int tipo)
{
    if(tipo == 1)
    {
        return fDeterminarMaisProximo(standard, andarPref);
    }

    if(tipo == 2)
    {
        return fDeterminarMaisProximo(master, andarPref);
    }

    if(tipo == 3)
    {
        return fDeterminarMaisProximo(deluxe, andarPref);
    }

    return 0;
}

//Determina se a quantidade de hospedes escolhida é coerente com a quantidade máxima por quarto e, caso seja, retorna o tipo de quarto 
int fVerificaTipoApto(int qtd)
{
    if(qtd < 1 || qtd > 5)
    {
        return 10; //o quarto precisa ter pelo menos 1 hospede e no máximo 5 hospedes
    }

    if(qtd <= 2)
    {
        return 1; // quarto do tipo single
    }

    if(qtd <= 3)
    {
        return 2; // quarto do tipo double
    }

    if(qtd < 6)
    {
        return 3; // quarto do tipo family
    }

    return 0;
}

//De acordo com as preferências e necessidades do hospedes e a disponibilidade dos quartos, retorna o andar e apto que mais se aproxima
int fDeterminarAndarApto(int andarPref, int tipoAndar, Quarto matriz[20][14], int qtd, int andarapto[2]) 
{
    int tipoApto = fVerificaTipoApto(qtd); 
    int andarPossivel = fDeterminarAndar(andarPref, tipoAndar);
    int andares[2]; 
    int aptos[2]; 

    // Define os limites dos andares com base no tipo de apartamento
    if (tipoAndar == 1) 
    {
        andares[1] = standard[1];
        andares[0] = standard[0];
    } 
    else if (tipoAndar == 2) 
    {
        andares[1] = master[1];
        andares[0] = master[0];
    } 
    else 
    {
        andares[1] = deluxe[1];
        andares[0] = deluxe[0];
    }

    do 
    {
        // Define os limites dos quartos com base na qtd de hospedes 
        if (tipoApto == 1) 
        {
            aptos[1] = single[1];
            aptos[0] = single[0];
        } 
        else if (tipoApto == 2) 
        {
            aptos[1] = couple[1];
            aptos[0] = couple[0];
        }
        else if (tipoApto == 3)
        {
            aptos[1] = family[1];
            aptos[0] = family[0];
        } 
        else 
        {
            return -2; //caso não seja nenhum dos tipos de quarto, encerra a função
        }

        // Verifica primeiro se existe um quarto disponivel e compatível no andar mais próximo a preferencia do hospede
        for (int j = aptos[1]; j <= aptos[0]; j++) 
        {
            if (matriz[20 - andarPossivel][j - 1].situacao == '.') 
            {
                andarapto[0] = 20 - andarPossivel; // retorna por meio de um array o andar
                andarapto[1] = j - 1;              // e o quarto 
                return 0;
            }
        }

        // Caso não exista, verifica se existe um quarto disponivel nos andares acima da preferência do hospede
        for(int i = andarPossivel + 1; i <= andares[0]; i++)
        {
            for (int j = aptos[1]; j <= aptos[0]; j++) 
            {
                if (matriz[20 - i][j - 1].situacao == '.') 
                {
                    andarapto[0] = 20 - i;
                    andarapto[1] = j - 1;
                    return 0; // 
                }
            }
        }

        // Caso também não exista, verifica se existe um quarto disponivel nos andares abaixo da preferencia
        for(int i = andarPossivel - 1; i >= andares[1]; i--)
        {
            for (int j = aptos[1]; j <= aptos[0]; j++) 
            {
                if (matriz[20 - i][j - 1].situacao == '.') 
                {
                    andarapto[0] = 20 - i;
                    andarapto[1] = j - 1;
                    return 0; 
                }
            }
        }

        tipoApto = tipoApto + 1; // Primeiro, o sistema vai tentar alocar no tipo de quarto com a menor capacidade compativel com a qtd de hospedes. Caso não tenha nenhum disponível, o sistema vai tentar alocá-los no segundo tipo de quarto compatível com menor capacidade e assim por diante.
    } while(1);

    return -1;
}

// Obtém os dados da reserva
int fDadosReserva(Quarto matriz[20][14], int andarap[2])
{
    int tipo, qtd, pref, dias;
    Reserva reserva;
    Hospede hospede;
    int qtdValida;

    hospede = fHospedeInfo(matriz); //pede os dados do hospede antes de fazer uma reserva
    if(campoVazio(hospede) == 1)
        return -1;

    do
    {
        printf("Quantas pessoas estao incluidas na estadia?(0 para sair): ");
        scanf("%d", &qtd);

        if (qtd == 0)  // caso o usuário queira sair da função sem sair do programa
            return -1;

        qtdValida = fVerificaTipoApto(qtd);

        if(qtdValida == 10)
        {
            printf("Nao ha apartamentos para essa quantidade de hospedes.\n\n");
            continue;
        }

        printf("Qual o tipo de quarto? [1 para 'Standard' | 2 para 'Master'| 3 para 'Deluxe'] (0 para sair): ");
        scanf("%d", &tipo);

        if (tipo == 0)
            return -1;

        if(tipo < 0 || tipo > 3)
        {
            printf("Tipo de quarto invalido.\n\n");
            continue;
        }

        printf("Informe um andar de preferencia: (0 para sair): ");
        scanf("%d", &pref);

        if (pref == 0) 
            return -1;

        printf("Quantos dias de estadia? (0 para sair): ");
        scanf("%d", &dias);

        if (dias == 0) 
            return -1;

        int status = fDeterminarAndarApto(pref, tipo, matriz, qtd, andarap);

        if(status == -2)
        {
            printf("Nao ha quartos disponiveis sob essas condicoes.\n\n");
            return -1;
        }

        GuardarDadosQuarto(matriz, andarap[0], andarap[1], hospede, qtd, dias);
    } while(qtdValida == 10 || tipo < 0 || tipo > 3); //enquanto a quantidade de hospedes ou o tipo de quarto estiver fora do intervalo

    return 0;
}

void fReserva(int i, int j, Quarto matriz[20][14])
{
    matriz[i][j].situacao = 'R';
    system("cls||clear");
    fMapaHotel(matriz);
    printf("\nReserva realizada com sucesso do quarto %d no andar %d\n\n", j+1, 20-i);
}


void fEfetuarReserva(Quarto matriz[20][14])
{
    int andarapto[2];
    system("cls||clear"); //Limpa as operações anteriores da tela (tanto no Windows como no Linux)
    fMapaHotel(matriz);
    printf("---------------------------------------\n");
    printf("RESERVAR UM QUARTO\n");
    printf("---------------------------------------\n");
    if(fDadosReserva(matriz, andarapto) == -1)
    {
        return; //caso o usuário tenha interrompido a função dos dados da reserva, o programa não seguirá com a reserva
    }
    fReserva(andarapto[0], andarapto[1], matriz);
}


//Cancela a reserva do hospede e retira a visualização do apartamento reservado ('R') 
void fCancelarReserva(Quarto matriz[20][14]) 
{
    int status; //variável para receber o status do apartamento
    int andar, apto;

    system("cls||clear");
    fMapaHotel(matriz);
    printf("---------------------------------------\n");
    printf("CANCELAR RESERVA\n");
    printf("---------------------------------------\n");

    do 
   {
        printf("Escolha um andar (0 para sair): ");
        scanf("%d", &andar);

        if(andar == 0) // caso o usuário queira sair da função sem sair do programa
            break;

        printf("Escolha um apartamento (0 para sair): ");
        scanf("%d", &apto);

        if(apto == 0)
            break;

        status = fVerificaApartamento(matriz, andar, apto);

        if(status == 2 || status == 4) //se o quarto estiver livre ou ocupado não é possível cancelar a reserva
       { 
            printf("Operacao indisponivel para esse quarto. Tente outro \n\n");
            continue;
        }

        if (status == 1)
        {
            matriz[20 - andar][apto - 1].situacao = '.';
            fMapaHotel(matriz);
            printf("\nA reserva do quarto %d do andar %d foi cancelada\n\n", andar, apto);
            break;
        }

        if (status == 3)
        {
          printf("Apartamento inexistente. Tente outro\n\n");
        }
    } while (status != 1 || (andar != 0 || apto != 0));  //Enquanto o status do quarto digitado não for "reservado" 
                                                        //ou o usuário não digitar 0 para cancelar a operação
}

//-------------------------------------------------
//FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DO CHECK-IN

//Realiza o check-in do hospede em um apartamento reservado ou em um não reservado
void fCheckIn(Quarto matriz[20][14])
{
    int booked; // variável para saber se o usuário possui reserva prévia ou não (retorna 1 para reservado e 0 caso contrário)

    system("cls||clear");
    fMapaHotel(matriz);
    printf("---------------------------------------\n");
    printf("CHECK-IN DE HOSPEDE\n");
    printf("---------------------------------------\n");

    printf("Ja foi feita uma reserva previamente? (1-Sim e 0-Nao): ");
    scanf("%d", &booked);

    if (booked == 1)
    {
        fCheckInComReserva(matriz);
    }         
    else if(booked == 0)
    {     
        fCheckInSemReserva(matriz);
    }
    else
    {
        printf("Opçao invalida. Por favor, tente novamente escolhendo entre (1-Sim e 0-Nao)\n\n");
    }
}

void fRealizarCheckIn(Quarto matriz[20][14], int andarapto[2])
{
    int i = andarapto[0];
    int j = andarapto[1];

    system("cls || clear");
    matriz[i][j].situacao = 'O'; // Marca o quarto como ocupado
    fMapaHotel(matriz);
    printf("\nO check-in foi realizado com sucesso para o quarto %d no andar %d\n", j+1, 20-i);
}

// Realiza o check-in para um hóspede que possui reserva
void fCheckInComReserva(Quarto matriz[20][14]) 
{
    int andar, apto;
    int status;
    char cpf[12];
    int booked;
    int reservaEncontrada = 0;
    int encontrado;
    int andarapto[2];

    do
    {
      // printf("Informe o andar da reserva (0 para sair): ");
      //   scanf("%d", &andar);

      //   if(andar == 0) // caso o usuário queira sair da função sem sair do programa
      //       break;

      //   printf("Informe o apartamento da reserva (0 para sair): ");
      //   scanf("%d", &apto);

      //   if(apto == 0)
      //       break;

        printf("Informe o CPF cadastrado na reserva (0 para sair): ");
        scanf("%s", cpf);

        if(strcmp(cpf, "0") == 0) 
        {
            break;
        }

        reservaEncontrada = 0; // Reinicia a variável de controle 
        encontrado = CpfApto(cpf, andar, apto, matriz, andarapto);
        status = fVerificaApartamento(matriz, 20 - andarapto[0], andarapto[1] + 1);
        if(encontrado == 0){
            printf("O CPF informado nao corresponde ao cadastrado neste quarto. Informe novamente\n\n");
            break;
        }

        if(encontrado && status == 1)
          reservaEncontrada = 1;


        // Verifica se há uma reserva para o CPF informado
        if (reservaEncontrada == 0) 
        {
            printf("Nenhuma reserva encontrada para o CPF informado.\n");
            printf("Gostaria de realizar o check-in sem reserva? (1-Sim, 0-Nao): ");
            scanf("%d", &booked);
            if (booked == 1) 
            {
                fCheckInSemReserva(matriz);
                break;
            } 
            else 
            {
                continue; // Volta a solicitar o CPF
            }
        } 
        else 
        {
            printf("Reserva encontrada no andar %d, apartamento %d. Confirmar check-in? (1-Sim, 0-Nao): ", 20 - andarapto[0], andarapto[1]+1);
            int confirmar;
            scanf("%d", &confirmar);

            if (confirmar != 1) 
            {
                printf("Check-in cancelado.\n");
                break;
            }

            andarapto[0] = 20 - andar;
            andarapto[1] = apto - 1;

            // Realiza o check-in
            fRealizarCheckIn(matriz, andarapto);
            break; // Sai da função após realizar o check-in
        }

    } while(1);
}

// Realiza o check-in para um hóspede que não possui reserva
void fCheckInSemReserva(Quarto matriz[20][14])
{
    int andarapto[2];

    if(fDadosReserva(matriz, andarapto) == -1)
    {
        return;
    }
    fRealizarCheckIn(matriz, andarapto);
 }

//-------------------------------------------------------
// FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DO CHECK-OUT
int fDefinirValorTipo(int tipo)
{
    if(tipo == 1)
    {
        return 250;
    } 

    if(tipo == 2)
    {
        return 375;
    }

    if(tipo == 3)
    {
        return 475;
    }

    return 0;
}

//Calcula o valor total da estadia de um hospede
int fDefinirValorTotal(int tipo, int dias)
{
    return fDefinirValorTipo(tipo)*dias;
}

//Retorna o nome do tipo de apartamento cujo o hospede estava hospedado
void fDefinirNomeTipo(int tipo, char nomeTipo[9])
{
    if(tipo == 1)
    {
        strcpy(nomeTipo, "Standard"); // atribui o nome do tipo de apartamento para a variável nomeTipo informada na chamada da função
    }

    if(tipo == 2)
    {
        strcpy(nomeTipo, "Master"); 
    }
    if(tipo == 3)
    {
        strcpy(nomeTipo, "Deluxe"); 
    }
}

//Cria uma nota contendo as informações da estadia do hospede com informações relevantes para a hora do pagamento
void fDadosCheckOut(Quarto matriz[20][14], int andar, int apto)
{
    char nomeTipo[9];
    fDefinirNomeTipo(matriz[20 - andar][apto - 1].tipo, nomeTipo);

    printf("\nCheck-Out realizado com sucesso.");
    printf("\n\n---------------------------------------\n");
    printf("RESUMO DA ESTADIA\n");
    printf("---------------------------------------\n");
    printf("Tipo de quarto: %s\n", nomeTipo);
    printf("Valor da diaria: %d reais\n", fDefinirValorTipo(matriz[20 - andar][apto - 1].tipo));
    printf("Dias de estadia: %d dias\n", matriz[20 - andar][apto - 1].reserva.diasEstadia);
    printf("Valor total da estadia: %d reais\n", fDefinirValorTotal(matriz[20 - andar][apto - 1].tipo, matriz[20 - andar][apto - 1].reserva.diasEstadia));

    printf("\n\nAGRADECEMOS PELA PREFERENCIA. ATE MAIS!\n");
    printf("---------------------------------------\n\n");
}

//Realiza o check-out do hospede, mudando o status do apartamento escolhido no mapa de ocupação do hotel 
void fCheckOut(Quarto matriz[20][14]) 
{
    int status, andar, apto;

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CHECK-OUT DE HOSPEDE\n");
    printf("---------------------------------------\n");
    fMapaHotel(matriz);

    do 
   {
        printf("Para fazer o check-out precisamos de algumas informacoes: \n");

        printf("O Andar do apartamento que o hospede esta ocupando(0 para sair): ");
        scanf("%d", &andar);

        if(andar == 0)  // caso o usuário queira sair da função sem sair do programa
            break;

        printf("O quarto que o hospede estava ocupando (0 para sair): ");
        scanf("%d", &apto);

        if(apto == 0)
            break;

        status = fVerificaApartamento(matriz, andar, apto);

        if (status == 1)
        {
            printf("O apartamento escolhido esta reservado. Por favor, tente outro.\n\n");
        }
        if (status == 2)
        {    
            matriz[20 - andar][apto - 1].situacao = '.';
            system("cls||clear");
            printf("\nO check-out foi realizado com sucesso para o apartamento %d no andar %d!\n", apto, andar);
            fMapaHotel(matriz);
            fDadosCheckOut(matriz, andar, apto);
            break;
        }

        if (status == 3)
        {
          printf("O apartamento escolhido parece nao existir. Por favor, tente outro.\n\n");
        }

        if (status == 4)
        {
          printf("O apartamento escolhido ja estava livre. Por favor, tente outro.\n\n");
        }
    } while(1); // enquanto o quarto escolhido existir
}

// FUNÇÕES RELACIONADAS ÀS INFORMAÇÕES DO HOSPEDE
int fDadosHospedePorCPF(char cpf[12], Quarto matriz[20][14])
{
    int andarapto[2] = {0,0};
    int encontrado = fVerificaHospede(cpf, matriz, andarapto);

            if(encontrado == 1)
            {
                Hospede hospede = matriz[andarapto[0]][andarapto[1]].hospede;
                fImprimirDados(hospede);
                return 1;
            }

    return 0;
}

void fSolicitarCPF(Quarto matriz[20][14])
{
    char cpf[12];
    printf("Informe o CPF do hospede: ");
    scanf("%s", cpf);
    if(fDadosHospedePorCPF(cpf, matriz) == 0)
        printf("CPF nao encontrado");
}

int CpfApto(char cpf[12], int andar, int apto, Quarto matriz[20][14], int andarapto[2]){
    for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 14; j++)
            { //verifica se o cpf e o mesmo e se o quarto esta reservado
                if (strcmp(matriz[20-i][j-1].hospede.cpf, cpf) == 0 && matriz[20-i][j-1].situacao == 'R')
                {
                    andarapto[0] = 20-i;
                    andarapto[1] = j-1;
                    return 1;
                }
            }
        }
    return 0;
}


//funcao para pedir os dados do hospede
Hospede fHospedeInfo(Quarto matriz[20][14])
{
    Hospede hospede;
    char resposta;
    int andarapto[2];

    fclearBuffer();

    printf("\nAntes de prosseguir, precisamos de alguns dados pessoais do hospede: \n\n");


    printf("CPF do hospede (Digite '+' para cancelar): ");
    gets(hospede.cpf);

    if(strcmp(hospede.cpf, "+") == 0)
    {
        return hospede;
    }

    if(fVerificaHospede(hospede.cpf, matriz, andarapto) == 1){
      printf("Usuario ja cadastrado anteriormente\n\n");
      hospede = matriz[andarapto[0]][andarapto[1]].hospede;
      return hospede; //Verifica se já existe um cadastro com o mesmo CPF, caso sim, para de pedir as informações e retorna as informações do hospede já cadastrado
    }


    printf("Nome do hospede (Digite '+' para cancelar): ");
    gets(hospede.nome);

    if(strcmp(hospede.nome, "+") == 0)
    {
        return hospede;
    }

    printf("Celular do hospede (Digite '+' para cancelar): ");
    gets(hospede.telefone);

    if(strcmp(hospede.telefone, "+") == 0)
    {
        return hospede;
    }

    printf("Email do hospede (Digite '+' para cancelar): ");
    gets(hospede.email);

    if(strcmp(hospede.nome, "+") == 0)
    {
        return hospede;
    } 

    printf("Agora, precisamos de algumas informacoes sobre o endereco : \n\n");

    printf("CEP (Digite '+' para cancelar): ");
    gets(hospede.endereco.cep);

    if(strcmp(hospede.endereco.cep, "+") == 0)
    {
        return hospede;
    } 

    printf("Endereco (Digite '+' para cancelar): ");
    gets(hospede.endereco.endereco);

    if(strcmp(hospede.endereco.endereco, "+") == 0)
    {
        return hospede;
    }

    printf("Bairro (Digite '+' para cancelar): ");
    gets(hospede.endereco.bairro);

    if(strcmp(hospede.endereco.bairro, "+") == 0)
    {
        return hospede;
    }

    printf("Cidade (Digite '+' para cancelar): ");
    gets(hospede.endereco.cidade);

    if(strcmp(hospede.endereco.bairro, "+") == 0)
    {
        return hospede;
    }

    printf("UF (Digite '+' para cancelar): ");
    gets(hospede.endereco.uf);

    if(strcmp(hospede.endereco.bairro, "+") == 0)
    {
        return hospede;
    }

    printf("\nAs informacoes do hospede foram cadastradas com sucesso!\n\n");
    return hospede;
}

int campoVazio(Hospede hospede) 
{
    if (hospede.nome[0] == '+' ||
        hospede.telefone[0] == '+' ||
        hospede.cpf[0] == '+' ||
        hospede.email[0] == '+' ||
        hospede.endereco.cep[0] == '+' ||
        hospede.endereco.endereco[0] == '+' ||
        hospede.endereco.bairro[0] == '+' ||
        hospede.endereco.cidade[0] == '+' ||
        hospede.endereco.uf[0] == '+') {
        return 1; // Input com caractere indicando cancelamento da operação
    } 
    else 
    {
        return 0; // input valido
    }
}

//Assegura o input do user não seja vazio em todos os campos a partir da utilizacao do "||"
int dataValidation(Hospede hospede) 
{
    if (hospede.nome[0] != '\0' ||
        hospede.telefone[0] != '\0' ||
        hospede.cpf[0] != '\0' ||
        hospede.email[0] != '\0' ||
        hospede.endereco.cep[0] != '\0' ||
        hospede.endereco.endereco[0] != '\0' ||
        hospede.endereco.bairro[0] != '\0' ||
        hospede.endereco.cidade[0] != '\0' ||
        hospede.endereco.uf[0] != '\0') {
        return 1; //Input valido
    } 
    else 
    {
        return 0; // input vazio
    }
}

// funcao para mostrar os dados cadastrados do hospede(se todos nao forem todos vazios)
void fImprimirDados(Hospede hospede)
{
    if(dataValidation(hospede))
    {

        system("cls||clear");
        printf("---------------------------------------\n");
        printf("Informacoes cadastradas do hospede:\n");
        printf("---------------------------------------\n");

        printf("Nome: %s\n", hospede.nome);
        printf("CPF: %s\n", hospede.cpf);
        printf("Numero de celular: %s\n", hospede.telefone);
        printf("Email:  %s\n", hospede.email);
        printf("CEP: %s\n", hospede.endereco.cep);
        printf("Logradouro: %s\n", hospede.endereco.endereco);
        printf("Bairro: %s\n", hospede.endereco.bairro);
        printf("Cidade: %s\n", hospede.endereco.cidade);
        printf("UF: %s\n", hospede.endereco.uf);
    } 
    else 
    {
        printf("\nNao foi possivel encontrar nenhuma informacao cadastrada do hospede. Tente realizar o cadastramento primeiro\n");
    }
}

//Mostra ao usuario a porcentagem de ocupacao em relacao a todos os quartos do hotel
void fTaxaOcupacao(Quarto matriz[20][14])
{
    // Métricas absolutas
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

    double ocupadosTotal, livresTotal, reservadosTotal;
    ocupadosTotal = (contadorOcupado/280)*100;
    reservadosTotal = (contadorReservado/280)*100;
    livresTotal = ((280-(contadorReservado+contadorOcupado))/280)*100;

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("METRICAS DE OCUPAÇÃO DO HOTEL\n");
    printf("---------------------------------------\n\n");


    printf(" -----------------------------------------\n");
    printf("| VISAO GERAL DO HOTEL                    |\n");
    printf("| %.2f%% dos apartamentos estao ocupados   |\n", ocupadosTotal);
    printf("| %.2f%% dos apartamentos estao reservados |\n", reservadosTotal);
    printf("| %.2f%% dos apartamentos estao livres   |\n", livresTotal);
    printf(" -----------------------------------------\n\n");
}

int fVerificaHospede(char cpfReserva[12], Quarto matriz[20][14], int andarapto[2])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 14; j++)
        { //verifica se o cpf e o mesmo e se o quarto esta reservado
            if (strcmp(matriz[20-i][j-1].hospede.cpf, cpfReserva) == 0)
            {
                andarapto[0] = 20-i;
                andarapto[1] = j-1;
                return 1;
            }
        }
    }
    return 0;
}
