
#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free, exit, NULL
#include <string.h> 

/* FUN��ES DE MANIPULA��O DE PFILA

Fila* CriaFila()  CRIA A FILA

int VaziaFila (Fila* f) VERIFICA SE A FILA EST� VAZIA RETORNA 1 QUANDO EST� VAZIA

void InsereFila (Fila* f, int v) INSER��O

int RetiraFila (Fila* f) REMO��O

Fila* liberaFila (Fila* f) LIBERA A FILA

void imprimeFila (Fila* f)IMPRIME A FILA
*/

//---------------------------------------------------------------
//Definindo o tipo pet

typedef struct {
    int id;                         // 100..999, único
    char nome[50];
    char especie[30];
    int idade;
    struct { int dia, mes, ano; } nascimento;
    int prioridade;                 // 0 = emergência, 1 = normal
    int atendido;                   // 0 = não, 1 = sim
} Pet;

//---------------------------------------------------------------
//Funções novas para manipulação de Pets
//---------------------------------------------------------------

// Função para criar um Pet padrão PARA TESTES
/*
Pet criaPet(int id, const char* nome, const char* especie, int idade) {
    Pet p;
    p.id = id;
    strcpy(p.nome, nome);
    strcpy(p.especie, especie);
    p.idade = 0;
    p.nascimento.dia = 1;
    p.nascimento.mes = 1;
    p.nascimento.ano = 2020;
    p.prioridade = 1;
    p.atendido = 0;
    return p;
} */
//----------------------------------------------------------------


typedef struct nos
{
    Pet info;  // Agora um no guarda um tipo pet
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

Nos* ins_fim (Nos *fim, Pet A) //retorna um ponteiro para o novo nó inserido no final. por exemplo:    f->fim = ins_fim(f->fim, 20);
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

void InsereFila (Fila* f, Pet v)
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

Pet RetiraFila (Fila* f)
{
    Pet v;
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
//---------------------------------------------------------
//Função para imprimir os pets na fila 
//---------------------------------------------------------
void imprimeFila(Fila* f) {
    Nos* q;
    printf("\n");
    printf("%-5s | %-15s | %-15s | %-5s | %-15s | %s\n",
           "ID", "Nome", "Especie", "Idade","Prioridade", "Data de nascimento");
    printf("---------------------------------------------------------------\n");

    for (q = f->ini; q != NULL; q = q->prox) {
        printf("%-5d | %-15s | %-15s | %-5d | %-15s | %02d/%02d/%04d \n", // <-- Alteração aqui
               q->info.id,
               q->info.nome,
               q->info.especie,
               q->info.idade,
               (q->info.prioridade == 0 ? "Emergencial(0)" : "Normal(1)"),
               q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano
        );
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
