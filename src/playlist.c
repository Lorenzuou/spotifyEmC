#include "playlist.h"
#include "pessoa.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

struct playlist
{
    char *nome;
    Lista *musicas;
};

// ----

char *getNomePlaylist(Playlist *playlist)
{
    return playlist->nome;
}

Playlist *novaPlaylist(char *nome)
{
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
    playlist->nome = strdup(nome);

    playlist->musicas = novaListaMusica();

    lerMusicas(playlist);

    return playlist;
}

Lista *novaListaPlaylist()
{
    return novaLista(sizeof(Playlist), destruirPlaylist, imprimirPlaylist, buscarPlaylist);
}

void destruirPlaylist(Playlist *playlist)
{
    free(playlist->nome);
    destruirLista(playlist->musicas);
    free(playlist);
}

void imprimirPlaylist(Playlist *playlist)
{
    printf("  PLAYLIST: %s\n", playlist->nome);
    imprimirLista(playlist->musicas);
}

void buscarPlaylist(Playlist *playlist, char *nome, int *resultado)
{
    *resultado = strcmp(playlist->nome, nome);
}

void adicionarMusica(Playlist *playlist, Musica *musica)
{
    adicionarLista(playlist->musicas, musica);
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
            Playlist *playlist = novaPlaylist(nomePlaylist);

            adicionarPlaylist(pessoa, playlist);
        }
    }

    fclose(file);
}

// ----

void lerMusicas(Playlist *playlist)
{
    // char *path = "data/Entrada/" ;
    // char *mais = malloc(sizeof(strlen(playlist->nome) + 13));

    char *fileName = getNomePlaylist(playlist);
    char path[100] = "data/Entrada/";
    strcat(path, fileName);

    FILE *file = fopen(path, "r");

    char linha[1024];

    char autor[100];
    char nome[100];

    while (fgets(linha, 1024, file))
    {
        // lendo e separando autor e música
        sscanf(linha, "%[^-] - %[^\n]", autor, nome);

        
        autor[strlen(autor) - 1] = '\0';

        Musica *musica = novaMusica(autor, nome);
        adicionarMusica(playlist, musica);
    }
}

Lista * getMusicas(Playlist * playlist){ 
    return playlist->musicas; 
}