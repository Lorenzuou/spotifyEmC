#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pessoa.h"
#include "util.h"
#include "playlist.h"

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

    //criando pasta para a guardar as playlists apos manipulacao
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
    destruirLista(pessoa->amizades);
    destruirLista(pessoa->playlists);

    free(pessoa);
}

void imprimirPessoa(Pessoa *pessoa)
{
    printf("PESSOA: %s\n", pessoa->nome);

    printf("\n");

    if (pessoa->amizades)
        imprimirLista(pessoa->amizades);

    printf("\n");

    if (pessoa->playlists)
        imprimirLista(pessoa->playlists);

    printf("------\n\n");
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

    //criando as pessoas e setando as amizades de acordo com o arquivo
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
            //adiciona as amizades nas pessoas
            char *nome1 = strtok(linha, ";");
            Pessoa *pessoa1 = buscarLista(pessoas, nome1);

            char *nome2 = strtok(NULL, ";");
            removerQuebraLinha(nome2);

            Pessoa *pessoa2 = buscarLista(pessoas, nome2);

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

    //criando as playlists e setando nas pessoas de acordo com o arquivo
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

void manipularDados(Lista *pessoas)
{
    int i = 0;
    Pessoa *pessoa;

    //necessário para limpar o conteúdo que estiver dentro de played-refatorada.txt
    FILE *inicioPlayedRefatorada = fopen("data/Saida/played-refatorada.txt", "w");
    fclose(inicioPlayedRefatorada);

    //percorrendo lista de pessoas e gerando as playlists de acordo com o nome do cantor/banda
    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        criarPlaylistsPorAutoria(pessoa);
        i++;
    }

    //necessário para limpar o conteúdo que estiver dentro de similaridades.txt
    FILE *fp = fopen("data/Saida/similaridades.txt", "w");
    fclose(fp);

    //percorrendo lista de pessoas analisando as similaridades, e adicionando as musicas que estao em uma amigo mas nao no outro (ponto extra)
    i = 0;
    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        Pessoa *amigo;
        int j = i;

        while (amigo = getConteudoByPosicao(pessoas, ++j))
        {
            analisarSimilaridades(pessoa, amigo);
        }

        mergePlaylistsPessoas(pessoa);

        i++;
    }

    i = 0;
    while (pessoa = getConteudoByPosicao(pessoas, i))
    {
        gerarArquivosSaidaPlaylist(pessoa);

        i++;
    }
}

void criarPlaylistsPorAutoria(Pessoa *pessoa)
{
    int j = 0;
    int qtdPlaylists = 0;
    Playlist *playlist;
    Lista *playlistsRefatoradas = novaListaPlaylist();

    FILE *refatorada = fopen("data/Saida", "w");

    //percorrendo as playlists da pessoa
    while (playlist = getConteudoByPosicao(pessoa->playlists, j))
    {
        int k = 0;

        Celula *celula;
        Lista *musicas = getMusicas(playlist);

        //percorrendo as musicas da playlist da pessoa
        while (celula = getCelula(musicas, 0))
        {
            Musica *musica = getConteudoByCelula(celula);

            //obtendo autor da musica
            char *autorMusica = getAutorMusica(musica);
            Playlist *playlistAutor = buscarLista(playlistsRefatoradas, autorMusica);

            //se a playlist com o nome do autor existe, move a musica para a playlist
            if (playlistAutor)
            {
                moverLista(musicas, getMusicas(playlistAutor), celula);
            }
            else //se não existe, cria uma nova playlist com o nome do autor e move a musica para a playlist
            {
                playlistAutor = novaPlaylist(autorMusica, 0);

                adicionarLista(playlistsRefatoradas, playlistAutor);
                moverLista(musicas, getMusicas(playlistAutor), celula);
                //qtdPlaylists++;
            }

            k++;
        }
        
        j++;
    }

    //destruindo as playlist antigas
    destruirLista(pessoa->playlists);

    //apontado para a nova lista de playlists
    pessoa->playlists = playlistsRefatoradas;
}

