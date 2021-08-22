#include "pessoa.h"
#include "util.h"
#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pessoa
{
    char *nome;
    Lista *playlists;
    Lista *amizades;
};

Pessoa *novaPessoa(char *nome)
{
    Pessoa *pessoa = (Pessoa *)malloc(sizeof(Pessoa));

    pessoa->nome = strdup(nome);
    pessoa->amizades = novaListaPessoa(NULL, imprimirAmizade, buscarPessoa);
    pessoa->playlists = novaListaPlaylist();

    char path[100] = "data/Saida/";
    strcat(path, pessoa->nome);
    mkdir(path);

    return pessoa;
}

Lista *novaListaPessoa(void *freeFunction, void *printFunction, void *searchFunction)
{
    return novaLista(sizeof(Pessoa), freeFunction, printFunction, searchFunction);
}

void destruirPessoa(Pessoa *pessoa)
{
    free(pessoa->nome);
    destruirLista(pessoa->amizades); // Problemas em dar free nas amizades (double free) faz sentido pq essa funcao vai ser chamada para todos os usuarios do programa
    destruirLista(pessoa->playlists);

    free(pessoa);
}

void imprimirPessoa(Pessoa *pessoa)
{
    printf("PESSOA: %s\n", pessoa->nome);

    if (pessoa->amizades)
        imprimirLista(pessoa->amizades);

    if (pessoa->playlists)
        ;
    imprimirLista(pessoa->playlists);
    printf("\n");
}

void imprimirAmizade(Pessoa *pessoa)
{
    printf("  AMIGO: %s\n", pessoa->nome);
}

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado)
{
    *resultado = strcmp(pessoa->nome, nome);
}

void adicionarPlaylist(Pessoa *pessoa, Playlist *playlist)
{
    adicionarLista(pessoa->playlists, playlist);
}

Lista *lerAmizades(char *path)
{
    int i = 0;

    Lista *pessoas = novaListaPessoa(destruirPessoa, imprimirPessoa, buscarPessoa);

    FILE *file = fopen(path, "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        if (i == 0)
        {
            //cria as pessoas de acordo com a primeira linha do arquivo
            char *nome = strtok(linha, ";");
            while (nome)
            {
                Pessoa *pessoa = novaPessoa(nome);
                adicionarLista(pessoas, pessoa);

                nome = strtok(NULL, ";");

                if (nome)
                {
                    removerQuebraLinha(nome);
                }
            }
        }
        else
        {
            imprimirLista(pessoas);

            //adiciona a as amizades nas pessoas
            char *nome1 = strtok(linha, ";");
            Pessoa *pessoa1 = buscarLista(pessoas, nome1);

            char *nome2 = strtok(NULL, ";");
            removerQuebraLinha(nome2);

            Pessoa *pessoa2 = buscarLista(pessoas, nome2);

            printf("essa eh a pessoa 2:\n");
            imprimirPessoa(pessoa2);

            adicionarLista(pessoa1->amizades, pessoa2);
            adicionarLista(pessoa2->amizades, pessoa1);
        }

        i++;
    }

    fclose(file);
    return pessoas;
}

void lerPlaylists(Lista *pessoas, char *path)
{
    int i = 0;

    FILE *file = fopen(path, "r");

    char linha[1024];

    while (fgets(linha, 1024, file))
    {
        char *nome = strtok(linha, ";");

        Pessoa *pessoa = buscarLista(pessoas, nome);
        int qtdPlaylists = atoi(strtok(NULL, ";"));

        for (int i = 0; i < qtdPlaylists; i++)
        {
            char *nomePlaylist = strtok(NULL, ";");

            if (nomePlaylist)
            {
                removerQuebraLinha(nomePlaylist);
            }
            Playlist *playlist = novaPlaylist(nomePlaylist, 1);

            adicionarPlaylist(pessoa, playlist);
        }
    }

    fclose(file);
}

int qtdSimilaridades(Playlist *pl1, Playlist *pl2)
{
    int qtd = 0;
    Musica *m1;
    int i = 0;
    while (m1 = getConteudoByPosicao(pl1, i++))
    {
        Musica *m2;
        int j = 0;
        while (m2 = getConteudoByPosicao(pl2, j++))
        {
            // printf("HU3%s\n",getNomeMusica(m1));
            //         if (!strcmp(getNomeMusica(m1), getNomeMusica(m2)))
            //         {

            //             qtd++;
            //         }
        }
    }

    return qtd;
}




