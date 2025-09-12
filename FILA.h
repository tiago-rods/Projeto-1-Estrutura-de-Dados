#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include<stdlib.h>
#include<stdio.h>
/* FUNÇÕES DE MANIPULAÇÃO DE FILA
Fila* criaFila() CRIA A FILA
int vaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAZIA RETORNA 1 QUANDO ESTÁ VAZIA
void insereFila (Fila* f, int v) INSERE O ELEMENTO V NA FILA
int retiraFila (Fila* f) REMOVE O ELEMENTO DO INÍCIO DA FILA
Fila* clearFila (Fila* f) LIBERA A FILA
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

int vaziaFila (Fila* f)
{
    if (f->ini == NULL) return 1;
    return 0;
}

Fila* criaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* insereFim (Nos *fim, int A)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) fim->prox = p;
    return p;
}

void insereFila (Fila* f, int v)
{
    f->fim = insereFim(f->fim,v);
    if (f->ini == NULL) f->ini = f->fim;
}

Nos* retiraInicio (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

int retiraFila (Fila* f)
    {
    int v;
    if (vaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retiraInicio(f->ini);
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


Fila* clearFila (Fila* f)
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

// Elabore uma função que conte quantos números pares possui
// uma fila e retorne esta quantidade

int contaPares(Fila* f){
    int cont = 0;
    Nos* q = f->ini;
    while (q != NULL) {
        if (q->info % 2 == 0) cont++;
        q = q->prox;
    }
    return cont;
}

// Elabore uma função que apague o valor 15 de uma fila se
// ela existir

Fila* removeValor15(Fila* f){   
    if(f == NULL || f->ini == NULL) return f; // Verifica se a fila está vazia

    while(f->ini != NULL && f->ini->info == 15){
        f->ini = retiraInicio(f->ini);
    }
    // verifica se a fila ficou vazia, neste caso, fim == inicio
    if(f->ini == NULL){
        f->fim = NULL;
        return f;
    }
    // remove ocorrencias de 15 no meio da fila
    Nos* anterior = f->ini;
    Nos* q = anterior->prox;

    while(q != NULL){
        if(15 == q->info){
            anterior->prox = q->prox;
            free(q);
        }
        else{
            anterior = q;
            q = q->prox;
        }
    }
    f->fim = anterior; // atualiza o fim da fila

    return f;
}

// Elabore uma função que dado uma fila, transforme-a em duas
// filas uma com os números pares e outra com os ímpares:

void separaParesImpares(Fila* f, Fila** filaPares, Fila** filaImpares){
    *filaPares = criaFila();
    *filaImpares = criaFila();

    if(vaziaFila(f))return;

    for(Nos* q = f->ini; q != NULL; q = q->prox){
        if(q->info % 2 == 0){
            insereFila(*filaPares, q->info);
        } else {
            insereFila(*filaImpares, q->info);
        }
    }
}


// Elabore uma função que inverta uma fila
Fila *inverteFila(Fila* f){
    
    if(vaziaFila(f)){
        return f;
    }
   int elemento = retiraFila(f);

   f = inverteFila(f);

   insereFila(f, elemento);

   return f;
}


#endif // FILA_H_INCLUDED