#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FILA.h"

// tipo Pet e caracteristicas
/*
typedef struct animal{
    int id;                  // entre 100 e 999
    char nome[50];
    char especie[30];
    int idade;
    data nascimento{int dia, mes, ano;};
    int prioridade;          // 0 = emergência, 1 = normal
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
    getchar(); // consome o '\n' deixado no buffer
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
//===============================================
//Funções principais
//===============================================


//Gera um novo id que ainda nao foi utilizado
int gerarID(){
    int id = rand() % 900 + 100; // 100 a 999
    return id;
}


//Cria um novo pet
Pet criaPet(){
    Pet p;

    p.id = gerarID();

    printf("Nome: ");
    fgets(p.nome, sizeof(p.nome), stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';


    printf("Especie: ");
    fgets(p.especie, sizeof(p.especie), stdin);
    p.especie[strcspn(p.especie, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &p.idade);
    getchar(); // limpa o \n deixado no buffer

    printf("Ano de nascimento: ");
    scanf("%d", &p.nascimento.ano);
    getchar();

    printf("Mes de nascimento: ");
    scanf("%d", &p.nascimento.mes);
    getchar();

    printf("Dia de nascimento: ");
    scanf("%d", &p.nascimento.dia);
    getchar();

    printf("Tipo de prioridade (0 = Emergencia | 1 = Normal ): ");
    scanf("%d", &p.prioridade);
    getchar();

    return p;
}

//Insere um novo pet na fila

void inserirPet(Fila *f0, Fila *f1){

    //cria o pet
    Pet novoPet = criaPet();

    //insere o pet na fila
    if (novoPet.prioridade == 0){
        InsereFila(f0, novoPet); // Insere na fila emergencial
    } else{
        InsereFila(f1, novoPet); // Insere na fila normal
    }
}


/* COMANDO PARA ATENDER UM PET E RETIRÁ-LO DA FILA DE ATENDIMENTO
    - VER SE HÁ PET NA FILA DE ESPERA, SENÃO, ATENDER DA FILA NORMAL
    - PETS RETIRADOS DA FILA DE ATENDIMENTO DEVEM SER INSERIDOS NA FILA DE ATENDIDOS
*/
// f0 - Emergencia, f1 - normal
void atenderPet(Fila *atendidos, Fila *f0, Fila *f1){
    // Cria esse Pet aux para salvar as info ao retirar
    Pet aux;
    // Se a fila emergencia estiver vazia
        if (VaziaFila(f0) == 1) {
            aux = RetiraFila(f1);
            printf("Atendimento Normal Concluido\n");
            imprimePet(aux);
        } else {
            aux = RetiraFila(f0);
            printf("Atendimento de Emergencia Concluido\n");
            imprimePet(aux);
        }
        InsereFila(atendidos, aux);

}


/*void buscarPet(){

    FAZER COMANDO PARA BUSCAR UM PET POR ID OU POR NOME E CASO SEJA ENCONTRADO, IMPRIMIR SUAS INFORMAÇÕES, OU RETORNAR O OBJETO PET

}
*/

/*void imprimirAtendimento(){

    IMPRIMIR AS DUAS FILAS DE ESPERA
}
*/

/*void imprimirProximo(){

    IMPRIMIR O PRÓXIMO PET A SER ATENDIDO
}
*/

/*void imprimirAtendidos(){

    IMPRIMIR TODOS OS PETS JÁ ATENDIDOS
}
*/

int main() {

    srand(time(NULL)); // semente para o programa inteiro

 // CRIANDO FILAS

    Fila *filaEmergencia = CriaFila();
    Fila *filaNormal     = CriaFila();
    Fila *filaAtendidos  = CriaFila();
    int numEscolha;

    do {
        numEscolha = mostrarMenu();

        switch (numEscolha) {
            case 1:

                inserirPet(filaEmergencia, filaNormal);
                break;

            case 2:
                // Atender próximo
                atenderPet(filaEmergencia, filaNormal, filaAtendidos);
                imprimeFila(filaAtendidos);
                imprimeFila(filaEmergencia);
                imprimeFila(filaNormal);
                break;

            case 3:
                // Buscar por nome ou ID
                //buscarPet(filaEmergencia, filaNormal, filaAtendidos);
                break;

            case 4:
                // Imprimir relatório das filas
                //imprimeRelatorio(filaEmergencia, filaNormal);
                break;

            case 5:
                // Mostrar próximo da fila
                //mostrarProximo(filaEmergencia, filaNormal);
                break;

            case 6:
                // Listar pets já atendidos
                //imprimeFila(filaEmergencia);
                break;

            case 7:
                printf("\nFinalizando o sistema.\n");
                break;

            default:
                printf("\nDigite um numero valido!\n");
                break;
        }

    } while (numEscolha != 7);

    // Libera memoria e deixa os ponteiros null pois o libera fila retorna null
    filaEmergencia = liberaFila(filaEmergencia);
    filaNormal     = liberaFila(filaNormal);
    filaAtendidos  = liberaFila(filaAtendidos);

    return 0;
}
