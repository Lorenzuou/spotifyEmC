#include "lista.h"
#include <string.h>
#include <stdlib.h>

struct celula
{
	void *conteudo;
	struct Celula *ant;
	struct Celula *prox;
};

struct lista
{
	int tamConteudo;
	Celula *primeiraCelula;
	Celula *ultimaCelula;
	freeData freeFunc;
	printData printFunc;
	searchData searchFunc;
};

Lista *novaLista(int tamConteudo, freeData freeFunc, printData printFunc, searchData searchFunc)
{
	Lista *lista = malloc(sizeof(*lista));

	lista->tamConteudo = tamConteudo;
	lista->primeiraCelula = NULL;
	lista->ultimaCelula = NULL;
	lista->freeFunc = freeFunc;
	lista->printFunc = printFunc;
	lista->searchFunc = searchFunc;

	return lista;
}

void destruirLista(Lista *lista)
{
	while (lista->primeiraCelula)
	{
		Celula *celula = lista->primeiraCelula;
		lista->primeiraCelula = celula->prox;

		if (lista->freeFunc)
			lista->freeFunc(celula->conteudo);

		free(celula);
	}
	free(lista);
}

void *buscarLista(Lista *lista, void *conteudo)
{
	Celula *atual = lista->primeiraCelula;

	while (atual)
	{
		int resultado = 1;
		if (lista->searchFunc)
			lista->searchFunc(atual->conteudo, conteudo, &resultado);

		if (resultado == 0)
			break;

		atual = atual->prox;
	}

	return atual ? atual->conteudo : NULL;
}

void imprimirLista(Lista *lista)
{
	Celula *celula = lista->primeiraCelula;
	if (!celula)
	{
		printf("A lista está vazia!\n");
	}
	else
	{
		while (celula)
		{
			if (lista->printFunc)
				lista->printFunc(celula->conteudo);

			celula = celula->prox;
		}
	}
}

void adicionarLista(Lista *lista, void *conteudo)
{
	Celula *novaCelula = calloc(1, sizeof(Celula));

	novaCelula->conteudo = conteudo;

	//troca o apontador da ultima celula de NULL para a celula nova
	if (lista->ultimaCelula)
	{
		novaCelula->ant = lista->ultimaCelula;
		lista->ultimaCelula->prox = novaCelula;
	}

	// movimenta a ultima celula da lista
	lista->ultimaCelula = novaCelula;

	// movimenta a primeira celula da lista
	if (!lista->primeiraCelula)
	{
		lista->primeiraCelula = novaCelula;
	}
}

void moverLista(Lista *listaOrigem, Lista *listaDestino, Celula *atual)
{
	//se houver celula anterior, ou seja, caso primeiro item nao seja escolhido
	if (atual->ant)
	{
		//atribui a proxima celula da celula atual no ponteiro de proximo celula da celula anterior
		//ex: 4-5-6 => 4-6
		Celula *anterior = atual->ant;
		anterior->prox = atual->prox;

		//tratamento para quando o ultimo da lista for escolhido
		if (!atual->prox)
		{
			listaOrigem->ultimaCelula = atual->ant;
		}
	}
	else
	{
		//tratamento para quando o primeiro da lista for escolhido
		listaOrigem->primeiraCelula = atual->prox;

		if (listaOrigem->primeiraCelula)
			listaOrigem->primeiraCelula->ant = NULL;
	}

	//definindo o ponteiro da celula escolhida como NULL, pois será adicionado no final da lista de destino
	atual->prox = NULL;

	//troca o apontador da ultima celula de NULL para a celula nova
	if (listaDestino->ultimaCelula)
	{
		listaDestino->ultimaCelula->prox = atual;
		atual->ant = listaDestino->ultimaCelula;
	}

	// movimenta a ultima celula da lista
	listaDestino->ultimaCelula = atual;

	// movimenta a primeira celula da lista
	if (!listaDestino->primeiraCelula)
	{
		listaDestino->primeiraCelula = atual;
	}
}

void *getConteudoByPosicao(Lista *lista, int posicao)
{
	Celula *atual = lista->primeiraCelula;

	for (int i = 0; i < posicao; i++)
	{
		atual = atual->prox;
	}

	return atual ? atual->conteudo : NULL;
}

void *getCelula(Lista *lista, int posicao)
{
	Celula *atual = lista->primeiraCelula;

	for (int i = 0; i < posicao; i++)
	{
		atual = atual->prox;
	}

	return atual;
}

void *getConteudoByCelula(Celula *celula)
{
	if (celula)
		return celula->conteudo;

	return NULL;
}

void *getCelulaAnterior(Celula *celula)
{
	if (celula)
		return celula->ant;

	return NULL;
}