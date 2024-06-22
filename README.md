# PROJETO: SISTEMA DE HOTEL
### Linguagens utilizadas:
<img src = "https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" />

### Desenvolvido por:
@luanagbrm, @GaiaOcean, @bialim, @linagrac 

## OBJETIVO

• Desenvolver um programa em C para controlar a ocupação e reservas dos apartamentos do hotel. Deve ser mantido o status de cada apartamento e as opções de check-in/check-out e a apresentação da ocupação. 

• Visando a simplificação por motivos pedagógicos, este projeto não está considerando qualquer controle de agenda, ignorando por completo as datas de reserva, datas de checkin e chekout, inclusive as disponibilidades de aptos no decorrer do tempo.

• Todas as operações apresentadas nos requisitos a seguir, podem ser aperfeiçoadas e complementadas conforme a criatividade dos alunos, desde que atendam o que está sendo proposto nestes objetivos (continua a simplificação de não considerar datas).

## REQUISITOS FUNCIONAIS

<b>REQ01</b> - O programa deve permitir ao usuário visualizar a ocupação dos apartamentos do hotel (mapa geral). 

<b>REQ02</b> - O programa deve permitir ao usuário fazer a reserva de um apartamento. 

<b>REQ03</b> - O programa deve permitir ao usuário realizar o checkin no hotel a partir de uma reserva realizada.

<b>REQ04</b> - O programa deve permitir ao usuário realizar o checkin no hotel de hospede que não fez reserva.

<b>REQ05</b> - O programa deve permitir ao usuário realizar o checkout, ou seja, liberar o apartamento que estava ocupado.

<b>REQ06</b> - O programa deve permitir ao usuário cancelar uma reserva.

<b>REQ07</b> - O programa deve permitir ao usuário visualizar as taxas de ocupação e de reservas do hotel. 

<b>REQ08</b> - O programa deve permitir ao usuário cadastrar as informações do hospede (CPF, nome, endereço completo, telefone celular e e-mail) no checkin. 

<b>REQ09</b> - O programa deve permitir ao usuário visualizar a situação de um apto. específico, e caso esteja ocupado, todas as informações do hospede.

## REQUISITOS OPCIONAIS

<b>REQ10</b> - O programa deve permitir ao usuário quando fizer a reserva, já cadastrar os dados do hospede

<b>REQ11</b> - O programa deve permitir ao usuário quando fizer o checkin, caso já exista uma reserva, conferir se se trata do hospede que fez a reserva. 

<b>REQ12</b> – Outros controles 
imaginados e criados pelos alunos 
do grupo que valorizam e 
aperfeiçoam o Projeto do Hotel.

## FUNCIONALIDADES ADICIONADAS PELO GRUPO

<b>Divisão dos apartamentos: </b>Cada quarto possui duas categorias, uma definida pela capacidade de hóspedes e outra pelo preço.

<b>Por preço:</b>
- Todos os apartamentos do andar 1 ao 14 são do tipo <b>Standard</b>
- Todos os apartamentos do andar 15 ao 18 são do tipo <b>Master</b>
- Todos os apartamentos nos andares 19 e 20 são do tipo <b>Deluxe</b>

<b>Por capacidade:</b>
- Em todos os andares, os apartamentos de 1 ao 4 são do tipo <b>Single</b>
- Em todos os andares, os apartamentos de 5 ao 9 são do tipo <b>Couple</b>
- Em todos os andares, os apartamentos de 10 ao 14 são do tipo <b>Family</b>

O sistema dá preferência por alocar os quartos de menor capacidade primeiro.

Para definir o apto, o hóspede irá informar um andar de preferência e, a partir disso, o sistema alocará-lo no apartamento mais próximo do informado dentro da faixa de valores que o tipo de apartamento possui e considerando a quantidade de hóspedes na reserva.
   
> Ex: tipo Master, andar de preferência 11 e 3 hospedes, o sistema tentará alocar, inicialmente, no apto 5, primeiro dos aptos para até 3 pessoas, do andar 15, o mais próximo do andar informado dentro dos andares do tipo Master

<b>Verificação de cadastro:</b> No momento de cadastro do hóspede, ao digitar o CPF, o sistema verifica se esse CPF já foi cadastro e, caso sim, recupera os dados para essa nova reserva para evitar duplicidade de cadastro.
