#include "avl.h"
#include <string.h>

/*Função que devolve o maior entre dois números inteiros!*/
int maior (int esq, int dir) {
   return (esq > dir ? esq : dir);
}

/*----------------------*/
//Apenas retorna a altura daquele nó (como um getAltura)
int altura (Arvore* a) {
   if(a==NULL)
      return -1;

   return a->altura;  	
}

//Usado para recalcular a altura após remoções e inserções
int atualizar_altura (Arvore *a) {
   //Retorna a maior altura entre a subárvore da direita e a da esquerda, somada a 1
   //(por conta do hop do nó atual)
   return (maior(altura(a->esq), altura(a->dir)) + 1);
}

/*----------------------*/
int balanceamento (Arvore *a) {
   return (altura(a->dir) - altura(a->esq));
}

/* OBSERVAÇÃO: não usar a função altura estava me prejudicando muito aqui pois ela torna o resultado
 * automático e faz com que não precise checar ponteiro nulo o tempo todo. */

/*----------------------*/
Arvore* rotacao_simples_esq (Arvore* a) {
   No* t;

   t = a->dir; //atualiza para a nova raiz (o filho da direita, uma vez que a direita esta desbalanceada)
   a->dir = t->esq; //a antiga raiz recebe a sua direita o filho da esquerda da nova raiz
   t->esq = a; //a raiz antiga se torna filha a esquerda da raiz nova
   a->altura = atualizar_altura(a);
   t->altura = atualizar_altura(t);

   return t; 
}

/* OBSERVAÇÃO 2: atualizar a altura da nova raiz (t) antes da antiga (a) faz com que o código funcione
 * erroneamente, pois a altura de t depende da altura de a... ou seja:
 * calcular a altura de t usando a altura desatualizada de a gerava um erro, o que fazia com que esse
 * erro se perpetuasse nos calculos do fator de balanceamento que depende da altura e, consequentemente,
 * gerava erros nas rotações (clown_face_emoji)*/

/*----------------------*/
Arvore* rotacao_simples_dir (Arvore* a) {
 
   No* t;

   t = a->esq; //atualiza para a nova raiz (que é o filho da esquerda)
   a->esq = t->dir; //a raiz antiga recebe na sua esquerda o filho da direita da raiz nova 
   t->dir = a; //a raiz antiga se torna a filha da direita da raiz nova
   a->altura = atualizar_altura(a);
   t->altura = atualizar_altura(t);

   return t;
}

/*----------------------*/
Arvore* rotacao_dupla_esq (Arvore* a) {
   a->dir = rotacao_simples_dir(a->dir); //rotação do filho a direita (pois eh o lado desbalanceado)

   return rotacao_simples_esq(a); //retorna a rotação do pai
}

/*----------------------*/
Arvore* rotacao_dupla_dir (Arvore* a) {
   a->esq = rotacao_simples_esq(a->esq);

   return rotacao_simples_dir(a);
}

/*----------------------*/
//Calcula os fbs da direita e ai realiza as rotações conforme necessario (se houver desbalanceamentos)
Arvore* atualizar_fb_dir (Arvore *a) {

   a->altura = atualizar_altura(a);

   if(balanceamento(a) == 2) //pois eh a direita
   {
      if(balanceamento(a->dir) >= 0) //se o sinal do filho for oposto
         a = rotacao_simples_esq(a); //chama rotação dupla a esquerda
      else
         a = rotacao_dupla_esq(a); //se for sinal igual, chama rotação simples
   }

   return a;
}

/*----------------------*/
Arvore* atualizar_fb_esq (Arvore *a) {
   a->altura = atualizar_altura(a);
   
   if(balanceamento(a) == -2)
   {
      if(balanceamento(a->esq) <= 0)
         a = rotacao_simples_dir(a);
      else
         a = rotacao_dupla_dir(a);
   }

   return a;
}

/*----------------------*/ 
//comentado p/ resolução do ex 3
// Arvore* inserir (Arvore *a, char chave) {
//    if(a == NULL)
//    {
//       a = (No*)malloc(sizeof(No));
//       a->chave = chave;
//       a->altura = 0;
//       a->dir = NULL;
//       a->esq = NULL;
//    }
//    else
//    {
//       //printf("socorro inserir else\n");

//       if(chave > a->chave)
//       {
//          a->dir = inserir(a->dir, chave);
         
//          //Depois que sai da recursão, assume-se que a inserção foi feita, portanto é necessário
//          //recalcular o fator de balanceamento (e, em uma cadeia, realizar as rotações necessárias
//          //caso haja desbalanceamento)
//          a = atualizar_fb_dir(a); 
//       }
//       else if(chave < a->chave)
//       {
//          a->esq = inserir(a->esq, chave);
//          a = atualizar_fb_esq(a); 
//       }
//    }

//    //printf("socorro inserir\n");


//    return a;
// }

Arvore* inserir_str (Arvore *a, char* chave) {
   if(a == NULL)
   {
      a = (No*)malloc(sizeof(No));
      strcpy(a->chave, chave);
      a->altura = 0;
      a->dir = NULL;
      a->esq = NULL;

      return a;
   }
   else
   {
      if(strcmp(chave, a->chave) < 0)
         {
            a->esq = inserir_str(a->esq, chave);
            return atualizar_fb_esq(a); 
         }
         else if(strcmp(chave, a->chave) > 0)
         {
            a->dir = inserir_str(a->dir, chave);
            return atualizar_fb_dir(a); 
         }
   }
}

/*Função para remover um nó de uma árvore binária de busca balanceada!*/
//comentado p/ resolução do ex 3
// Arvore* remover (Arvore *a, char chave) {
//    if (a == NULL) {
//       return NULL;
//    }
//    else {
//       if (chave < a->chave) {
//          a->esq = remover (a->esq, chave);
//          a = atualizar_fb_dir (a);
//       }
//       else if (chave > a->chave) {
//          a->dir = remover (a->dir, chave);
//          a = atualizar_fb_esq (a);
//       }
//       else {
//          if ((a->esq == NULL) && (a->dir == NULL)) {
//             free (a);
//             a = NULL;
//          }
//          else if (a->esq == NULL) {
//             No *tmp = a;
//             a = a->dir;
//             free (tmp);
//          }
//          else if (a->dir == NULL) {
//             No *tmp = a;
//             a = a->esq;
//             free (tmp);
//          }
//          else {
//             No *tmp = a->esq;
//             while (tmp->dir != NULL) {
//                tmp = tmp->dir;
//             }
//             a->chave = tmp->chave; 
//             tmp->chave = chave;
//             a->esq = remover (a->esq, chave); 
//             a = atualizar_fb_dir (a);
//          }
//       }
      
//       return a; 
//    }   
// }

/*Função para imprimir os nós de uma árvore binária de acordo com um percurso in-ordem!*/
void imprimir_in_order (Arvore* a, int nivel) {
   if (a != NULL) {
      int i;
      for (i = 0; i < nivel; i++) {
         printf("      ");
      }
      printf("Chave: %s (altura: %d, fb: %+d) no nível: %d\n", a->chave, a->altura, balanceamento(a), nivel);
      imprimir_in_order (a->esq, nivel + 1);
      imprimir_in_order (a->dir, nivel + 1);
   }
}

