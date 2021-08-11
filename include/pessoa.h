#ifndef PESSOA_H
#define PESSOA_H
#include "lista.h"
#include "musica.h"

typedef struct pessoa Pessoa;




void destruirPessoa(Pessoa *pessoa); 

void imprimirPessoa(Pessoa *pessoa);

void imprimirAmizade(Pessoa *pessoa);

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado); 


void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado);


Lista *lerAmizades(char *path); 

void lerPlaylists(Lista * pessoas, char *path); 


#endif