void gerarArquivosSaidaPlaylist(Pessoa *pessoa)
{
    int j = 0;
    Playlist *playlist;

    //percorrendo as playlists da pessoa
    while (playlist = getConteudoByPosicao(pessoa->playlists, j++))
    {
        Musica *musica;
        int k = 0;

        char path[100] = "data/Saida/";
        strcat(path, pessoa->nome);
        strcat(path, "/");
        strcat(path, getNomePlaylist(playlist));
        strcat(path, ".txt");

        //necessário para limpar o conteúdo que estiver dentro de similaridades.txt
        FILE *fp = fopen(path, "w");
        fclose(fp);

        //percorrendo as musicas da playlist da pessoa
        while (musica = getConteudoByPosicao(getMusicas(playlist), k++))
        {
            char *autorMusica = getAutorMusica(musica);
            char *nomeMusica = getNomeMusica(musica);

            FILE *fp = fopen(path, "a");
            fprintf(fp, "%s - %s\n", autorMusica, nomeMusica);
            fclose(fp);
        }
    }
    adicionarPlaylistArquivo(j - 1, pessoa);
}

void adicionarPlaylistArquivo(int qtdPlaylists, Pessoa *pessoa)
{
    FILE *fp = fopen("data/Saida/played-refatorada.txt", "a");

    fprintf(fp, "%s,%i", pessoa->nome, qtdPlaylists);
    Playlist *playlist;
    int i = 0;

    //percorrendo as playlists da pessoa
    while (playlist = getConteudoByPosicao(pessoa->playlists, i))
    {
        char nomeArquivo[100];
        strcpy(nomeArquivo, getNomePlaylist(playlist));
        strcat(nomeArquivo, ".txt");
        fprintf(fp, ",%s", nomeArquivo);

        i++;
    }

    fprintf(fp, "\n");
    fclose(fp);
}

void mergePlaylistsPessoas(Pessoa *pessoa)
{
    int j = 0;
    Pessoa *amigo;

    //percorrendo os amigos da pessoa
    while (amigo = getConteudoByPosicao(pessoa->amizades, j++))
    {
        Playlist *playlist;
        int k = 0;

        //percorrendo as playlists da pessoa
        while (playlist = getConteudoByPosicao(pessoa->playlists, k++))
        {
            //se encontrar uma playlist no amigo que tenha o mesmo nome da playlist da pessoa, checa as musicas
            Playlist *playlistAmigo = buscarLista(amigo->playlists, getNomePlaylist(playlist));
            if (playlistAmigo)
            {
                Musica *musica;
                int m = 0;

                //percorrendo as musicas da playlist da pessoa
                while (musica = getConteudoByPosicao(getMusicas(playlist), m++))
                {
                    //se nao encontrar a musica da pessoa no amigo, adiciona a musica na playlist do amigo
                    Musica *musicaAmigo = buscarLista(getMusicas(playlistAmigo), musica);
                    if (!musicaAmigo)
                    {
                        Musica *copiaMusica = novaMusica(getAutorMusica(musica), getNomeMusica(musica));
                        adicionarMusica(playlistAmigo, copiaMusica);
                    }
                }
            }
        }
    }
}

void analisarSimilaridades(Pessoa *pessoa, Pessoa *pessoa2)
{
    int j = 0;
    Pessoa *amigo;

    FILE *fp = fopen("data/Saida/similaridades.txt", "a");

    //verificando se as pessoas sao amigas
    amigo = buscarLista(pessoa->amizades, pessoa2->nome);
    if (amigo)
    {
        Playlist *playlist;
        int k = 0;
        int similaridades = 0;

        //se forem amigos, percorre a playlist da pessoa
        while (playlist = getConteudoByPosicao(pessoa->playlists, k++))
        {
            //se encontrar uma playlist no amigo que tenha o mesmo nome da playlist da pessoa, checa as musicas
            Playlist *playlistAmigo = buscarLista(amigo->playlists, getNomePlaylist(playlist));
            if (playlistAmigo)
            {
                Musica *musica;
                int m = 0;

                //percorrendo as musicas da playlist da pessoa
                while (musica = getConteudoByPosicao(getMusicas(playlist), m++))
                {
                    //se encontrar a musica na playlist do amigo, incrementa contador
                    Musica *musicaAmigo = buscarLista(getMusicas(playlistAmigo), musica);
                    if (musicaAmigo)
                    {
                        similaridades++;
                    }
                }
            }
        }

        //escrevendo no arquivo a quantidade de similaridades
        fprintf(fp, "%s;%s;%i", pessoa->nome, amigo->nome, similaridades);
    }
}
