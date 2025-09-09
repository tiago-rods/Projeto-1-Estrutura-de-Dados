#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free, exit, NULL

/* FUN��ES DE MANIPULA��O DE PFILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA EST� VAZIA RETORNA 1 QUANDO EST� VAZIA

void InsereFila (Fila* f, int v) INSER��O

int RetiraFila (Fila* f) REMO��O

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f)IMPRIME A FILA
*/
typedef struct nos
{
    int info;
    struct nos *prox;
}Nos;

typedef struct fila
{
    Nos * ini;
    Nos * fim;
} Fila;

int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1; //A fila ta vazia
    return 0; //A fila nao ta vazia 

}


Fila* CriaFila () //o que sera retornado da função sera um ponteiro para um fila 
{
    Fila* f = (Fila*) malloc(sizeof(Fila));// cria um ponteiro para fila f e aloca um tamanho de memoria no tamanho de uma fila 
    //quando eu uso malloc, um ponteiro genérico é criado, e precisamos especificar para o tipo de dado que ele está apontando
    //por isso usamos (Fila*)
    f->ini = f->fim = NULL; // a fila esta sem conteudo
    return f; //retorna a fila 
}

Nos* ins_fim (Nos *fim, int A) //retorna um ponteiro para o novo nó inserido no final. por exemplo:    f->fim = ins_fim(f->fim, 20);
{
    Nos *p = (Nos*)malloc(sizeof(Nos)); //cria um ponteiro para o nó, e esse ponteiro se chama p 
    p->info = A; //Insere o valor inteiro no nó
    p->prox = NULL; //Como esse sera o final da fila, nao tera proximo
    if (fim != NULL) //fim é um ponteiro que aponta para um nó, definindo assim o nó fim. Portanto se ele for null
    //significa que ele nao esta apontando para ninguem
   {
     fim->prox = p;// o nó apontado por fim tem a parte prox, que é um ponteiro para outro nó, nesse ponteiro tera o endereço de p
   }
    return p;

}

void InsereFila (Fila* f, int v)
{
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

int RetiraFila (Fila* f)
{
    int v;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info);
    }
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}





#endif // FILA_H_INCLUDED
