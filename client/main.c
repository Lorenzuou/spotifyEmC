#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "pessoa.h"
#include "lista.h"

int main()
{
    // lendo os dois primeiros arquivos do programa.
    Lista *pessoas = lerAmizades("data/Entrada/amizade.txt");
    lerPlaylists(pessoas, "data/Entrada/playlists.txt");

    printf("\n\n\n-------------------------------\n");
    printf("-------------------------------\n");
    printf("--------LEITURA INICIAL--------\n");
    printf("-------------------------------\n");
    printf("-------------------------------\n\n\n");

    imprimirLista(pessoas);

    printf("---------------------------\n");
    printf("--------REFATORANDO--------\n");
    printf("-------------E-------------\n");
    printf("---------MESCLANDO---------\n");
    printf("---------------------------\n\n\n");

    // efetuando as manipulacoes solicitadas pelo roteiro do trabalho e imprimindo o resultado
    manipularDados(pessoas);
    imprimirLista(pessoas);

    //destruindo objetos
    destruirLista(pessoas);
    return 0;
}