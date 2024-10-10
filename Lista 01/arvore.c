//========= CÓDIGO DISPONIBILIZADO PELA PROFESSORA ====
//Soluções seguem abaixo

#include "arvore.h"

Arvore* cria_arv_vazia (void) {
   return NULL;
}

Arvore* constroi_arv (char c, Arvore *e, Arvore *d) {
   Arvore *no = (Arvore*)malloc(sizeof(Arvore));
   no->info = c;
   no->esq = e;
   no->dir = d;
   return no;
}

int verifica_arv_vazia (Arvore *a) {
   return (a == NULL);
}

void arv_libera (Arvore* a) {
   if (!verifica_arv_vazia(a)) {
      arv_libera (a->esq);
      arv_libera (a->dir);
      free(a);
   }
}

//========= SOLUÇÕES DESENVOLVIDAS ====

//========= Exercício 2 - pré-ordem (RED) ====
void percorre_arv_po(Arvore *a)
{
    if(!verifica_arv_vazia(a))
    {
        printf("%c ", a->info); //visita a raiz
        percorre_arv_po(a->esq); //recursão para a esquerda
        percorre_arv_po(a->dir); //recursão para a direita
    }
}

//========= Exercício 2 - in-ordem (ERD) ====
void percorre_arv_io(Arvore *a)
{
    if(!verifica_arv_vazia(a))
    {
        percorre_arv_io(a->esq); //recursão para a esquerda
        printf("%c ", a->info); //visita a raiz
        percorre_arv_io(a->dir); //recursão para a direita
    }
}

//========= Exercício 2 - pós-ordem (EDR) ====
void percorre_arv_pso(Arvore *a)
{
    if(!verifica_arv_vazia(a))
    {
        percorre_arv_pso(a->esq); //recursão para a esquerda
        percorre_arv_pso(a->dir); //recursão para a direita
        printf("%c ", a->info); //visita a raiz
    }
}

//========= Exercício 3 - pertence ====
int pertence_arv (Arvore *a, char c)
{
    int pertence = 0;
    
    if(!verifica_arv_vazia(a))
    {
        //Busca utilizando o pré-ordem (RED)
        if(a->info == c) //visita a raiz
            return 1;
       //Poderia ter utilizado: return (pertence_arv(a->esq, c) || pertence_arv(a->dir, c));
       pertence = pertence_arv(a->esq, c); //recursão para a esquerda
        pertence = pertence_arv(a->dir, c); //recursão para a direita
    }

    return pertence;
}

//========= Exercício 4 - conta nós ====
int conta_nos (Arvore *a)
{
    int qtdd_nos = 0;

    //Percorre utilizando o pós ordem (EDR)
    if(!verifica_arv_vazia(a))
    {
        //acumula a quantidade de nós encontrados a esquerda e direita
        qtdd_nos += conta_nos(a->esq); //recursão para a esquerda
        qtdd_nos += conta_nos(a->dir); //recursão para a direita

        //se chegar até aqui, siginifica que encontrou um nó, portanto, retorna a quantidade de nós
        //que já tinha encontrado + 1 (o atual)
        return ++qtdd_nos; //visita a raiz (nesse caso, retorna a quantidade de um nó)

       //OTIMIZAÇÃO: return (conta_nos(a->esq) + conta_nos(a->dir) + 1);
       //OU SEJA, a quantidade de nos, em qualquer no que se esteja, é a 
       //quantidade de nós da subarvore a esquerda, somada a quantidade de 
       //nós da subarvore a direita e somada ao nó atual!
    }

    return qtdd_nos;
}

//========= Exercício 5 - calcula altura (altura = niveis) ====
int calcula_altura_arvore (Arvore *a)
{
    //caso base da recursão
    if(verifica_arv_vazia(a))
        return -1;

    //Percorre utilizando o pós ordem (EDR)

    int alt_esq = 0, alt_dir = 0;

    //acumula a quantidade de níveis, mas, para não contar um mesmo nível duas vezes, a contagem
    //é separada entre esquerda e direita, considerando sempre a maior altura até o momento

    alt_esq = calcula_altura_arvore(a->esq); //recursão para a esquerda
    alt_dir = calcula_altura_arvore(a->dir); //recursão para a direita

    //Visita a raiz (nesse caso, retorna o nível atual mais alto)
    if(alt_esq > alt_dir) 
        return ++alt_esq;

    return ++alt_dir;

   //OTIIZAÇÃO return (max(calcula_altura_arvore(a->esq), calcula_altura_arvore(a->dir)) + 1)
   //OU SEJA, a alturaa, em qualquer no que se esteja, é a é a maior altura entre as alturas das 
   //subárvores, somada ao hop atual!
}

//========= Exercício 6 - conta folhas (maior dificuldade...) ====
int conta_nos_folha (Arvore *a)
{
    int qtdd_folhas = 0;
    
    //caso base
    if(verifica_arv_vazia(a))
        return qtdd_folhas;
    
    if(a->dir==NULL && a->esq==NULL)
        return ++qtdd_folhas;

    qtdd_folhas += conta_nos_folha(a->esq);
    qtdd_folhas += conta_nos_folha(a->dir);

    return qtdd_folhas;

   //OTIIZAÇÃO:
   //if(a->dir==NULL && a->esq==NULL) (se for uma folha)...
   //     return 1;
   //return (conta_nos_folha(a->esq) + conta_nos_folha(a->dir));
   //OU SEJA, a quantidade de folhas, em qualquer no que se esteja (se ele não for uma folha), 
   //é a quantidade de folhas da subarvore da esquerda, somada a quantidade de folhas da 
   //subarvore da direita
}

int main (int argc, char *argv[]) {

    Arvore *a = constroi_arv ('a',
        constroi_arv('b',
        cria_arv_vazia(),
        constroi_arv('d', cria_arv_vazia(),cria_arv_vazia())
        ),
        constroi_arv('c',
        constroi_arv('e',cria_arv_vazia(),cria_arv_vazia()),
        constroi_arv('f',cria_arv_vazia(),cria_arv_vazia())
        )
    );	

    printf("pre-ordem (RED): ");
    percorre_arv_po(a);
    printf("\nin-ordem (ERD): ");
    percorre_arv_io(a);
    printf("\npos-ordem (EDR): ");
    percorre_arv_pso(a);
    printf("\n\n");

    (pertence_arv(a, 'a')) ? printf("'a' pertence a arvore!\n") : printf("'a'  não pertence a arvore!\n");
    (pertence_arv(a, 'f')) ? printf("'f' pertence a arvore!\n") : printf("'f'  não pertence a arvore!\n");
    (pertence_arv(a, 'c')) ? printf("'c' pertence a arvore!\n") : printf("'c'  não pertence a arvore!\n");
    (pertence_arv(a, 'z')) ? printf("'z' pertence a arvore!\n") : printf("'z'  não pertence a arvore!\n");

    printf("\nA quantidade de nós de a eh: %d\n", conta_nos(a));

    printf("\nA altura da arvore eh: %d\n", calcula_altura_arvore(a));

    printf("\nA quantidade de nós-folha na arvore eh: %d\n", conta_nos_folha(a));

    arv_libera (a);

    return 0;
}
