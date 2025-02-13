#include <stdio.h>
#include <stdlib.h>

#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define NIL -1   

/* ---------------- CÓDIGO DISPONIBILIZADO PELA PROFESSORA ----------------*/
/*Estrutura para um nó em uma lista encadeada: */
typedef struct NoA {
   int id;          /*Identificador armazenado no nó. */
   struct NoA *next; /* Próximo nó na lista encadeada. */
} NoA;

/*Estrutura de Grafo com lista de adjacências: */
typedef struct grafoA {
   int E; /* Quantidade de arestas. */
   int V; /* Quantidade de vértices. */
   NoA **Adj; /* Lista de adjacências. */
} GrafoA;

typedef struct DFS
{
   int cor;
   int descoberta; //d[v]
   int finalizacao; //f[v]
   int pai; //pi[v]
} DFS;


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

void inserirAdjLista(GrafoA* G, int v1, int v2)
{
   NoA* no = (NoA*) malloc(sizeof(NoA));

   no->id = v2;
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
         no = no->next;
      }

      printf("\n");
   }
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


/* --------------------------- RESOLUÇÃO DESENVOLVIDA --------------------------- */
void dfsVisit(GrafoA* G, DFS* V, int vertice, int* tempo)
{
   V[vertice].cor = CINZA; //Realizei uma visita, portanto o vértice recebe cor de descoberto
   (*tempo)++; //Atualiza o tempo
   V[vertice].descoberta = *tempo; //Marca o instante de descoberta do vértice atual

   //Perco os vértices adjacentes à vertice
   NoA* no = G->Adj[vertice]->next;
   while(no!=NULL)
   {
      //Se o vertice vizinho não foi visitado ainda...
      if(V[no->id].cor == BRANCO)
      {
         //...Define o vertice atual como pai desse vizinho...
         V[no->id].pai = vertice;
         
         //...Recursão para o vértice vizinho
         dfsVisit(G, V, no->id, &tempo);
      }

      no = no->next;
   }

   //Após sair do laço de repetição e da recursão, significa que houve backtracking e todos os vizinhos
   //do vértice atual foram visitados e finalizados
   V[vertice].cor = PRETO;
   V[vertice].finalizacao = *tempo;

}

void buscaProfundidade(GrafoA* G)
{
   //Aloca um vetor p/ o tipo DFS de tamanho n=qtdd de vértices do grafo   
   DFS* vetor = (DFS*)malloc(sizeof(DFS)*G->V); 

   //Inicializa as informações DFS de todos os vértices do grafo
   for(int v=0; v<G->V; v++)
   {
      vetor[v].cor = BRANCO;
      vetor[v].descoberta = NIL;
      vetor[v].finalizacao = NIL;
      vetor[v].pai = NIL;
   }

   int tempo = 0;

   for(int v=0; v<G->V; v++)
   {
      if(vetor[v].cor == BRANCO)
         dfsVisit(G, vetor, v, &tempo);
   }
}

/* */
int main () {

   int Va = 12; /*Número de vértices*/

   GrafoA* Ga = criar_grafo_adj (Va);

   inserirAdjLista(Ga, 0, 3);
   inserirAdjLista(Ga, 0, 1);

   inserirAdjLista(Ga, 1, 2);

   inserirAdjLista(Ga, 2, 5);

   inserirAdjLista(Ga, 4, 1);

   inserirAdjLista(Ga, 5, 6);
   inserirAdjLista(Ga, 5, 4);

   inserirAdjLista(Ga, 6, 4);
   inserirAdjLista(Ga, 6, 3);
   inserirAdjLista(Ga, 6, 0);

   inserirAdjLista(Ga, 7, 8);

   inserirAdjLista(Ga, 9, 10);

   inserirAdjLista(Ga, 10, 11);

   inserirAdjLista(Ga, 11, 9);

   imprimeListaAdj(Ga);
   printf("\n");

   buscaProfundidade(Ga);

   liberar_grafo_adj (Ga);

   return 0;
}

