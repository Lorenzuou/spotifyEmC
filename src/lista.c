#include "lista.h"
#include <string.h>
#include <stdlib.h>
struct celula
{
	void *conteudo;
	struct Celula *prox;
};

struct lista
{
	int tamConteudo;
	Celula *primeiraCelula;
	Celula *ultimaCelula;
	freeData freeFunc;
	printData printFunc;
};

Lista *novaLista(int tamConteudo, freeData freeFunc, printData printFunc)
{
	Lista *lista = malloc(sizeof(*lista));

	lista->tamConteudo = tamConteudo;
	lista->primeiraCelula = NULL;
	lista->ultimaCelula = NULL;
	lista->freeFunc = freeFunc;
	lista->printFunc = printFunc;

	return lista;
}

void destruirLista(Lista *lista)
{
	while (lista->primeiraCelula)
	{
		//printf("Destroying %d\n", mostraPrimeiro(lista));

		Celula *celula = lista->primeiraCelula;
		lista->primeiraCelula = celula->prox;

		if (lista->freeFunc)
			lista->freeFunc(celula->conteudo);

		free(celula);
	}
	free(lista);
}

void imprimirLista(Lista *lista)
{
	int i = 1;

	Celula *celula = lista->primeiraCelula;
	if (!celula)
	{
		printf("A lista está vazia!\n");
	}
	else
	{
		while (celula)
		{
			printf("%d - ", i);
			if (lista->printFunc)
				lista->printFunc(celula->conteudo);

			celula = celula->prox;
			i++;
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
void *removerItemLista(Lista *lista, int indice)
{
	int cont = 0;
	Celula *ant = NULL;
	Celula *c = lista->primeiraCelula;
	void *mat;
	while (cont != indice - 1)
	{
		ant = c;
		c = c->prox;

		cont++;
	}

	mat = c->conteudo;

	if (c == lista->primeiraCelula && c == lista->ultimaCelula)
	{
		lista->primeiraCelula = lista->ultimaCelula = NULL;
	}
	else if (c == lista->primeiraCelula)
	{
		lista->primeiraCelula = c->prox;
	}
	else if (c == lista->ultimaCelula)
	{
		lista->ultimaCelula = ant;
		lista->ultimaCelula->prox = NULL;
	}
	else
	{
		ant->prox = c->prox;
	}
	free(c);
	return (mat);
}


void moverLista(Lista *listaOrigem, Lista *listaDestino, int opcao)
{
	Celula *atual = listaOrigem->primeiraCelula;
	Celula *anterior = NULL;

	//percorrendo a lista até a posicao anterior à informada
	//ex: posicao = 5; percorre ate 4
	for (int i = 1; i < opcao; i++)
	{
		//definindo o anterior
		if (i == opcao - 1)
		{
			anterior = atual;
		}

		//definindo a celula atual
		atual = atual->prox;
	}

	//se houver celula anterior, ou seja, caso primeiro item nao seja escolhido
	if (anterior)
	{
		//atribui a proxima celula da celula atual no ponteiro de proximo celula da celula anterior
		//ex: 4-5-6 => 4-6
		anterior->prox = atual->prox;

		//tratamento para quando o ultimo da lista for escolhido
		if (!atual->prox)
		{
			listaOrigem->ultimaCelula = anterior;
		}
	}
	else
	{
		//tratamento para quando o primeiro da lista for escolhido
		listaOrigem->primeiraCelula = atual->prox;
	}

	//definindo o ponteiro da celula escolhida como NULL, pois será adicionado no final da lista de destino
	atual->prox = NULL;

	//troca o apontador da ultima celula de NULL para a celula nova
	if (listaDestino->ultimaCelula)
	{
		listaDestino->ultimaCelula->prox = atual;
	}

	// movimenta a ultima celula da lista
	listaDestino->ultimaCelula = atual;

	// movimenta a primeira celula da lista
	if (!listaDestino->primeiraCelula)
	{
		listaDestino->primeiraCelula = atual;
	}
}

void *getCelula(Lista *lista, int posicao)
{
	Celula *atual = lista->primeiraCelula;
	Celula *anterior = NULL;

	for (int i = 0; i < posicao; i++)
	{
		atual = atual->prox;
	}

	return atual ? atual->conteudo : NULL;
}