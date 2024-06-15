//BCGL-Hotel-Ativ04 - Programa Hotel.
//Grupo: Beatriz Lima Morais, Carolina Olmos Gracio Castanho, Grazielle Batista de Almeida e Luana Gabrielle Rodrigues Macedo - (09/06/2024).
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
#include <stdlib.h>
#include <string.h>

//Structures importantes para o programa

//struct para as informacoes pessoais do hospede
typedef struct{
  char cep[14];
  char numero[5];
  char complemento[2];
  char logradouro[25];
  char bairro[30];
  char cidade[20];
  char uf[3];
}EndCompleto;

//struture para o endereco do hospede
typedef struct{
  char nome[40];
  char cpf[12];
  // char adress[50];
  char telefone[12];
  char email[20];
  EndCompleto endereco;
} Hospede; // stores guest info

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
//divisão por tipo 
int standard[2]={14,1}; 
int master[2]={18,15}; 
int deluxe[2]={20,19};

//divisao por qtd de hospedes
int single[2]={4,1};
int couple[2]={9,5};
int family[2]={14,10};

int andarapto[2];

// Funções importantes para o funcionamento do programa
void fInicializarMatriz(Quarto matriz[20][14]);  
void fMapaHotel(Quarto matriz[20][14]);
int fVerificaApartamento(Quarto matriz[20][14], int andar, int apto);
void fTaxaOcupacao(Quarto matriz[20][14]);
void fclearBuffer();


// Funções relacionadas às informações do hospede
Hospede fHospedeInfo();
int dataValiDation();
void fImprimirDados(Hospede hospede);
int fDadosHospedePorCPF(char cpf[12], Quarto matriz[20][14]);
void fHospedeQuarto (Quarto matriz[20][14]);
void fSolicitarCPF(Quarto matriz[20][14]);


// Funções relacionadas às funcionalidades da reserva
void fDadosReserva(Quarto matriz[20][14]);
void fReserva(int andar, int apto, Quarto matriz[20][14]);
int fVerificaTipoAndar(int tipo);
int fVerificaTipoApto(int qtd);
int fDeterminarMaisProximo(int sequencia[], int andarPref);
int fDeterminarAndar(int andarPref, int tipo);
int fDeterminarAndarApto(int andarPref, int tipoAndar, Quarto matriz[20][14], int qtd, int andarapto[2]);
void GuardarDadosQuarto(Quarto matriz[20][14], int i, int j, int tipo, Hospede hospede, int qtd, int diasEstadia);
void fCancelarReserva(Quarto matriz[20][14]);

//Funções relacionadas às funcionalidades do check-in
void fCheckIn(Quarto matriz[20][14]);

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
        printf("1 - Verificar a ocupação dos quartos\n");
        printf("2 - Reservar um quarto\n");
        printf("3 - Check-in de hospede\n");
        printf("4 - Check-out de hospede\n");
        printf("5 - Cancelar reserva\n");
        printf("6 - Ver métricas de ocupação dos quartos\n");
        printf("7 - Ver informações do hospede\n");
        printf("8 - Verificar disponibilidade do quarto\n");
        printf("12 - Sair\n");
        printf("---------------------------------------\n");
        scanf("%d", &opcao);

        switch(opcao) 
        {
            case 1:
                fMapaHotel(Tab);
                break;
            case 2:
                fDadosReserva(Tab);
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
                fSolicitarCPF(Tab);
                break;
            case 8:
                fHospedeQuarto(Tab);
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while(opcao != 12);

    return 0;
}

// Inicializa a matriz de quartos
void fInicializarMatriz(Quarto matriz[20][14]) 
{
    for (int i = 0; i < 20; i++)
      for (int j = 0; j < 14; j++) 
        matriz[i][j].situacao = '.'; // Define todos os quartos como livres inicialmente
}

