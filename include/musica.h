#ifndef MUSICA_H
#define MUSICA_H

#include "lista.h"

typedef struct musica Musica;

/**
*@brief obtem o nome do autor da música
* @param musica struct de musica
* @return string com o nome do autor da musica
*/
char *getAutorMusica(Musica *musica);

/**
*@brief obtem o nome da música
* @param musica struct de musica
* @return string com o nome da musica
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
*@brief cria uma lista de struct de Musica
* @return Retorna o ponteiro de uma Lista vazia de músicas
*/
Lista  *novaListaMusica(); 

/**
*@brief Função para comparar se duas musicas sao iguais. 
* @param musica1 musica a ser comparada
* @param musica2 musica a ser comparada
* @param resultado 0 se eh igual | qualquer outro numero, indica que não
*/
void buscarMusica(Musica *musica1, Musica *musica2, int *resultado);

#endif