Quando for subir o arquivo pro repositório (só quando a gente concordar que ta tudo certinho i tals), usa esse script no terminal do codespace do vscode

git add *

git commit -m "Explique o que você mexeu"

git branch -m main

git push -u https://github.com/luanagbrm/Hotel-LIC main




DOCUMENTAÇÃO:

Quais são os atributos do hospede?
  - nome
  - cpf
  - Estrutura endereço
  - telefone
  - email
  - data de nascimento

Quais são os atributos da reserva?
  - Tudo do apartamento
  - Tudo do hospede
  - qtd hospedes
  - dias de estadia

Quais são os atributos do apartamento?

  - tipo
  - qtd max de hospedes
  - andar
  - numero
  - status

Funções base:
  1. fazer a reserva
      - pergunta:
        - qtd hospedes;
        - necessidade especiais;
        - tipo do apto;
            - Determinar o apto  
      - Adicionar o resto das informações da Estrutura reserva;
    
2. check-in
     - pergunta:
           - cpf
             1. cpf encontrado
               - fazer check-in
             2. cpf não encontrado
               - chamar função reserva
               - fazer check-in

3. check-out
   - pergunta:
       - cpf
         - encontrar quarto
         - calcular valor total
         - apresentar dados da Reserva e o valor total
        
4. cancelar reserva
  - cpf
    - cancelar a reserva

5. visualizar status
   - apto e o andar
     1. se disponivel
       - informar disponibilidade
     2. se indisponivel
        - informar indisponibilidade
        - informar os dados do hospede do quarto informado
       
Funções de apoio:
  1. pedir dados do usuario
  2. pedir dados da reserva
  3. determinar apto
  4. pedir cpf
  5. determinar aptos por tipo e qtd


   
               
             




