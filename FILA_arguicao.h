#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Data {
        int dia, mes, ano;
} Data;


typedef struct animal{
    int id;
    char nome[50];
    char especie[30];
    int idade;
    Data nascimento;
    int prioridade;
} Pet;


typedef struct nos {
    Pet info;
    struct nos *prox;
} Nos;

typedef struct fila
{
    Nos * inicio;
    Nos * fim;
} Fila;


int VaziaFila (Fila* f)
{
    if (f->inicio == NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL) {
        perror("Erro ao alocar memória para a fila");
        exit(EXIT_FAILURE);
    }
    f->inicio = f->fim = NULL;
    return f;
}

Nos* insereFim (Nos *fim, Pet A)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    if (p == NULL) {
        perror("Erro ao alocar memória para o nó da fila");
        exit(EXIT_FAILURE);
    }
    p->info = A;
    p->prox = NULL;
    if (fim != NULL)
    {
        fim->prox = p;
    }
    return p;

}

void InsereFila(Fila* f, Pet v)
{
    f->fim = insereFim(f->fim, v);
    if (f->inicio == NULL)
    f->inicio = f->fim;
}


Nos* retiraInicio (Nos* inicio)
{
    if (inicio == NULL) {
        p = NULL;
        return p;
    }
    Nos* p = inicio->prox;
    free(inicio);
    return p;
}

Pet RetiraFila (Fila* f)
{
    Pet p;
    if (VaziaFila(f))
    {
        printf("Fila vazia. Nao e possivel retirar Pet.\n");
        return NULL;
    }

    p = f->inicio->info;


    f->inicio = retiraInicio(f->inicio);
    if (f->inicio == NULL)
        f->fim = NULL;

    return p;
}


void imprimeFila(Fila* f) {
    if (VaziaFila(f)) {
        printf("A fila esta vazia.\n");
        return;
    }
    Nos* q;
    printf("\n");
    printf("%-5s | %-15s | %-15s | %-5s | %-15s | %-15s\n",
           "ID", "Nome", "Especie", "Idade", "Prioridade", "Nascimento");
    printf("--------------------------------------------------------------------------------\n");

    for (q = f->inicio; q != NULL; q = q->prox) {
        printf("%-5d | %-15s | %-15s | %-5d | %-15s | %02d/%02d/%04d \n",
               q->info.id,
               q->info.nome,
               q->info.especie,
               q->info.idade,
               (q->info.prioridade == 0 ? "Emergencial" : "Normal"),
               q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano
        );
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    if (f == NULL) {
        return NULL;
    }
    Nos* q = f->inicio;
    while (q != NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}


#endif
