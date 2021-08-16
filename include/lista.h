#include <stdio.h>
#include <stdlib.h>

typedef struct lista Lista;

typedef struct celula Celula;

typedef void (*freeData)(void *);

typedef void (*printData)(void *);

typedef void (*searchData)(void *, void *, int *);

/**
*@brief cria uma nova lista genérica
* @param tamConteudo tamanho em bites do conteúdo de cada elemento da lista
* @param freeFunc funcao de free da struct 
* @param printFunc funcao de printar a struct
* @return Uma lista vazia do conteudo a ser listado
*/
Lista *novaLista(int tamConteudo, freeData freeFunc, printData printFunc, searchData searchFunc);

/**
*@brief retorna um ponteiro de void do tipo de conteudo da lista
* @param lista Lista do conteudo a ser extraido
* @param posicao posicao do conteudo na lista
* @return ponteiro de void do tipo de conteudo da lista
*/
void *getConteudoByPosicao(Lista *lista, int posicao);

void *getConteudoByCelula(Celula *celula);

void *getCelulaAnterior(Celula *celula);

void *getCelula(Lista *lista, int posicao);

/**
*@brief libera a memoria da lista e de todos os conteudos dentro dela
* @param lista Lista do conteudo
*/
void destruirLista(Lista *lista);

/**
*@brief libera a memoria da lista e de todos os conteudos dentro dela
* @param lista Lista do conteudo
*/
void *buscarLista(Lista *lista, void *conteudo);

/**
*@brief remove o primeiro elemento da lista 
* @param lista Lista do conteudo
*/
void removerPrimeiroLista(Lista *lista);

/**
*@brief Usa a funcao de imporimir o conteudo da lista
* @param lista Lista do conteudo
*/
void imprimirLista(Lista *lista);

/**
*@brief adiciona um elemento à lista
* @param lista Lista do conteudo
* @param conteudo conteudo a ser adicionado
*/
void adicionarLista(Lista *lista, void *conteudo);

/**
*@brief move o conteudo de uma lista a outra
* @param listaOrigem Lista do origem do conteudo
* @param listaDestino Lista de destino do conteudo
* @param posicao posicao do conteudo na lista de origem a ser movido
*/
void moverLista(Lista *listaOrigem, Lista *listaDestino, Celula *atual);
