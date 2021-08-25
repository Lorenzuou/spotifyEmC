#ifndef LISTA_H
#define LISTA_H

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
*@brief libera a memoria da lista e de todos os conteudos dentro dela
* @param lista Lista a ser destruida
*/
void destruirLista(Lista *lista);

/**
*@brief busca um conteudo na lista atraves de uma funcao generica de comparacao
* @param lista lista a ser percorrida para achar o conteudo
* @param conteudo objeto a ser utilizado na funcao de comparacao generica
* @return se achar, retorna o conteudo da celula da lista
*/
void *buscarLista(Lista *lista, void *conteudo);

/**
*@brief imprime no terminal a lista de acordo com a funcao generica de print
* @param lista Lista a ser impressa
*/
void imprimirLista(Lista *lista);

/**
*@brief adiciona um elemento à lista
* @param lista lista a ter o conteudo adicionado
* @param conteudo conteudo a ser adicionado
*/
void adicionarLista(Lista *lista, void *conteudo);

/**
*@brief move uma celula de uma lista para outra
* @param listaOrigem Lista do origem do conteudo
* @param listaDestino Lista de destino do conteudo
* @param atual celula da lista de origem a ser movida
*/
void moverLista(Lista *listaOrigem, Lista *listaDestino, Celula *atual);

/**
*@brief obtem um ponteiro de void do tipo de conteudo da lista a partir de uma posicao da lista
* @param lista Lista do conteudo a ser extraido
* @param posicao posicao do conteudo na lista
* @return ponteiro de void do tipo de conteudo da lista
*/
void *getConteudoByPosicao(Lista *lista, int posicao);

/**
*@brief obtem uma celula a partir de uma posicao da lista
* @param lista Lista a ter a celula obtida
* @param posicao posicao da celula na lista
* @return celula na posicao informada
*/
void *getCelula(Lista *lista, int posicao);

/**
*@brief obtem um ponteiro de void com o conteudo da celula
* @param celula celula para obter o conteudo
* @return ponteiro de void com o conteudo da celula
*/
void *getConteudoByCelula(Celula *celula);

/**
*@brief obtem um ponteiro de void com a celula anterior
* @param celula celula para obter a celula anterior
* @return ponteiro de void com a celula anterior
*/
void *getCelulaAnterior(Celula *celula);

#endif