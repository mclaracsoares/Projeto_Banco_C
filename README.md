# Projeto_Banco_C

### Autor: Maria Clara C Soares

### Descrição:

Este projeto consiste em um sistema simples de banco implementado em linguagem C, utilizando arquivos binários para o armazenamento de dados das contas dos clientes. O programa oferece diversas funcionalidades comuns em um sistema bancário, como cadastro de contas, consulta de saldo, depósito, saque, listagem de contas e remoção de contas.

### Funcionalidades:

Cadastrar nova conta: Permite o cadastro de uma nova conta, solicitando informações como número da conta, saldo, nome do titular, CPF e telefone.

Consultar saldo: Permite ao cliente consultar o saldo de uma conta informando o número da mesma.

Depósito: Realiza o depósito de um valor em uma conta específica, solicitando o número da conta e o valor a ser depositado.

Saque: Permite o saque de um valor de uma conta, desde que haja saldo suficiente, solicitando o número da conta e o valor desejado.

Listar contas: Exibe uma listagem de todas as contas cadastradas no sistema, apresentando o número da conta, nome do titular, telefone e CPF.

Remover conta: Remove uma conta do sistema, tornando-a inativa, ao informar o número da conta a ser removida.

### Instruções de Uso:

Ao executar o programa, o usuário será apresentado a um menu com as opções disponíveis.

O usuário deve escolher a opção desejada digitando o número correspondente e pressionando Enter.

Para as opções que requerem entrada de dados, como número da conta, saldo, etc., o usuário deverá seguir as instruções fornecidas pelo programa.

O programa continuará em execução até que o usuário escolha a opção de sair (opção 0).

Após encerrar o programa, todos os dados das contas serão salvos no arquivo binário cadastro_contas.bin.

### Observações:

É importante manter o arquivo cadastro_contas.bin junto com o executável do programa para garantir o correto funcionamento e persistência dos dados entre as execuções.

Este projeto foi desenvolvido como uma aplicação de console em linguagem C e pode ser compilado e executado em um ambiente de desenvolvimento compatível.
