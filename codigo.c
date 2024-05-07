#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define conta_tam sizeof(struct Conta)
struct Conta {
    char numero[20];
    float saldo;
    char nome[50];
    char cpf[15];
    char telefone[20];
    int status; // 1/0
};
int buscarConta(FILE *arquivo, char numeroConta[]) {
    struct Conta conta;
    int posicao = 0;
    int encontrado = 0;
    rewind(arquivo);
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if ((strcmp(conta.numero, numeroConta) == 0) &&
            (conta.status==1)) {
            encontrado = 1;
            break;
        }
        posicao++;
    }
    if (posicao == 0 && !encontrado) {
        return -2; // ta vazio
    } else if (!encontrado) {
        return -1; // não achou
    } else if (ferror(arquivo)) {
        return -3; // erro de leitura
    }
    return posicao;
}
void atualizarArquivo(FILE *arquivo, struct Conta conta) {
    fseek(arquivo, 0, SEEK_END);
    fwrite(&conta, conta_tam, 1, arquivo);
}
void cadastrarConta(FILE *arquivo, char numeroConta[]) {
    struct Conta novaConta;
    if (buscarConta(arquivo, numeroConta)>=0) {
        printf("Número de conta já existente. Não foi possível cadastrar.\n");
        return;
    }
    strcpy(novaConta.numero, numeroConta);
    novaConta.status = 1; // ativa
    printf("Digite o saldo: ");
    scanf("%f", &novaConta.saldo);
    printf("Digite o nome: ");
    scanf("%s", novaConta.nome);
    printf("Digite o CPF: ");
    scanf("%s", novaConta.cpf);
    printf("Digite o telefone: \n");
    scanf("%s", novaConta.telefone);
    atualizarArquivo(arquivo, novaConta);
    printf("Conta cadastrada com sucesso!\n");
}
void consultarSaldo(FILE *arquivo, char numeroConta[]) {
    struct Conta conta;
    int found = 0;
    rewind(arquivo);
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if (strcmp(conta.numero, numeroConta) == 0 && conta.status == 1) {
            printf("Saldo da conta %s: %.2f\n", conta.numero, conta.saldo);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Conta não cadastrada\n");
    }
}
void depositar(FILE *arquivo, char numeroConta[]) {
    struct Conta conta;
    float valor;
    int found = 0;
    rewind(arquivo);
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if (strcmp(conta.numero, numeroConta) == 0 && conta.status == 1) {
            found = 1;
            printf("Digite o valor a ser depositado: ");
            scanf("%f", &valor);
            conta.saldo += valor;
            fseek(arquivo, -conta_tam, SEEK_CUR);
            fwrite(&conta, conta_tam, 1, arquivo);
            printf("Depósito realizado com sucesso, o novo saldo é de: %.2f\n", conta.saldo);
            break;
        }
    }
    if (!found) {
        printf("Conta não cadastrada\n");
    }
}
void sacar(FILE *arquivo, char numeroConta[]) {
    struct Conta conta;
    float valor;
    int found = 0;
    rewind(arquivo);
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if (strcmp(conta.numero, numeroConta) == 0 && conta.status == 1) {
            found = 1;
            printf("Digite o valor desejado para o saque: ");
            scanf("%f", &valor);
            if (conta.saldo >= valor) {
                conta.saldo -= valor;
                fseek(arquivo, -conta_tam, SEEK_CUR);
                fwrite(&conta, conta_tam, 1, arquivo);
                printf("Saque realizado com sucesso, o novo saldo é de: %.2f\n", conta.saldo);
            } else {
                printf("Saldo insuficiente para o saque\n");
            }
            break;
        }
    }
    if (!found) {
        printf("Conta não cadastrada\n");
    }
}
void listarContas(FILE *arquivo) {
    struct Conta conta;
    rewind(arquivo);
    printf("Listagem de Contas:\n");
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if (conta.status == 1) {
            printf("Conta: %s, Nome: %s, Telefone: %s, CPF: %s\n",
                   conta.numero, conta.nome, conta.telefone, conta.cpf);
        }
    }
}
void removerConta(FILE *arquivo, char numeroConta[]) {
    struct Conta conta;
    int found = 0;
    rewind(arquivo);
    while (fread(&conta, conta_tam, 1, arquivo) == 1) {
        if (strcmp(conta.numero, numeroConta) == 0 && conta.status == 1) {
            found = 1;
            conta.status = 0; // status 0
            fseek(arquivo, -conta_tam, SEEK_CUR);
            fwrite(&conta, conta_tam, 1, arquivo);
            printf("Conta removida com sucesso\n");
            break;
        }
    }
    if (!found) {
        printf("Conta não cadastrada\n");
    }
}
int main() {
    FILE *arquivo;
    int opcao;
    char numeroConta[20];
    arquivo = fopen("cadastro_contas.bin", "rb+");
    if (arquivo == NULL) {
        arquivo = fopen("cadastro_contas.bin", "wb+");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo\n");
            return 1;
        }
    }
    printf("Bem-vindo ao Banco Dinheiro Certo\n");
    do {
        printf("\nEscolha a opção:\n");
        printf("1 - Cadastrar nova conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depósito\n");
        printf("4 - Saque\n");
        printf("5 - Listar contas\n");
        printf("6 - Remover conta\n");
        printf("0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o número da nova conta: ");
                scanf("%s", numeroConta);
                cadastrarConta(arquivo, numeroConta);
                break;
            case 2:
                printf("Digite o número da conta: ");
                scanf("%s", numeroConta);
                consultarSaldo(arquivo, numeroConta);
                break;
            case 3:
                printf("Digite o número da conta: ");
                scanf("%s", numeroConta);
                depositar(arquivo, numeroConta);
                break;
            case 4:
                printf("Digite o número da conta: ");
                scanf("%s", numeroConta);
                sacar(arquivo, numeroConta);
                break;
            case 5:
                listarContas(arquivo);
                break;
            case 6:
                printf("Digite o número da conta a ser removida: ");
                scanf("%s", numeroConta);
                removerConta(arquivo, numeroConta);
                break;
            case 0:
                printf("Encerrando o programa\n");
                break;
            default:
                printf("Opção inválida. Tente de novo\n");
        }
    } while (opcao != 0);
    fclose(arquivo);
    return 0;
}
