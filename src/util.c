

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

#define TAM_UTIL 1

void removerQuebraLinha(char *nome)
{
    int size = strlen(nome);
    if (nome[size - 1] == '\n')
        nome[size - 2] = '\0';
}

char *lerLinha(FILE *fp)
{
    // if (linha == NULL)
    // {
    //     char linha[1024];
    // }
    // fgets(linha, 1024, fp);

    // printf("%s", linha);

    // return linha;
}

char *lerLinhaArquivo(char *texto)
{
    int caracter;
    size_t tamanhoChunk = TAM_UTIL;
    size_t posicaoChunk = 0;

    char *string = malloc(sizeof(char) * TAM_UTIL + 1);

    if (string == NULL)
    {
        printf("Não ha espaço para ser alocado em memoria\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while ((caracter = texto[i]) != '\n' && caracter != '\r') //enquanto não encontrar uma quebra de linha, continua a ler os caracteres
    {
        string[posicaoChunk++] = caracter;
        if (posicaoChunk == tamanhoChunk) // Se o tamanho da string é maior que o chunk, aumenta-se o tamanho alocado da string com realloc
        {
            tamanhoChunk += TAM_UTIL;

            string = realloc(string, sizeof(char) * tamanhoChunk);

            if (string == NULL)
            {
                printf("Não há mais espaço para ser alocado em memória\n");
                exit(EXIT_FAILURE);
            }
        }
        i++;
    }

    string[posicaoChunk] = '\0';

    return string;
}
