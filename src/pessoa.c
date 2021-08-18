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
    pessoa->amizades = novaListaPessoa(NULL, imprimirAmizade, buscarPessoa);
    pessoa->playlists = novaListaPlaylist();

    char path[100] = "data/Saida/";
    strcat(path, pessoa->nome);
    mkdir(path);

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


int qtdSimilaridades(Playlist* pl1, Playlist* pl2){ 
    int qtd = 0; 



    return qtd;

 }

void analisarSimilaridades(Pessoa *pessoa)
{
    int j = 0;
    Pessoa *amigo;
    while (amigo = getConteudoByPosicao(pessoa->amizades, j++))
    {
        printf("%s\n", amigo->nome);
        Playlist *playlist;
        int k = 0;
        while (playlist = getConteudoByPosicao(pessoa->playlists, k++))
        {
            Playlist *playlistAmigo;
            int m = 0;

            while (playlistAmigo = getConteudoByPosicao(amigo->playlists, m++))
            {
                if(!strcmp(getNomePlaylist(playlistAmigo),getNomePlaylist(playlist))){ // se strcmp == 0, itera as musicas similares da playlist

                
                int qtd = qtdSimilaridades(playlistAmigo,playlist); 



                   
                }

            }
        }
    }
}

void manipularDados(Lista *pessoas)
{
    int i = 0;
    Pessoa *pessoa;

    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        criarPlaylistsPorAutoria(pessoa);
        //analisar similaridades

        analisarSimilaridades(pessoa);

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

    FILE *refatorada = fopen("data/Saida", "w");

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

            char path[100] = "data/Saida/";
            strcat(path, pessoa->nome);
            strcat(path, "/");
            strcat(path, autorMusica);
            strcat(path, ".txt");

            if (playlistAutor)
            {
                moverLista(musicas, getMusicas(playlistAutor), celula);
            }
            else
            {
                playlistAutor = novaPlaylist(autorMusica, 0);
                FILE *fp = fopen(path, "w");
                fclose(fp);
                adicionarLista(playlistsRefatoradas, playlistAutor);
                moverLista(musicas, getMusicas(playlistAutor), celula);
            }
            k++;
            FILE *fp = fopen(path, "a");
            fprintf(fp, "%s - %s\n", autorMusica, getNomeMusica(musica));
            fclose(fp);
        }
        j++;
    }

    destruirLista(pessoa->playlists);
    pessoa->playlists = playlistsRefatoradas;
}

void sad()
{
}