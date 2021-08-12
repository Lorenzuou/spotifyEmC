#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "pessoa.h"
#include "musica.h"
#include "lista.h"

int main()
{
    //Ler o arquivo com os usuarios e a lista de amizades dos programas

    // char path[100] = "data/Entrada/amizade.txt";
    // lerAmizades(path);

    // FILE *fp;
    // fp = fopen("data/Entrada/amizade.txt", "r");
    // if (fp == NULL)
    // {
    //     perror("fopen()");
    //     return EXIT_FAILURE;
    // }
    // char *texto = lerLinha(fp);

    // fclose(fp);

    // lendo os dois primeiros arquivos  do programa.

    Lista *pessoas = lerAmizades("data/Entrada/amizade.txt");

    Lista * playlists = lerPlaylists(pessoas,"data/Entrada/playlists.txt");

    



    destruirLista(pessoas);
    //destruirLista(playlists); talvez nao precise dar free nessa lista pq as playlists sao desalocadas no free anterior



    return 0;
}