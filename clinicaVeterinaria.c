
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> //para _getch, le um caractere sem precisar do ENTER
#include "FILA.h"

typedef struct {
    int id;                  // entre 100 e 999 (único)
    char nome[50];
    char especie[30];
    int idade;
    struct {
        int dia, mes, ano;
    } data;
    int prioridade;          // 0 = emergência, 1 = normal
    int atendido;            // 0 = não, 1 = sim
} Pet;


// --------------------------------------------------------
// Menu
// --------------------------------------------------------
void mostrarMenu();
int numeroAleatorio();

int main(){

    mostrarMenu();


}

void mostrarMenu() {
    printf("\n==============================================\n");
    printf("   CLÍNICA VETERINÁRIA - GERENCIAMENTO DE FILAS\n");
    printf("==============================================\n");
    printf("\t\t 1) Inserir pet na fila\n");
    printf("\t\t 2) Atender próximo pet\n");
    printf("\t\t 3) Buscar pet por Nome/ID\n");
    printf("\t\t 4) Imprimir relatório das filas\n");
    printf("\t\t 5) Mostrar próximo a ser atendido\n");
    printf("\t\t 6) Listar pets já atendidos\n");
    printf("7) Finalizar\n");
    printf("----------------------------------------------\n");
    printf("Escolha: ");
}
// ----------------------------------------------------------------

// Função para gerar um ID único entre 100 e 999
int numeroAleatorio() {
    return (rand() % 900) + 100;
}

