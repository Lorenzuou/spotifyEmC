#ifndef PESSOA_H
#define PESSOA_H

#include "lista.h"
#include "playlist.h"

typedef struct pessoa Pessoa;

Pessoa *novaPessoa(char *nome);

Lista *novaListaPessoa(void * freeFunction,void * printFunction, void * searchFunction);

void destruirPessoa(Pessoa *pessoa); 

void destruirAmizade(Pessoa * pessoa); 

void imprimirPessoa(Pessoa *pessoa);

void imprimirAmizade(Pessoa *pessoa);

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado); 

void adicionarPlaylist(Pessoa *pessoa, Playlist *playlist);

Lista *lerAmizades(char *path); 

void lerPlaylists(Lista *pessoas, char *path); 

void manipularDados(Lista *pessoas);

void criarPlaylistsPorAutoria(Pessoa *pessoa);

#endif