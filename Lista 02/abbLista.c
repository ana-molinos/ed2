#include "abbLista.h"
#include <stdlib.h>
#include <time.h>

// ============== FUNÇÕES DISPONIBILIZADAS PELA PROFESSORA =============== 

Arvore* cria_arv_vazia (void) {
   return NULL;
}

void arv_libera (Arvore* a) {
   if (a != NULL) {
      arv_libera (a->esq);
      arv_libera (a->dir);
      free(a);
   }
}

void pre_order (Arvore* a) {
   if (a != NULL) {
      printf("%d ", a->info);
      pre_order (a->esq);
      pre_order (a->dir);
   } 
}

// ============== SOLUÇÕES DA LISTA =============== 

//========= Q1 - inserir
Arvore* inserir (Arvore *a, int v) {
    //Se for árvore vazia, cria o nó    
    if(a == NULL)
    {
        a = (Arvore*) malloc(sizeof(Arvore));
        a->info = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(v<a->info) //Se o valor for menor que a chave, chama recursão a esq
        a->esq = inserir(a->esq, v);
    else if(v>a->info) //Se o valor for maior que a chave, chama recursão a dir
        a->dir = inserir(a->dir, v);

   return a;
}

//========= Q1 - remover
/*Casos de remoção:
 *Nó folha: apenas remove
 *Nó com apenas uma subárvore: usa um auxiliar pra armazenar a raiz, atualiza a raiz com a subárvore
 *                             existente e desaloca a antiga raiz
 *Nó com duas subárvores: encontra o valor, troca ele com o elemento mais à esquerda da subárvore à 
 *                        direita (assim garante que a raiz será atualizada corretamente com o padrão 
 *                        de menores à esquerda e maiores à direita) e depois aplica recursão para
 *                        garantir que ele será removido do restante da árvore
 */
Arvore* remover (Arvore *a, int v) {
   
   if(a!=NULL)
   {
      //Parte de busca do elemento
      if(a->info==v) //Se encontrou...
      {
         if(a->esq==NULL && a->dir==NULL) //Se o nó for folha
         {
            free(a);
            a = NULL;
         }
         else if(a->esq==NULL) //Se o nó possuir apenas a subárvore da direita
         {
            Arvore* tmp = a; //Cria um ptr auxiliar para armazenar a raiz temporariamente
            a = a->dir; //Atualiza a raiz para que receba a subárvore à direita
            free(tmp); //Desaloca a antiga raiz
            tmp = NULL; //Aterra o ptr auxiliar
         }
         else if(a->dir==NULL) //Se o nó possuir apenas a subárvore da esquerda
         {
            Arvore* tmp = a; //Cria um ptr auxiliar para armazenar a raiz temporariamente
            a = a->esq; //Atualiza a raiz para que receba a subárvore à esquerda
            free(tmp); //Desaloca a antiga raiz
            tmp = NULL; //Aterra o ptr auxiliar
         }
         else
         {
            Arvore* tmp = a->dir; //Olha para a subárvore da direita

            //Encontra o elemento mais à esquerda da subárvore da direita
            //(i.e., o menor elemento dos maiores elementos da subarvore em questão)
            while(tmp->esq!=NULL)
               tmp = tmp->esq; //andando sempre p/ esquerda

            //Troca os valores atualizando a nova raiz da subarvore
            a->info = tmp->info;
            tmp->info = v;

            //Garante a remoção do valor desejado por meio da recursão
            a->dir = remover(a->dir, v);
         }

      }
      //Se não encontrou, recursão de busca para remover na subárvore à esquerda ou à direita
      else if(v<a->info)
         {a->esq = remover(a->esq, v);}
      else if(v>a->info)
         {a->dir = remover(a->dir, v);}
   }

   return a; //Retorna a (sub)árvore atualizada
}


//========= Q1 - busca
int buscar (Arvore *a, int v) {
   
    if(a!=NULL)
    {
        //Se encontrou a informação desejada, retorna true...
        if(a->info==v)
            return 1;
        
        //Caso contrario, a informação deve estar OU na subárvore à esquerda 
        //OU na subárvore à direita, conforme magnitude do valor procurado
        if(v<a->info)
         return buscar(a->esq, v);

         if(v>a->info)
            return buscar(a->dir, v);
    }
  
  //Se não encontrar em nenhum dos nós, significa que o elemento não existe na árvore, logo, retorna
  //false
  return 0;   
}

//========= Q2 - min ===== (é o elemento mais a esquerda de toda a árvore)
int min (Arvore *a)
{
   if(a==NULL)
      return -1;

   if(a->esq!=NULL)
      return min(a->esq);
   
   return a->info;
}

//========= Q2 - max ===== (é o elemento mais a direita de toda a árvore)
int max (Arvore *a)
{
   if(a==NULL)
      return -1;

   if(a->dir!=NULL)
     return max(a->dir);
   
   return a->info;
}

//========= Q3 - imprime_decrescente ===== (percorrer a árvore na ordem DRE)
void imprime_decrescente (Arvore *a)
{
   if(a!=NULL)
   {
      imprime_decrescente(a->dir);
      printf("%d ", a->info);
      imprime_decrescente(a->esq);
   }
}

//========= Q4 - maior ramo =====
int maior_ramo (Arvore *a)
{
   if(a!=NULL)
   {
      int ramo_esq = 0, ramo_dir = 0;

      //Acumula os valores dos nós anteriores por recursão
      ramo_esq += maior_ramo(a->esq);
      ramo_dir += maior_ramo(a->dir);

      //Compara qual lado tem o maior ramo e retorna somando o valor do nó atual
      if(ramo_esq>ramo_dir)
         return ramo_esq + a->info;

      return ramo_dir + a->info;
   }

   return 0;
}

void imprime_hierarquia (Arvore* a, int n) {
   if (a != NULL) {
      
      for(int i=0; i<n*2; i++)
         printf(" ");
      
      printf("%d\n", a->info);
      imprime_hierarquia(a->esq, ++n);
      imprime_hierarquia(a->dir, n);
   } 
}

int main (int argc, char *argv[]) {

   int i;

   Arvore *a = cria_arv_vazia ();

   //inserir
   //....
    a = inserir (a, 50);
    a = inserir (a, 30);
    a = inserir (a, 90);
    a = inserir (a, 20);
    a = inserir (a, 40);
    a = inserir (a, 95);
    a = inserir (a, 10);
    a = inserir (a, 35);
    a = inserir (a, 45);
   
   printf("\n");
   pre_order (a);	
   printf("\n");

   printf("\n");
   imprime_hierarquia(a, 0);	
   printf("\n");

    buscar(a, 40) ? printf("40 estah na arvore\n") : printf("40 nao estah na arvore\n");
    buscar(a, 75) ? printf("75 estah na arvore\n") : printf("75 nao estah na arvore\n");

    printf("\nChave minima encontrada na arvore: %d\n", min(a));
    printf("\nChave maxima encontrada na arvore: %d\n", max(a));

    printf("\nElementos da arvore em ordem descrente: ");
    imprime_decrescente(a);
    printf("\n");

    printf("\nSoma dos elementos d maior ramo encontrado: %d\n", maior_ramo(a));

    printf("\n--- REMOÇÃO DO 35 ---\n");
   a = remover(a, 35);

   printf("\n");
   pre_order (a);	
   printf("\n");

   printf("\n");
   imprime_hierarquia(a, 0);	
   printf("\n");

   // ====== Q5 ====

   Arvore *arv_deg = cria_arv_vazia(),
          *arv = cria_arv_vazia();

   clock_t inicio, fim;
   double duracao;

   printf("\n---------- QUESTÃO 05: -----------\n");

   for(int i=0; i<100000; i++)
      arv_deg = inserir(arv_deg, i);

   printf("\nBuscando por 100.000 (chave inexistente) em arvore degenerada\n");
   
   inicio = clock();
   if(buscar(arv_deg, 100000))
      printf("Encontrou!\n");
   fim = clock();
   duracao = (fim - inicio)/(double) CLOCKS_PER_SEC*1000;
   printf("Tempo decorrido de busca (em milissegundos): %.5f\n", duracao);

   srand(time(NULL));
   
   for(int i=0; i<100000; i++)
      arv = inserir(arv, rand()%99999);

   //imprime_hierarquia(arv, 0);

   printf("\nBuscando por 100.000 (chave inexistente) em arvore aleatoria\n");
   
   inicio = clock();
   if(buscar(arv, 100000))
      printf("Encontrou!\n");
   fim = clock();
   duracao = (fim - inicio)/(double) CLOCKS_PER_SEC*1000;
   printf("Tempo decorrido de busca (em milissegundos): %.5f\n", duracao);

   arv_libera(a);
   arv_libera(arv_deg);
   arv_libera(arv);

   return 0;
}

