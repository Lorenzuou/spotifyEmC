#include "pessoa.h"
#include "lista.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pessoa
{
    char *nome;
    int numPlaylists;
    Lista *playlists;
    Lista *amizades;
};

Pessoa *novaPessoa(char *nome)
{
    Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));

    pessoa->nome = strdup(nome);
    // pessoa->numPlaylists = numPlaylists;
    // pessoa->playlists = playlists;

    return pessoa;
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

Lista *novaListaPessoas()
{
    Lista *playlist;
    playlist = novaLista(sizeof(Pessoa), destruirPessoa, imprimirPessoa);

    return playlist;
}

void inserePessoa(Lista * lista, Pessoa *pessoa){ 
    adicionarLista(lista,pessoa); 
}

void lerAmizades(char *path)
{

    Lista *pessoas = novaListaPessoas(); 



    FILE *file = fopen(path, "r");

    char linha[1024];

    while (fgets(linha,1024,file)  )
    {

        char *nome = strtok(linha, ";");
        Pessoa *pessoa = novaPessoa(nome);
        adicionarLista(pessoas,pessoa); 
        printf("%s ", nome);

        char *token;
        while (token = strtok(NULL, ";"))
        {
            pessoa = novaPessoa(token); 
            adicionarLista(pessoas,pessoa); 
           

        }
    }

    fclose(file);
}