#include "playlist.h"
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




Lista *getMusicas(Playlist *playlist)
{
    return playlist->musicas;
}

Playlist *novaPlaylist(char *nome, int lerMusicasArquivo)
{
    Playlist *playlist = (Playlist *)malloc(sizeof(Playlist));
    playlist->nome = strdup(nome);

    playlist->musicas = novaListaMusica();

    if (lerMusicasArquivo)
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

    if (playlist->musicas)
        imprimirLista(playlist->musicas);

    printf("\n");
}

void buscarPlaylist(Playlist *playlist, char *nome, int *resultado)
{
    *resultado = strcmp(playlist->nome, nome);
}

void adicionarMusica(Playlist *playlist, Musica *musica)
{
    adicionarLista(playlist->musicas, musica);
}

// ----------------------------

void lerMusicas(Playlist *playlist)
{
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

        removerQuebraLinha(nome);


        Musica *musica = novaMusica(autor, nome);
        adicionarMusica(playlist, musica);
    }
    fclose(file);
}