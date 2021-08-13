#ifndef PLAYLIST_H
#define PLAYLIST_H


#include "lista.h"
#include "musica.h"
typedef struct playlist Playlist;


// ----

char *getNomePlaylist(Playlist *playlist);

Playlist *novaPlaylist(char *nome);

Lista *novaListaPlaylist();

void imprimirPlaylist(Playlist *playlist); 

void destruirPlaylist(Playlist *playlist);

void buscarPlaylist(Playlist *playlist);

void adicionarMusica(Playlist *playlist, Musica *musica);

void lerPlaylists(Lista *pessoas, char *path); 

// ----



void lerMusicas(Playlist *playlist);

#endif