void analisarSimilaridades(Pessoa *pessoa, Pessoa *pessoa2)
{
    int j = 0;
    Pessoa *amigo;
    
    FILE *fp = fopen("data/Saida/similaridades.txt","a");
    
    amigo = buscarLista(pessoa->amizades, pessoa2->nome); 
  
    if(amigo){ 
        printf("NOME AMIGO %s",amigo->nome);
        Playlist *playlist;
        int k = 0;
        int similaridades = 0;
        while (playlist = getConteudoByPosicao(pessoa->playlists, k++))
        {
            Playlist *playlistAmigo = buscarLista(amigo->playlists, getNomePlaylist(playlist));
            if (playlistAmigo)
            {

            

                Musica *musica;
                int m = 0;
                while (musica = getConteudoByPosicao(getMusicas(playlist), m++))
                {
                  
                    Musica *musicaAmigo = buscarLista(getMusicas(playlistAmigo), musica);

                    if (musicaAmigo)
                    {
                        // printf("Comparacao %i \n", );
                        similaridades++;
                
                    }
                }
                //printf("\n------------------------\n\n");
                
            }

        }
        fprintf(fp,"%s;%s;%i",pessoa->nome,amigo->nome,similaridades); 

      
        }
    
}

void manipularDados(Lista *pessoas)
{
    int i = 0;
    Pessoa *pessoa;

    FILE *inicioPlayedRefatorada = fopen("data/Saida/played-refatorada.txt", "w"); // necessário para limpar o conteúdo que estiver dentro de played-refatorada.txt
    fclose(inicioPlayedRefatorada);

    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
      
        criarPlaylistsPorAutoria(pessoa);

        i++;
    }

    i = 0;
    FILE *fp = fopen("data/Saida/similaridades.txt","w");
    fclose(fp);
    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        Pessoa *amigo; 
        int j = i;
        while( amigo = getConteudoByPosicao(pessoas,++j)){ 
            
            analisarSimilaridades(pessoa,amigo);
            
        }


        i++;
    }
}

void adicionarPlaylistArquivo(int qtdPlaylists, Pessoa *pessoa)
{
    FILE *fp = fopen("data/Saida/played-refatorada.txt", "a");

    fprintf(fp, "%s,%i", pessoa->nome, qtdPlaylists);
    Playlist *playlist;
    int i = 0;
    while (playlist = getConteudoByPosicao(pessoa->playlists, i))
    {

        char nomeArquivo[100]; 
        strcpy(nomeArquivo , getNomePlaylist(playlist));
        strcat(nomeArquivo,".txt"); 
        fprintf(fp, ",%s", nomeArquivo);

        i++;
    }
    fprintf(fp, "\n");
    fclose(fp);
}

void criarPlaylistsPorAutoria(Pessoa *pessoa)
{
    int j = 0;
    Playlist *playlist;
    Lista *playlistsRefatoradas = novaListaPlaylist();

    FILE *refatorada = fopen("data/Saida", "w");

    int qtdPlaylists = 0;
    while (playlist = getConteudoByPosicao(pessoa->playlists, j))
    {
        int k = 0;

        Celula *celula;
        Lista *musicas = getMusicas(playlist);

        while (celula = getCelula(musicas, 0))
        {

            Musica *musica = getConteudoByCelula(celula);

            char *autorMusica = getAutorMusica(musica);

            Playlist *playlistAutor = buscarLista(playlistsRefatoradas, autorMusica);

            char path[100] = "data/Saida/";
            strcat(path, pessoa->nome);
            strcat(path, "/");
            strcat(path, autorMusica);
            strcat(path, ".txt");

            if (playlistAutor) //Se a playlist com o nome do autor existe
            {
                moverLista(musicas, getMusicas(playlistAutor), celula);
            }
            else // Se não existe, cria uma nova playlist com o nome do autor
            {
                playlistAutor = novaPlaylist(autorMusica, 0);
                FILE *fp = fopen(path, "w");
                fclose(fp);
                adicionarLista(playlistsRefatoradas, playlistAutor);
                moverLista(musicas, getMusicas(playlistAutor), celula);
                qtdPlaylists++;
            }

            FILE *fp = fopen(path, "a");
            fprintf(fp, "%s - %s\n", autorMusica, getNomeMusica(musica));
            fclose(fp);

            k++;
        }
        j++;
    }

    destruirLista(pessoa->playlists);
    pessoa->playlists = playlistsRefatoradas;
    adicionarPlaylistArquivo(qtdPlaylists, pessoa);
}
