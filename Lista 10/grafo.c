#include <stdio.h>
#include <stdlib.h>


/* ---------------- CÓDIGO DISPONIBILIZADO PELA PROFESSORA ----------------*/
/*Estrutura para um nó em uma lista encadeada: */
typedef struct NoA {
   int id;          /*Identificador armazenado no nó. */
   int peso;
   struct NoA *next; /* Próximo nó na lista encadeada. */
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   NoA **Adj; /* Lista de adjacências. */
} GrafoA;

/*Estrutura de Grafo com matriz de adjacências: */
typedef struct grafoM {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   int **Mat; /* Matrix de adjacências. */
} GrafoM;

/*Função para criar um grafo com lista de adjacências.*/
GrafoA* criar_grafo_adj (int tamanho) {
   int v;
   GrafoA *G = (GrafoA *)malloc(sizeof(GrafoA));

   G->E = 0;
   G->V = tamanho;
   G->Adj = (NoA **)malloc(tamanho * sizeof(NoA *));

   for (v = 0; v < G->V; v++) {
      NoA* no = (NoA*)malloc(sizeof(NoA));
      
      G->Adj[v] = no;
      G->Adj[v]->next = NULL;
      G->Adj[v]->id = v;
      G->Adj[v]->peso = 0;
   }
   return G;
}

/*Função para criar um grafo com matriz de adjacências.*/
GrafoM* criar_grafo_mat (int tamanho) {
   int v;
   GrafoM *G = (GrafoM *)malloc(sizeof(GrafoM));
   G->E = 0;
   G->V = tamanho;
   G->Mat = (int **)malloc(tamanho * sizeof(int *));
   for (v = 0; v < G->V; v++) {
      G->Mat[v] = (int *)malloc(tamanho * sizeof(int));
   }
   return G;
}

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo_adj (GrafoA *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Adj[v] != NULL) {
         free(G->Adj[v]);
      }
   }
   free(G->Adj);
   free(G);
}

/*Função para destruir um grafo construído com matriz de adjacências.*/
void liberar_grafo_mat (GrafoM *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Mat[v] != NULL) {
         free(G->Mat[v]);
      }
   }
   free(G->Mat);
   free(G);
}

void limparAdjMat(GrafoM* G)
{
   for(int i=0; i<G->V; i++)
   {
      for(int j=0; j<G->V; j++)
         G->Mat[i][j] = 0;
   }
}

//Insere uma adjacência à matriz.
//Parâmetros: o grafo, linha, coluna e peso da aresta (se não houver, usar 1)
void inserirAdjMat(GrafoM* G, int i, int j, int peso)
{
   G->Mat[i][j] = peso;

   (G->E)++;
}

void imprimeMatAdj(GrafoM* G)
{
   printf("    ");
   
   for(int i=0; i<G->V; i++)
      printf("%2d ", i);

   printf("\n\n");
   
   for(int i=0; i<G->V; i++)
   {
      printf("%2d  ", i);
      
      for(int j=0; j<G->V; j++)
         printf("%2d ", G->Mat[i][j]);

      printf("\n");

   }
}

void inserirAdjLista(GrafoA* G, int i, int j)
{
   NoA* no = (NoA*) malloc(sizeof(NoA));

   no->id = j;
   no->next = G->Adj[i]->next;
   G->Adj[i]->next = no;

   (G->E++);
}

void inserirAdjListaPeso(GrafoA* G, int v1, int v2, int peso)
{
   NoA* no = (NoA*) malloc(sizeof(NoA));

   no->id = v2;
   no->peso = peso;
   no->next = G->Adj[v1]->next;
   G->Adj[v1]->next = no;

   (G->E++);
}

void imprimeListaAdj(GrafoA* G)
{
   for(int v=0; v<G->V; v++)
   {
      printf("%d ->  ", v);

      NoA* no = G->Adj[v]->next;
      while(no!=NULL)
      {
         printf("%d ", no->id);
         
         if(no->peso!=0) printf("(p: %d)  ", no->peso);

         no = no->next;
      }

      printf("\n");
   }
}

int contaArestasIncidentes(GrafoM* G, int v)
{
   int cont = 0;

   for(int i=0; i<G->V; i++)
   {
      if(G->Mat[i][v] > 0)
         cont++;
   }

   return cont;
}

int contaArestasSaindo(GrafoM* G, int v)
{
   int cont = 0;

   for(int i=0; i<G->V; i++)
   {
      if(G->Mat[v][i] > 0)
         cont++;
   }

   return cont;
}

void listaVizinhos(GrafoA* G, int v)
{
   printf("Vizinhos de %d: ", v);
   
   NoA* no = G->Adj[v];

   while(no->next!=NULL)
   {
      printf("%d ", no->next->id);
      no = no->next;
   }
   printf("\n\n");
}

