#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "lista.h"

typedef struct playlist Playlist;

typedef struct musica Musica;

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

Musica *novaMusica(char *autor, char *nome); 

void imprimirMusica(Musica *musica); 

void destruirMusica(Musica *musica);

void buscarMusica(Musica *musica);

void lerMusicas(Playlist *playlist);

#endif