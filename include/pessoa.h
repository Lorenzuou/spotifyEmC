#ifndef PESSOA_H
#define PESSOA_H

#include "lista.h"
#include "playlist.h"

typedef struct pessoa Pessoa;

Pessoa *novaPessoa(char *nome);

void destruirPessoa(Pessoa *pessoa); 

void imprimirPessoa(Pessoa *pessoa);

void imprimirAmizade(Pessoa *pessoa);

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado); 

void adicionarPlaylist(Pessoa *pessoa, Playlist *playlist);

Lista *lerAmizades(char *path); 

#endif