/* */
int main () {

   /*LISTA DE ADJACÊNCIA*/
   int Va = 6; /*Número de vértices*/

   GrafoA* Ga = criar_grafo_adj (Va);

   /*Exercício 1*/
   printf("Lista de adjacencia do grafo não direcionado - ex 1\n");

   inserirAdjLista(Ga, 0, 1);
   inserirAdjLista(Ga, 0, 2);
   inserirAdjLista(Ga, 0, 5);

   inserirAdjLista(Ga, 1, 0);
   inserirAdjLista(Ga, 1, 2);
   inserirAdjLista(Ga, 1, 3);

   inserirAdjLista(Ga, 2, 0);
   inserirAdjLista(Ga, 2, 1);
   inserirAdjLista(Ga, 2, 3);
   inserirAdjLista(Ga, 2, 4);

   inserirAdjLista(Ga, 3, 1);
   inserirAdjLista(Ga, 3, 2);
   inserirAdjLista(Ga, 3, 4);

   inserirAdjLista(Ga, 4, 2);
   inserirAdjLista(Ga, 4, 3);
   inserirAdjLista(Ga, 4, 4);

   inserirAdjLista(Ga, 5, 0);
   inserirAdjLista(Ga, 5, 4);

   imprimeListaAdj(Ga);
   printf("\n");

   liberar_grafo_adj (Ga);

   /*Exercício 2*/
   GrafoA* Ga2 = criar_grafo_adj (Va);

   printf("Lista de adjacencia do grafo direcionado - ex 2\n");

   inserirAdjLista(Ga2, 0, 5);
   inserirAdjLista(Ga2, 0, 1);

   inserirAdjLista(Ga2, 1, 3);
   inserirAdjLista(Ga2, 1, 2);

   inserirAdjLista(Ga2, 2, 4);
   inserirAdjLista(Ga2, 2, 0);

   inserirAdjLista(Ga2, 3, 2);

   inserirAdjLista(Ga2, 4, 3);

   inserirAdjLista(Ga2, 5, 4);

   imprimeListaAdj(Ga2);
   printf("\n");

   liberar_grafo_adj(Ga2);

   /*Exercício 3*/
   GrafoA* Ga3 = criar_grafo_adj (Va);

   printf("Lista de adjacencia do grafo direcionado com pesos - ex 3\n");

   inserirAdjListaPeso(Ga3, 0, 1, 1);
   inserirAdjListaPeso(Ga3, 0, 3, 5);

   inserirAdjListaPeso(Ga3, 1, 3, 8);

   inserirAdjListaPeso(Ga3, 2, 0, 5);
   inserirAdjListaPeso(Ga3, 2, 3, 4);

   inserirAdjListaPeso(Ga3, 3, 4, 3);
   inserirAdjListaPeso(Ga3, 3, 3, 6);

   inserirAdjListaPeso(Ga3, 4, 2, 7);
   inserirAdjListaPeso(Ga3, 4, 5, 9);

   inserirAdjListaPeso(Ga3, 5, 0, 2);

   imprimeListaAdj(Ga3);
   printf("\n");

   listaVizinhos(Ga3, 2);

   liberar_grafo_adj(Ga3);

   /*MATRIZ DE ADJACÊNCIA*/    
   int Vm = 6; /*Número de vértices*/

   GrafoM* Gm = criar_grafo_mat (Vm);

   /*Exercício 1*/
   printf("Matriz de adjacencia do grafo não direcionado - ex 1\n");
   limparAdjMat(Gm);

   inserirAdjMat(Gm, 0, 1, 1);
   inserirAdjMat(Gm, 0, 2, 1);
   inserirAdjMat(Gm, 0, 5, 1);

   inserirAdjMat(Gm, 1, 0, 1);
   inserirAdjMat(Gm, 1, 2, 1);
   inserirAdjMat(Gm, 1, 3, 1);

   inserirAdjMat(Gm, 2, 0, 1);
   inserirAdjMat(Gm, 2, 1, 1);
   inserirAdjMat(Gm, 2, 3, 1);
   inserirAdjMat(Gm, 2, 4, 1);

   inserirAdjMat(Gm, 3, 1, 1);
   inserirAdjMat(Gm, 3, 2, 1);
   inserirAdjMat(Gm, 3, 4, 1);

   inserirAdjMat(Gm, 4, 2, 1);
   inserirAdjMat(Gm, 4, 3, 1);
   inserirAdjMat(Gm, 4, 5, 1);

   inserirAdjMat(Gm, 5, 0, 1);
   inserirAdjMat(Gm, 5, 4, 1);

   imprimeMatAdj(Gm);
   printf("\n");

   /*Exercício 2*/
   printf("Matriz de adjacencia do grafo direcionado - ex 2\n");
   limparAdjMat(Gm);

   inserirAdjMat(Gm, 0, 1, 1);
   inserirAdjMat(Gm, 0, 5, 1);

   inserirAdjMat(Gm, 1, 2, 1);
   inserirAdjMat(Gm, 1, 3, 1);

   inserirAdjMat(Gm, 2, 0, 1);
   inserirAdjMat(Gm, 2, 4, 1);

   inserirAdjMat(Gm, 3, 2, 1);

   inserirAdjMat(Gm, 4, 3, 1);

   inserirAdjMat(Gm, 5, 4, 1);

   imprimeMatAdj(Gm);
   printf("\n");

   /*Exercício 3*/
   printf("Matriz de adjacencia do grafo direcionado com pesos - ex 3\n");
   limparAdjMat(Gm);

   inserirAdjMat(Gm, 0, 1, 1);
   inserirAdjMat(Gm, 0, 3, 5);

   inserirAdjMat(Gm, 1, 3, 8);

   inserirAdjMat(Gm, 2, 0, 5);
   inserirAdjMat(Gm, 2, 3, 4);

   inserirAdjMat(Gm, 3, 4, 3);
   inserirAdjMat(Gm, 3, 3, 6);

   inserirAdjMat(Gm, 4, 2, 7);
   inserirAdjMat(Gm, 4, 5, 9);

   inserirAdjMat(Gm, 5, 0, 2);

   imprimeMatAdj(Gm);
   printf("\n");

   printf("Numero de arestas incidentes ao vértice 3: %d\n", contaArestasIncidentes(Gm, 3));
   printf("Numero de arestas que saem do vértice 4: %d\n", contaArestasSaindo(Gm, 4));

   liberar_grafo_mat (Gm);

   return 0;
}

