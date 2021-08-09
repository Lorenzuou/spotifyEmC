#include "musica.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>





struct musica{ 
    char *nome; 
    char *autor; 
}; 


struct playlist{ 
    char * nome;
    Musica *musicas; 
}; 


Musica *novaMusica(char *nome, char * autor){ 
    Musica *musica = (Musica*)malloc(sizeof(Musica));

    musica->nome = strdup(nome); 
    musica->autor = strdup(autor); 


}




void imprimirMusica(){ 


}


void destruirMusica(){ 


}

Lista *novaPlaylist()
{
    Lista *playlist;
    playlist = novaLista(sizeof(Musica), destruirMusica, imprimirMusica);

    return playlist;
}


