#include "pessoa.h"
#include "musica.h"
#include "lista.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pessoa
{
    char *nome;
    Lista *playlists;
    Lista *amizades;
};

Pessoa *novaPessoa(char *nome)
{
    Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));

    pessoa->nome = strdup(nome);
    pessoa->amizades = novaLista(sizeof(Pessoa), destruirPessoa, imprimirAmizade, buscarPessoa);
    //pessoa->playlists = novaLista(sizeof(Musica), destruirMusica, imprimirMusica);;

    return pessoa;
}

void destruirPessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    destruirLista(pessoa->amizades);
    destruirLista(pessoa->playlists);

    free(pessoa);
}

void imprimirPessoa(Pessoa *pessoa)
{
    printf("PESSOA: %s\n", pessoa->nome);
    imprimirLista(pessoa->amizades);
    printf("\n");
}

void imprimirAmizade(Pessoa *pessoa)
{
    printf("  AMIGO: %s\n", pessoa->nome);
}

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado)
{

    *resultado = strcmp(pessoa->nome, nome);
}

void lerAmizades(char *path)
{
    int i = 0;

    Lista *pessoas = novaLista(sizeof(Pessoa), destruirPessoa, imprimirPessoa, buscarPessoa);

    FILE *file = fopen(path, "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (i == 0)
        {
            //cria as pessoas de acordo com a primeira linha do arquivo
            char *nome = strtok(linha, ";");
            while (nome)
            {
                Pessoa *pessoa = novaPessoa(strdup(nome));
                adicionarLista(pessoas, pessoa);

                nome = strtok(NULL, ";");

                if (nome)
                {
                    removerQuebraLinha(nome);
                }
            }
        }
        else
        {
            //adiciona a as amizades nas pessoas
            char *nome1 = strtok(linha, ";");
            Pessoa *pessoa1 = buscarLista(pessoas, nome1);

            char *nome2 = strtok(NULL, ";");
            removerQuebraLinha(nome2);

            Pessoa *pessoa2 = buscarLista(pessoas, nome2);

            adicionarLista(pessoa1->amizades, pessoa2);
            adicionarLista(pessoa2->amizades, pessoa1);
        }

        i++;
    }

    imprimirLista(pessoas);

    fclose(file);
}
