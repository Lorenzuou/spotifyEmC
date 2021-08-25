#include <string.h>

void removerQuebraLinha(char *nome)
{
    int size = strlen(nome);
    if (nome[size - 1] == '\n')
        nome[size - 1] = '\0';
}