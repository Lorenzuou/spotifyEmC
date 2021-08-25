#ifndef PESSOA_H
#define PESSOA_H

#include "lista.h"
#include "playlist.h"

typedef struct pessoa Pessoa;

/**
*@brief cria e aloca uma nova instância da struct de Pessoa
* @param nome string nome da pessoa
* @return Ponteiro de struct de pessoa
*/
Pessoa *novaPessoa(char *nome);

/**
*@brief Cria uma nova Lista de struct de pessoas
* @param freeFunction ponteiro da função de liberação de memória das instâncias da Lista
* @param printFunction ponteiro de funcao para imprimir os elemntos da Lista  
* @param searchFunction ponteiro de funcao de busca de elementos na Lista
* @return Ponteiro de struct de música
*/
Lista *novaListaPessoa(void * freeFunction,void * printFunction, void * searchFunction);

/**
*@brief Libera a memória alocada por uma struct de Pessoa
* @param pessoa ponteiro de struct de Pessoa
*/
void destruirPessoa(Pessoa *pessoa); 

/**
*@brief Imprime os dados de uma struct de pessoa
* @param pessoa ponteiro da função de struct de Pessoa
*/
void imprimirPessoa(Pessoa *pessoa);

/**
*@brief Imprime os dados de uma struct de pessoa amiga de uma pessoa
* @param pessoa ponteiro da função de struct de Pessoa
*/
void imprimirAmizade(Pessoa *pessoa);

/**
*@brief Função para verificar se a pessoa em uma lista de pessoa tem o mesmo nome enviado por parâmetro. 
* @param pessoa ponteiro da função de struct de Pessoa
* @param nome string com o nome da pessoa que será comparado
* @param resultado 0 se encontrou a pessoa | 1 se não encontrou  
*/
void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado); 

/**
*@brief Cria uma nova Lista de struct de pessoas
* @param freeFunction ponteiro da função de liberação de memória das instâncias da Lista
* @param printFunction ponteiro de funcao para imprimir os elemntos da Lista  
* @param searchFunction ponteiro de funcao de busca de elementos na Lista
* @return Ponteiro de struct de música
*/
void adicionarPlaylist(Pessoa *pessoa, Playlist *playlist);

/**
*@brief Lê todas as pessoas presentes no arquivo especificado pelo parâmetro e também a lista de amizades, alocando na lista de amizades de cada pessoa quem são seus respectivos amigos. Ao final, retorna uma Lista de Pessoas correspondente a todas as pessoas do arquivo. 
* @param path caminho do arquivo a ser lido
* @return Ponteiro de struct de música
*/
Lista *lerAmizades(char *path); 

/**
*@brief Lê o arquivo especificado no caminho em path e atribui, nas listas de playlists de cada pessoa, suas respectivas playlists. 
* @param pessoas Lista de ponteiros de struct de Pessoa
* @param path caminho do arquivo a ser lido
*/
void lerPlaylists(Lista *pessoas, char *path); 

/**
*@brief Percorre a lista de pessoas duas vezes. Primeiro para chamar a função de refatoramento das playlists criarPlaylistsPorAutoria(), e posteriormente chama a função de identificação de similaridades entre as músicas das pessoas analisarSimilaridades()
* @param pessoas Lista de ponteiros de struct de Pessoa
*/
void manipularDados(Lista *pessoas);

/**
*@brief percorre as músicas de uma pessoa e as reagrupa com base no autor. Cria, assim, pastas no diretório de Saida com o nome da pessoa e, para cada playlist, um arquivo nomeado com o nome do autor e a lista de músicas no conteúdo. 
* @param pessoa ponteiro de struct de Pessoa 
*/
void criarPlaylistsPorAutoria(Pessoa *pessoa);

/**
* @brief gera os arquivos de saida para cada pessoa
* Pré-Condição: a pasta "Saida" deve existir
* @param Pessoa pessoa a ter os arquivos de saida gerados
*/
void gerarArquivosSaidaPlaylist(Pessoa *pessoa);

/**
* @brief gera o arquivo played-refatorada.txt
* @param qtdPlaylists quantidade de playlists para a pessoa
* @param pessoa pessoa que a ser escrita no arquivo
*/
void adicionarPlaylistArquivo(int qtdPlaylists, Pessoa *pessoa);

/**
* @brief adiciona as musicas que estao na playlist de um amigo e nao estao na do outro (ponto extra)
* @param pessoa pessoa a ser analisada
*/
void mergePlaylistsPessoas(Pessoa *pessoa);

/**
* @brief analisa as similaridades musicais entre duas pessoas
* @param pessoa pessoa a ser comparada
* @param pessoa2 pessoa a ser comparada
*/
void analisarSimilaridades(Pessoa *pessoa, Pessoa *pessoa2); 

#endif