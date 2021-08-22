#ifndef PLAYLIST_H
#define PLAYLIST_H


#include "lista.h"
#include "musica.h"
typedef struct playlist Playlist;


// ----

/**
*@brief Retorna o nome da playlist
* @param playlist ponteiro de Struct de playlist 
* @return string com o nome da playlist
*/
char *getNomePlaylist(Playlist *playlist);

/**
*@brief Cria uma nova playlist 
* @param nome string com o nome da playlist
* @param lerMusicasArquivo Se 0, 
* @return Ponteiro de struct de música
*/

// Nao entendi direito essa funcao ainda dps eu faço
Playlist *novaPlaylist(char *nome, int lerMusicasArquivo);


/**
*@brief Cria uma nova lista de Playlists
* @return Ponteiro de struct de Lista de Playlist
*/
Lista *novaListaPlaylist();



/**
*@brief Imprime o nome da playlist e de suas músicas
* @param playlist Ponteiro de struct de Playlist
*/
void imprimirPlaylist(Playlist *playlist); 

/**
*@brief Cria uma nova playlist 
* @param nome string com o nome da playlist
* @param lerMusicasArquivo Se 0, 
* @return Ponteiro de struct de música
*/
void destruirPlaylist(Playlist *playlist);

/**
*@brief Função para buscar uma playlist pelo nome. Se o nome corresponder ao nome da playlist, o valor de resultado será 0, se não, o valor será 1 
* @param nome string com o nome da playlist a ser buscada
* @param playlist playlist que sera verificada 
* @param resultado ponteiro de inteirop que será usado como o verificador do resultado da busca 
*/
void buscarPlaylist(Playlist *playlist, char *nome, int *resultado); 

/**
*@brief Adiciona a música à uma plaulist especificada
* @param playlist ponteiro de struct da playlist que será incrementada
* @param musica ponteiro de struct da música que será adicionada à playlist 
*/
void adicionarMusica(Playlist *playlist, Musica *musica);

/**
*@brief Retorna uma lista de músicas da playlist especificada 
* @param playlist ponteiro de struct de playlist que será lida
* @return ponteiro de Lista de músicas
*/
Lista *getMusicas(Playlist * playlist); 



/**
*@brief Lê a lista de músicas que se encontra dentro do diretório data/Entrada no arquivo que estiver com o nome da playlist especificada 
* @param playlist ponteiro de struct de playlist que será lida
*/
void lerMusicas(Playlist *playlist);

#endif