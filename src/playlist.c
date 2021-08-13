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

struct musica
{
    char *autor;
    char *nome;
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

     playlist->musicas = novaLista(sizeof(Musica), destruirMusica, imprimirMusica, buscarMusica);

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
    //destruirLista(playlist->musicas);
}

void imprimirPlaylist(Playlist *playlist)
{
    printf("  PLAYLIST: %s\n", playlist->nome);
    imprimirLista(playlist->musicas);
}

void buscarPlaylist(Playlist *playlist)
{

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

Musica *novaMusica(char *autor, char *nome)
{
    Musica *musica = (Musica *)malloc(sizeof(Musica));

    musica->autor = strdup(autor);
    musica->nome = strdup(nome);

    return musica; 
}

void imprimirMusica(Musica *musica)
{
    printf("    MUSICA: %s - %s\n", musica->autor, musica->nome);
}

void destruirMusica(Musica *musica)
{
    free(musica->autor);
    free(musica->nome);
}

void buscarMusica(Musica *musica)
{

}

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
        Musica *musica = novaMusica(autor, nome); 
        adicionarMusica(playlist, musica);
    }   
}