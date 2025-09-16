#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD:clinica_veterinaria.c
#include <time.h>
=======
#include <string.h>
#include <time.h>
#include <conio.h> //para _getch, le um caractere sem precisar do ENTER
>>>>>>> 91974166f806ec8b1e8fa9786b9fac5df1733398:clinicaVeterinaria.c
#include "FILA.h"
#include <string.h> 
/* ============== TODO ============== */
// - função para atender o próximo pet (retirar da fila e adicionar ao histórico)
// - Verificar o motivo de pets selecionados para irem para a fila normal irem para a fila de emergência
// -
// -
// -
// -
// -
/* ============== TODO ============== */

<<<<<<< HEAD:clinica_veterinaria.c
//* ============== DONE ============== */
// -
// -
// -
// -
// -
// -
// -
// -
//* ============== DONE ============== */


int mostrarMenu();
Pet criaPet();
void inserirPet(Fila *filaComum, Fila *filaEmergencial);
int geraIdUnico(Fila *f1, Fila *f2, Fila *f3);
int gerarID();
void registrarNoHistorico(Fila *historico, Pet p);
void atenderPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos);
Pet* buscarPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, char *termo, int buscarPorId);
void buscarPetInterface(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos);
void imprimeRelatorio(Fila *filaEmergencia, Fila *filaNormal);


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
                break;

            case 3:
                // Buscar por nome ou ID
                buscarPetInterface(filaEmergencia, filaNormal, filaAtendidos);
                break;

            case 4:
                // Imprimir relatório das filas
                imprimeRelatorio(filaEmergencia, filaNormal);
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
=======
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
>>>>>>> 91974166f806ec8b1e8fa9786b9fac5df1733398:clinicaVeterinaria.c


