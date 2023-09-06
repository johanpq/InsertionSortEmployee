#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"
#include <time.h>

struct funcionario
{
    char nome[101];
    char cargo[21];
    int documento;
};

//função de criar os funcionarios, alocando dinamicamente, copiando e armazenando na struct
Funcionario *cria_funcionario(char *nome, char *cargo, int documento)
{
    Funcionario *f = (Funcionario *)malloc(sizeof(Funcionario));
    if (f == NULL)
    {
        printf("Erro ao alocar memoria!");
        exit(1);
    }

    strcpy(f->nome, nome);
    strcpy(f->cargo, cargo);
    f->documento = documento;

    return f;
}

void insertion_sort_funcionarios(Funcionario **funcionario, int tamanho)
{
    double time_start = clock();
    int i, j;
    Funcionario *aux;
    // Laço principal:
    // Percorre o vetor a partir do 1o item até o penúltimo
    for (i = 0; i < tamanho - 1; i++)
    {
        // compara o item i com o proximo item da lista
        if (strcmp(funcionario[i]->nome, funcionario[i + 1]->nome) > 0)
        {
            // Se o item i for maior que o item i+1, armazena o item i+1 na variavel auxiliar aux
            aux = funcionario[i + 1];
            // Promove a troca de itens
            funcionario[i + 1] = funcionario[i];
            funcionario[i] = aux;
            // J recebe o indice do item anterior para iniciar o laço interno que faŕa
            // as comparações do item base(aux) com os item anteriores.
            j = i - 1;
            while (j >= 0)
            {
                if (strcmp(aux->nome, funcionario[j]->nome) < 0)
                {
                    // Se o item base for menor que o item anterior, será realizada a troca
                    funcionario[j + 1] = funcionario[j];
                    funcionario[j] = aux;
                }
                else
                {
                    // Se o item anterior não for maior que o item base, o laço se encerra
                    break;
                }
                // caso a troca seja realizada, aux será comparado com o item anterior
                j--;
            }
        }
    }
    double time_end = clock();
    printf("Elapsed time: %e\n", time_end - time_start);

}
//função que abre o arquivo txt  e faz a leitura dos funcionarios
FILE *abrir_arquivo(Funcionario **funcionario, int *tamanho)
{
    char nome[101], cargo[21];
    int documento;
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }


    int i;
    for (i = 0; fscanf(arquivo, "%100s %20s %d", nome, cargo, &documento) != EOF; i++)
    {
        funcionario[i] = cria_funcionario(nome, cargo, documento);
    }

    *tamanho = i;
    return (arquivo);
}

//função usada para gravar os dados ordenados em um arquivo. 
void grava_arquivo(Funcionario **funcionario, int tamanho)
{
    int contador;
    FILE *arquivo = fopen("funcionarios.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
    
    insertion_sort_funcionarios(funcionario, tamanho);
    for (contador = 0; contador < tamanho; contador++)
        fprintf(arquivo, "%s\t %s\t %d\n", funcionario[contador]->nome, funcionario[contador]->cargo, funcionario[contador]->documento);


    fclose(arquivo);
}

//função para imprimir os funcionarios, ordenando com a chamada da função insetion sort
void imprime(Funcionario **funcionario, int tamanho)
{

    int contador;
    insertion_sort_funcionarios(funcionario, tamanho);
    for (contador = 0; contador < tamanho; contador++)
        printf("%s\t %s\t %d\n", funcionario[contador]->nome, funcionario[contador]->cargo, funcionario[contador]->documento);
}

//função para limpar o buffer
void limpar_buffer(void){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

//função para deixar em maiusculo
void maiusculo(char *s1, char *s2){
    int i = 0;
    while(s1[i] != '\0'){
        s2[i] = toupper(s1[i]);
        i++;
    }
    s2[i] = '\0';
}

