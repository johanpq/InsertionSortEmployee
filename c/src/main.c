#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "funcionario.c"

#define N_FUNCIONARIOS 1000


int main() {
    void limpar_buffer();
    int opcao;
    Funcionario **funcs = (Funcionario **)malloc(N_FUNCIONARIOS * sizeof(Funcionario *));
    int numFuncionarios = 0;

    FILE* arquivo = abrir_arquivo(funcs,&numFuncionarios);

    char nome[101];
    char cargo[21];

    int documento;

    do {
        printf("\n-- BEM VINDO --\n");
        printf("-- DIGITE A OPCAO DESEJADA --\n");
        printf("1-- CADASTRAR FUNCIONARIO --\n");
        printf("2-- LISTAR FUNCIONARIO\n");
        printf("3-- SAIR\n");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
            if (numFuncionarios < N_FUNCIONARIOS){
                printf("Digite o nome do funcionario: ");
                scanf(" %[^\n]", nome);
                limpar_buffer();
                printf("Digite o cargo do funcionario: ");
                scanf(" %[^\n]", cargo);
                limpar_buffer();
                printf("Digite o numero do documento do funcionario: ");
                while(scanf("%d", &documento) != 1){
                    printf("Digite somente numeros!\n");
                    printf("Digite o numero do documento do funcionario: ");
                    scanf("%d", &documento);
                    limpar_buffer();
                }
                limpar_buffer();
                //formata entrada
                maiusculo(nome, nome);               
                maiusculo(cargo, cargo);

                funcs[numFuncionarios] = cria_funcionario(nome, cargo, documento);
                numFuncionarios++; 
                break;
            }
            else{
                printf("Limite de funcionarios atingido");
                break;
            }
            case 2:
                if(numFuncionarios != 0){
                    printf("Imprimindo lista de funcionarios...\n");
                    imprime(funcs, numFuncionarios);
                }
                else{
                    printf("Nenhum Funcionario Cadastrado!\n");
                }
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default: printf("Entrada Invalida!\n");
           break;
        }
    } while (opcao != 3);
    grava_arquivo(funcs, numFuncionarios);
    int i;
    // Libera a memoria alocada para os funcionarios
    for ( i = 0; i < numFuncionarios; i++) {
        free(funcs[i]);
    }
    free(funcs);
    return 0;
}