// --------------------------------------------------------
// Menu
// --------------------------------------------------------
<<<<<<< HEAD:clinica_veterinaria.c
int mostrarMenu() {

    int escolha;
=======
void mostrarMenu();
int numeroAleatorio();

int main(){

    mostrarMenu();


}

void mostrarMenu() {
>>>>>>> 91974166f806ec8b1e8fa9786b9fac5df1733398:clinicaVeterinaria.c
    printf("\n==============================================\n");
    printf("   CLINICA VETERINARIA - GERENCIAMENTO DE FILAS\n");
    printf("==============================================\n");
<<<<<<< HEAD:clinica_veterinaria.c
    printf("1) Inserir pet na fila\n");
    printf("2) Atender proximo pet\n");
    printf("3) Buscar pet por Nome/ID\n");
    printf("4) Imprimir relatorio das filas\n");
    printf("5) Mostrar proximo a ser atendido\n");
    printf("6) Listar pets ja atendidos\n");
=======
    printf("\t\t 1) Inserir pet na fila\n");
    printf("\t\t 2) Atender próximo pet\n");
    printf("\t\t 3) Buscar pet por Nome/ID\n");
    printf("\t\t 4) Imprimir relatório das filas\n");
    printf("\t\t 5) Mostrar próximo a ser atendido\n");
    printf("\t\t 6) Listar pets já atendidos\n");
>>>>>>> 91974166f806ec8b1e8fa9786b9fac5df1733398:clinicaVeterinaria.c
    printf("7) Finalizar\n");
    printf("----------------------------------------------\n");

    printf("Escolha: ");
    fflush(stdout);
    scanf("%d", &escolha);
    getchar(); // consome o '\n' deixado no buffer
    return escolha;
}
// ----------------------------------------------------------------



//===============================================
//Funções principais
//===============================================


//Gera um novo id que ainda nao foi utilizado
int gerarID(){
    int id = rand() % 900 + 100; // 100 a 999
    return id;
}
// ----------------------------------------------------------------

<<<<<<< HEAD:clinica_veterinaria.c
int geraIdUnico(Fila *f1, Fila *f2, Fila *f3) {
    int id;
    int unico;
    Nos *q;

    do {
        unico = 1; // Assume que o ID é único
        id = gerarID();

        // Verifica na fila 1
        for (q = f1->inicio; q != NULL; q = q->prox) {
            if (q->info.id == id) {
                unico = 0; // ID já existe
                break;
            }
        }

        // Verifica na fila 2 se ainda é único
        if (unico) {
            for (q = f2->inicio; q != NULL; q = q->prox) {
                if (q->info.id == id) {
                    unico = 0; // ID já existe
                    break;
                }
            }
        }

        // Verifica na fila 3 se ainda é único
        if (unico) {
            for (q = f3->inicio; q != NULL; q = q->prox) {
                if (q->info.id == id) {
                    unico = 0; // ID já existe
                    break;
                }
            }
        }

    } while (!unico); // Repete até encontrar um ID único

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

void inserirPet(Fila *filaComum, Fila *filaEmergencial){

    //cria o pet
    Pet novoPet = criaPet();

    //insere o pet na fila
    if (novoPet.prioridade == 0){
        InsereFila(filaEmergencial, novoPet); // Insere na fila emergencial
    } else{
        InsereFila(filaComum, novoPet); // Insere na fila normal
    }
}

//=================================================================

//TODO verificar se os pets já atendidos sairam da fila de espera de seu respectivo tipo
void atenderPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos) {
    Pet petAtendido;
    
    // Verifica se há pets na fila de emergência primeiro
    if (!VaziaFila(filaEmergencia)) {
        petAtendido = RetiraFila(filaEmergencia);
        printf("\n=== ATENDENDO PET DE EMERGENCIA ===\n");
    } 
    // Se não há emergência, verifica fila normal
    else if (!VaziaFila(filaNormal)) {
        petAtendido = RetiraFila(filaNormal);
        printf("\n=== ATENDENDO PET NORMAL ===\n");
    } 
    // Se ambas estão vazias
    else {
        printf("\nNao ha pets aguardando atendimento!\n");
        return;
    }
    
    // Marca o pet como atendido
    petAtendido.atendido = 1;
    
    // Adiciona à fila de atendidos
    InsereFila(filaAtendidos, petAtendido);
    
    // Mostra informações do pet atendido
    printf("Pet atendido com sucesso!\n");
    printf("ID: %d | Nome: %s | Especie: %s\n", 
           petAtendido.id, petAtendido.nome, petAtendido.especie);
    printf("Prioridade: %s\n", (petAtendido.prioridade == 0 ? "Emergencial" : "Normal"));
}

//= ================================================
//TODO talvez fazer um switch case para escolher se quer buscar por nome ou id 
Pet* buscarPet(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos, char *termo, int buscarPorId) {
    Nos *q;
    
    // Buscar na fila de emergência
    for (q = filaEmergencia->inicio; q != NULL; q = q->prox) {
        if (buscarPorId) {
            int id = atoi(termo);
            if (q->info.id == id) {
                printf("\n=== PET ENCONTRADO NA FILA DE EMERGENCIA ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                        q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Emergencial\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

                return &(q->info);
            }
            // OBS: strstr faz a busca por substring assim se o nome for "deki" e buscar "dek" ele acha
        } else {
            if (strstr(q->info.nome, termo) != NULL) { 
                printf("\n=== PET ENCONTRADO NA FILA DE EMERGENCIA ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                       q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Emergencial\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);

                return &(q->info);
            }
        }
    }
    
    // Buscar na fila normal
    for (q = filaNormal->inicio; q != NULL; q = q->prox) {
        if (buscarPorId) {
            int id = atoi(termo);
            if (q->info.id == id) {
                printf("\n=== PET ENCONTRADO NA FILA NORMAL ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                       q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Normal\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                return &(q->info);
            }
        } else {
            if (strstr(q->info.nome, termo) != NULL) {
                printf("\n=== PET ENCONTRADO NA FILA NORMAL ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                       q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Prioridade: Normal\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                return &(q->info);
            }
        }
    }
    
    // Buscar na fila de atendidos
    for (q = filaAtendidos->inicio; q != NULL; q = q->prox) {
        if (buscarPorId) {
            int id = atoi(termo); //converte a string para int
            if (q->info.id == id) {
                printf("\n=== PET ENCONTRADO NA FILA DE ATENDIDOS ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                       q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Status: ATENDIDO\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                return &(q->info);
            }
        } else {
            if (strstr(q->info.nome, termo) != NULL) {
                printf("\n=== PET ENCONTRADO NA FILA DE ATENDIDOS ===\n");

                printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n",
                       q->info.id, q->info.nome, q->info.especie, q->info.idade);
                printf("Nascimento: %02d/%02d/%04d | Status: ATENDIDO\n",
                       q->info.nascimento.dia, q->info.nascimento.mes, q->info.nascimento.ano);
                return &(q->info);
            }
        }
    }
    
    printf("\nPet nao encontrado!\n");
    return NULL;
}

//= =============================================

void buscarPetInterface(Fila *filaEmergencia, Fila *filaNormal, Fila *filaAtendidos) {
    char termo[50];
    int opcao;
    
    printf("\nBuscar por:\n");
    printf("1) ID\n");
    printf("2) Nome\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            printf("Digite o ID: ");
            fgets(termo, sizeof(termo), stdin); //std
            termo[strcspn(termo, "\n")] = '\0'; //strcsonspn remove o \n do final da string, assim não precisa usar o getchar depois do fgets
            buscarPet(filaEmergencia, filaNormal, filaAtendidos, termo, 1);
            break;
        case 2:
            printf("Digite o nome (ou parte do nome): ");
            fgets(termo, sizeof(termo), stdin);
            termo[strcspn(termo, "\n")] = '\0';
            buscarPet(filaEmergencia, filaNormal, filaAtendidos, termo, 0);
            break;
        default:
            printf("Opcao invalida!\n");
            break;
    }
}



void imprimeRelatorio(Fila *filaEmergencia, Fila *filaNormal) {
    int countEmergencia = 0, countNormal = 0;
    Nos *q;
    
    // Conta pets na fila de emergência
    for (q = filaEmergencia->inicio; q != NULL; q = q->prox) {
        countEmergencia++;
    }
    
    // Conta pets na fila normal
    for (q = filaNormal->inicio; q != NULL; q = q->prox) {
        countNormal++;
    }
    
    printf("\n==============================================\n");
    printf("           RELATORIO DAS FILAS\n");
    printf("==============================================\n");
    printf("Pets na fila de EMERGENCIA: %d\n", countEmergencia);
    printf("Pets na fila NORMAL: %d\n", countNormal);
    printf("Total de pets aguardando: %d\n", countEmergencia + countNormal);
    printf("==============================================\n");
    
    if (countEmergencia > 0) {
        printf("\n--- FILA DE EMERGENCIA ---\n");
        imprimeFila(filaEmergencia);
    }
    
    if (countNormal > 0) {
        printf("\n--- FILA NORMAL ---\n");
        imprimeFila(filaNormal);
    }
    
    if (countEmergencia == 0 && countNormal == 0) {
        printf("\nNenhum pet aguardando atendimento.\n");
    }
}


/*void imprimirProximo(){

    IMPRIMIR O PRÓXIMO PET A SER ATENDIDO
}
*/

/*void imprimirAtendidos(){


=======
// Função para gerar um ID único entre 100 e 999
int numeroAleatorio() {
    return (rand() % 900) + 100;
>>>>>>> 91974166f806ec8b1e8fa9786b9fac5df1733398:clinicaVeterinaria.c
}
*/

