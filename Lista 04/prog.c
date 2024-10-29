#include "avl.h"

int main () {

   Arvore *avl = NULL;

   /* -------------------------------------- EXERCÍCIO 1 ---------------------------------------*/ 
   // char insercao[19] = {'Q', 'Z', 'B', 'Y', 'T', 'M', 'E', 'W', 'X', 'S', 'F', 'G', 'A', 'H', 'N', 'O', 'P', 'R'};  

   // for(int i=0; i<18; i++)
   // {
   //    avl = inserir(avl, insercao[i]);
   //    printf("inseriu %c\n", insercao[i]);
   // }

   /* -------------------------------------- EXERCÍCIO 2 ---------------------------------------*/ 
   // int insercao_int[34] = {14, 5, 28, 2, 8, 18, 33, 1, 3, 6, 11, 15, 20, 30, 38, 4, 7, 10, 12, 16, 19, 21, 29, 31, 35, 39, 13, 22, 32, 34, 36, 40, 37};

   // for(int i=0; i<34; i++)
   // {
   //    avl = inserir(avl, insercao_int[i]);
   //    printf("inseriu %d\n", insercao_int[i]);
   // }

   // imprimir_in_order (avl, 0);

   // avl = remover(avl, 1);

   // printf("\n");

   /* -------------------------------------- EXERCÍCIO 3 ---------------------------------------*/ 
   char* insercao_str[] = {"Pedro", "Joaquim", "Sandra", "Daniele", "Jhony", "Bruna", "Roberto", 
                           "Ricardo", "Rafael", "Hayana", "Lorena", "Mariana", "Marina", "Roberta", 
                           "Chayene", "Edmundo"};
   
   for(int i=0; i < sizeof(insercao_str)/sizeof(insercao_str[0]); i++)
   {
      avl = inserir_str(avl, insercao_str[i]);
      printf("inseriu %s\n", insercao_str[i]);
   }

   imprimir_in_order(avl, 0);

   return 0;
}
