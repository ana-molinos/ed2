#include <stdio.h>

int pai (int i) {
   return (i - 1)/2; 
}

int esquerda(int i) { return i*2+1;}

int direita(int i) { return i*2+2;}

//Realiza a troca entre dois elementos do vetor, util no momento de ordenação
void trocar (int V[], int a, int b) {
   int aux = V[a];
   V[a] = V[b];
   V[b] = aux;
}

void imprimir (int V[], int size) {
   int i;
   for (i = 0; i < size; i++) {
      printf("%d ", V[i]);
   }
   printf("\n");
}

void max_heapify (int V[], int size, int i) {
   int maior, dir, esq;
   
   maior = i;
   dir = direita(i);
   esq = esquerda(i);
   
   //Os ifs desencadeados são necessários para testar se a posição do nó filho calculada está dentro
   //dos limites do arranjo
   if(esq<size && V[esq]>V[maior])
      maior = esq;

   if(dir<size && V[dir]>V[maior])
      maior = dir;

   if(V[i]<V[maior])
   {
      trocar(V, i, maior);
      max_heapify(V, size, maior);
   }
}

void build_max_heap (int V[], int size) {
   for(int i=(size/2-1); i>=0; i--)
      max_heapify(V, size, i);
}

void heap_sort (int V[], int size) {
   build_max_heap(V, size); //constrói o heap max

   //Ordena
   for(int i=size-1; i>=0; i--)
   {
      trocar(V, 0, i);
      size--;
      max_heapify(V, size, 0);
   }
}

int main () {

   int i;

   int size = 10;

   int V[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
  
   printf("Vetor inicial : ");
   imprimir (V, size);

   heap_sort (V, size);

   printf("Vetor ordenado: ");
   imprimir (V, size);
  
   return 0;
}
