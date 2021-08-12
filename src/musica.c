#include "musica.h"
#include "lista.h"

#include <string.h>
#include <stdlib.h>

struct musica
{
    char *nome;
    char *autor;
};

struct playlist
{
    char *nome;
    Musica *musicas;
};

Musica *novaMusica(char *nome, char *autor)
{
    Musica *musica = (Musica *)malloc(sizeof(Musica));

    musica->nome = strdup(nome);
    musica->autor = strdup(autor);
}

void imprimirMusica()
{
}

void destruirMusica()
{
}

void buscarMusica()
{
}

void destruirPlaylist(Playlist *p)
{
    free(p->nome);
    //destruirLista(p->musicas);
}
void imprimirPlaylist()
{
}

char *getNomePlaylist(Playlist *play)
{
    return play->nome;
}
Lista *novaListaPlaylists()
{

    return novaLista(sizeof(Playlist), destruirPlaylist, imprimirPlaylist, NULL);
}

void atribuirMusicas(Playlist *playlist)
{
    // char *path = "data/Entrada/" ; 
    // char *mais = malloc(sizeof(strlen(playlist->nome) + 13)); 


    char *fileName = playlist->nome;
    char path[100] = "data/Entrada/";
    strcat(path, fileName);


   
    FILE *file = fopen(path, "r");

    char linha[1024];

    char *str1; 
    char *str2; 

    while (fgets(linha, 1024, file))
    {
      // ler as musicas aqui 

    }   
}
Playlist *novaPlaylist(char *nome)
{
    Playlist *playlist;
    playlist = novaLista(sizeof(Playlist), destruirMusica, imprimirMusica, buscarMusica);
    playlist->nome = strdup(nome);
    //printf("%s",playlist->nome);

    atribuirMusicas(playlist);

    return playlist;
}