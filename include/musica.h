#ifndef MUSICA_H
#define MUSICA_H



typedef struct musica Musica;
typedef struct playlist Playlist;


void imprimirMusica(); 

void destruirMusica();

void buscarMusica();


char * getNomePlaylist(Playlist *nova);

Playlist *novaPlaylist(char *nome); 



#endif