#ifndef PESSOA_H
#define PESSOA_H


typedef struct pessoa Pessoa;




void destruirPessoa(Pessoa *pessoa); 

void imprimirPessoa(Pessoa *pessoa);

void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado); 


void buscarPessoa(Pessoa *pessoa, char *nome, int *resultado);

#endif