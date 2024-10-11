#ifndef ABBLISTA_H
#define ABBLISTA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct arvore {
   int info;
   struct arvore *esq;
   struct arvore *dir;
} Arvore;

// ============== FUNÇÕES DISPONIBILIZADAS PELA PROFESSORA =============== 

Arvore* cria_arv_vazia (void);
void arv_libera (Arvore* a);
void pre_order (Arvore* a); 

void imprime_hierarquia (Arvore* a, int n);

// ============== SOLUÇÕES DA LISTA =============== 

Arvore* inserir (Arvore *a, int v);
Arvore* remover (Arvore *a, int v);
int buscar (Arvore *a, int v);

int min (Arvore *a);
int max (Arvore *a);

void imprime_decrescente (Arvore *a);
int maior_ramo (Arvore *a);

#endif