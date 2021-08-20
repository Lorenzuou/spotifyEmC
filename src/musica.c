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

// int string_compare(char str1[], char str2[])
// {
//     int ctr = 0;

//     while (str1[ctr] == str2[ctr])
//     {
//         // printf(" Caracter1: %c ", str1[ctr]);

//         // printf(" Caracter2: %c \n", str2[ctr]);

//         if (str1[ctr] == '\0' || str2[ctr] == '\0')
//             break;
//         ctr++;
//     }
//     if (str1[ctr] == '\0')
//     {
//         while (str2[ctr] == ' ' || str2[ctr] == '\n')
//         {
//             ctr++;
//         }
//         if (str2[ctr] == '\0')
//             return 0;
//         else
//             return 1;
//     }
//     else if (str2[ctr] == '\0')
//     {
//         while (str1[ctr] == ' ' || str1[ctr] == '\n')
//         {
//             ctr++;
//         }
//         if (str1[ctr] == '\0')
//             return 0;
//         else
//             return 1;
//     }
//     else if (str1[ctr] == ' ')
//     {
//         while( str1[ctr] == ' '){ 
//             if(str2[ctr] == ' ')
//             ctr++;
//         }
//     }

//     // if (str1[ctr] == '\0' && str2[ctr] == '\0')
//     //     while (str1)

//     //         return 0;
//     // else
//     //     return -1;
//     return 1;
// }

void buscarMusica(Musica *musica1, Musica *musica2, int *resultado)
{

    printf("%i\n", strcmp(getNomeMusica(musica1), getNomeMusica(musica2)));
    printf("%i\n", strcmp(musica2->autor, musica1->autor));
    // printf("|| M1: %s || M2: %s ||",musica1->nome,musica2->nome);
    imprimirMusica(musica2);
    imprimirMusica(musica1);
    //abs(strcmp(musica1->autor, musica2->autor)) + abs(strcmp(musica1->nome, musica2->nome));
    int opa = string_compare(getNomeMusica(musica1), getNomeMusica(musica2));
    printf("\nOPA %i ", opa);
    *resultado = string_compare(getNomeMusica(musica1), getNomeMusica(musica2));
}
