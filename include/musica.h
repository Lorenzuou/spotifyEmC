#ifndef MUSICA_H
#define MUSICA_H

#include "lista.h"
typedef struct musica Musica;

Musica *novaMusica(char *autor, char *nome); 

void imprimirMusica(Musica *musica); 

void destruirMusica(Musica *musica);

void buscarMusica(Musica *musica);

Lista  *novaListaMusica(); 


#endif