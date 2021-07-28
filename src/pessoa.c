#include "pessoa.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>

struct pessoa
{
    char *nome;
    int numPlaylists;
    Lista *playlists;
    Lista *amizades;
};

Pessoa *novaPessoa(char *nome, int numPlaylists, Lista *playlists)
{
    Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));

    pessoa->nome = strdup(nome);
    pessoa->numPlaylists = numPlaylists;
    pessoa->playlists = playlists;

    return pessoa;
}

Lista *novaListaPessoas()
{
    Lista *playlist;
    playlist = novaLista(sizeof(Pessoa), destruirPessoa, imprimirPessoa);

    return playlist;
}

void destruirPessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    //Fazer as funcoes de dar free nas playlists e amizades do usuario

    free(pessoa);
}

void imprimirPessoa(Pessoa *pessoa)
{
    
}
