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
    pessoa->amizades = novaListaPessoa(destruirAmizade, imprimirAmizade, buscarPessoa);
    pessoa->playlists = novaListaPlaylist();

    return pessoa;
}

Lista *novaListaPessoa(void *freeFunction, void *printFunction, void *searchFunction)
{
    return novaLista(sizeof(Pessoa), freeFunction, printFunction, searchFunction);
}

void destruirPessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    destruirLista(pessoa->amizades); // Problemas em dar free nas amizades (double free) faz sentido pq essa funcao vai ser chamada para todos os usuarios do programa
    destruirLista(pessoa->playlists);

    free(pessoa);
}

void destruirAmizade(Pessoa *pessoa)
{
    free(pessoa->nome);
    free(pessoa);
}

void imprimirPessoa(Pessoa *pessoa)
{
    printf("PESSOA: %s\n", pessoa->nome);

    if (pessoa->amizades)
        imprimirLista(pessoa->amizades);

    if (pessoa->playlists)
        ;
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

    Lista *pessoas = novaListaPessoa(destruirPessoa, imprimirPessoa, buscarPessoa);

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

void lerPlaylists(Lista *pessoas, char *path)
{
    int i = 0;

    FILE *file = fopen(path, "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        char *nome = strtok(linha, ";");

        Pessoa *pessoa = buscarLista(pessoas, nome);
        int qtdPlaylists = atoi(strtok(NULL, ";"));

        for (int i = 0; i < qtdPlaylists; i++)
        {
            char *nomePlaylist = strtok(NULL, ";");

            if (nomePlaylist)
            {
                removerQuebraLinha(nomePlaylist);
            }
            Playlist *playlist = novaPlaylist(nomePlaylist, 1);

            adicionarPlaylist(pessoa, playlist);
        }
    }

    fclose(file);
}

void manipularDados(Lista *pessoas)
{
    int i = 0;
    Pessoa * pessoa;
    
    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        criarPlaylistsPorAutoria(pessoa);
        //analisar similaridades

        i++;
    }
}

void criarPlaylistsPorAutoria(Pessoa *pessoa)
{
    int j = 0;
    Playlist *playlist;
    Lista *playlistsRefatoradas = novaListaPlaylist();

    // printf("\n---------------\n");
    // printf("%s\n", pessoa->nome);
    // printf("---------------");


    while (playlist = getConteudoByPosicao(pessoa->playlists, j))
    {
        int k = 0;
        Celula *celula;
        Lista *musicas = getMusicas(playlist);

        //printf("\n%s\n", getNomePlaylist(playlist));

        while (celula = getCelula(musicas, 0))
        {
            //printf("  %d - ", k);

            Musica *musica = getConteudoByCelula(celula);
            //printf("%s - %s\n", getAutorMusica(musica), getNomeMusica(musica));

            char *autorMusica = getAutorMusica(musica);

            Playlist *playlistAutor = buscarLista(playlistsRefatoradas, autorMusica);
            if (playlistAutor)
            {
                moverLista(musicas, getMusicas(playlistAutor), celula);
            }
            else
            {
                playlistAutor = novaPlaylist(autorMusica, 0);
                adicionarLista(playlistsRefatoradas, playlistAutor);

                moverLista(musicas, getMusicas(playlistAutor), celula);
            }

            k++;
        }

        j++;
    }

    destruirLista(pessoa->playlists);
    pessoa->playlists = playlistsRefatoradas;
}
