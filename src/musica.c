#include "musica.h"
#include "lista.h"

struct musica
{
    char *autor;
    char *nome;
};

char *getAutorMusica(Musica *musica)
{
    return musica->autor;
}

char *getNomeMusica(Musica *musica)
{
    return musica->nome;
}

Musica *novaMusica(char *autor, char *nome)
{
    Musica *musica = (Musica *)malloc(sizeof(Musica));

    musica->autor = strdup(autor);
    musica->nome = strdup(nome);

    return musica;
}

void imprimirMusica(Musica *musica)
{
    printf("    MUSICA: %s - %s\n", musica->autor, musica->nome);
}

void destruirMusica(Musica *musica)
{
    free(musica->autor);
    free(musica->nome);
    free(musica);
}

Lista *novaListaMusica()
{
    return novaLista(sizeof(Musica), destruirMusica, imprimirMusica, buscarMusica);
}

void buscarMusica(Musica *musica1, Musica *musica2, int *resultado)
{
    *resultado = abs(strcmp(musica1->autor, musica2->autor)) + abs(strcmp(musica1->nome, musica2->nome));
}
