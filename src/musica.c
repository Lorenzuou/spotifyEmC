#include "musica.h"
#include "lista.h"
#include <string.h>
#include <stdlib.h>





struct musica{ 
    char *nome; 
    char *autor; 
}; 


Musica * novaMusica(char *nome, char * autor){ 
    Musica *musica = (Musica*)malloc(sizeof(Musica));

    musica->nome = strdup(nome); 
    musica->autor = strdup(autor); 


}

Lista *novaPlaylist()
{
    Lista *playlist;
    playlist = novaLista(sizeof(Musica), destruirMusica, imprimirMusica);

    return playlist;
}






Lista * novaPlaylist(){ 


}


void imprimirMusica(){ 


}


void destruirMusica(){ 


}