// Apresenta o mapa de ocupação do hotel
void fMapaHotel(Quarto matriz[20][14]) 
{
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


void GuardarDadosQuarto(Quarto matriz[20][14], int i, int j, int tipo, Hospede hospede, int qtd, int diasEstadia){
  matriz[i][j].hospede = hospede;
  matriz[i][j].tipo = tipo;
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

void fHospedeQuarto(Quarto matriz[20][14]) {
    int andar, apto;
        

        printf("Digite o andar (0 para sair): ");
        scanf("%d", &andar);

        if (andar == 0) {
            return;
        }

        printf("Digite o apartamento (0 para sair): ");
        scanf("%d", &apto);

        if (apto == 0) {
            return;
        }
        
        int status = fVerificaApartamento(matriz, andar, apto);

        if (status == 1) {
            printf("\nO apartamento %d no andar %d está reservado.\n", apto, andar);
            Hospede hospede = matriz[20 - andar][apto - 1].hospede;
            fImprimirDados(hospede);
        } else if(status == 2) {
            printf("\nO apartamento %d no andar %d está ocupado.\n", apto, andar);
            Hospede hospede = matriz[20 - andar][apto - 1].hospede;
            fImprimirDados(hospede);
        } else if(status == 4) {
            printf("\nO apartamento %d no andar %d está livre.\n", apto, andar);
        } else {
            printf("\nApartamento inexistente.\n");
        }
    
}

//funcao para limpar o buffer
void fclearBuffer() { 
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}


//----------------------------------------------------
// FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DA RESERVA

//Determina o andar mais próximo possível ao que foi dado como preferência pelo usuário, levando em consideração o tipo de apartamento
int fDeterminarMaisProximo(int sequencia[], int andarPref) {
    int dif, ultimo, menor = 99, posicao = 0, i = sequencia[1];

    for (int i = sequencia[1]; i <= sequencia[0]; i++) { 
        dif = andarPref - i;
        if (dif < 0) {
            dif = -dif;
        }
        if (dif < menor) {
            menor = dif;
            posicao = i;
        }
    }

    return posicao;
}

int fDeterminarAndar(int andarPref, int tipo){
    if(tipo == 1){
        return fDeterminarMaisProximo(standard, andarPref);
    }

    if(tipo == 2){
        return fDeterminarMaisProximo(master, andarPref);
    }

    if(tipo == 3){
        return fDeterminarMaisProximo(deluxe, andarPref);
    }

    return 0;
}

//Determina se a quantidade de hospedes escolhida é coerente com a quantidade máxima por quarto e, caso seja, retorna o tipo de quarto 
int fVerificaTipoApto(int qtd){
    if(qtd < 1 || qtd > 5){
        return 10; //o quarto precisa ter pelo menos 1 hospede e no máximo 5 hospedes
    }

    if(qtd <= 2){
        return 1; // quarto do tipo single
    }

    if(qtd <= 3){
        return 2; // quarto do tipo double
    }

    if(qtd < 6){
        return 3; // quarto do tipo family
    }

    return 0;
}

//Faz a reserva do quarto de acordo com as preferências e necessidades do hospedes
int fDeterminarAndarApto(int andarPref, int tipoAndar, Quarto matriz[20][14], int qtd, int andarapto[2]) {
    int tipoApto = fVerificaTipoApto(qtd);
    int andarPossivel = fDeterminarAndar(andarPref, tipoAndar);
    int andares[2]; 
    int aptos[2]; 

    // Define os limites dos andares e quartos com base no tipo
    if (tipoAndar == 1) {
        andares[1] = standard[1];
        andares[0] = standard[0];
    } else if (tipoAndar == 2) {
        andares[1] = master[1];
        andares[0] = master[0];
    } else {
        andares[1] = deluxe[1];
        andares[0] = deluxe[0];
    }

    if (tipoApto == 1) {
        aptos[1] = single[1];
        aptos[0] = single[0];
    } else if (tipoApto == 2) {
        aptos[1] = couple[1];
        aptos[0] = couple[0];
    } else {
        aptos[1] = family[1];
        aptos[0] = family[0];
    } 

    // Verifica primeiro se existe um quarto disponivel no andar mais próximo a preferencia do hospede e o reserva
        for (int j = aptos[1]; j <= aptos[0]; j++) {
            if (matriz[20 - andarPossivel][j - 1].situacao == '.') {
                andarapto[0] = 20 - andarPossivel;
                andarapto[1] = j - 1;
                fReserva(andarPossivel, j, matriz);
                return 0;
                }
        }

        // Caso não exista, verifica se existe um quarto disponivel nos andares acima da preferência do hospede e o reserva
        for(int i = andarPossivel + 1; i <= andares[0]; i++){
            for (int j = aptos[1]; j <= aptos[0]; j++) {
                if (matriz[20 - i][j - 1].situacao == '.') {
                    andarapto[0] = 20 - andarPossivel;
                    andarapto[1] = j - 1;
                    fReserva(i, j, matriz);
                    return 0; // 
                }
            }
        }

        // Caso também não exista, verifica se existe um quarto disponivel nos andares abaixo da preferencia e o reserva
        for(int i = andarPossivel - 1; i >= andares[1]; i++){
            for (int j = aptos[1]; j <= aptos[0]; j++) {
                if (matriz[20 - i][j - 1].situacao == '.') {
                    andarapto[0] = 20 - andarPossivel;
                    andarapto[1] = j - 1;
                    fReserva(i, j, matriz);
                    return 0; 
                }
            }
        }

        return -1; 
}


void fDadosReserva(Quarto matriz[20][14])
{
    int tipo, qtd, pref, dias;
    Reserva reserva;
    Hospede hospede;
    int andarapto[2];
    int qtdValida;

    system("cls||clear"); //Limpa as operações anteriores da tela (tanto no Windows como no Linux)
    printf("---------------------------------------\n");
    printf("RESERVAR UM QUARTO\n");
    printf("---------------------------------------\n");

    hospede = fHospedeInfo(); //pede os dados do hospede antes de fazer uma reserva
    
    do
    {
        printf("Quantas pessoas estao incluidas na reserva?(0 para sair): ");
        scanf("%d", &qtd);

        if (qtd == 0)  // caso o usuário queira sair da função sem sair do programa
            break;

        qtdValida = fVerificaTipoApto(qtd);

        if(qtdValida == 10){
            printf("Nao ha apartamentos para essa quantidade de hospedes.\n\n");
            continue;
        }

        printf("Qual o tipo de quarto? [1 para 'Standard' | 2 para 'Master'| 3 para 'Deluxe'] (0 para sair): ");
        scanf("%d", &tipo);

        if (tipo == 0) 
            break;

        if(tipo < 0 || tipo > 3){
            printf("Tipo de quarto invalido.\n\n");
            continue;
        }

        printf("Informe um andar de preferência para a reserva: (0 para sair): ");
        scanf("%d", &pref);

        if (pref == 0) 
            break;

      printf("Para quantos dias sao a reserva? (0 para sair): ");
      scanf("%d", &dias);

        if (dias == 0) 
          break;

        fDeterminarAndarApto(pref, tipo, matriz, qtd, andarapto);
        GuardarDadosQuarto(matriz, andarapto[0], andarapto[1], tipo, hospede, qtd, dias);
    } while(qtdValida == 10 || tipo < 0 || tipo > 3);
}

void fReserva(int andar, int apto, Quarto matriz[20][14]){
    matriz[20 - andar][apto - 1].situacao = 'R';
    system("cls||clear");
    printf("\nReserva realizada com sucesso do quarto %d no andar %d\n\n", apto, andar);
    fMapaHotel(matriz);
}

//Cancela a reserva do hospede e retira a visualização do apartamento reservado ('R') 
void fCancelarReserva(Quarto matriz[20][14]) 
{
    int status; //variável para receber o status do apartamento
    int a, b;

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CANCELAR RESERVA\n");
    printf("---------------------------------------\n");

    do 
  {
        printf("Escolha um andar(0 para sair): ");
        scanf("%d", &a);

        if(a == 0) // caso o usuário queira sair da função sem sair do programa
            break;

        printf("Escolha um apartamento: ");
        scanf("%d", &b);

        if(b == 0)
            break;

        status = fVerificaApartamento(matriz, a, b);

        if(status == 2 || status == 4) //se o quarto estiver livre ou ocupado não é possível cancelar a reserva
    { 
            printf("Operação indisponível para esse quarto. Tente outro \n\n");
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
    } while (status != 1 || (a != 0 || b != 0));  //Enquanto o status do quarto digitado não for "reservado" 
                                                //ou o usuário não digitar 0 para cancelar a operação
}

//-------------------------------------------------
//FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DO CHECK-IN

//Realiza o check-in do hospede em um apartamento reservado ou em um não reservado
void fCheckIn(Quarto matriz[20][14])
{
    int status, andar, apto, booked; // variável para saber se o usuário possui reserva prévia ou não (retorna 1 para reservado e 0 caso contrário)

    system("cls||clear");
    printf("---------------------------------------\n");
    printf("CHECK-IN DE HOSPEDE\n");
    printf("---------------------------------------\n");

    do 
  {
        printf("Já foi feita uma reserva previamente? (1-Sim e 0-Nao): ");
        scanf("%d", &booked);

        if (booked != 1 && booked != 0)
        {
            printf("Opção inválida. Por favor, tente novamente escolhendo entre (1-Sim e 0-Nao)\n\n");
        } 
      else 
      {     
            Hospede hospede;
            fHospedeInfo();//solicita os dados pessoais do hospede antes de realizar o check-in

            printf("Informe o andar do quarto a ser ocupado (0 para sair): ");
            scanf("%d", &andar);

            if (andar == 0)  // caso o usuário queira sair da função sem sair do programa
                break;

            printf("Informe o número do quarto a ser ocupado (0 para sair): ");
            scanf("%d", &apto);

            if (apto == 0)  // caso o usuário queira sair da função sem sair do programa
                break;

            status = fVerificaApartamento(matriz, andar, apto);

            if (status == 3)
      {
                printf("O apartamento informado não existe. Por favor, tente outro.\n\n");
                continue;
            }

            // Se a situação do apartamento for "reservado" e o hospede possuir reserva prévia OU se a situação do apartamento for "livre" e o hospede não possuir reserva, o check-in é realizado
            if (status == 1 && booked || status == 4 && !booked)
      { 
                matriz[20 - andar][apto - 1].situacao = 'O'; // Marca o quarto como ocupado
                printf("\nO check-in foi realizado com sucesso para o quarto %d no andar %d\n", apto, andar);
                fMapaHotel(matriz);
                break;
            } 
        else 
        { 
                if(booked) //Se foi informado que o hospede possui reserva prévia, o apartamento existe mas esta ocupado ou livre, então não há reserva
                    printf("Não há reserva para esse apartamento. Tente outro\n\n");
                else
                    printf("Apartamento não está disponível. Tente outro.\n\n");
            }
        }
    } while (1); //continua o loop até que um check-in seja realizado com sucesso
}


//-------------------------------------------------------
// FUNÇÕES RELACIONADAS ÀS FUNCIONALIDADES DO CHECK-OUT
int fDefinirValorTipo(int tipo){
    if(tipo == 1){
        return 250;
    } 

    if(tipo == 2){
        return 375;
    }

    if(tipo == 3){
        return 475;
    }
}

int fDefinirValorTotal(int tipo, int dias){
    return fDefinirValorTipo(tipo)*dias;
}

void fDefinirNomeTipo(int tipo, char nomeTipo[9]){
    if(tipo == 1){
        strcpy(nomeTipo, "Standard"); 
    } 
    if(tipo == 2){
        strcpy(nomeTipo, "Master"); 
    }
    if(tipo == 3){
        strcpy(nomeTipo, "Deluxe"); 
    }
}

void fDadosCheckOut(Quarto matriz[20][14], int andar, int apto){
    char nomeTipo[9];
    fDefinirNomeTipo(matriz[20 - andar][apto - 1].tipo, nomeTipo);
    
    printf("\n\n---------------------------------------\n");
    printf("RESUMO DA ESTADIA\n");
    printf("---------------------------------------\n");
    printf("Tipo de quarto: %s\n", nomeTipo);
    printf("Valor da diaria: %d reais\n", fDefinirValorTipo(matriz[20 - andar][apto - 1].tipo));
    printf("Valor total da estadia: %d reais\n", fDefinirValorTotal(matriz[20 - andar][apto - 1].tipo, matriz[20 - andar][apto - 1].reserva.diasEstadia));
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

    do 
  {
        printf("Para fazer o check-out precisamos de algumas informações: \n");

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
            printf("O apartamento escolhido está reservado. Por favor, tente outro.\n\n");
        }
        if (status == 2)
      {    
            matriz[20 - andar][apto - 1].situacao = '.';
            system("cls||clear");
            printf("\nO check-out foi realizado com sucesso para o apartamento %d no andar %d!\n", apto, andar);
            fDadosCheckOut(matriz, andar, apto);
            fMapaHotel(matriz);
            break;
        }

        if (status == 3)
        {
          printf("O apartamento escolhido parece não existir. Por favor, tente outro.\n\n");
        }

        if (status == 4)
        {
          printf("O apartamento escolhido já estava livre. Por favor, tente outro.\n\n");
    }
    } while(1); // enquanto o quarto escolhido existir
}

// FUNÇÕES RELACIONADAS ÀS INFORMAÇÕES DO HOSPEDE
int fDadosHospedePorCPF(char cpf[12], Quarto matriz[20][14]){
    for(int i = 0; i < 20; i++)
        for(int j = 0; j < 14; j++)
            if(strcmp(matriz[20-i][j - 1].hospede.cpf, cpf) == 0){
                Hospede hospede = matriz[20-i][j - 1].hospede;
                printf("O CPF %s corresponde ao hospede: \n", cpf);
                fImprimirDados(hospede);
                return 0;
            }

    return 1;
}

void fSolicitarCPF(Quarto matriz[20][14]){
    char cpf[12];
    printf("Informe o CPF do hospede\n:");
    scanf("%s", cpf);
    if(fDadosHospedePorCPF(cpf, matriz) == 1)
        printf("CPF nao encontrado");
}



//funcao para pedir os dados do hospede
Hospede fHospedeInfo(){
    Hospede hospede;

    fclearBuffer();

    printf("\nAntes de prosseguir, precisamos de alguns dados pessoais do hospede: \n\n");


    printf("CPF do hospede: ");
    gets(hospede.cpf);
    

    printf("Nome do hospede: ");
    gets(hospede.nome);
    

    printf("Celular do hospede: ");
    gets(hospede.telefone);

    printf("Email do hospede: ");
    gets(hospede.email);

    printf("Agora, precisamos de algumas informacoes sobre o endereco : \n\n");

    printf("CEP: ");
    gets(hospede.endereco.cep);

    printf("Logradouro: ");
    gets(hospede.endereco.logradouro);

    printf("Numero da residencia: ");
    gets(hospede.endereco.numero);

    printf("Complemento: ");
    gets(hospede.endereco.complemento);

    printf("Bairro: ");
    gets(hospede.endereco.bairro);

    printf("Cidade: ");
    gets(hospede.endereco.cidade);

    printf("UF: ");
    gets(hospede.endereco.uf);

    printf("\nAs informacoes do hospede foram cadastradas com sucesso!\n");
    return hospede;
}

//Assegura o input do user não seja vazio em todos os campos a partir da utilizacao do "||"
int dataValidation(Hospede hospede) {
    if (hospede.nome[0] != '\0' ||
        hospede.telefone[0] != '\0' ||
        hospede.cpf[0] != '\0' ||
        hospede.email[0] != '\0' ||
        hospede.endereco.cep[0] != '\0' ||
        hospede.endereco.numero[0] != '\0' ||
        hospede.endereco.complemento[0] != '\0' ||
        hospede.endereco.logradouro[0] != '\0' ||
        hospede.endereco.bairro[0] != '\0' ||
        hospede.endereco.cidade[0] != '\0' ||
        hospede.endereco.uf[0] != '\0') {
        return 1; //Input valido
    } else {
        return 0; // input vazio
    }
}

// funcao para mostrar os dados cadastrados do hospede(se todos nao forem todos vazios)
void fImprimirDados(Hospede hospede){

  if(dataValidation(hospede)){
      system("cls||clear");
      printf("---------------------------------------\n");
      printf("Informacoes cadastradas do hospede:\n");
      printf("---------------------------------------\n");
    
      printf("Nome: %s\n", hospede.nome);
      printf("CPF: %s\n", hospede.cpf);
      printf("Numero de celular: %s\n", hospede.telefone);
      printf("Email:  %s\n", hospede.email);
      printf("CEP: %s\n", hospede.endereco.cep);
      printf("Logradouro: %s\n", hospede.endereco.logradouro);
      printf("Numero da residencia:  %s\n", hospede.endereco.numero);
      printf("Complemento: %s\n", hospede.endereco.complemento);
      printf("Bairro: %s\n", hospede.endereco.bairro);
      printf("Cidade: %s\n", hospede.endereco.cidade);
      printf("UF: %s\n", hospede.endereco.uf);
  } else {
        printf("\nNao foi possivel encontrar nenhuma informacao cadastrada do hospede. Tente realizar o cadastramento primeiro\n");
  }
}

//Mostra ao usuario a porcentagem de ocupacao em relacao a todos os quartos do hotel
void fTaxaOcupacao(Quarto matriz[20][14])
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
    printf("MÉTRICAS DE OCUPAÇÃO DO HOTEL\n");
    printf("---------------------------------------\n\n");


    printf(" ---------------------------------------\n");
    printf("|%.2f%% dos apartamentos estao ocupados  |\n", (contadorOcupado/280)*100);
    printf("|%.2f%% dos apartamentos estao reservados|\n", (contadorReservado/280)*100);
    printf("|%.2f%% dos apartamentos estao livres  |\n",
        (((280-(contadorReservado+contadorOcupado))/280)*100));
    printf(" ---------------------------------------");
}

