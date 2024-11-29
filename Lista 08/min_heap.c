#include <stdio.h>
#include <stdlib.h>


/* --- CÓDIGO IMPLEMENTADO PELA PROFESSORA --- */
int pai (int i) {
   return (i - 1)/2;
}

int esquerda (int i) {
   return (i * 2) + 1;
}

int direita (int i) {
   return (i * 2) + 2;
}

void trocar (int *V, int a, int b) {
   int aux = V[a];
   V[a] = V[b];
   V[b] = aux;
}

void imprimir (int *V, int size) {
   int i;
   for (i = 0; i < size; i++) {
      printf("%d ", V[i]);
   }
   printf("\n");
}


/* --- RESOLUÇÃO DA LISTA DE EXERCÍCIOS --- */
void min_heapify (int *V, int size, int i) {
   int dir = direita(i);
   int esq = esquerda(i);
   int menor = i;

   if(dir<size && V[dir]<V[menor])
      menor = dir;
   
   if(esq<size && V[esq]<V[menor])
      menor = esq;

   if(menor!=i)
   {
      trocar(V, i, menor);
      min_heapify(V, size, menor);
   }
}

void build_min_heap (int *V, int size) {
   for(int i=(size/2-1); i>=0; i--)
      min_heapify(V, size, i);
}

int heap_extract_min (int *V, int *size) {
   
   int min = V[0];

   trocar(V, 0, (*size)-1);

   min_heapify(V, --(*size), 0);

   return min;
}

void heap_decrease_key (int *V, int i, int chave, int size) {
   if(chave < V[i])
   {
      V[i] = chave;

      int pai_ = pai(i);

      while(pai_>=0 && V[i]<V[pai_])
      {
         trocar(V, i, pai_);
         i = pai_;
         pai_ = pai(i);
      }
   }
}

void min_heap_insert (int *V, int chave, int *size) {
   (*size)++;

   V[(*size)-1] = __INT_MAX__;

   heap_decrease_key(V, (*size)-1, chave, *size);
}

int main () {

   int size = 10;

   //vetor inicial:  
   int v[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

   
   imprimir (v, size);

   build_min_heap (v, size);
   
   imprimir (v, size);
   
   heap_extract_min (v, &size);
   
   imprimir (v, size);
   
   //Modificando a última chave {16} para o valor {1}!
   heap_decrease_key (v, size-1, 1, size);
   
   imprimir (v, size);

   //Inserindo uma nova chave com valor {0}!
   min_heap_insert (v, 0, &size);
   
   imprimir (v, size);
   
   
   return 0;
}


