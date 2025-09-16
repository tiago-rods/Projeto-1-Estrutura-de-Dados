#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

#include <stdio.h>   // printf
#include <stdlib.h>  // malloc, free, exit, NULL
#include <string.h>

//---------------------------------------------------------------
//Estruturas de dados
//---------------------------------------------------------------

typedef struct Data {
        int dia, mes, ano;
} Data;


typedef struct {
    int id;
    char nome[50];
    char especie[30];
    int idade;
    Data nascimento;
    int prioridade;          // 0 = emergência, 1 = normal
    int atendido;            // 0 = não, 1 = sim
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


//---------------------------------------------------------
//Funções para manipulação da fila
//---------------------------------------------------------


int VaziaFila (Fila* f)
{
    if (f->inicio == NULL) return 1; //A fila está vazia
    return 0; //A fila não está vazia

}


Fila* CriaFila () //o que será retornado da função será um ponteiro para uma fila
{
    Fila* f = (Fila*) malloc(sizeof(Fila));// cria um ponteiro para fila f e aloca um tamanho de memória no tamanho de uma fila
    if (f == NULL) { // Boa prática: verificar se a alocação foi bem-sucedida
        perror("Erro ao alocar memória para a fila");
        exit(EXIT_FAILURE);
    }
    f->inicio = f->fim = NULL; // a fila está sem conteúdo
    return f; //retorna a fila
}

Nos* insereFim (Nos *fim, Pet A) //retorna um ponteiro para o novo nó inserido no final.
{
    Nos *p = (Nos*)malloc(sizeof(Nos)); //cria um ponteiro para o nó, e esse ponteiro se chama p
    if (p == NULL) { // Boa prática: verificar se a alocação foi bem-sucedida
        perror("Erro ao alocar memória para o nó da fila");
        exit(EXIT_FAILURE);
    }
    p->info = A; //Insere o valor do tipo Pet no nó
    p->prox = NULL; //Como esse será o final da fila, não terá próximo
    if (fim != NULL) // Se a fila não estava vazia
    {
        fim->prox = p; // o nó apontado por fim terá sua parte prox apontando para o novo nó p
    }
    return p;

}

void InsereFila(Fila* f, Pet v)
{
    f->fim = insereFim(f->fim, v);
    if (f->inicio == NULL) /* fila antes vazia? */
    f->inicio = f->fim;
}

// Renomeado para retira_ini para consistência com a chamada em RetiraFila
Nos* retiraInicio (Nos* inicio)
{
    if (inicio == NULL) { // Evita tentar desreferenciar um ponteiro NULL
        return NULL;
    }
    Nos* p = inicio->prox;
    free(inicio);
    return p;
}

Pet RetiraFila (Fila* f)
{
    Pet v; // O Pet a ser retornado
    if (VaziaFila(f))
    {
        printf("Fila vazia. Nao e possivel retirar Pet.\n");
        exit(EXIT_FAILURE); /* aborta programa, pois não há o que retirar */
    }
    v = f->inicio->info; // Pega a informação do Pet do início da fila
    f->inicio = retiraInicio(f->inicio); // Remove o nó do início
    if (f->inicio == NULL) /* fila ficou vazia? */
    f->fim = NULL; // Se o início é NULL, o fim também deve ser
    return v;
}
//---------------------------------------------------------
//Função para imprimir os pets na fila
//---------------------------------------------------------
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
               (q->info.prioridade == 0 ? "Emergencial" : "Normal"), // Texto mais amigável
               q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano
        );
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    if (f == NULL) { // Se a fila já é NULL, não há nada para liberar
        return NULL;
    }
    Nos* q = f->inicio;
    while (q != NULL)
    {
        Nos* t = q->prox; // Guarda o próximo nó antes de liberar o atual
        free(q);
        q = t;
    }
    free(f); // Libera a estrutura Fila em si
    return NULL; // Retorna NULL para indicar que a fila foi liberada
}


#endif // FILA_H_INCLUDE