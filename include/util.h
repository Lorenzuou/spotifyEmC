
#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include <stdlib.h>



/**
*@brief lê e retorna uma linha de um arquivo de texto especificado. A cada chamada da função, enquanto o arquivo não for fechado, ela lera uma nova linha 
* @param fp FILE aberta 
* @return string da linha lida
*/
char *lerLinha(FILE *fp); 


#endif
