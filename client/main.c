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

    FILE *fp;
    fp = fopen("data/Entrada/amizade.txt", "r");
    if (fp == NULL)
    {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    char *texto = lerLinha(fp);

    fclose(fp);

    Lista * pessoas = lerAmizades("data/Entrada/amizade.txt");

    lerPlaylists(pessoas,"data/Entrada/playlists.txt");

    return 0;
}