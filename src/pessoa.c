#include "pessoa.h"
#include "util.h"
#include "playlist.h"
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
    pessoa->amizades = novaLista(sizeof(Pessoa), NULL, imprimirAmizade, buscarPessoa);
    pessoa->playlists = novaListaPlaylist();

    return pessoa;
}

void destruirPessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    destruirAmizades(pessoa->amizades); // Problemas em dar free nas amizades (double free) faz sentido pq essa funcao vai ser chamada para todos os usuarios do programa
    destruirLista(pessoa->playlists);

    free(pessoa);
}

void destruirAmizades(Pessoa *pessoa)
{

    free(pessoa->amizades);
}

void imprimirPessoa(Pessoa *pessoa)
{
    printf("PESSOA: %s\n", pessoa->nome);
    imprimirLista(pessoa->amizades);
    imprimirLista(pessoa->playlists);
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

void adicionarPlaylist(Pessoa *pessoa, Playlist *playlist)
{
    adicionarLista(pessoa->playlists, playlist);
}

Lista *lerAmizades(char *path)
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
                Pessoa *pessoa = novaPessoa(nome);
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

    fclose(file);
    return pessoas;
}

void criarPlaylistsPorAutoria(Lista *pessoas)
{
    int posicao = 0;
    Pessoa *pessoa;

    while (pessoa = getCelula(pessoas, posicao))
    {
        Playlist *playlist;
        int j = 0;

        while (playlist = getCelula(pessoa->playlists, j))
        {

            Musica *musica;
            int k = 0;
            while(musica = getCelula(getMusicas(playlist), k)){
                
                printf("dasds");

                // COMPARAR AS MUSICAS AQUI E CRIAR AS PLAYLISTS

                k++;
            }
            
            
            j++;
        }

        posicao++;
    }
}
