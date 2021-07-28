#include "pessoa.h"
#include <stdlib.h>



struct pessoa { 
    char* nome; 

}; 


Pessoa *novaPessoa(){ 
    Pessoa *pessoa = (Pessoa*)malloc(sizeof(Pessoa)); 
    char* nome;
  

    return pessoa; 
}



