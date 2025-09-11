#include <stdio.h>
#include <stdlib.h>
#include "FILA.h"

/*
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
*/

// --------------------------------------------------------
// Menu
// --------------------------------------------------------
int mostrarMenu() {

    int escolha;
    printf("\n==============================================\n");
    printf("   CLINICA VETERINARIA - GERENCIAMENTO DE FILAS\n");
    printf("==============================================\n");
    printf("1) Inserir pet na fila\n");
    printf("2) Atender proximo pet\n");
    printf("3) Buscar pet por Nome/ID\n");
    printf("4) Imprimir relatorio das filas\n");
    printf("5) Mostrar proximo a ser atendido\n");
    printf("6) Listar pets ja atendidos\n");
    printf("7) Finalizar\n");
    printf("----------------------------------------------\n");

    printf("Escolha: ");
    fflush(stdout);   
    scanf("%d", &escolha);

    return escolha;
}



//codigo para testar o funcionamento
/*int main() {
    Fila* f = CriaFila();

    // Inserindo alguns pets
    InsereFila(f, criaPet(101, "Rex", "Cachorro", 5));
    InsereFila(f, criaPet(202, "Mimi", "Gato", 2));
    InsereFila(f, criaPet(303, "Bob", "Coelho", 4));

    printf("Fila inicial:");
    imprimeFila(f);

    // Retirando um pet e mostrando
    Pet p = RetiraFila(f);
    printf("\nPet atendido: %s (ID:%d)\n", p.nome, p.id);

    printf("\nFila após atendimento:");
    imprimeFila(f);

    f = liberaFila(f);
    return 0;
}
*/

int main(){
    int numEscolha = mostrarMenu();

    

    return 0;
}