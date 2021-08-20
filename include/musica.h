#ifndef MUSICA_H
#define MUSICA_H

#include "lista.h"
typedef struct musica Musica;


/**
*@brief receber o Nome do autor da música
* @param musica struct de musica
* @return string com o nome do Autor 
*/
char *getAutorMusica(Musica *musica);


/**
*@brief receber o Nome do autor da música
* @param musica struct de musica
* @return string com o nome do Autor 
*/
char *getNomeMusica(Musica *musica);

/**
*@brief cria uma nova struct de musica
* @param autor string com o nome do autor da musica
* @param nome string nome da musica
* @return Ponteiro de struct de música
*/
Musica *novaMusica(char *autor, char *nome); 


/**
*@brief procedimento para imprimir o nome e o autor da música no terminal 
* @param musica ponteiro de struct de Musica
*/
void imprimirMusica(Musica *musica); 


/**
*@brief liberar a memória alocada pela struct de música
* @param musica ponteiro de struct de Musica
*/
void destruirMusica(Musica *musica);

/**
*@brief cria uma nova struct de musica
* @param autor string com o nome do autor da musica
* @param nome string nome da musica
* @return Ponteiro de struct de música
*/
void buscarMusica(Musica *musica1, Musica *musica2, int *resultado);

/**
*@brief cria uma nova struct de Lista de struct de Musica
* @return Retorna o ponteiro de uma Lista vazia de músicas
*/
Lista  *novaListaMusica(); 


#endif