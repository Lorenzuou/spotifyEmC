#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "lista.h"
#include "musica.h"

typedef struct playlist Playlist;

/**
*@brief obtem o nome da playlist
* @param playlist ponteiro de struct de playlist 
* @return string com o nome da playlist
*/
char *getNomePlaylist(Playlist *playlist);

/**
*@brief cria uma nova playlist 
* @param nome string com o nome da playlist
* @param lerMusicasArquivo se 1, cria a playlist e adiciona as musicas a partir do nome do arquivo da playlist | se 0, cria a playlist sem ler e adicionar as musicas 
* @return Ponteiro de struct de música
*/
Playlist *novaPlaylist(char *nome, int lerMusicasArquivo);

/**
*@brief cria uma nova lista de Playlists
* @return Ponteiro de struct de Lista de Playlist
*/
Lista *novaListaPlaylist();

/**
*@brief Imprime o nome da playlist e de suas músicas
* @param playlist Ponteiro de struct de Playlist
*/
void imprimirPlaylist(Playlist *playlist); 

/**
*@brief liberar a memória alocada pela struct de playlist
* @param playlist ponteiro de struct de Playlist
*/
void destruirPlaylist(Playlist *playlist);

/**
*@brief Função para buscar uma playlist pelo nome. Se o nome corresponder ao nome da playlist, o valor de resultado será 0, se não, o valor será 1 
* @param playlist playlist que sera verificada 
* @param nome string com o nome da playlist a ser buscada
* @param resultado ponteiro de inteiro que será usado como o verificador do resultado da busca 
*/
void buscarPlaylist(Playlist *playlist, char *nome, int *resultado); 

/**
*@brief Adiciona a música à uma playlist especificada
* @param playlist ponteiro de struct da playlist que receberá a musica
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