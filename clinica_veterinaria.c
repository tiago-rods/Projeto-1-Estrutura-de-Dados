#include <stdio.h>
#include <stdlib.h>
#include "FILA.h"

typedef struct {
    int id;                  // entre 100 e 999 (único)
    char nome[50];
    char especie[30];
    int idade;
    struct {
        int dia, mes, ano;
    } nascimento;
    int prioridade;          // 0 = emergência, 1 = normal
    int atendido;            // 0 = não, 1 = sim
} Pet;


// --------------------------------------------------------
// Menu
// --------------------------------------------------------
static void mostrarMenu(void) {
    printf("\n==============================================\n");
    printf("   CLÍNICA VETERINÁRIA - GERENCIAMENTO DE FILAS\n");
    printf("==============================================\n");
    printf("1) Inserir pet na fila\n");
    printf("2) Atender próximo pet\n");
    printf("3) Buscar pet por Nome/ID\n");
    printf("4) Imprimir relatório das filas\n");
    printf("5) Mostrar próximo a ser atendido\n");
    printf("6) Listar pets já atendidos\n");
    printf("7) Finalizar\n");
    printf("----------------------------------------------\n");
    printf("Escolha: ");
}

void main(){


}

