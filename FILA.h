#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

/* FUNCOES DE MANIPULACAO DE FILA

Fila* CriaFila()  CRIA A FILA
int VaziaFila (Fila* f) VERIFICA SE A FILA ESTA VAZIA RETORNA 1 QUANDO ESTA VAZIA
void InsereFila (Fila* f, int v) INSERCAO
int RetiraFila (Fila* f) REMOCAO
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
    // Verifica se o primeiro elemento é NULL, se for, retorna 1;
    if (f->ini == NULL) return 1;
    return 0;

}


Fila* CriaFila ()
{
    // Pega um endereço de memoria do tipo Fila que guarda inicio e fim como NULL;
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

/* A fila funciona da esquerda para a direita:
São 3 elementos, sendo o último, aquele que aponta para NULL
Inicio -> prox -> prox -> prox -> NULL

*/

Nos* ins_fim (Nos *fim, int A)
{
    // Pega um espaço de armazenamento e cria o No p;
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info = A;
    p->prox = NULL; // o fim é NULL
    if (fim != NULL) {/* verifica se lista nao estava vazia */
        // o ultimo elemento agora é o novo adicionado
        fim->prox = p;
    }
    return p;
}

void InsereFila (Fila* f, int v)
{
    // O novo fim é o endereço do no criado
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    // inicio e fim apontam para o mesmo elemento, pois só tem 1.
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox; // Pega o segundo elemento da pilha
    free(ini); // Remove o primeiro
    return p;
}

int RetiraFila (Fila* f)
{
    int v; // valor que sera retirado
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        return 0;
    }
    v = f->ini->info; // Pega o valor do primeiro 
    f->ini = retira_ini(f->ini); // Inicio agora é o segundo, pq o primeiro deu free()
    if (f->ini == NULL) {/* fila ficou vazia? */
    f->fim = NULL; }
    return v;
}

void imprimeFila (Fila* f)
{
    if(!VaziaFila(f)) {
    // Itera sobre um outro nó criado para n perder o valor do inicio
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox) {
        printf("%d - ",q->info);
    }
    printf("\n");
    return;
    }
    printf("Fila Vazia\n");
}

// Libera completamente a fila
Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox; // Guarda o endereço do próximo para poder virar o novo primeiro
        free(q); // libera o anterior
        q = t;
    }
    free(f); // sobraria o último, ai da free()
    return NULL;
}

// Contar quantos números pares possui uma fila e retornar esta quantidade
// Passa ini (que é o primeiro elemento)
int nPares (Fila* f) {
    int qnt = 0;
    while (f->ini != NULL) {
        if(f->ini->info % 2 == 0 ) {
            qnt++;
        }
        f->ini = f->ini->prox;
    }
    return qnt;
}

// Apagar uma informação de uma fila se ela existir
void apagaNum(Fila *f, int num) {
    Fila* aux = CriaFila();
    int valor;

    // Se o valor retirado for diferente de num, insere na outra fila
    while (!VaziaFila(f)) {
        valor = RetiraFila(f);  // retira sempre do início
        if (valor != num) {
            InsereFila(aux, valor);
        }
    }

    // Agora transfere de volta para f
    while (!VaziaFila(aux)) {
        valor = RetiraFila(aux);
        InsereFila(f, valor);
    }

    // Libera a memória da fila auxiliar, que não é mais necessária.
    liberaFila(aux);
}

// Elabore uma função que dado uma fila, transforme-a em duas filas uma com os números pares e outra com os ímpares
// Deixando de existir a fila principal
void parImpar(Fila* f, Fila* impar, Fila* par) {
    if(!VaziaFila(f)) {
        while(f->ini != NULL) {
            if (f->ini->info % 2 == 0) {
                InsereFila(par, RetiraFila(f));
            } else {
                InsereFila(impar, RetiraFila(f));
            }
        }
    }
    free(f);
}


// Poderia fazer também usando pilha: tira da pricipal dando push, depois da pop na invertida
// Se quiser manter a principal, copia os valore para um fila aux
void inverteFila(Fila* f, Fila* invertida) {
    int valor;

    while (!VaziaFila(f)) {
        valor = RetiraFila(f); // pega sempre do início

        // cria auxiliar para reposicionar
        Fila* aux = CriaFila();

        // primeiro insere o valor novo
        InsereFila(aux, valor);

        // depois passa o que já estava em invertida para o aux
        while (!VaziaFila(invertida)) {
            InsereFila(aux, RetiraFila(invertida));
        }

        // agora aux virou a invertida atualizada
        *invertida = *aux; // copia os ponteiros ini/fim
        free(aux);         // libera só a estrutura (não os nós)
    }
}

#endif // FILA_H_INCLUDED
